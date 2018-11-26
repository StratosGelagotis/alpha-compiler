#include "phase4.hpp"
int iinstruction;
extern unsigned total; 
extern quad * quads;
extern unsigned int currQuad;

generator_func_t generators[] = {
	generate_ASSIGN,
	generate_MUL,
	generate_UMINUS, //
	generate_NOT,
	generate_IF_LESSEQ,
	generate_IF_GREATER,
	generate_RETURN,
	generate_FUNCEND,
	generate_TABLEGETELEM,
	generate_ADD,
	generate_DIV,
	generate_AND, //
	generate_IF_EQ,
	generate_IF_GREATEREQ,
	generate_CALL,
	generate_GETRETVAL,
	generate_NEWTABLE,
	generate_TABLESETELEM,
	generate_SUB,
	generate_MOD,
	generate_OR,
	generate_IF_NOTEQ,
	generate_IF_LESS,
	generate_PARAM,
	generate_FUNCSTART,
	generate_JUMP,
	generate_NOP
};

vector <instruction *> instructions;
list<incomplete_jump*> incomplete_jump_List;

unsigned int ij_jump = 0;

vector <double> numConsts;
unsigned totalNumConsts;
vector <string>	stringConsts;
unsigned totalStringConsts;
vector <string>	namedLibfuncs;
unsigned totalNamedLibfuncs;
vector <userfunc*>	userFuncs;
unsigned totalUserFuncs;

unsigned consts_newstring(string s){
	int i;
	unsigned index=-1;
	for(i=0;i<stringConsts.size();i++){
		if(s==stringConsts[i]){
			index=i;
			break;
		}
	}
	if(index==-1){
		stringConsts.push_back(s);
		index=stringConsts.size()-1;
	}
	return index;
}

unsigned consts_newnumber(double s){
	unsigned i=0;
	for(i=0;i<numConsts.size();i++){
		if(s==numConsts[i]){
			break;
		}
	}
	if(i==numConsts.size()){
		numConsts.push_back(s);
		i=numConsts.size()-1;
	}
	return i;
}

unsigned libfuncs_newused(string s){
	unsigned i=0;
	for(i=0;i<namedLibfuncs.size();i++){
		if(s==namedLibfuncs[i]){
			break;
		}
	}
	if(i==namedLibfuncs.size()){
		namedLibfuncs.push_back(s);
		i=namedLibfuncs.size()-1;
	}
	return i;
}

unsigned userfuncs_newfunc(SymbolTableEntry* s){
	int i;
	unsigned index=-1;
	
	for(i=0;i<userFuncs.size();i++){
		if(s->value.funcVal->name==userFuncs[i]->id){
			index=i;
			break;
		}
	}
	if(i==-1){
		userfunc* fu;
		fu->address=s->taddress;
		fu->id=s->value.funcVal->name;
		fu->localsize=s->totalLocals;
		userFuncs.push_back(fu);
		index=userFuncs.size()-1;
	}else index=i;
	return index;
}

/*
vector environment(vector<SymbolTableEntry*> * scopetable){
	vector<SymbolTableEntry*> mem;
	SymbolTableEntry* sym;
	int i;
	for(i=0;i<scopetable.size();i++){
		for(sym=scopetable[i];sym->nextscope!=NULL;sym=sym->nextscope){
			if(sym->symbol_t==var_s){
				s.push_back(sym);
			}
		}
	}
	return s;
}*/

void make_operand(expr* e,vmarg* arg){
	switch(e->type){
		case assignexpr_e:
		case var_e:
		case tableitem_e:
		case arithexpr_e:
		case boolexpr_e:
		case newtable_e:{
			assert(e->sym);
			arg->val=e->sym->offset;

			switch (e->sym->scopespace){
				case programvar: 	{arg->type=global_a; 	break;}
				case functionlocal: {arg->type=local_a; 	break;}
				case formalarg:		{arg->type=formal_a;	break;}
				default: assert(-1);
			}
			break;
		}
		case constbool_e:{
			arg->val=e->boolConst;
			arg->type=bool_a;
			break;
		}
		case constnum_e:{
			arg->val=consts_newnumber(e->numConst);
			arg->type=number_a;
			break;
		}
		case conststring_e:{
			arg->val=consts_newstring(e->strConst);
			arg->type=string_a;
			break;
		}
		case nil_e:{
			arg->type=nil_a;
			break;
		}
		case programfunc_e:{
			arg->type=userfunc_a;
			//arg->val=e->sym->taddress;
			arg->val=userfuncs_newfunc(e->sym);
			break;
		}
		case libraryfunc_e:{
			arg->type=libfunc_a;
			arg->val=libfuncs_newused(e->sym->value.funcVal->name);
			break;
		}
		default:{ 
			cout<<"EIMAI STO ASSERT"<<endl;
			assert(0);
		}
	}
}

