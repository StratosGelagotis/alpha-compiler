#include "phase5.hpp"

#define AVM_STACKENV_SIZE 4

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic
#define AVM_ENDING_PC codeSize

#define AVM_WIPEOUT(m) memset(&(m),0,sizeof(m))

bool executionFinished;
unsigned pc=0;
unsigned currLine = 0;
unsigned codeSize = 0;

unsigned top,topsp;

#define AVM_NUMACTUALS_OFFSET 4
#define AVM_SAVEDPC_OFFSET 3
#define AVM_SAVEDTOP_OFFSET 2
#define AVM_SAVEDTOPSP_OFFSET 1

#define AVM_STACK_SIZE 4096
#define N 4096

avm_memcell Stack[AVM_STACK_SIZE];

unsigned totalActuals = 0;

vector <instruction *> instructions;
vector <double> numConsts;
vector <string> stringConsts;
vector <string> namedLibfuncs;
vector <userfunc*> userFuncs;

static void avm_initStack(void){

 for(unsigned i=0; i<AVM_STACK_SIZE; ++i){
    AVM_WIPEOUT(Stack[i]);
    Stack[i].type = undef_m ;
 }
}

/*
extern char* number_tostring(avm_memcell* v);
extern char* string_tostring(avm_memcell* v);
extern char* bool_tostring(avm_memcell* v);
extern char* table_tostring(avm_memcell* v);
extern char* userfunc_tostring(avm_memcell* v);
extern char* libfunc_tostring(avm_memcell* v);
extern char* nil_tostring(avm_memcell* v);
extern char* undef_tostring(avm_memcell* v);
*/

void* avm_tablegetelem(avm_table* table, avm_memcell* index){
	return NULL;
}

avm_memcell ax , bx , cx ;
avm_memcell retval ; 

void avm_error(string format){
	cout<<"Runtime Error: ----------> "<<format<<" <--------- at line : "<<currLine<<endl;
	executionFinished=1;
}

string* consts_getstring (unsigned index){
	return &stringConsts[index];
}

string* libfuncs_getused (unsigned index){
	return &namedLibfuncs[index];
}

double consts_getnumber (unsigned index){
	return numConsts[index];
}

avm_memcell* avm_translate_operand (vmarg * arg, avm_memcell* reg){
	switch(arg->type){
		case global_a : return &Stack[AVM_STACK_SIZE-1-arg->val];
		case local_a : return &Stack[topsp-arg->val];
		case formal_a : return &Stack[topsp+AVM_STACKENV_SIZE+1+arg->val];
		case retval_a : return &retval;
		
		case number_a :{
			reg->type = number_m;
			reg->data.numVal = consts_getnumber(arg->val);
			return reg;
		}
		case string_a:{
			reg->type = string_m;
			reg->data.strVal = consts_getstring(arg->val);
			return reg;
		}
		case bool_a:{
			reg->type = bool_m;
			reg->data.boolVal = arg->val;
			return reg;
		}
		case nil_a:{
			reg->type = nil_m;
			return reg;
		}	
		case userfunc_a:{
			reg->type = userfunc_m;
			reg->data.funcVal = arg->val;
			return reg;
		}
		case libfunc_a:{
			reg->type = libfunc_m;
			reg->data.libfuncVal = libfuncs_getused(arg->val);
			return reg;
		}
	}
}

void avm_tablebucketsdestroy(avm_table_bucket** p){
 for(unsigned i=0; i<AVM_TABLE_HASHSIZE; ++i, ++p){
  	for(avm_table_bucket *b = *p; b;){
	   avm_table_bucket* del = b;
	   b = b->next;
	   avm_memcellclear(&del->key);
	   avm_memcellclear(&del->value);
	   free(del);
  }
  p[i] = (avm_table_bucket* )0;
 }
}

void avm_tabledestroy(avm_table* t){
 avm_tablebucketsdestroy(t->strIndexed);
 avm_tablebucketsdestroy(t->numIndexed);
 free(t);
}

void avm_tableincrefcounter(avm_table* t){
	++t->refCounter;
}

