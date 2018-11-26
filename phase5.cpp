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

avm_memcell ax , bx , cx ;
avm_memcell retval ; 

void avm_error(string format){
	cout<<"Runtime Error: ----------> "<<format<<" at LINE: "<<currLine<<endl;
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
		memclear_func_t f = memclearFuncs[m->type];
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
	
	//cout<<"TO TOP EINAI                  "<<top<<endl;
	//assert(lv && ( &Stack[AVM_STACK_SIZE-1] >= lv && lv > &Stack[top] || lv==&retval));
	assert(lv && ( &Stack[AVM_STACK_SIZE-1] >= lv && lv > &Stack[0] || lv==&retval));

	assert(rv);
	
	avm_assign(lv,rv);
}

unsigned avm_get_envvalue(unsigned i){
	//assert(Stack[i].type == number_m);
	//cout<<"EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE sto i "<<i<<" "<<Stack[i].type <<endl;
	unsigned val = (unsigned) Stack[i].data.numVal;
	assert(Stack[i].data.numVal == (double) val);
	return val;
}

avm_table* avm_tablenew(){
	avm_table* table=new avm_table();
	table->refCounter=0;
	table->total=0;
}

void execute_newtable (instruction* instr){
	avm_memcell* lv = avm_translate_operand(&instr->result, (avm_memcell*) 0);
	assert(lv && (&Stack[AVM_STACK_SIZE-1] >= lv && lv > &Stack[0] || lv==&retval));
	
	avm_memcellclear(lv);
	
	lv->type = table_m;
	lv->data.tableVal = avm_tablenew();
	avm_tableincrefcounter(lv->data.tableVal);
} 