void reset_operand(vmarg* arg){
	arg->type=ignore_a;
}

void patch_incomplete_jumps(){

for(auto it=incomplete_jump_List.begin();it!=incomplete_jump_List.end();it++){

		if((*it)->iaddress==currQuad)
				instructions[(*it)->instrNo]->result.val = instructions.size();

		else
				instructions[(*it)->instrNo]->result.val = quads[(*it)->iaddress].taddress;		
	}
}

void add_incomplete_jump(unsigned instrNo , unsigned iaddress){
	incomplete_jump *tmp  = new incomplete_jump();
	tmp->instrNo=instrNo;
	cout<<"INSTRNO IS:"<<instrNo<<endl;
	tmp->iaddress=iaddress;
	incomplete_jump_List.push_front(tmp);
 }

int nextinstructionlabel(){
	if(!instructions.empty())
		return instructions.size();
	return 0;
}

int currprocessedquad(){
	return iinstruction;
}

void make_numberoperand(vmarg* arg , double val){
	arg->val = consts_newnumber(val);
	arg->type = number_a;
}

void make_booloperand(vmarg* arg, unsigned val){
	arg->val = val;
	arg->type = bool_a;
}

void make_retvaloperand(vmarg* arg){
	arg->type = retval_a;
	//arg->val=nextinstructionlabel();
	arg->val=0;
}

void emit2(instruction t){

	instruction *tmp = new instruction();
	tmp->opcode=t.opcode;

	//tmp->result= new vmarg();
	tmp->result.type=t.result.type;
	tmp->result.val= t.result.val;

	//tmp->arg1=new vmarg();
	tmp->arg1.type=t.arg1.type;
	tmp->arg1.val=t.arg1.val;

//	tmp->arg2=new vmarg();
	tmp->arg2.type=t.arg2.type;
	tmp->arg2.val=t.arg2.val;

	tmp->srcLine=t.srcLine;

	instructions.push_back(tmp);
}

void generate_arithmetic(vmopcode op,quad *quad){

	instruction t;

	t.opcode=op;
	if(quad->arg1!=(expr*)0)	make_operand(quad->arg1 , &t.arg1);
	else{
		t.arg1.type=ignore_a;
	}
	//cout<<"++++++++++++++++ARG1 END+++++++++++++++"<<endl;
	if(quad->arg2!=(expr*)0)	make_operand(quad->arg2 , &t.arg2);
	else{
		t.arg2.type=ignore_a;
	}
	//cout<<"++++++++++++++++ARG2 END+++++++++++++++"<<endl;
	make_operand(quad->result , &t.result);
	quad->taddress = nextinstructionlabel();
	t.srcLine=quad->line;
	emit2(t);
}

void generate_relational(vmopcode op , quad * quad){
	instruction t;
	t.opcode= op ;
	if(quad->arg1!=(expr*)0)	make_operand(quad->arg1 , &t.arg1);
	else{
		t.arg1.type=ignore_a;
	}
	if(quad->arg2!=(expr*)0)	make_operand(quad->arg2 , &t.arg2);
	else{
		t.arg2.type=ignore_a;
	}

	t.result.type = label_a;
	if(quad->label <  currprocessedquad() ){
		t.result.val = quads[quad->label].taddress;
	}
	else{
		add_incomplete_jump(nextinstructionlabel() , quad->label);
	}
	quad->taddress = nextinstructionlabel();
	t.srcLine=quad->line;
	emit2(t);
}

