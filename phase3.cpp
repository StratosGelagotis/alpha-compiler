#include "Phase3.hpp"
#define EXPAND_SIZE 1024
#define CURR_SIZE (total*sizeof(quad))
#define NEW_SIZE (EXPAND_SIZE*sizeof(quad)+CURR_SIZE)

extern int yyerror(string yaccProvidedMessage);

stack<int> functionLocalStack;
const char * iopcodeStrings[]= {
	"assign",
	"mul",
	"uminus",
	"not",
	"if_lesseq",
	"if_greater",
	"ret",
	"funcend",
	"tablegetelem",
	"add",
	"div",
	"and",
	"if_eq",
	"if_greatereq",
	"call",
	"getretval",
	"tablecreate",
	"tablesetelem",
	"sub",
	"mod",
	"or",
	"if_noteq",
	"if_less",
	"param","funcstart","jump"};

const char* getiopcodeStrings(int val){
		return iopcodeStrings[val];
	}

unsigned tempCounter=0;

unsigned programVarOffset = 0 ;
unsigned functionLocalOffset = 0 ;
unsigned formalArgOffset =0 ;

unsigned scopeSpaceCounter =1;

stack<int> OffsetStack;

unsigned total=0;
quad * quads=NULL;
unsigned int currQuad=0;

list<expr*> exprList;
auto exprListIter = exprList.begin();

list<pair*> pairList;
auto pairListIter=exprList.begin();

scopespace_t currScopeSpace(){
		if(scopeSpaceCounter==1)
			return programvar;
		else if(scopeSpaceCounter % 2 == 0)
			return formalarg;
		else
			return functionlocal;
	}

unsigned currScopeOffset(){
		switch(currScopeSpace()){
			case programvar: return programVarOffset; break;
			case functionlocal: return functionLocalOffset;	break;
			case formalarg: return formalArgOffset;	break;
			default:assert(0);
		}
	}

void inCurrScopeOffset(){
	switch(currScopeSpace()){
			case programvar	   :	++programVarOffset;break;
			case functionlocal :	++functionLocalOffset;break;
			case formalarg 	   :	++formalArgOffset;break;
			default:assert(0);
		}
	}

void enterScopeSpace(){
	++scopeSpaceCounter;
}

void exitScopeSpace(){
		if(scopeSpaceCounter>1)
			--scopeSpaceCounter;
		else
			cout<<"EXIT SCOPE SPACE PATAtOE------------------------------------------\n";
}

void resetFormalArgsOffset(){
		formalArgOffset=0;
}

void resetFunctionLocalOffset(){
		functionLocalOffset=0;
}

void restoreCurrScopeOffset(unsigned n){
	switch(currScopeSpace()){
			case programvar: programVarOffset = n; break;
			case functionlocal: functionLocalOffset = n; break;
			case formalarg: formalArgOffset = n; break;
			default:assert(0);
	}
}

unsigned nextQuadLabel(){
	return currQuad;
}

void patchLabel(unsigned quadNo , unsigned label){
	assert(quadNo < currQuad);
	quads[quadNo].label = label;
}

expr* newexpr(enum expr_t type){
	expr* tmp=new expr();
	tmp->type=type;
	return tmp;
}

expr* lvalue_expr(SymbolTableEntry *sym){
		expr* e = new expr();
		memset(e,0,sizeof(expr));
		e->next =(expr*) 0;
		e->sym=sym;
		switch(sym->type){
			case var_s: e->type = var_e; break;
			case programfunc_s : e->type=programfunc_e; break;
			case libraryfunc_s: e->type = libraryfunc_e;break;
			default:assert(0);
			}
	return e;
	}

void expand(){
	assert(total ==currQuad);
	quad* p =(quad*)malloc(NEW_SIZE);
		if(quads){
			memcpy(p,quads,CURR_SIZE);
			free(quads);
		}
	quads = p;
	total += EXPAND_SIZE;
}

void emit(
		iopcode op,
		expr*   arg1,
		expr*   arg2,
		expr*   result,
		int label,
		int line )
			{
				if(currQuad == total)
					expand();
				quad* p = quads + currQuad++;
				p->arg1 = arg1;
				p->arg2 = arg2;
				p->result = result;
				p->label = label;
				p->line = line;
				p->op=op;
	}

string newtempname(){
	string tmp("_t");
	tmp+=std::to_string(tempCounter) ;
	tempCounter++;
	return tmp;
}

void resettemp(){
	tempCounter=0;
}