unsigned hashFunction(avm_memcell* t){
	unsigned hashRet=0;
	if(t->type==number_m)	hashRet=(int)t->data.numVal%AVM_TABLE_HASHSIZE;
	else if(t->type==string_m){
		const char* carray;
		carray=t->data.strVal->c_str();
		int sum=0;
		for(int i=0;i<t->data.strVal->length();i++){
			sum+=carray[i];
		}
		hashRet=sum%AVM_TABLE_HASHSIZE;
	}
	else{
		avm_error("(hashfunction)Unsupported table key(Tables,User functions and Library functions are not supported in Alpha Programming language)");
		executionFinished=1;
	}
	return hashRet;
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

void avm_tablesetelem(avm_table* table,avm_memcell* index,avm_memcell* c){
	unsigned hash=hashFunction(index);
	avm_table_bucket* tmp;
	avm_table_bucket* n=new avm_table_bucket();
	//cout<<"Type of index is:"<<index->type<<endl;
	switch(index->type){
		//numIndexed Table
		case number_m:
			for(tmp=table->numIndexed[hash];tmp!=NULL;tmp=tmp->next){
				if(tmp->key.data.numVal==index->data.numVal){
					//Vrhkame to tableBucket
					avm_assign(&tmp->value,c);
					return;
				}
			}
			table->total++;
			
			avm_assign(&n->key,index);
			avm_assign(&n->value,c);
			n->next=table->numIndexed[hash];
			table->numIndexed[hash]=n;
			break;
		//strIndexed table
		case string_m:
			for(tmp=table->strIndexed[hash];tmp!=NULL;tmp=tmp->next){
				if(tmp->key.data.strVal==index->data.strVal){
					//Vrhkame to tableBucket
					avm_assign(&tmp->value,c);
					return;
				}
			}
			table->total++;

			avm_assign(&n->key,index);
			avm_assign(&n->value,c);
			n->next=table->strIndexed[hash];
			table->strIndexed[hash]=n;
			break;
		default:
			avm_error("(tablesetelem)Unsupported table key(Tables,User functions and Library functions are not supported in Alpha Programming language)");
	}
}

void execute_tablesetelem(instruction* instr){
	avm_memcell* t = avm_translate_operand(&instr->arg1, (avm_memcell*)0);
	avm_memcell* i = avm_translate_operand(&instr->arg2, &ax);
	avm_memcell* c = avm_translate_operand(&instr->result, &bx);
	
	assert(t && &Stack[AVM_STACK_SIZE-1] >= t && t > &Stack[0]);
	assert(i && c);
	
	if(t->type != table_m){
		string msg="Illegal use of type"+ typeStrings[t->type] +"as table!";
		/*
		char msg[100];
		strcpy(msg,typeStrings[t->type].c_str()); */
		avm_error(msg);
	}else
		avm_tablesetelem(t->data.tableVal, i, c);
}

avm_memcell* avm_tablegetelem(avm_table* table,avm_memcell* index){
	unsigned hash=hashFunction(index);
	avm_table_bucket* tmp;
	//cout<<"Type of index in getelem is:"<<index->type<<endl;
	switch(index->type){
		//numIndexed Table
		case number_m:
			for(tmp=table->numIndexed[hash];tmp!=NULL;tmp=tmp->next){
				if(tmp->key.data.numVal==index->data.numVal){
					//Vrhkame to tableBucket
					return &tmp->value;
				}
			}
			break;
		//strIndexed table
		case string_m:
			for(tmp=table->strIndexed[hash];tmp!=NULL;tmp=tmp->next){
				if(tmp->key.data.strVal==index->data.strVal){
					//Vrhkame to tableBucket
					return &tmp->value;
				}
			}
			break;
		default:
			return NULL;
			avm_error("(tablegetelem)Unsupported table key(Tables,User functions and Library functions are not supported in Alpha Programming language)");
	}
}

void execute_tablegetelem(instruction* instr){

	avm_memcell* lv =  avm_translate_operand(&instr->result, (avm_memcell*)0);
	avm_memcell* t = avm_translate_operand(&instr->arg1, (avm_memcell*)0);
	avm_memcell* i = avm_translate_operand(&instr->arg2, &ax);
	
	assert(lv && &Stack[N-1] >= lv && lv> &Stack[top] || lv == &retval);
	assert (t && &Stack[N-1] >= t && t > &Stack[top]);
	assert(i);
	
	avm_memcellclear(lv);
	lv->type = nil_m;
	
	if( t->type != table_m){
		string msg="illegal use of type"+ typeStrings[t->type]+"as table!!!";
		avm_error(msg);
	}
	else{
		avm_memcell* content = avm_tablegetelem(t->data.tableVal, i);
		if(content)
			avm_assign(lv, content);
		/*else{
			string ts = avm_tostring(t);
			string is = avm_tostring(i);
			avm_warning("%s[%s] not found!", ts , is);
			free(ts);
			free(is);
		}*/
	}
}

userfunc* avm_getfuncinfo(unsigned address){
	return userFuncs[address];
}

void execute_funcenter ( instruction * instr){
	//cout<<"MPHKA FUNCENTER!! \n";
	avm_memcell* func=avm_translate_operand(&instr->result,&cx);
	assert(func);
	//assert(pc==func->data.funcVal);

	totalActuals=0;
	userfunc* funcInfo =avm_getfuncinfo(func->data.funcVal);

	//cout<<"PAY ATTENTION HERE:"<<funcInfo->id<<endl;
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

	//assert(lv && ( &Stack[AVM_STACK_SIZE-1] >= lv && lv > &Stack[top] || lv==&retval));
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


string number_tostring(avm_memcell* v);

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
 	string s="[ ";
 	if(v->type==table_m){
 		avm_table_bucket *tmp,*tmp2;
 		int i=0;
 		for(tmp=v->data.tableVal->strIndexed[i];i<AVM_TABLE_HASHSIZE;tmp=v->data.tableVal->strIndexed[++i]){
 			for(tmp2=tmp;tmp2!=NULL;tmp2=tmp2->next){
 				s+="{";
 				s+=string_tostring(&tmp2->key);
 				s+=" : ";
 				s+=avm_tostring(&tmp2->value)+"}\n";
 			}
 		}

 		for(i=0,tmp=v->data.tableVal->numIndexed[i];i<AVM_TABLE_HASHSIZE;tmp=v->data.tableVal->numIndexed[++i]){
 			for(tmp2=tmp;tmp2!=NULL;tmp2=tmp2->next){
 				s+="{";
 				s+=number_tostring(&tmp2->key);
 				s+=" : ";
 				s+=avm_tostring(&tmp2->value);
 				s+="}\n";
 			}
 		}
 		s+="]\n";
 	}else{
 		avm_error("No table or unsupported type to print");

 	}
 	return s;
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
	avm_push_envvalue(top+totalActuals+2);
	avm_push_envvalue(topsp);
	/*avm_push_envvalue(totalActuals);
	avm_push_envvalue(pc+1);
	avm_push_envvalue(top +totalActuals +2);
	avm_push_envvalue(topsp);*/
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

void avm_calllibfunc(string id){
	
	library_func_t f=avm_getlibraryfunc(id);
	if(!f){
		avm_error("unsupported library function "+ id +" called!! ");
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
			//pc = func->data.funcVal= ;
			pc = userFuncs[func->data.funcVal]->address;

			//cout<<"Feugw apo call!!!\n";
			assert(pc < AVM_ENDING_PC);
			assert(instructions[pc]->opcode == funcenter_v);
			break;
		}
		
		case string_m: avm_calllibfunc(*func->data.strVal); break;
		case libfunc_m: avm_calllibfunc(*func->data.libfuncVal); break;
		
		default:{
			string s = avm_tostring(func);
			avm_error("call: cannot bind "+ s+" to function");
			//free(s);
			executionFinished = 1;
		}
	}
}

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
	
	if(rv1->type == undef_m || rv2->type == undef_m ){
		avm_error("'undef' involved in equality!");
		executionFinished=1;
	}
	else if(rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type == nil_m && rv2->type == nil_m;
	else if(rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	else if(rv1->type != rv2->type){
		avm_error(typeStrings[rv1->type]+"=="+typeStrings[rv2->type] +"is illegal!!!");
		executionFinished=1;
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
		executionFinished=1;
	}
	else if(rv1->type == nil_m || rv2->type == nil_m)
		result = !(rv1->type == nil_m && rv2->type == nil_m);
	else if(rv1->type == bool_m || rv2->type == bool_m)
		result = !(avm_tobool(rv1) == avm_tobool(rv2));
	else if(rv1->type != rv2->type){
		avm_error(typeStrings[rv1->type]+"=="+typeStrings[rv2->type] +"is illegal!!!");
		executionFinished=1;
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
		executionFinished=1;
	}
	else if(rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type == nil_m && rv2->type == nil_m;
	else if(rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	else if(rv1->type != rv2->type){
		avm_error(typeStrings[rv1->type]+"=="+typeStrings[rv2->type] +"is illegal!!!");
		executionFinished=1;
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
		executionFinished=1;
	}
	else if(rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type == nil_m && rv2->type == nil_m;
	else if(rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) == avm_tobool(rv2));
	else if(rv1->type != rv2->type){
		avm_error(typeStrings[rv1->type]+"=="+typeStrings[rv2->type] +"is illegal!!!");
		executionFinished=1;
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
		executionFinished=1;
	}
	else if(rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type == nil_m && rv2->type == nil_m;
	else if(rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) < avm_tobool(rv2));
	else if(rv1->type != rv2->type){
		avm_error(typeStrings[rv1->type]+"=="+typeStrings[rv2->type] +"is illegal!!!");
		executionFinished=1;
		
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
		executionFinished=1;
	}
	else if(rv1->type == nil_m || rv2->type == nil_m)
		result = rv1->type == nil_m && rv2->type == nil_m;
	else if(rv1->type == bool_m || rv2->type == bool_m)
		result = (avm_tobool(rv1) > avm_tobool(rv2));
	else if(rv1->type != rv2->type){
		avm_error(typeStrings[rv1->type]+"=="+typeStrings[rv2->type] +"is illegal!!!");
		executionFinished=1;
	}
	else{
		//DISPATCHING ME VASH TO TYPO TOU rv1
		result=avm_jgt(rv1,rv2);
	}
	
	if(!executionFinished && result)
		pc = instr->result.val;
}

void execute_nop(instruction* instr){}

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
			executionFinished=1;
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


void libfunc_typeof(){
	unsigned n=avm_totalactuals();
	if(n!=1)
		avm_error("one argument expected instead of:"+std::to_string(n));
	else{
		avm_memcellclear(&retval);
		retval.type=string_m;

		string* tmp=new string(typeStrings[avm_getactual(0)->type]);
		retval.data.strVal=tmp;
	}
}

void libfunc_sqrt(){
	unsigned n=avm_totalactuals();
	if(n!=1)
		avm_error(" SQRT: one argument expected instead of:"+std::to_string(n));
	else{
		avm_memcellclear(&retval);
		retval.type=number_m;
		
		double tmp = avm_getactual(0)->data.numVal;
	
		if(tmp<=0  || avm_getactual(0)->type!=0 ){
			//avm_error(" invalid input in SQRT function ");
			retval.type = nil_m;
			string *lola = new string("nil");
			retval.data.strVal=lola;			
		}
		else {
			tmp = sqrt(tmp);
			retval.data.numVal   = tmp;
		}
	}
}

void libfunc_cos(){
	unsigned n=avm_totalactuals();
	if(n!=1)
		avm_error(" COS: one argument expected instead of:"+std::to_string(n));
		else{
		avm_memcellclear(&retval);
		retval.type=number_m;
		
		double tmp = avm_getactual(0)->data.numVal;
		
		if(tmp<=0  || avm_getactual(0)->type!=0 ){
			avm_error(" invalid input in COS function ");
		}
		else 
			tmp *=  (3.14159265/180);
			tmp = cos(tmp);

		retval.data.numVal   = tmp;
	}
}

void libfunc_sin(){
	unsigned n=avm_totalactuals();
	if(n!=1)
		avm_error(" SIN: one argument expected instead of:"+std::to_string(n));
		else{
		avm_memcellclear(&retval);
		retval.type=number_m;
		
		double tmp = avm_getactual(0)->data.numVal;
		
		if(tmp<=0  || avm_getactual(0)->type!=0 ){
			avm_error(" invalid input in SIN function ");
		}
		else 
			tmp *=  (3.14159265/180);
			tmp = sin(tmp);

		retval.data.numVal   = tmp;
	}
}

bool is_double(string s)
{
    char* endptr = 0;
    strtod(s.c_str(), &endptr);

    if(*endptr != '\0' || endptr == s)
        return false;
    return true;
}

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void libfunc_input(){
	string str;
	bool done=false;	
	unsigned n=avm_totalactuals();
	if(n!=0)
		avm_error("LIB FUNC INPUT: den dexetai argument ");

	avm_memcellclear(&retval);
	cin>>str;

	if(str=="nil"){
		retval.type=nil_m;
		string *lola = new string("nil");
		retval.data.strVal = lola;
	}
	else if(str=="true"){
		retval.type=bool_m;
		retval.data.boolVal = true;
	}
	else if(str=="false"){
		retval.type=bool_m;
		retval.data.boolVal = false;
	}		
	else if(is_number(str) || is_double(str)){
		retval.type=number_m;
		retval.data.numVal = std::stod(str);
	}
	else{
		string *lola = new string(str);
		retval.type=string_m;
		retval.data.strVal =lola;
	}	

}

void libfunc_strtonum(){

	unsigned n=avm_totalactuals();
	if(n!=1)
		avm_error(" STRTONUM: one argument expected instead of:"+std::to_string(n));
		
	else{
			avm_memcellclear(&retval);
			retval.type=string_m;

		if( avm_getactual(0)->type!=string_m ){
				avm_error(" invalid input in strtonum function(string only) ");
				retval.type = nil_m;
				string *lola = new string("nil");
				retval.data.strVal=lola;
		}

		else if(avm_getactual(0)->type==string_m){

			string s = avm_tostring(avm_getactual(0));	

			if(is_number(s) || is_double(s) ){
				retval.type=number_m;
				retval.data.numVal=atof(s.c_str());
			}

			else{
				retval.type = nil_m;
				string *lola = new string("nil");
				retval.data.strVal=lola;
			}			
		}
	}
}

void libfunc_totalarguments(){
	
	unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);
	
	if(!p_topsp){
		avm_error(" 'totalarguments' called outside a function! ");
		retval.type =nil_m;
	}
	else{
		retval.type = number_m;
		retval.data.numVal = avm_get_envvalue(p_topsp +AVM_NUMACTUALS_OFFSET);
	}
}

const char* number_tostring(avm_memcell* v){
 	return std::to_string(v->data.numVal);
}

void libfunc_print(){
	unsigned n = avm_totalactuals();
	for(unsigned i = 0; i < n; ++i){
		string s = avm_tostring(avm_getactual(i));
		/*if(is_number(s) || is_double(s)){
				cout<<s[0]<<s[1]<<s[2]<<s[3]<<endl;
		}
		else{	
		cout<<s<<endl;
		//free(s);
		}*/
		cout<<s<<endl;
	}
}

void libfunc_argument(){
		
	unsigned p_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
	avm_memcellclear(&retval);

	unsigned n=avm_totalactuals();
	if(n!=1)
		avm_error("LIB FUNC ARGUMENT: one argument expected instead of: "+std::to_string(n));

	int totalarg =  avm_get_envvalue(p_topsp +AVM_NUMACTUALS_OFFSET);
	
	retval.type=number_m;
	
	if(!p_topsp){
		avm_error(" LibFunction'argument' called outside a function! ");
		retval.type =nil_m;
	}
			if( (avm_getactual(0)->data.numVal) > totalarg  || avm_getactual(0)->type!=0 ){
			avm_error(" invalid input in argument function ");
		}

	else{

		for(int i=0;i<totalarg;i++){
			if(i == avm_getactual(0)->data.numVal){
				retval.type=number_m;
				retval.data.numVal = avm_get_envvalue(p_topsp +AVM_NUMACTUALS_OFFSET + (i+1) );		
			}
		}
	}
}

void libfunc_tablelength(){
	unsigned n=avm_totalactuals();
	if(n!=1){
		avm_error("In library function tablelength(): one argument expected instead of:"+std::to_string(n));
	}else{
		avm_memcell* cell=avm_getactual(0);
		if(cell->type!=table_m){
			string msg("In library function tablelength(): Parameter"+avm_tostring(cell) +"is not a table value");
			avm_error(msg);
		}else{
			avm_memcellclear(&retval);
			avm_table* tmp=cell->data.tableVal;
			retval.type=number_m;
			retval.data.numVal=tmp->total;
		}
	}
}
//void avm_tablesetelem(avm_table* table,avm_memcell* index,avm_memcell* c)
void libfunc_tableindices(){
	unsigned n=avm_totalactuals();
	if(n!=1){
		avm_error("In library function tableindices():one argument expected instead of:"+std::to_string(n));
	}else{
		avm_memcell* cell=avm_getactual(0);
		if(cell->type!=table_m){
			string msg("In library function tableindices(): Parameter"+avm_tostring(cell) +"is not a table value");
			avm_error(msg);
		}else{
			avm_memcellclear(&retval);
			avm_table* table=cell->data.tableVal;
			avm_table_bucket *tmp,*tmp2;
	 		int i=0;
	 		retval.type=table_m;
	 		avm_table* indices=avm_tablenew();
	 		int index=0;
	 		avm_memcell* tempcell=new avm_memcell();
	 		tempcell->type=number_m;
	 		tempcell->data.numVal=index;
	 		for(tmp=cell->data.tableVal->strIndexed[i];i<AVM_TABLE_HASHSIZE;tmp=cell->data.tableVal->strIndexed[++i]){
	 			for(tmp2=tmp;tmp2!=NULL;tmp2=tmp2->next){
	 				avm_tablesetelem(indices,tempcell,&tmp2->key);
	 				tempcell->data.numVal=++index;
	 			}
	 		}
	 		i=0;
	 		for(tmp=cell->data.tableVal->numIndexed[i];i<AVM_TABLE_HASHSIZE;tmp=cell->data.tableVal->numIndexed[++i]){
	 			for(tmp2=tmp;tmp2!=NULL;tmp2=tmp2->next){
	 				avm_tablesetelem(indices,tempcell,&tmp2->key);	
	 				tempcell->data.numVal=++index;
	 			}
	 		}
	 		retval.data.tableVal=indices;
		}
	}
}
void libfunc_tablecopy(){
	unsigned n=avm_totalactuals();
	if(n!=1){
		avm_error("In library function tablecopy():one argument expected instead of:"+std::to_string(n));
	}else{
		avm_memcell* cell=avm_getactual(0);
		if(cell->type!=table_m){
			string msg("In library function tableindices(): Parameter"+avm_tostring(cell) +"is not a table value");
			avm_error(msg);
		}else{
			avm_memcellclear(&retval);
			avm_table* table=cell->data.tableVal;
			avm_table_bucket *tmp,*tmp2;
	 		int i=0;
	 		retval.type=table_m;
	 		avm_table* copy=avm_tablenew();
	 		//int index=0;
	 		//avm_memcell* tempkey=new avm_memcell();
	 		//avm_memcell* tempvalue=new avm_memcell();
	 		//tempcell->type=number_m;
	 		//tempcell->data.numVal=index;
	 		for(tmp=cell->data.tableVal->strIndexed[i];i<AVM_TABLE_HASHSIZE;tmp=cell->data.tableVal->strIndexed[++i]){
	 			for(tmp2=tmp;tmp2!=NULL;tmp2=tmp2->next){
	 				//if(tmp)
	 				avm_tablesetelem(copy,&tmp2->key,&tmp2->value);
	 				
	 			}
	 		}
	 		i=0;
	 		for(tmp=cell->data.tableVal->numIndexed[i];i<AVM_TABLE_HASHSIZE;tmp=cell->data.tableVal->numIndexed[++i]){
	 			for(tmp2=tmp;tmp2!=NULL;tmp2=tmp2->next){
	 				avm_tablesetelem(copy,&tmp2->key,&tmp2->value);	
	 			}
	 		}
	 		retval.data.tableVal=copy;
		}

	}
}


library_func_t LibraryFuncs[]={
	libfunc_print,
	libfunc_typeof,
	libfunc_sqrt,
	libfunc_cos,
	libfunc_sin,
	libfunc_strtonum,
	libfunc_totalarguments,
	libfunc_argument,
	libfunc_input,
	libfunc_tablelength,
	libfunc_tableindices,
	libfunc_tablecopy	
};

string LibArray[]={
	"print",
	"typeof",
	"sqrt",
	"cos",
	"sin",
	"strtonum",
	"totalarguments",
	"argument",
	"input",
	"tablelength",
	"tableindices",
	"tablecopy"
};

library_func_t avm_getlibraryfunc(string id){
	//return libfunc_print;
	
	//library_func_t f;
	for(int i=0;i<13;i++){
		if(id==LibArray[i])	
			return LibraryFuncs[i];
	}
}

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

		fread(&line , 1 , sizeof(unsigned int) , fp) ; 
		snake->srcLine=line;
		fread(&type , 1 , sizeof(unsigned char) , fp);
		fread(&val , 1 , sizeof(unsigned) , fp) ; 
		

		snake->arg1.type=(vmarg_t)type;
		snake->arg1.val=val;
		
		

		fread(&type , 1 , sizeof(unsigned char) , fp);
		fread(&val , 1 , sizeof(unsigned) , fp) ; 
		
		snake->arg2.type=(vmarg_t)type;
		snake->arg2.val=val;		

		fread(&type , 1 , sizeof(unsigned char) , fp);
		fread(&val , 1 , sizeof(unsigned) , fp) ; 
		
		snake->result.type=(vmarg_t)type;
		snake->result.val=val;	
		
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

string getvmopcodeToString(int val){
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
				cout<<tmp<<endl; //print instruction opcode
				
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

void printuserfuncs(){
	auto it=userFuncs.begin();
	cout<<"*******PRINT USERFUNCS**********\n";
	for(;it!=userFuncs.end();it++){
		cout<<"ID:"<<(*it)->id<<" || address:"<<(*it)->address<<endl;
	}
}

int main(){

	ReadBinary();
	//code= instructions[0];
	avm_initStack();
	printInstructions();
	printuserfuncs();
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