void generate_ADD(quad* q){generate_arithmetic(add_v,q);}
void generate_SUB(quad* q){generate_arithmetic(sub_v,q);}
void generate_MUL(quad* q){generate_arithmetic(mul_v,q);}
void generate_DIV(quad* q){generate_arithmetic(div_v,q);}
void generate_MOD(quad* q){generate_arithmetic(mod_v,q);}

void generate_UMINUS(quad* q){

instruction t;

	t.opcode=mul_v;
	make_operand(q->arg1 , &t.arg1);
	make_operand(newexpr_constnum(-1) , &t.arg2);

	make_operand(q->result , &t.result);
	q->taddress = nextinstructionlabel();
	t.srcLine=q->line;
	emit2(t);
}

void generate_NEWTABLE(quad* q){generate_arithmetic(newtable_v,q);}
void generate_TABLEGETELEM(quad* q){cout<<"KALEITAI H GETELEMENT "<<endl; generate_arithmetic(tablegetelem_v,q);}
void generate_TABLESETELEM(quad* q){generate_arithmetic(tablesetelem_v,q);}
void generate_ASSIGN(quad* q){generate_arithmetic(assign_v,q);}
void generate_JUMP(quad* q){generate_relational(jump_v,q);}
void generate_IF_EQ(quad* q){generate_relational(jeq_v,q);}
void generate_IF_NOTEQ(quad* q){generate_relational(jne_v,q);}
void generate_IF_GREATER(quad* q){generate_relational(jgt_v,q);}
void generate_IF_GREATEREQ(quad* q){generate_relational(jge_v,q);}
void generate_IF_LESS(quad* q){generate_relational(jlt_v,q);}
void generate_IF_LESSEQ(quad* q){generate_relational(jle_v,q);}

void generate_GETRETVAL(quad* q){
	q->taddress = nextinstructionlabel();
	instruction t;

	t.arg2.type=ignore_a;
	
	t.opcode = assign_v;
	make_operand(q->result, &t.result);
	make_retvaloperand(&t.arg1);
	t.srcLine=q->line;
	emit2(t);
}

stack<SymbolTableEntry*> funcStack;

void generate_FUNCSTART(quad* q){
	SymbolTableEntry* f;
	
	f=q->result->sym;
	f->taddress=nextinstructionlabel();
	q->taddress=nextinstructionlabel();

	userfunc* fu=new userfunc();
	fu->address=f->taddress;
	fu->localsize=f->totalLocals;
	fu->id=f->value.funcVal->name;
	userFuncs.push_back(fu);
	
	funcStack.push(f);

	instruction t;
	t.arg1.type=ignore_a;
	t.arg2.type=ignore_a;

	t.opcode=funcenter_v;
	t.srcLine=q->line;
	make_operand(q->result,&t.result);
	emit2(t);

}
//void backpatch(list<int> returnList,int i){}

void generate_RETURN(quad* q){
	q->taddress=nextinstructionlabel();

	instruction t;
	t.srcLine=q->line;

	t.opcode=assign_v;
	make_retvaloperand(&t.result);
	reset_operand(&t.arg1);
	reset_operand(&t.arg2);

	make_operand(q->arg1,&t.arg1);
	emit2(t);

	SymbolTableEntry* f;
	f=funcStack.top();
	f->returnList.push_back(nextinstructionlabel());
	//append(f.returnList,nextinstructionlabel());

	t.opcode=jump_v;
	reset_operand(&t.arg1);
	reset_operand(&t.arg2);
	t.result.type=label_a;
	emit2(t);
}

void generate_FUNCEND(quad* q){
	SymbolTableEntry* f;
	f=funcStack.top();
	funcStack.pop();
	
	for(auto it=f->returnList.begin();it!=f->returnList.end();it++){
		//*it=nextinstructionlabel();
		instructions[*it]->result.val=nextinstructionlabel();
	}
	//backpatch(f->returnList,nextinstructionlabel());

	q->taddress=nextinstructionlabel();

	instruction t;
	t.srcLine=q->line;
	t.opcode=funcexit_v;
	reset_operand(&t.arg1);
	reset_operand(&t.arg2);
	make_operand(q->result,&t.result);
	emit2(t);
}