void avm_tabledecrefcounter (avm_table* t){
 assert(t->refCounter > 0);
 if(!--t->refCounter)
  avm_tabledestroy(t);
}

typedef void (*memclear_func_t)(avm_memcell*);

void memclear_string(avm_memcell* m){
	assert(m->data.strVal);
}

void memclear_table(avm_memcell* m){
	assert(m->data.tableVal);
	avm_tabledecrefcounter(m->data.tableVal);
}

memclear_func_t memclearFuncs[]={
	0,//number
	memclear_string,
	0,//bool
	memclear_string,
	0,//userfunc
	0,//libfunc
	0,//nil
	0//undef
};

void avm_memcellclear(avm_memcell* m){
	if(m->type != undef_m){
		memclear_func_t f=memclearFuncs[m->type];
		if(f)	
				(*f)(m);
		m->type=undef_m;
	}
}

void avm_assign (avm_memcell* lv, avm_memcell* rv){
	
	if(lv == rv) return;
	if(lv->type == table_m && rv->type == table_m && lv->data.tableVal == rv->data.tableVal) 
		return;
	//if(rv->type == undef_m)
	//	avm_warning("assigning from 'undef' content!");
	
	avm_memcellclear(lv);
	
	memcpy(lv, rv, sizeof(avm_memcell));
	
	if(lv->type == string_m)
		lv->data.strVal = rv->data.strVal;
	else if(lv->type == table_m)
		avm_tableincrefcounter(lv->data.tableVal);
}

void execute_assign (instruction* instr){
	
	avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*)0);
	avm_memcell* rv = avm_translate_operand(&instr->arg1,&ax);
	
	assert(lv && ( &Stack[AVM_STACK_SIZE-1] >= lv && lv > &Stack[top] || lv==&retval));
	assert(rv);
	
	avm_assign(lv,rv);
}

unsigned avm_get_envvalue(unsigned i){
	assert(Stack[i].type == number_m);
	unsigned val = (unsigned) Stack[i].data.numVal;
	assert(Stack[i].data.numVal == (double) val);
	return val;
}

void execute_newtable (instruction* instr){
	avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*) 0);
	assert(lv && (&Stack[N-1] >= lv && lv > &Stack[top] || lv==&retval));
	
	avm_memcellclear(lv);
	
	lv->type = table_m;
	//lv->data.tableVal = avm_tablenew();
	avm_tableincrefcounter(lv->data.tableVal);
}

void execute_tablesetelem(instruction* instr){
/*	avm_memcell* t = avm_translate_operand(&instr->result, (avm_memcell*)0);
	avm_memcell* i = avm_translate_operand(&instr->arg1, &ax);
	avm_memcell* c = avm_translate_operand(&instr->arg2, &bx);
	
	assert(t && &Stack[N-1] >= t && t > &Stack[top]);
	assert(i && c);
	
	if(t->type != table_m)
		avm_error("illegal use of type %s as table!", typeStrings[t->type]);
	else
		avm_tablesetelem(t->data.tableVal, i, c);
*/}

void execute_tablegetelem(instruction* instr){
/*	
	avm_memcell* lv =  avm_translate_operand(&instr->result, (avm_memcell*)0);
	avm_memcell* t = avm_translate_operand(&instr->arg1, (avm_memcell*)0);
	avm_memcell* i = avm_translate_operand(&instr->arg2, &ax);
	
	assert(lv && &Stack[N-1] >= lv && lv> &Stack[top] || lv == &retval);
	assert (t && &Stack[N-1] >= t && t > &Stack[top]);
	assert(i);
	
	avm_memcellclear(lv);
	lv->type = nil_m;
	
	if( t->type != table_m){
		avm_error("illegal use of type %s as table!", typeStrings[t->type]);
	}
	else{
		avm_memcell* content = avm_tablegetelem(t->data.tableVal, i);
		if(content)
			avm_assign(lv, content);
		else{
			char* ts = avm_tostring(t);
			char* is = avm_tostring(i);
			avm_warning("%s[%s] not found!", ts , is);
			free(ts);
			free(is);
		}
	}
*/}
userfunc* avm_getfuncinfo(unsigned address){}