/*
SymbolTableEntry* newtemp(){
	string name = newtempname();
	SymbolTableEntry* sym = lookup_name(name, scope);
	if (sym==NULL)
		return insert_var(name,var_s);
	else
		return sym;
}
*/

SymbolTableEntry* newtemp(){
	string name = newtempname();
	SymbolTableEntry* sym = lookup_name(name, scope);
	if (sym==NULL){
		sym = insert_var(name,var_s);
			if(sym->value.varVal->scope==0){
					sym->scopespace=programvar;
					sym->offset=programVarOffset;
					programVarOffset++;
				}
				else{
					sym->offset=currScopeOffset();
					sym->scopespace=currScopeSpace();
					inCurrScopeOffset();
				}
		return sym;
}
	else
		return sym;
}


expr* emit_iftableitem(expr* e){
	if(e->type != tableitem_e)
		return e;
	else{
		expr* result=newexpr(var_e);
		result->sym=newtemp();
		emit(tablegetelem,e,e->index,result,-100,yylineno);
		return result;
	}
}

expr* newexpr_constbool(int k){
	expr* ex=newexpr(constbool_e);
	ex->boolConst=k;
	return ex;
}

expr* newexpr_conststring(string k){
	expr* ex=newexpr(conststring_e);
	ex->strConst=k;
	return
	ex;
}

expr* newexpr_constnum(int k){
	expr* ex=newexpr(constnum_e);
	ex->numConst=k;
	return ex;
}

void checkuminus(expr* e){
	if(	e->type==constbool_e	||
		e->type==conststring_e	||
		e->type==nil_e			||
		e->type==newtable_e		||
		e->type==programfunc_e	||
		e->type==libraryfunc_e	||
		e->type==boolexpr_e	){
		yyerror("ILLEGAL EXPR TO UNARY -");
	}
}

expr* make_call(expr* lvalue){
	expr* func=emit_iftableitem(lvalue);
	exprList.reverse();
	for(expr* arg: exprList)
		emit(param,arg,(expr*)0,(expr*)0,-21,yylineno);
	exprList.clear();
	emit(call,func,(expr*)0,(expr*)0,-21,yylineno);
	expr* result=newexpr(var_e);
	result->sym=newtemp();
	emit(getretval,(expr*)0,(expr*)0,result,-21,yylineno);
	return result;
}

expr* member_item(expr* lvalue,string* name){
	lvalue=emit_iftableitem(lvalue);
	expr* item=newexpr(tableitem_e);
	item->sym=lvalue->sym;
	item->index=newexpr_conststring(*name);
	return item;
}

void printQuads(){
		for(int i=0;i<currQuad;i++){
			cout<<i<<" ";
				cout<<getiopcodeStrings(quads[i].op)<<" || ";

				if(quads[i].arg1!=NULL){
					if(quads[i].arg1->sym==NULL){
						if(quads[i].arg1->type==constnum_e)
							cout<<quads[i].arg1->numConst<<" || ";
						else if(quads[i].arg1->type==constbool_e)
							cout<<quads[i].arg1->boolConst<<" || ";
						else if(quads[i].arg1->type==conststring_e)
							cout<<quads[i].arg1->strConst<<" || ";
						else
							cout<<"nil |+ ";
						}
					else
						cout<<quads[i].arg1->sym->value.varVal->name<<" || ";
					}
					if(quads[i].arg2!=NULL){
						if(quads[i].arg2->sym==NULL){
							if(quads[i].arg2->type==constnum_e)
								cout<<quads[i].arg2->numConst<<" || ";
							else if(quads[i].arg2->type==constbool_e)
								cout<<quads[i].arg2->boolConst<<" || ";
							else if(quads[i].arg2->type==conststring_e)
								cout<<quads[i].arg2->strConst<<" || ";
							else
								cout<<"nil || ";
							}
						else
							cout<<quads[i].arg2->sym->value.varVal->name<<" || ";
						}

					if(quads[i].result!=NULL){
						if(quads[i].result->sym==NULL){
							if(quads[i].result->type==constnum_e)
								cout<<quads[i].result->numConst<<" || ";
							else if(quads[i].result->type==constbool_e)
								cout<<quads[i].result->boolConst<<" || ";
							else if(quads[i].result->type==conststring_e)
								cout<<quads[i].result->strConst<<" || ";
							else
								cout<<"nil || ";
							}
						else
							cout<<quads[i].result->sym->value.varVal->name<<" || ";
						}
			cout<<"line : "<<quads[i].line<<" || ";
			cout<<"label : "<<quads[i].label<<endl;
			}
}
