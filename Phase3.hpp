#include "sym.hpp"
extern int scope;
extern int yylineno;

typedef enum iopcode{
	assign,		
	mul,
	uminus,
	not1,	//
	if_lesseq,
	if_greater,
	ret,
	funcend,
	tablegetelem,
	add,
	div1,  	//
	and1,	//
	if_eq,
	if_greatereq,
	call,
	getretval,
	tablecreate,
	tablesetelem,
	sub,
	mod,
	or1,	//
	if_noteq,
	if_less,
	param,
	funcstart,
	jump
}iopcode;

void enterScopeSpace();
void exitScopeSpace();

typedef enum expr_t{
		
		var_e,
		tableitem_e,
		
		programfunc_e,
		libraryfunc_e,
		
		arithexpr_e,
		boolexpr_e,
		assignexpr_e,
		newtable_e,
		
		constnum_e,
		constbool_e,
		conststring_e,
		
		nil_e
}expr_t;

typedef struct expr{
	expr_t	 type;
	SymbolTableEntry* sym;   //symbol*  sym;
	expr*  	 index;
	double 	 numConst;
	string   strConst;		//char*   strConst; 		
	bool     boolConst;	
		//unsigned char boolConst;
	expr*    next;
}expr;

typedef struct quad{
	iopcode  op;
	expr*    result;
	expr*    arg1;
	expr*	 arg2;
	int label;
	unsigned line;
	int taddress;
}quad;

typedef struct pair
{
	expr* key;
	expr* value;
}pair;

typedef struct stmtStruct {
	//breakStruct * b;
	//continueStruct * c;
	list<int> continueList;
	list<int> breakList;
}stmtStruct;

typedef	 struct forStruct{
		int test;
		int enter;	
}forStruct;

typedef struct callsuffix{
	//list<expr*> elist;
	bool method;
	string* name;
}callsuffix;


scopespace_t currScopeSpace();
void inCurrScopeOffset();
unsigned currScopeOffset();
expr* newexpr(enum expr_t type);
expr* lvalue_expr(SymbolTableEntry *sym);
SymbolTableEntry* newtemp();
expr* emit_iftableitem(expr* e);
string newtempname();
void resettemp();
void expand();
void emit(iopcode op,expr*arg1,expr*arg2,expr* result,int label,int line);
void printQuads();
expr* newexpr_constbool(int k);
expr* newexpr_conststring(string k);
expr* newexpr_constnum(int k);
void checkuminus(expr* e);
void resetFormalArgsOffset();
void resetFunctionLocalOffset();
void restoreCurrScopeOffset(unsigned n);
unsigned nextQuadLabel();
void patchLabel(unsigned quadNo , unsigned label);
expr* make_call(expr* lvalue);
expr* member_item(expr* lvalue,string* name);
unsigned int isTempExpr(expr *e);

/*
 *  auto  iter = container.GetObj()->begin();
 while (iter!=container.GetObj()->end()){
   (*(iter++))->Execute();
 }
 * */