void generate_NOT(quad* q){
	q->taddress=nextinstructionlabel();
	instruction t;
    t.srcLine=q->line;

	t.opcode=jeq_v;
	make_operand(q->arg1,&t.arg1);
	make_booloperand(&t.arg2,false);
	t.result.type=label_a;
	t.result.val=nextinstructionlabel()+3;
	emit2(t);

	t.opcode=assign_v;
	make_booloperand(&t.arg1,false);
	reset_operand(&t.arg2);
	make_operand(q->result,&t.result);
	emit2(t);

	t.opcode=jump_v;
	reset_operand(&t.arg1);
	reset_operand(&t.arg2);
	t.result.type=label_a;
	t.result.val=nextinstructionlabel()+2;
	emit2(t);

	t.opcode = assign_v;
	make_booloperand(&t.arg1, true);
	reset_operand(&t.arg2);
	make_operand(q->result, &t.result);
	emit2(t);
}

void generate_AND(quad* q){
	q->taddress=nextinstructionlabel();

	instruction t;
	t.srcLine=q->line;

	t.opcode = jeq_v;
	make_operand(q->arg1, &t.arg1);
	make_booloperand(&t.arg2, false);
	t.result.type = label_a;
	t.result.val = nextinstructionlabel()+4;
	emit2(t);

	make_operand(q->arg2, &t.arg1);
	t.result.val = nextinstructionlabel()+3;
	emit2(t);

	t.opcode = assign_v;
	make_booloperand(&t.arg1, true);
	reset_operand(&t.arg2);
	make_operand(q->result, &t.result);
	emit2(t);

	t.opcode = jump_v;
	reset_operand (&t.arg1);
	reset_operand(&t.arg2);
	t.result.type = label_a;
	t.result.val = nextinstructionlabel()+2;
	emit2(t);

	t.opcode = assign_v;
	make_booloperand(&t.arg1, false);
	reset_operand(&t.arg2);
	make_operand(q->result, &t.result);
	emit2(t);
}

void generate_OR(quad* q){
	q->taddress=nextinstructionlabel();
	instruction t;
	t.srcLine=q->line;

	t.opcode = jeq_v;
	make_operand(q->arg1, &t.arg1);
	make_booloperand(&t.arg2, true);
	t.result.type = label_a;
	t.result.val = nextinstructionlabel()+4;
	emit2(t);

	make_operand(q->arg2, &t.arg1);
	t.result.val = nextinstructionlabel()+3;
	emit2(t);

	t.opcode = assign_v;
	make_booloperand(&t.arg1, false);
	reset_operand(&t.arg2);
	make_operand(q->result, &t.result);
	emit2(t);

	t.opcode = jump_v;
	reset_operand (&t.arg1);
	reset_operand(&t.arg2);
	t.result.type = label_a;
	t.result.val = nextinstructionlabel()+2;
	emit2(t);

	t.opcode = assign_v;
	make_booloperand(&t.arg1, true);
	reset_operand(&t.arg2);
	make_operand(q->result, &t.result);
	emit2(t);
}

void generate_PARAM(quad* q){
	q->taddress=nextinstructionlabel();
	instruction t;
	t.srcLine=q->line;

	t.opcode=pusharg_v;
	reset_operand(&t.arg2);
	reset_operand(&t.result);
	make_operand(q->arg1,&t.arg1);
	emit2(t);
}

void generate_CALL(quad* q){
	q->taddress=nextinstructionlabel();
	instruction t;
	t.srcLine=q->line;

	t.opcode=call_v;
	reset_operand(&t.arg2);
	reset_operand(&t.result);
	make_operand(q->arg1,&t.arg1);
	emit2(t);
}

void generate_NOP(quad * q){
	instruction t;
	t.srcLine=q->line;

	t.opcode=nop_v;
	reset_operand(&t.arg1);
	reset_operand(&t.arg2);
	reset_operand(&t.result);
	emit2(t);
}