void execute_funcenter ( instruction * instr){
	avm_memcell* func=avm_translate_operand(&instr->result,&ax);
	assert(func);
	assert(pc=func->data.funcVal);

	totalActuals=0;
	userfunc* funcInfo=avm_getfuncinfo(pc);
	topsp=top;
	top=top-(funcInfo->localsize);
}

void execute_funcexit ( instruction * unused){
	unsigned oldTop = top;
	top = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
	pc = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
	topsp =  avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

	while(oldTop++ <=top)
		avm_memcellclear( &Stack[oldTop]);
}	

typedef double (*arithmetic_func_t) (double x , double y);

double add_impl(double x , double y){return x+y;}
double sub_impl(double x, double y){return x-y;}
double mul_impl(double x, double y){return x*y;}

double div_impl(double x, double y){
	if(y!=0)
		return x/y;
	else
	 avm_error("div by 0");
	return 0.0000;
}

double mod_impl(double x , double y){
	if(y!=0)
		return ((unsigned)x % (unsigned)y);
	else
	 	avm_error("div by 0");
	return 0.0000;
}

arithmetic_func_t arithmeticFuncs[]={
	
	add_impl,
	sub_impl,
	mul_impl,
	div_impl,
	mod_impl
	
};

void execute_arithmetic(instruction * instr){
	avm_memcell* lv = avm_translate_operand(&instr->result , (avm_memcell*)0);
	avm_memcell* rv1 = avm_translate_operand(&instr->arg1 , &ax);
	avm_memcell* rv2 = avm_translate_operand(&instr->arg2 , &bx);

	assert(lv && ( &Stack[AVM_STACK_SIZE-1] >= lv && lv > &Stack[top] || lv==&retval));
	//assert( lv && (  (&Stack[AVM_STACK_SIZE-1] <= lv && &Stack[top] >lv) || lv==&retval) );
	//assert( lv && ( &Stack[0] <= lv && &Stack[top] >lv || lv==&retval) );
	assert(rv1 && rv2);

	if(rv1->type != number_m ||  rv2->type !=number_m){
		avm_error("not a number in arithmetic");
		executionFinished = true;
	}
	else{
		arithmetic_func_t op = arithmeticFuncs[instr->opcode - add_v];
		avm_memcellclear(lv);
		lv->type = number_m;
		lv->data.numVal = (*op)(rv1->data.numVal , rv2->data.numVal);
	}
}

typedef string (*tostring_func_t)(avm_memcell*);

 string number_tostring(avm_memcell* v){
 	return std::to_string(v->data.numVal);
}

 string string_tostring(avm_memcell* v){
 	string lola(*(v->data.strVal));
 	return lola;
 }

 string bool_tostring(avm_memcell* v){

 	if(v->data.boolVal==1)
 		return "true";
 	return "false";
 }

 string table_tostring(avm_memcell* v){
 	return "hashtable";
 }

 string userfunc_tostring(avm_memcell* v){
 	unsigned lola2 (v->data.funcVal) ;			// fvskvndiuvgzsgiusgrliudsrvusb
 		string lola = "Function " ; lola+=lola2;
 	return lola ;
 }
 
 string libfunc_tostring(avm_memcell* v){
 	string lola2(*(v->data.libfuncVal));
 	string lola = " Lib Function " +lola2;

 	return lola;
 }

 string nil_tostring(avm_memcell* v){
 	return "nil";
 }
 
 string undef_tostring(avm_memcell* v){
 	return "Undefined";
 }

tostring_func_t tostringFuncs[]={
	number_tostring,
	string_tostring,
	bool_tostring,
	table_tostring,
	userfunc_tostring,
	libfunc_tostring,
	nil_tostring,
	undef_tostring
};

string avm_tostring(avm_memcell* m){
	assert(m->type >= 0 && m->type <= undef_m);
	return ( *tostringFuncs[m->type])(m);
}