void generate(void){
	cout<<"quad size is "<< total<<endl;
	//int total = instructions.size();

	for( iinstruction = 0; iinstruction<currQuad; ++iinstruction) {
		//cout<<"GENERATE=" <<iinstruction<<endl;
	//	cout<<"opcode is: "<<quads[iinstruction].op<<endl;
		(*generators[ quads[iinstruction].op] )(quads+iinstruction ) ;
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

extern unsigned programVarOffset;

void WriteBinary(){

	FILE *fp = fopen("test.bin","wb");

	if(!fp)
		cout<<"cannot open file"<<endl;

	unsigned m = 340200501;

	fwrite(&m,1, sizeof(unsigned),fp);
	
	m = programVarOffset;
	//cout<<"sdfg"<<programVarOffset<<endl;
	fwrite(&m,1, sizeof(unsigned),fp);

	m = stringConsts.size();
	fwrite(&m ,1, sizeof(unsigned),fp);

	for(auto it = stringConsts.begin();it!=stringConsts.end();it++){
		unsigned tmp = (*it).length();
		fwrite(&tmp , 1 , sizeof(unsigned) ,fp );
		
		string lola = *it;
		for( int i=0; i < lola.length();i++){
			//char c = *it;
			char c = lola[i];
			fwrite(&c,1,sizeof(char) , fp  );		
		}
	}

	unsigned len=numConsts.size();
	fwrite(&len,1,sizeof(unsigned),fp);

	for(auto it = numConsts.begin();it!=numConsts.end();it++){
		double a = *it;
		fwrite( &a , 1 , sizeof(double) , fp); 
	}

	len = userFuncs.size();
	fwrite(&len , 1 , sizeof(unsigned) , fp);

	for(auto it = userFuncs.begin();it!=userFuncs.end(); it++){
		unsigned add = (*it)->address;
		unsigned lsize = (*it)->localsize;
		string tmp = (*it)->id;

		fwrite(&add,1,sizeof(unsigned) , fp	);
		fwrite(&lsize , 1, sizeof(unsigned) , fp);

		unsigned del = tmp.length();
		fwrite( &del , 1 , sizeof(unsigned) , fp);

		for(int i = 0 ; i< tmp.length();i++){
			char c = tmp[i];
			fwrite(&c,1,sizeof(char) , fp  );	
		}
	}	

	m= namedLibfuncs.size();
	fwrite(&m ,1, sizeof(unsigned),fp);

	for(auto it = namedLibfuncs.begin();it!=namedLibfuncs.end();it++){
		unsigned tmp = (*it).length();
		fwrite(&tmp , 1 , sizeof(unsigned) ,fp );
		
		string lola = *it;
		for( int i=0; i < lola.length();i++){
			//char c = *it;			
			char c = lola[i];
			fwrite(&c,1,sizeof(char) , fp  );		
		}
	}

	m = instructions.size();
	fwrite(&m, 1 , sizeof(unsigned) , fp); 

	for (auto it = instructions.begin();it!=instructions.end();it++){

		vmopcode opcode = (*it)->opcode;
		vmarg arg1 = (*it)->arg1;
		vmarg arg2 = (*it)->arg2;
		vmarg result = (*it)->result;

		fwrite( &opcode , 1 , sizeof(unsigned char) , fp);

		unsigned char type  = (*it)->arg1.type;
		unsigned val = (*it)->arg1.val;
		
		unsigned int line = (*it)->srcLine;

		fwrite(&line , 1, sizeof(unsigned int) , fp);
		fwrite(&type , 1 , sizeof(unsigned char) , fp);
		fwrite(&val , 1 , sizeof(unsigned) , fp) ; 
	
		//fwrite(&line , 1, sizeof(unsigned int) , fp);

		type  = (*it)->arg2.type;
		val = (*it)->arg2.val;
		//line = (*it)->srcLine;

		fwrite(&type , 1 , sizeof(unsigned char) , fp);
		fwrite(&val , 1 , sizeof(unsigned) , fp) ; 
		//fwrite(&line , 1, sizeof(unsigned int) , fp);

		type  = (*it)->result.type;
		val = (*it)->result.val;
		//line = (*it)->srcLine;

		fwrite(&type , 1 , sizeof(unsigned char) , fp);
		fwrite(&val , 1 , sizeof(unsigned) , fp) ;
		//fwrite(&line , 1, sizeof(unsigned int) , fp); 

	
	}
}