unsigned avm_totalactuals(){
	return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

typedef bool (*tobool_func_t)(avm_memcell* m);

bool number_tobool(avm_memcell* m) { return m->data.numVal != 0;}
bool string_tobool(avm_memcell* m) { return m->data.strVal->length() != 0;}
bool bool_tobool(avm_memcell* m) { return m->data.boolVal;}
bool table_tobool(avm_memcell* m) { return 1;}
bool userfunc_tobool(avm_memcell* m) { return 1;}
bool libfunc_tobool(avm_memcell* m) { return 1;}
bool nil_tobool(avm_memcell* m) { return 0;}
bool undef_tobool(avm_memcell* m) {assert(0); return 0;}

tobool_func_t toboolFuncs[]={
	number_tobool,
	string_tobool,
	bool_tobool,
	table_tobool,
	userfunc_tobool,
	libfunc_tobool,
	nil_tobool,
	undef_tobool
};

bool avm_tobool( avm_memcell* m){
	assert(m->type >= 0 && m->type < undef_m);
	return (*toboolFuncs[m->type])(m);
}

void avm_dec_top(){
	if(!top) {
		avm_error("Stack overflow");
		executionFinished = 1;		
	}
	else --top;
}

void avm_push_envvalue(unsigned value){
	Stack[top].type = number_m;
	Stack[top].data.numVal = value;
	avm_dec_top();
}

void avm_callsaveenvironment(){
	
	avm_push_envvalue(totalActuals);
	avm_push_envvalue(pc+1);
	avm_push_envvalue(top +totalActuals +2);
	avm_push_envvalue(topsp);
}

avm_memcell* avm_getactual (unsigned i){
	assert(i< avm_totalactuals());
	return &Stack[topsp + AVM_STACKENV_SIZE + 1 + i];
}

void execute_pusharg(instruction* instr){
	avm_memcell* arg = avm_translate_operand(&instr->arg1, &ax);
	assert(arg);
	
	avm_assign(&Stack[top], arg);
	++totalActuals;
	avm_dec_top();
}

library_func_t avm_getlibraryfunc(string id);

/*
void execute_funcenter ( instruction * instr){
	avm_memcell* func=avm_translate_operand(&instr->result,&ax);
	assert(func);
	assert(pc=func->data.funcVal);

	totalActuals=0;
	userfunc* funcInfo=avm_getfuncinfo(pc);
	topsp=top;
	top=top-(funcInfo->localsize);
}
*/
void avm_calllibfunc(string id){
	library_func_t f=avm_getlibraryfunc(id);
	if(!f){
		avm_error("unsupported library faunction"+ id +"called!!");
		executionFinished=1;
	}else{
		topsp=top;
		//top--;
		totalActuals=0;

		(*f)();
		if(!executionFinished){
			execute_funcexit((instruction*)0);
		}
	}
}

void execute_call( instruction* instr){
	
	avm_memcell* func = avm_translate_operand(&instr->arg1, &ax);
	assert(func);
	avm_callsaveenvironment();
	
	switch(func->type){
		
		case userfunc_m:{
			pc = func->data.funcVal;
			assert(pc < AVM_ENDING_PC);
			assert(instructions[pc]->opcode == funcenter_v);
			break;
		}
		
		case string_m: avm_calllibfunc(*func->data.strVal); break;
		case libfunc_m: avm_calllibfunc(*func->data.libfuncVal); break;
		
		default:{
			//string s = avm_tostring(func);
			//avm_error("call: cannot bind '%s' to function", s);
			//free(s);
			executionFinished = 1;
		}
	}
}


const string typeStrings[]={
	"number",
	"string",
	"bool",
	"table",
	"userfunc",
	"libfunc",
	"nil",
	"undef"
};

void execute_uminus(instruction* instr){}
void execute_and(instruction* instr){}
void execute_or(instruction* instr){}
void execute_not(instruction* instr){}

typedef bool (*comp_func_t)(avm_memcell* rv1,avm_memcell* rv2);

bool avm_jeq(avm_memcell* lv,avm_memcell* rv){
	//Apo execute_jump{	pc=instr->result.val;}
	if(lv->type==number_m)	return lv->data.numVal == rv->data.numVal;
	else if(lv->type==string_m) return lv->data.strVal == rv->data.strVal;
	else return (toboolFuncs[lv->type])(lv) == (toboolFuncs[rv->type])(rv);
}

bool avm_jne(avm_memcell* lv,avm_memcell* rv){
	if(lv->type==number_m)	return lv->data.numVal != rv->data.numVal;
	else if(lv->type==string_m) return lv->data.strVal != rv->data.strVal;
	else return (toboolFuncs[lv->type])(lv) != (toboolFuncs[rv->type])(rv);
}

bool avm_jle(avm_memcell* lv,avm_memcell* rv){
	if(lv->type==number_m)	return lv->data.numVal <= rv->data.numVal;
	else if(lv->type==string_m) return lv->data.strVal <= rv->data.strVal;
	else return (toboolFuncs[lv->type])(lv) <= (toboolFuncs[rv->type])(rv);
}

bool avm_jge(avm_memcell* lv,avm_memcell* rv){
	if(lv->type==number_m)	return lv->data.numVal >= rv->data.numVal;
	else if(lv->type==string_m) return lv->data.strVal >= rv->data.strVal;
	else return (toboolFuncs[lv->type])(lv) >= (toboolFuncs[rv->type])(rv);
}

bool avm_jlt(avm_memcell* lv,avm_memcell* rv){
	if(lv->type==number_m)	return lv->data.numVal < rv->data.numVal;
	else if(lv->type==string_m) return lv->data.strVal < rv->data.strVal;
	else return (toboolFuncs[lv->type])(lv) < (toboolFuncs[rv->type])(rv);
}

bool avm_jgt(avm_memcell* lv,avm_memcell* rv){
	if(lv->type==number_m)	return lv->data.numVal > rv->data.numVal;
	else if(lv->type==string_m) return lv->data.strVal > rv->data.strVal;
	else return (toboolFuncs[lv->type])(lv) > (toboolFuncs[rv->type])(rv);
}

comp_func_t comparisonFuncs[]{
	avm_jeq,
	avm_jne,
	avm_jle,
	avm_jge,
	avm_jlt,
	avm_jgt
};

void execute_jeq(instruction* instr){
	
	assert(instr->result.type == label_a);
	
	avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);
	
	unsigned char result = 0;
	
	if(rv1->type == undef_m || rv2->type == undef_m){
		avm_error("'undef' involved in equality!");
	}
	else if(rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type == nil_m && rv2->type == nil_m;
	else if(rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	else if(rv1->type != rv2->type){
		avm_error(typeStrings[rv1->type]+"=="+typeStrings[rv2->type] +"is illegal!!!");
	}
	else{
		//DISPATCHING ME VASH TO TYPO TOU rv1
		result=avm_jeq(rv1,rv2);

	}
	
	if(!executionFinished && result)
		pc = instr->result.val;
}

void execute_jne(instruction* instr){

	assert(instr->result.type == label_a);
	
	avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);
	
	unsigned char result = 0;
	
	if(rv1->type == undef_m || rv2->type == undef_m){
		avm_error("'undef' involved in nequality!");
	}
	else if(rv1->type == nil_m || rv2->type == nil_m)
		result = !(rv1->type == nil_m && rv2->type == nil_m);
	else if(rv1->type == bool_m || rv2->type == bool_m)
		result = !(avm_tobool(rv1) == avm_tobool(rv2));
	else if(rv1->type != rv2->type){
		avm_error(typeStrings[rv1->type]+"=="+typeStrings[rv2->type] +"is illegal!!!");
	}
	else{
		//DISPATCHING ME VASH TO TYPO TOU rv1

		result=avm_jne(rv1,rv2);
	}
	
	if(!executionFinished && result)
		pc = instr->result.val;
}

void execute_jle(instruction* instr){
	assert(instr->result.type == label_a);
	
	avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);
	
	unsigned char result = 0;
	
	if(rv1->type == undef_m || rv2->type == undef_m){
		avm_error("'undef' involved in jump_less_equal!");
	}
	else if(rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type == nil_m && rv2->type == nil_m;
	else if(rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	else if(rv1->type != rv2->type){
		avm_error(typeStrings[rv1->type]+"=="+typeStrings[rv2->type] +"is illegal!!!");
	}
	else{
		//DISPATCHING ME VASH TO TYPO TOU rv1
		result=avm_jle(rv1,rv2);
	}
	
	if(!executionFinished && result)
		pc = instr->result.val;
}

void execute_jge(instruction* instr){
	assert(instr->result.type == label_a);
	
	avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);
	
	unsigned char result = 0;
	
	if(rv1->type == undef_m || rv2->type == undef_m){
		avm_error("'undef' involved in jump_less_equal!");
	}
	else if(rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type == nil_m && rv2->type == nil_m;
	else if(rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	else if(rv1->type != rv2->type){
		avm_error(typeStrings[rv1->type]+"=="+typeStrings[rv2->type] +"is illegal!!!");
	}
	else{
		//DISPATCHING ME VASH TO TYPO TOU rv1
		result=avm_jge(rv1,rv2);
	}
	
	if(!executionFinished && result)
		pc = instr->result.val;
}

void execute_jlt(instruction* instr){
	assert(instr->result.type == label_a);
	
	avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);
	
	unsigned char result = 0;
	
	if(rv1->type == undef_m || rv2->type == undef_m){
		avm_error("'undef' involved in jump_less_equal!");
	}
	else if(rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type == nil_m && rv2->type == nil_m;
	else if(rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) < avm_tobool(rv2));
	else if(rv1->type != rv2->type){
		avm_error(typeStrings[rv1->type]+"=="+typeStrings[rv2->type] +"is illegal!!!");
		
	}
	else{
		//DISPATCHING ME VASH TO TYPO TOU rv1
		result=avm_jlt(rv1,rv2);
	}
	
	if(!executionFinished && result)
		pc = instr->result.val;
}

void execute_jgt(instruction* instr){
	assert(instr->result.type == label_a);
	
	avm_memcell* rv1 = avm_translate_operand(&instr->arg1, &ax);
	avm_memcell* rv2 = avm_translate_operand(&instr->arg2, &bx);
	
	unsigned char result = 0;
	
	if(rv1->type == undef_m || rv2->type == undef_m){
		avm_error("'undef' involved in jump_less_equal!");
	}
	else if(rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type == nil_m && rv2->type == nil_m;
	else if(rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) > avm_tobool(rv2));
	else if(rv1->type != rv2->type){
		avm_error(typeStrings[rv1->type]+"=="+typeStrings[rv2->type] +"is illegal!!!");
	}
	else{
		//DISPATCHING ME VASH TO TYPO TOU rv1
		result=avm_jgt(rv1,rv2);
	}
	
	if(!executionFinished && result)
		pc = instr->result.val;
}

void execute_nop(instruction* instr){

}

void execute_jump(instruction* instr){
	pc=instr->result.val;
}
//dispatch gia comparison functions



execute_func_t executeFuncs[] = {
	execute_assign,
	execute_add,
	execute_sub,
	execute_mul,
	execute_div,
	execute_mod,
	execute_uminus,
	execute_and,
	execute_or,
	execute_not,
	execute_jeq,
	execute_jne,
	execute_jle,
	execute_jge,
	execute_jlt,
	execute_jgt,
	execute_call,
	execute_pusharg,
	execute_funcenter,
	execute_funcexit,
	execute_newtable,
	execute_tablegetelem,
	execute_tablesetelem,
	execute_nop,
	execute_jump
};

void execute_cycle(){
	if(executionFinished)
		return;
	else if(pc==AVM_ENDING_PC){
			executionFinished=true;
			return;
		}
	else{
		assert(pc < AVM_ENDING_PC);
		//instruction * instr = code + pc;
	   instruction * instr = instructions[pc]; 
	
		assert(instr->opcode >= 0 &&
			instr->opcode <= AVM_MAX_INSTRUCTIONS);
		if(instr->srcLine)
			currLine = instr->srcLine;
		unsigned oldPC = pc;
		(*executeFuncs[instr->opcode]) (instr);
		if(pc == oldPC)
			++pc;
	}
}

void libfunc_print(){
	unsigned n = avm_totalactuals();
	for(unsigned i = 0; i < n; ++i){
		string s = avm_tostring(avm_getactual(i));
		cout<<s<<endl;
		//free(s);
	}
}

void libfunc_typeof(){
	unsigned n=avm_totalactuals();
	if(n!=1)
		avm_error("one argument expected instead of:"+n);
	else{
		//avm_memcellclear(&retval);
		retval.type=string_m;
		/*
		EDW ISWS THELEI KAI STRDUP
		*/

		//ISWS XANETAI H DIEUTHYNSH!! CAUTION!!!!
		//string tmp(typeStrings[avm_getactual(0)->type]);
		string tmp("table");
		retval.data.strVal=&tmp;
	}
}

library_func_t LibraryFuncs[]={
	libfunc_print,
	libfunc_typeof
};

library_func_t avm_getlibraryfunc(string id){
	return libfunc_print;
}
            

/*
void libfunc_totalarguments(){
	
	unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);
	
	if(!p_topsp){
		avm_error("'totalarguments' called outside a function!");
		retval.type =nil_m;
	}
	else{
		retval.type = number_m;
		retval.data.numVal = avm_get_envvalue(p_topsp +AVM_NUMACTUALS_OFFSET);
	}
}
*/
void avm_registerlibfunc(string id, library_func_t addr){

}

void avm_initialize(){
	
	avm_initStack();
	//isws ftiaksete ena map me string -> function pointer
	//avm_registerlibfunc("print",libfunc_print);
	//avm_registerlibfunc("typeof",libfunc_typeof);
}

void ReadBinary(){

FILE *fp = fopen("test.bin","rb");

	if(!fp)
		cout<<"cannot open file"<<endl;

	unsigned m;

	fread(&m,1, sizeof(unsigned),fp);
	if(m!=340200501){
		cout<<"YOU HAVE BEEN HACKED "<<endl;
		exit(-1);
	}

	fread(&m ,1, sizeof(unsigned),fp);
	top = N-1-m;
	topsp = top;

	fread(&m ,1, sizeof(unsigned),fp);

	for(int i=0;i<m;i++){
		unsigned tmp ;
		fread(&tmp , 1 , sizeof(unsigned) ,fp );
		
		string s ;

		for(int j=0;j<tmp;j++){
			char c;
			fread(&c,1,sizeof(char) , fp  );
			s+=c;			
		}
		stringConsts.push_back(s);
	}

	unsigned len;
	fread(&len,1,sizeof(unsigned),fp);

	for(int i=0; i<len ; i++){
		double a ;
		fread( &a , 1 , sizeof(double) , fp); 
		numConsts.push_back(a);
	}

	fread(&len , 1 , sizeof(unsigned) , fp);

	for(int i=0;i<len;i++){
		unsigned add ;
		unsigned lsize ;
		
		fread(&add,1,sizeof(unsigned) , fp	);
		fread(&lsize , 1, sizeof(unsigned) , fp);

		unsigned del ;
		fread( &del , 1 , sizeof(unsigned) , fp);

		string s ;

		for(int j=0;j<del;j++){
			char c;
			fread(&c,1,sizeof(char) , fp  );
			s+=c;			
		}

		userfunc * u = new userfunc();
			u->address=add;
			u->localsize = lsize;
			u->id = s;	
			userFuncs.push_back(u);
	}	

	fread(&m ,1, sizeof(unsigned),fp);

		for(int i=0;i<m;i++){
			unsigned tmp ;
			fread(&tmp , 1 , sizeof(unsigned) ,fp );
			
			string s ;

			for(int j=0;j<tmp;j++){
				char c;
				fread(&c,1,sizeof(char) , fp  );
				s+=c;			
			}
			namedLibfuncs.push_back(s);
	}

	fread(&m, 1 , sizeof(unsigned) , fp); 

	for (int i = 0 ; i < m ; i++){

		instruction *snake = new instruction();

		vmopcode opcode ;

		fread( &opcode , 1 , sizeof(unsigned char) , fp);

		snake->opcode = opcode; 

		unsigned char type  ;
		unsigned val ;
		unsigned int line;

		fread(&type , 1 , sizeof(unsigned char) , fp);
		fread(&val , 1 , sizeof(unsigned) , fp) ; 
		fread(&line , 1 , sizeof(unsigned int) , fp) ; 

		snake->arg1.type=(vmarg_t)type;
		snake->arg1.val=val;
		snake->arg1.line=line;
		snake->srcLine=line;

		fread(&type , 1 , sizeof(unsigned char) , fp);
		fread(&val , 1 , sizeof(unsigned) , fp) ; 
		fread(&line , 1 , sizeof(unsigned int) , fp) ; 

		snake->arg2.type=(vmarg_t)type;
		snake->arg2.val=val;
		snake->arg1.line=line;
		snake->srcLine=line;

		fread(&type , 1 , sizeof(unsigned char) , fp);
		fread(&val , 1 , sizeof(unsigned) , fp) ; 
		fread(&line , 1 , sizeof(unsigned int) , fp) ; 

		snake->result.type=(vmarg_t)type;
		snake->result.val=val;	
		snake->result.line=line;
		snake->srcLine=line;
		instructions.push_back(snake);
	}
}

const char * vmarg_tStrings[]= {
	"label_a",
	"global_a",
	"formal_a",
	"local_a",
	"number_a",
	"string_a",
	"bool_a",
	"nil_a",
	"userfunc_a",
	"libfunc_a",
	"retval_a"
};

const char* getVmarg_tType(int val){
		return vmarg_tStrings[val];
}

const char* vmopcodeToString[]{
	"assign_v","add_v","sub_v","mul_v","div_v","mod_v",
	"uminus_v","and_v","or_v","not_v","jeq_v","jne_v",
	"jle_v","jge_v","jlt_v","jgt_v","call_v","pusharg_v",
	"funcenter_v","funcexit_v",
	"newtable_v","tablegetelem_v","tablesetelem_v",
	"nop_v","jump_v"
};

const char* getvmopcodeToString(int val){
	return vmopcodeToString[val];
}

void printInstructions(){
	cout<<"<===INSTRUCTIONS===>"<<endl;
	auto i=0;
	if(!instructions.empty()){
		for(auto it=instructions.begin();it!=instructions.end();it++){
			cout<<i++<<" || ";
				string tmp;
				tmp = getvmopcodeToString( (*it)->opcode );			
				cout<<tmp<<" || LINE: "<<(*it)->srcLine <<endl; //print instruction opcode
				
				if((*it)->arg1.type!=ignore_a){
				tmp = getVmarg_tType( (*it)->arg1.type);
				cout<<"ARG 1: "<<tmp<<" || "<<(*it)->arg1.val<<endl; //print vmarg type & value
				}

				if((*it)->arg2.type!=ignore_a){
				tmp = getVmarg_tType( (*it)->arg2.type);
				cout<<"ARG 2: "<<tmp <<" || "<<(*it)->arg2.val<<endl; //print vmarg type & value
				}

				if((*it)->result.type!=ignore_a){
				tmp = getVmarg_tType( (*it)->result.type);
				cout<<"RESULT: "<<tmp <<" || "<<(*it)->result.val<<endl;//print vmarg type & value
				}
		}
	}
	else
		cout<<"NO INSTRUCTIONS\n";
}

int main(){

	ReadBinary();
	//code= instructions[0];
	avm_initStack();
	printInstructions();

	codeSize = instructions.size();
	cout<<"**********************************************************\n";
	cout<<"**********************PROGRAM OUTPUT**********************\n";
	cout<<"**********************************************************\n";
	while(true){
		if(executionFinished){
			break;
		}else{
			execute_cycle();
		}
	}
}