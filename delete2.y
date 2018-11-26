%{
//#include "header.hpp"
#include "phase4.hpp"
extern	unsigned programVarOffset  ;
extern unsigned functionLocalOffset ;
extern unsigned formalArgOffset  ;
extern void generate_UMINUS(quad* q);

extern list<expr*> exprList;
extern list<pair*> pairList;
extern stack<int> functionLocalStack;

extern unsigned scopeSpaceCounter ;

extern stack<int> OffsetStack;

extern int yylineno;
extern FILE* yyin;
int yylex();
int yyerror(string yaccProvidedMessage);
int yyinput();
extern char* yytext;
int scope=0;
int scope2=scope;
bool bes;
int loopcounter;
%}

%start program

%union {
struct  forStruct * forprefix2;
//struct breakStruct * breakstmt;
//struct continueStruct *	continuestmt;
struct stmtStruct  *Stmt2;
string* stringValue;
int intValue;
double realValue;
struct expr* exprNode;
struct callsuffix* callsuf;
struct SymbolTableEntry* SymbolTableEntry;
}

%type <exprNode> lvalue;
%type <forprefix2> forprefix;

%type <SymbolTableEntry> fid;
%type <exprNode> expr;
%type <exprNode> term;
%type <exprNode> assignexpr;
%type <exprNode> const;
%type <exprNode> primary;
%type <exprNode> number;
%type <exprNode> call;
%type <callsuf> methodcall;
%type <callsuf> normcall;
%type <callsuf> callsuffix;
%type <exprNode> objectdef;
%type <exprNode> elist;
%type <exprNode> _elist_;
%type <intValue> ifprefix;
%type <intValue> elseprefix;
%type<intValue> whilestmt;
%type<intValue> whilestart;
%type<intValue> whilecond;
%type<intValue> loopstart;
%type<intValue> loopend;
%type<intValue> N;
%type<intValue> M;
%type <Stmt2> stmt;
%type <Stmt2> stmts;
%type <Stmt2> loopstmt;
%type <Stmt2> forstmt;
%type <intValue> jafterfunc;
%type <SymbolTableEntry>funcdef;
%type<SymbolTableEntry> funcprefix;
%type <intValue> funcbody;
%type<Stmt2> block;

%type<Stmt2> ifstmt;

%type <exprNode> member;

%token <stringValue> IF
%token <intValue>    INTEGER
%token <stringValue> ELSE
%token <stringValue> WHILE
%token <realValue>	 REAL
%token <stringValue> STRING
%token <stringValue> FOR
%token <stringValue> FUNCTION
%token <stringValue> RETURN
%token<Stmt2> BREAK;
%token<Stmt2> CONTINUE;
%token <stringValue> AND
%token <stringValue> NOT
%token <stringValue> OR
%token <stringValue> LOCAL
%token <stringValue> TRUE
%token <stringValue> FALSE
%token <stringValue> NIL
%token <stringValue> COMMA
%token <stringValue> COLON
%token <stringValue> DOUBLE_POINT
%token <stringValue> DOUBLE_ANWKATW
%token <stringValue> ID
%token <stringValue> LEFT_BRACKET
%token <stringValue> RIGHT_BRACKET
%token <stringValue> RIGHT_SQUERE_BRACKET
%token <stringValue> LEFT_SQUERE_BRACKET
%token <stringValue> SEMICOLON

%right ASGN
%left OR
%left AND
%nonassoc EQUAL NEQUAL

%nonassoc GT GE LT  LE
%left PLUS MINUS
%left MUL DIV MODULO
%right NOT PLUSPLUS MINUSMINUS UMINUS
%left POINT DOUBLE_POINT
%left RIGHT_SQUERE_BRACKET LEFT_SQUERE_BRACKET
%left LEFT_PARENTHESIS RIGHT_PARENTHESIS

%%

stmts: stmts {  if($1==NULL) $1 = new stmtStruct();  } stmt   {

/*		$1 = new stmtStruct();
		$1->b=new breakStruct();
		$1->c= new continueStruct();*/

		$$ = new stmtStruct();

		if($1!=NULL ){
		
			for(auto it = $1->breakList.begin();it!=$1->breakList.end();it++){
				cout<<*it<<endl;
				$$->breakList.push_front(*it);
			}
			for(auto it = $1->continueList.begin();it!=$1->continueList.end();it++){
				cout<<*it<<endl;
				$$->continueList.push_front(*it);
			}
}

if($3!=NULL ){

		for(auto it = $3->breakList.begin();it!=$3->breakList.end();++it){
			cout<<*it<<endl;
			$$->breakList.push_front(*it);
		}
		for(auto it = $3->continueList.begin();it!=$3->continueList.end();it++){
			cout<<*it<<endl;
			$$->continueList.push_front(*it);
		}
}
	/*	for(auto it = $2->continueList.begin();it!=$2->continueList.end();it++){
		cout<<*it<<endl;
			$$->continueList.push_front(*it);
		}*/

	cout<<"apo stmts se stmts stmt \n";}
| 						{$$=NULL;cout<<"apo stmts se tpt \n";}
;

program: stmts {}
;

stmt: expr SEMICOLON{
	$$=NULL;
	cout<<"apo statement se Semicolon \n";
}
|ifstmt	 		 	{cout<<"apo statement phga se Ifstmt \n";
	$$=$1;}
|whilestmt 		 	{cout<<"apo statement phga se Whilestmt \n";
	$$=NULL;
	}
|forstmt 		 	{cout<<"apo statement phga se Forstmt \n";
	$$=$1;;
	}
|returnstmt		 	{cout<<"apo statement phga se Returnstmt \n";
					if(scope==0) yyerror("Return statement at scope 0");
					$$=NULL;
					}
|BREAK SEMICOLON 	{cout<<"apo statement phga se Breaksemicolostmt \n";
					if(loopcounter==0) yyerror("Break statement at scope 0");

					$1=new stmtStruct();

					$1->breakList.push_front(currQuad);

		emit(jump,(expr*)0,(expr*)0,(expr*)0,-21,yylineno);
		$$=$1;
	}
|CONTINUE SEMICOLON {cout<<"apo statement phga se Continuesemicolostmt \n";
					if(loopcounter==0) yyerror("Continue statement at scope 0");

					$1=new stmtStruct();

					$1->continueList.push_front(currQuad);

		emit(jump,(expr*)0,(expr*)0,(expr*)0,-21,yylineno);
		$$=$1;
	}

|block 				{$$=$1;cout<<"apo statement phga se Block \n";}
|funcdef  			{$$=NULL;cout<<"apo statement phga se Funcdef \n";}
|SEMICOLON 			{$$=NULL;cout<<"apo statement phga se Semicolon \n";}
;

expr:assignexpr		{cout<<"apo expr se assignexpr \n";
	$$=$1;
}

|expr PLUS expr  	{cout<<"apo expr phga se Plus expr"<<endl;
					expr* ex1=(expr*)$1;
					expr* ex2=(expr*)$3;
					$$=newexpr(arithexpr_e);
					$$->sym=newtemp();
					emit(add,ex1,ex2,$$,-21,yylineno);
}
|expr MINUS expr 	{cout<<"apo expr phga se Minus expr"<<endl;
					expr* ex1=(expr*)$1;
					expr* ex2=(expr*)$3;
					$$=newexpr(arithexpr_e);
					$$->sym=newtemp();
					emit(sub,ex1,ex2,$$,-21,yylineno);
					}
|expr MUL expr 		{cout<<"apo expr phga se Mul expr"<<endl;
					expr* ex1=(expr*)$1;
					expr* ex2=(expr*)$3;
					$$=newexpr(arithexpr_e);
					$$->sym=newtemp();
					emit(mul,ex1,ex2,$$,-21,yylineno);
}
|expr DIV expr 		{cout<<"apo expr phga se Div expr"<<endl;
					expr* ex1=(expr*)$1;
					expr* ex2=(expr*)$3;
					$$=newexpr(arithexpr_e);
					$$->sym=newtemp();
					emit(div1,ex1,ex2,$$,-21,yylineno);//ELEGXOS !=0 PARANOMASTHS
}
|expr MODULO expr	{cout<<"apo expr phga se Modulo expr"<<endl;
					expr* ex1=(expr*)$1;
					expr* ex2=(expr*)$3;
					$$=newexpr(arithexpr_e);
					$$->sym=newtemp();
					emit(mod,ex1,ex2,$$,-21,yylineno);  //ELEGXOS !=0 PARANOMASTHS
}
|expr GT expr 		{cout<<"apo expr phga se GT expr"<<endl;
					expr* ex1=(expr*)$1;
					expr* ex2=(expr*)$3;
					$$=newexpr(boolexpr_e);
					$$->sym=newtemp();
					emit(if_greater,ex1,ex2,(expr*)0,currQuad+3,yylineno);
					emit(assign,newexpr_constbool(0),(expr*)0,$$,-21,yylineno);
					emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
					emit(assign,newexpr_constbool(1),(expr*)0,$$,-21,yylineno);
				}
|expr GE expr 		{cout<<"apo expr phga se GE expr"<<endl;
					expr* ex1=(expr*)$1;
					expr* ex2=(expr*)$3;
					$$=newexpr(boolexpr_e);
					$$->sym=newtemp();
					emit(if_greatereq,ex1,ex2,(expr*)0,currQuad+3,yylineno);
					emit(assign,newexpr_constbool(0),(expr*)0,$$,-21,yylineno);
					emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
					emit(assign,newexpr_constbool(1),(expr*)0,$$,-21,yylineno);
				}
|expr LT expr 		{cout<<"apo expr phga se LE expr"<<endl;
					expr* ex1=(expr*)$1;
					expr* ex2=(expr*)$3;
					$$=newexpr(boolexpr_e);
					$$->sym=newtemp();
					emit(if_less,ex1,ex2,(expr*)0,currQuad+3,yylineno);
					emit(assign,newexpr_constbool(0),(expr*)0,$$,-21,yylineno);
					emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
					emit(assign,newexpr_constbool(1),(expr*)0,$$,-21,yylineno);
				}
|expr LE expr 		{cout<<"apo expr phga se LE expr"<<endl;
					expr* ex1=(expr*)$1;
					expr* ex2=(expr*)$3;
					$$=newexpr(boolexpr_e);
					$$->sym=newtemp();
					emit(if_lesseq,ex1,ex2,(expr*)0,currQuad+3,yylineno);
					emit(assign,newexpr_constbool(0),(expr*)0,$$,-21,yylineno);
					emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
					emit(assign,newexpr_constbool(1),(expr*)0,$$,-21,yylineno);
				}
|expr EQUAL expr 	{cout<<"apo expr phga se Equal expr"<<endl;
					expr* ex1=(expr*)$1;
					expr* ex2=(expr*)$3;
					$$=newexpr(boolexpr_e);
					$$->sym=newtemp();
					emit(if_eq,ex1,ex2,(expr*)0,currQuad+3,yylineno);
					emit(assign,newexpr_constbool(0),(expr*)0,$$,-21,yylineno);
					emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
					emit(assign,newexpr_constbool(1),(expr*)0,$$,-21,yylineno);
				}
|expr NEQUAL expr 	{cout<<"apo expr phga se Nequal expr"<<endl;
					expr* ex1=(expr*)$1;
					expr* ex2=(expr*)$3;
					$$=newexpr(boolexpr_e);
					$$->sym=newtemp();
					emit(if_noteq,ex1,ex2,(expr*)0,currQuad+3,yylineno);
					emit(assign,newexpr_constbool(0),(expr*)0,$$,-21,yylineno);
					emit(jump,(expr*)0,(expr*)0,(expr*)0,currQuad+2,yylineno);
					emit(assign,newexpr_constbool(1),(expr*)0,$$,-21,yylineno);
				}
|expr AND expr	 	{cout<<"apo expr phga se And expr"<<endl;
					expr* ex1=(expr*)$1;
					expr* ex2=(expr*)$3;
					$$=newexpr(boolexpr_e);
					$$->sym=newtemp();
					emit(and1,ex1,ex2,$$,-21,yylineno);
				}
|expr OR expr		{cout<<"apo expr phga se Or expr"<<endl;
					expr* ex1=(expr*)$1;
					expr* ex2=(expr*)$3;
					$$=newexpr(boolexpr_e);
					$$->sym=newtemp();
					emit(or1,ex1,ex2,$$,-21,yylineno);
				}
|term				{cout<<"apo expr phga se term "<<endl;
	$$=$1;
}
;

term: LEFT_PARENTHESIS expr RIGHT_PARENTHESIS	{
							$$=$2;
							cout<<"apo term se ( expr ) \n";
			}

| MINUS expr %prec UMINUS 	{cout<<"apo term phga se Uminus"<<endl;
							expr* ex=(expr*) $2;
							checkuminus(ex);
							$$=newexpr(arithexpr_e);
							$$->sym=newtemp();
							emit(uminus,ex,(expr*)0,$$,-21,yylineno);
						}
| NOT expr					{cout<<"apo term phga se Not expr"<<endl;
							expr* ex=(expr*) $2;
							checkuminus(ex);
							$$=newexpr(arithexpr_e);
							$$->sym=newtemp();
							emit(not1,ex,(expr*)0,$$,-21,yylineno);
						}
| PLUSPLUS lvalue			{cout<<"apo term phga se PlusPlus lvalue"<<endl;
							if (((expr *)$2)->type==programfunc_e || ((expr *)$2)->type==libraryfunc_e){
								string lola="ERROR: USING ILEGAL OPERATOR -> ";lola+="++";lola+=" <- on function -> ";lola+=*yylval.stringValue;lola+=" <-";
								yyerror(lola);
							}
							if($2->type == tableitem_e){
								$$ = emit_iftableitem($2);
								emit(add,$$,newexpr_constnum(1),$$,-21,yylineno);
								emit(tablesetelem,$2,$2->index,$$,-21,yylineno);
							}else{
								emit(add,$2,newexpr_constnum(1),$2,-21,yylineno);
								$$ = newexpr(arithexpr_e);
								$$->sym = newtemp();
								emit(assign,$2,(expr*)0,$$,-21,yylineno);
							}
}
| lvalue PLUSPLUS			{cout<<"apo term phga se lvalue PlusPlus"<<endl;
							if (((expr *)$1)->type==programfunc_e || ((expr *)$1)->type==libraryfunc_e){
								string lola="ERROR: USING ILEGAL OPERATOR -> ";lola+="++";lola+=" <- on function -> ";lola+=*yylval.stringValue;lola+=" <-";
								yyerror(lola);
							}
							$$ = newexpr(var_e);
							$$->sym = newtemp();

							if($1->type == tableitem_e){
								expr* value = emit_iftableitem($1);
								emit(assign,value,(expr*)0,$$,-21,yylineno);
								emit(add,value,newexpr_constnum(1),value,-21,yylineno);
								emit(tablesetelem,$1,$1->index,value,-21,yylineno);
							}else{
								emit(assign,$1,(expr*)0,$$,-21,yylineno);
								emit(add,$1,newexpr_constnum(1),$1,-21,yylineno);
							}

}
| MINUSMINUS lvalue			{cout<<"apo term phga se MinusMinus lvalue"<<endl;
							if (((expr *)$2)->type==programfunc_e || ((expr *)$2)->type==libraryfunc_e ){
								string lola="ERROR: USING ILEGAL OPERATOR -> ";lola+="--";lola+=" <- on function -> ";lola+=*yylval.stringValue;lola+=" <-";
								yyerror(lola);
							}
							if($2->type == tableitem_e){
								$$ = emit_iftableitem($2);
								emit(sub,$$,newexpr_constnum(1),$$,-21,yylineno);
								emit(tablesetelem,$2,$2->index,$$,-21,yylineno);
							}else{
								emit(sub,$2,newexpr_constnum(1),$2,-21,yylineno);
								$$ = newexpr(arithexpr_e);
								$$->sym = newtemp();
								emit(assign,$2,(expr*)0,$$,-21,yylineno);
							}
}
| lvalue MINUSMINUS 		{cout<<"apo term phga se lvalue MinusMinus"<<endl;
								if (((expr *)$1)->type==programfunc_e || ((expr *)$1)->type==libraryfunc_e ){
								string lola="ERROR: USING ILEGAL OPERATOR -> ";lola+="--";lola+=" <- on function -> ";lola+=*yylval.stringValue;lola+=" <-";
								yyerror(lola);
							}
							$$ = newexpr(var_e);
							$$->sym = newtemp();

							if($1->type == tableitem_e){
								expr* value = emit_iftableitem($1);
								emit(assign,value,(expr*)0,$$,-21,yylineno);
								emit(sub,value,newexpr_constnum(1),value,-21,yylineno);
								emit(tablesetelem,$1,$1 ->index,value,-21,yylineno);
							}else{
								emit(assign,$1,(expr*)0,$$,-21,yylineno);
								emit(sub,$1,newexpr_constnum(1),$1,-21,yylineno);
							}
}
| primary					{$$=$1;cout<<"apo term phga se primary "<<endl;}
;

assignexpr: lvalue ASGN expr {
			cout<<"apo assignedexpr se lvalue ASGN expr \n";

	if ( ((expr* )$1)->type == programfunc_e ){
	string lola = "ERROR: Trying to use Userfun: ->"+*yylval.stringValue+"<- as lvalue";
			yyerror(lola);
	}
	if ( ((expr*)$1)->type == libraryfunc_e ){
	string lola = "ERROR: Trying to use libraryfunc_s: ->"+((SymbolTableEntry*)$1)->value.funcVal->name+"<- as lvalue";
			yyerror(lola);
	}
	if ( $1->type == tableitem_e)
		{
			emit(tablesetelem,$1,$1->index,$3,-21,yylineno);
			
			$$=emit_iftableitem($1);
			$$->type = assignexpr_e;
		}
	else{
			emit(assign,$3,(expr*)0,$1,-21,yylineno);

			$$=newexpr(assignexpr_e);
			$$->sym = newtemp();
			emit(assign,$1,(expr*)0,$$,-21,yylineno);
		}
}
;

primary: lvalue									{
	$$=emit_iftableitem($1);
	cout<<"apo primary se lvalue \n";}
|call											{cout<<"apo primary phga se call "<<endl;
	$$=$1;
}
|objectdef										{cout<<"apo primary phga se objectdef"<<endl;
	$$=$1;
}
|LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS		{cout<<"apo primary phga se left par funcdef right parenth "<<endl;
	$$=newexpr(programfunc_e);
	$$->sym=$2;

}
|const											{cout<<"apo primary phga se const "<<endl;

}
;

lvalue: ID {

	//resetFunctionLocalOffset();					//------------------------
				cout<<"apo lvalue se ID \n";
		SymbolTableEntry *t = lookup_all(*yylval.stringValue,(symbol_t)666);
		if(t == NULL){
			/*if(scope != 0){
				t=insert_var(*yylval.stringValue,var_s);
				t->offset=currScopeOffset();
				t->scopespace=currScopeSpace();
				inCurrScopeOffset();
			}else{
				t=insert_var(*yylval.stringValue,var_s);
				t->offset=currScopeOffset();
				t->scopespace=currScopeSpace();
				inCurrScopeOffset();
			}	*/
				t=insert_var(*yylval.stringValue,var_s);

					if(t->value.varVal->scope==0){
					t->scopespace=programvar;
					t->offset=programVarOffset;
					programVarOffset++;
					$$ = (expr *)lvalue_expr(t);
				}
				else{
					t->offset=currScopeOffset();
					t->scopespace=currScopeSpace();
					inCurrScopeOffset();
					$$ = (expr *)lvalue_expr(t);
				}
		}
		else{	//make ccout<<"to scope edw einai : "<<scope<<endl;
			if(t->type==var_s && !checkVisibility(t) )
				yyerror("ERROR: Accesing variable: -> " + *yylval.stringValue +"<- but is not visible");
			else if( checkVisibility(t) ){
					$$ = (expr *)lvalue_expr(t);
			}
		}
}

| LOCAL ID {
			cout<<"apo lvalue se Local Id \n";
	SymbolTableEntry *t = lookup_scope(0,*yylval.stringValue,libraryfunc_s);

	if( t!=NULL ){
		if(scope!=0 ){
			string lola = "ERROR: Trying to shadow libraryfunc_s";
			lola+=" -> ";lola+=*yylval.stringValue;lola+=" <- ";
			yyerror(lola);
			}
			$$ = (expr *)lvalue_expr(t);
	}
	else  {
		if((t= lookup_scope(scope,*yylval.stringValue,(symbol_t)666))==NULL){
		/*	if(scope != 0){
				t=insert_var(*yylval.stringValue,var_s);

				t->offset=currScopeOffset();
				t->scopespace=currScopeSpace();
				inCurrScopeOffset();
			}else{
				t=insert_var(*yylval.stringValue,var_s);
				t->offset=currScopeOffset();
				t->scopespace=currScopeSpace();
				inCurrScopeOffset();
			}*/
			t=insert_var(*yylval.stringValue,var_s);

				if(t->value.varVal->scope==0){
					t->scopespace=programvar;
					t->offset=programVarOffset;
					programVarOffset++;
					$$ = (expr *)lvalue_expr(t);
				}
				else{
					t->offset=currScopeOffset();
					t->scopespace=currScopeSpace();
					inCurrScopeOffset();
					$$ = (expr *)lvalue_expr(t);
				}
		}
			else{
				/*	if(t->type==programfunc_s){
					string lola="ERROR: Trying to shadow programfunc_s fucntion";
					lola+=" -> ";
					lola+=*yylval.stringValue;
					lola+=" <- ";
						yyerror(lola);
					}
					else if( t-> type == var_s){
						string lola="ERROR: Trying to shadow local var ";
						lola+="-> "; lola+=*yylval.stringValue; lola+=" <-";
						yyerror(lola);
					}	*/
			}		$$ = (expr *)lvalue_expr(t);
	}
}
| DOUBLE_ANWKATW ID {
			cout<<"apo lvalue se Double_anw katw \n";
	SymbolTableEntry *t = lookup_scope(0,*yylval.stringValue,(symbol_t)666);
			if(t==NULL){
				string lola="ERROR: No var_s var/func found with this name ->";
				lola+=*yylval.stringValue; lola+="<- ";
				yyerror(lola);
			}
	if(t!=NULL)
		$$ = (expr *)lvalue_expr(t);

}
| member {cout<<"apo DOUBLE_ANWKATW se member \n";
	$$=$1;
}
;

member: lvalue POINT ID	{	cout<<"apo member phga se lvalue Point Id"<<endl;
	$$=member_item($1,$3);
}
| lvalue LEFT_SQUERE_BRACKET expr RIGHT_SQUERE_BRACKET	{cout<<"apo member phga se lvalue left [ expr ]"<<endl;
	$1=emit_iftableitem($1);
	$$=newexpr(tableitem_e);
	$$->sym=$1->sym;
	$$->index=$3;
}
| call POINT ID											{cout<<"apo member phga se point id"<<endl;
	$$=member_item($1,$3);
}
| call LEFT_SQUERE_BRACKET expr RIGHT_SQUERE_BRACKET	{cout<<"apo member phga se call [ expr ] "<<endl;
	$1=emit_iftableitem($1);
	$$=newexpr(tableitem_e);
	$$->sym=$1->sym;
	$$->index=$3;
}
;

call: call LEFT_PARENTHESIS elist RIGHT_PARENTHESIS		{cout<<"apo call se call ( elist ) "<<endl;
	$$=make_call($1);
}
| lvalue callsuffix										{cout<<"apo call lvalue callsuffix "<<endl;
	if($2->method){
		expr* self=$1;
		$1=emit_iftableitem(member_item(self,$2->name));
		exprList.push_front(self);
	}
	$$=make_call($1);
}
| LEFT_PARENTHESIS funcdef RIGHT_PARENTHESIS LEFT_PARENTHESIS elist RIGHT_PARENTHESIS {cout<<"apo call ( funcdef ) ( elist )"<<endl;
	expr* func=newexpr(programfunc_e);
	func->sym=$2;
	$$=make_call(func);
}
;

callsuffix: normcall			{cout<<"apo callsuffix se normcall "<<endl;
	$$=$1;
}
|methodcall						{cout<<"apo callsuffix se methodcamll "<<endl;
	$$=$1;
}
;

normcall: LEFT_PARENTHESIS elist RIGHT_PARENTHESIS	{cout<<"apo normcall se ( elist ) "<<endl;
	$$=new callsuffix();
	//$$.elist=$2;
	$$->method=false;
	$$->name=NULL;
}
;

methodcall: DOUBLE_POINT ID LEFT_PARENTHESIS elist RIGHT_PARENTHESIS {cout<<"apo methodcall se doublepoint id ( elist ) "<<endl;
		$$=new callsuffix();
		//$$.elist=$4;
		$$->method=true;
		$$->name=$2;
}
;

elist: {cout<<"Mpika ELIST\n";
	exprList.clear();
	//$$=exprList.front();
  }
|{exprList.clear();}expr _elist_	{cout<<"apo elist se expr elist \n";
	expr* ex=(expr*)$2;
	exprList.push_front(ex);

}
;

_elist_: COMMA expr _elist_ {
	expr* ex=(expr*)$2;
	exprList.push_front(ex);
}
| {}
;

objectdef: LEFT_SQUERE_BRACKET elist RIGHT_SQUERE_BRACKET {cout<<"apo objectdef se [elist] \n";
	expr *t=newexpr(newtable_e);
	t->sym=newtemp();
	emit(tablecreate,(expr*)0,(expr*)0,t,-21,yylineno);
	int i=0;
	if(!exprList.empty()){
	for(expr* e: exprList)
		emit(tablesetelem,t,newexpr_constnum(i++),e,-21,yylineno);
	}
	exprList.clear();
	$$=t;
}

|  LEFT_SQUERE_BRACKET indexed RIGHT_SQUERE_BRACKET {cout<<"apo object def se [indexed] \n";

	expr* t=newexpr(newtable_e);
	t->sym=newtemp();
	emit(tablecreate,(expr*)0,(expr*)0,t,-21,yylineno);
	if(!pairList.empty()){
		pairList.reverse();
		for(pair* p: pairList){	emit(tablesetelem,t,p->key,p->value,-21,yylineno);
		}
	}
	$$=t;
}
;

indexed:{
	pairList.clear();
} indexedelem _indexed_ {cout<<"apo indexed se indexedele_indexed_ \n ";

}
;

_indexed_: COMMA indexedelem _indexed_ {}
| {}
;

indexedelem: LEFT_BRACKET expr COLON expr RIGHT_BRACKET
{
	pair* p=new pair();
	p->key=(expr*)$2;
	p->value=(expr*)$4;
	pairList.push_front(p);
};

block: LEFT_BRACKET {
		//enterScopeSpace();
		if(currScopeSpace()==formalarg){
			bes=false;
			enterScopeSpace();
		}
		//cout<<"-----------------------------------------------------to scopeSpaceCounter =  "<<scopeSpaceCounter<<endl;
		if( scopeSpaceCounter % 2 != 0 &&  scopeSpaceCounter  != 1){
			OffsetStack.push(functionLocalOffset);
				cout<<"-----------------------------------------------------STOIBAS SIZE =  "<<OffsetStack.size()<<endl;
	}
	resetFunctionLocalOffset();

	if(scopeSpaceCounter % 2 == 0 && scopeSpaceCounter!=1)
	enterScopeSpace();

	scope++;
}
stmts RIGHT_BRACKET {hide(scope);

		if(!OffsetStack.empty() &&  currScopeSpace()==functionlocal ){
				functionLocalOffset=OffsetStack.top();
				OffsetStack.pop();
				cout<<"-----------------------------------------------------STOIBAS SIZE =  "<<OffsetStack.size()<<endl;
		}

		if(scopeSpaceCounter  != 1){
			exitScopeSpace();
			exitScopeSpace();
		}
		scope--;
		$$=$3;
	}
;

fid: {	cout<<"Bika fid \n";
		string out="_AutoGenFunc_";
		out+=std::to_string(scope);
		out+="_";
		out+=std::to_string(yylineno);
		SymbolTableEntry* entry=insert_fun(out,programfunc_s);
		enterScopeSpace();										//------------------------
		$$=(SymbolTableEntry*)entry;
}
| ID {	cout<<"Bika fid me name \n";
		SymbolTableEntry* t=lookup_scope(0,*yylval.stringValue,libraryfunc_s);
		if(t!=NULL){
			string lola0="ERROR: Trying to shadow the Library function ->"+*yylval.stringValue+"<- ";
			//$$=(SymbolTableEntry*)t;
			yyerror(lola0);
		}else{
			t= lookup_scope(scope,*yylval.stringValue,(symbol_t)666);
			if(t==NULL  ){
				SymbolTableEntry* entry=insert_fun(*yylval.stringValue,programfunc_s);

				enterScopeSpace();

				$$=(SymbolTableEntry*)entry;
			}else{
				if(  t->type==programfunc_s && t->isActive==true   )	{
					string lola0 ="ERROR:(redefinition) The function ->" +*yylval.stringValue+"<- alreay exists at scope: "+ std::to_string(scope);
					yyerror(lola0);
			}	else if
					( (t->type==var_s || t->type==var_s) && t->isActive==true )	{
						string lola="ERROR:(redefinition) The variable ->" +*yylval.stringValue+"<- alreay exists at scope: "+ std::to_string(scope);
						yyerror(lola);
					}
				else if (t->type==2 ){
					string msg="ERROR:(redefinition) The var_s variable ->" +*yylval.stringValue+"<- alreay exists at scope: "+ std::to_string(scope);
					yyerror(msg);
				}
			}
		}
}
;

funcargs:LEFT_PARENTHESIS idlist  RIGHT_PARENTHESIS {
	cout<<" KAINOURGIO 1\n";
	//enterScopeSpace();
	//resetFunctionLocalOffset();
};

funcbody:block{cout<<" KAINOURGIO 2\n";
	//exitScopeSpace();
	}

funcprefix:FUNCTION fid{cout<<" KAINOURGIO 3\n";
	$$=$2;
	$$->iaddress=currQuad;

	emit(funcstart,(expr*)0,(expr*)0,lvalue_expr($$),-21,yylineno);
	functionLocalStack.push(currScopeOffset());
	//enterScopeSpace();
	//resetFormalArgsOffset();
	}
jafterfunc:{
	$$=currQuad;
	emit(jump,(expr*)0,(expr*)0,(expr*)0,-21,yylineno);
}

funcdef: jafterfunc funcprefix funcargs funcbody{cout<<" KAINOURGIO 4\n";
	//exitScopeSpace();
	$2->totalLocals=functionLocalOffset;
	//functionLocalOffset=functionLocalStack.top();
	//functionLocalStack.pop();
	//functionLocalOffset = OffsetStack.top();
	//OffsetStack.pop();
	$$=$2;
	emit(funcend,(expr*)0,(expr*)0,lvalue_expr($2),-21,yylineno);
	patchLabel($1,currQuad);
	}
;

const: number{$$=$1;}
| STRING{
	//string tmp(*(string*)$1);
	//string *tmp=new string($1->c_str());
	$$=newexpr(conststring_e);

	string* a=new string($1->c_str());
	$$->strConst=*a;

	//string* tmp;
	//strcpy(tmp,$1);
	//$$=newexpr_conststring(tmp);
}
| NIL {
	$$=newexpr(nil_e);
}
| TRUE{
	$$=newexpr(constbool_e);
	$$->boolConst=TRUE;
}
| FALSE{
	$$=newexpr(constbool_e);
	$$->boolConst=FALSE;
}
;

number: INTEGER  {cout<<"apo number se Interger \n";
	int k=(int)$1;
	$$=newexpr(constnum_e);
	$$->numConst=k;
	//cout<<":TO K EINAI : "<<k<<endl;
}
| REAL			 {cout<<"apo number se Real \n";
	double k=(double)$1;
	$$=newexpr(constnum_e);
	$$->numConst=k;
}
;

idlist: ID {
	//resetFormalArgsOffset();
	int scope2 =scope; scope2++;
	SymbolTableEntry* t=lookup_scope(scope2,*yylval.stringValue,(symbol_t)666);

	if(t!=NULL && t->type== libraryfunc_s){
		cout<<"LIBBBBBB FUNCCCCCCCCCCCC";
	}
	if(t!=NULL){
		string lola = "ERROR: Bre8ike local var ->";
		lola+=*yylval.stringValue; lola+="<- pou dhlwnete arg se function idiou scope: ";lola+=std::to_string(scope);
		yyerror(lola);
	}
	if(t==NULL){
		if(!containsLib(*yylval.stringValue)){
		scope++;

		SymbolTableEntry * tmp = insert_var(*yylval.stringValue, var_s);

		tmp->scopespace=currScopeSpace();
		//cout<<"TO CURR OFFSET EINAI "<<currScopeOffset()<<endl;
		tmp->offset=currScopeOffset();
		//resetFormalArgsOffset();

		SymbolTableEntry* func=lookupFunc(scope-1);

			if(func ==NULL)cout<<"einai null auto pou brhka \n";

				if(func!=NULL){
					insertArguments(func->value.funcVal,tmp->value.varVal);
					//printFunc(func->value.funcVal);
				}
		scope--;
		}else{	string lola= "ERROR: libraryfunc_s ->"; lola+=*yylval.stringValue; lola+="<- As Argumnent ";
		yyerror(lola);}

		//enterScopeSpace();//------------------------S
		bes=true;
	}

}_idlist_ {}
| {}
;

_idlist_: COMMA ID {
		scope++;
		SymbolTableEntry * tmp = lookup_scope(scope,*yylval.stringValue,(symbol_t)666);
		SymbolTableEntry* entry;
		string msg;
		if(tmp != NULL){
		msg ="ERROR: bre8ikan arguments me idio onoma ->"+*yylval.stringValue+"<-";
		yyerror(msg);
		}else{
			if(containsLib(*yylval.stringValue)){
			msg= "ERROR: libraryfunc_s ->" + *yylval.stringValue + "<- As Argumnent ";
			yyerror(msg);
			}else{
				if(scopeSpaceCounter % 2 != 0)
					enterScopeSpace();

				entry=insert_var(*yylval.stringValue,var_s);

				inCurrScopeOffset();

				entry->scopespace=currScopeSpace();
				entry->offset=currScopeOffset();

				SymbolTableEntry* func=lookupFunc(scope-1);

				//exitScopeSpace();//------------------------

				if(func != NULL){
				insertArguments(func->value.funcVal,entry->value.varVal);
				//printFunc(func->value.funcVal);
				}
			}
		}
		scope--;
	//enterScopeSpace();//------------------------
	bes=true;

} _idlist_ {}
| {}
;

ifprefix: IF LEFT_PARENTHESIS expr RIGHT_PARENTHESIS{

		emit(if_eq , $3 , newexpr_constbool(1),(expr*)0, currQuad+2,yylineno);

		$$ = currQuad;

		emit(jump, (expr*)0, (expr*)0, (expr*)0,-21,yylineno);
};

elseprefix: ELSE{
	$$ = currQuad;
	emit(jump, (expr*)0, (expr*)0, (expr*)0,-21,yylineno);
};

ifstmt:ifprefix stmt		{cout<<"apo ifstmt se ( expr ) stmt \n";
	patchLabel($1,currQuad);
	$$=$2;
}

|ifprefix stmt elseprefix stmt	{cout<<"apo ifstmt se if ( expr ) stmt Else stmt \n";
	patchLabel($1,$3+1);
	patchLabel($3,currQuad);

	$$ = new stmtStruct();

		if($2!=NULL  ){

			for(auto it = $2->breakList.begin();it!=$2->breakList.end();it++){
				cout<<*it<<endl;
				$$->breakList.push_front(*it);
			}
			for(auto it = $2->continueList.begin();it!=$2->continueList.end();it++){
				cout<<*it<<endl;
				$$->continueList.push_front(*it);
			}
}

if($4!=NULL ){

		for(auto it = $4->breakList.begin();it!=$4->breakList.end();++it){
			cout<<*it<<endl;
			$$->breakList.push_front(*it);
		}
		for(auto it = $4->continueList.begin();it!=$4->continueList.end();it++){
			cout<<*it<<endl;
			$$->continueList.push_front(*it);
		}
}

}
;

loopstart : {++loopcounter;
};

loopend : {
	--loopcounter;
};

loopstmt : loopstart stmt loopend {
	$$ = $2;
};

whilestart:WHILE{	cout<<" WHILESTART SE WHILE "<<endl;
	$$ = currQuad;
};

whilecond: LEFT_PARENTHESIS expr RIGHT_PARENTHESIS  {cout<<"apo whilestmt while ( expr ) stmt \n";
	emit(if_eq,$2,newexpr_constbool(1),(expr*)0,currQuad+2,yylineno);
	$$ = currQuad;
	emit(jump,(expr*)0,(expr*)0,(expr*)0,-21,yylineno);
};

whilestmt:whilestart whilecond loopstmt {	cout<<" whilestart whilecond loopstmt "<<endl;
	emit(jump, (expr*)0,(expr*)0,(expr*)0,$1,yylineno);
	patchLabel($2,currQuad);
	//patchLabel( ,currQuad);
	//patchLabel( ,$1);

	for(auto it = $3->breakList.begin();it!=$3->breakList.end();it++ ){
		patchLabel(*it, currQuad);		
	}
	for(auto it = $3->continueList.begin();it!=$3->continueList.end();it++){
		patchLabel(*it , $1);
	}
}
;

N : {	cout<<" Se N "<<endl;
	$$ = currQuad;
	emit(jump,(expr*)0,(expr*)0,(expr*)0,-21,yylineno);
}
;

M: {cout<<" Se M "<<endl;
	$$ = currQuad;
}
;

forprefix : FOR LEFT_PARENTHESIS elist SEMICOLON M expr SEMICOLON{
	cout<<"APO forprefix SE \n";
	$$ = new forStruct();
	$$->test=$5;
	$$->enter = currQuad;
	emit(if_eq,$6,newexpr_constbool(1),(expr*)0,-21,yylineno);
}
;

forstmt: forprefix N  elist RIGHT_PARENTHESIS N loopstmt N {cout<<"apo forstmt se for ( elist semicolon expr Semicolon elist) stmt \n";
	patchLabel($1->enter,$5+1);
	patchLabel($2,currQuad);
	patchLabel($5,$1->test);
	patchLabel($7,$2+1);

	for(auto it = $6->breakList.begin();it!=$6->breakList.end();it++){
			patchLabel(*it,currQuad);
	}
	for(auto it = $6->continueList.begin();it!=$6->continueList.end();it++){
			patchLabel(*it,$2+1);
	}
	$$=$6;
}
;

returnstmt: RETURN SEMICOLON	{cout<<"apo returnstmt se Return Semicolon \n";
	if(currScopeSpace()!=functionlocal){
		yyerror("Return statement out of function");}
	emit(ret,(expr*)0,(expr*)0,(expr*)0,-21,yylineno);
	}
| RETURN expr SEMICOLON			{cout<<"apo returnstmt se Return expr Semicolon \n";
	if(currScopeSpace()!=functionlocal){
		yyerror("Return statement out of function");}
	emit(ret,$2,(expr*)0,(expr*)0,-21,yylineno);
	}
;

%%
int yyerror(string  yaccProvidedMessage){
//cout<<"error sto line "<<yylineno<<" before token "<<yytext<<endl;
cout<<endl<<yaccProvidedMessage<<" at line "<<yylineno<<" before token: ->"<<yytext<<"<-    <---ERROR "<<endl<<endl;
//exit(-1);
}
	void pray_start(){
		scopeTable =  vector<SymbolTableEntry*>();

		for(int i=0;i<1500;i++){
			scopeTable.push_back(NULL);
		}
		table = create();
	insert_fun("print" ,libraryfunc_s );
	insert_fun("input" ,libraryfunc_s );
	insert_fun("tableindices" ,libraryfunc_s );
	insert_fun("tablelength" ,libraryfunc_s );
	insert_fun("tablecopy" ,libraryfunc_s );
	insert_fun("totalarguments" ,libraryfunc_s );
	insert_fun("argument" ,libraryfunc_s );
	insert_fun("typeof" ,libraryfunc_s );
	insert_fun("strtonum" ,libraryfunc_s);
	insert_fun("sqrt" ,libraryfunc_s );
	insert_fun("cos" ,libraryfunc_s );
	insert_fun("sin" ,libraryfunc_s );
}

void print_table(){
		cout<<"-------------------------||--------------------------------- \n";
		for(auto it = scopeTable.begin();it!=scopeTable.end();it++ ){
		if(*it!=NULL)
				for(; *it!=NULL; (*it)=(*it)->nextscope )	{
				cout<<"Is Active: "<<(*it)->isActive<<" || ";

				if((*it)->type==1)
					cout<<"Scope: "<<(*it)->value.funcVal->scope<<" || ";
				else
					cout<<"Scope: "<<(*it)->value.varVal->scope<<" || ";

				if((*it)->type ==1 ||(*it)->type ==2 ){
				cout<<"Name: "<<(*it)->value.funcVal->name<<" || ";
				cout<<"Line: "<<(*it)->value.funcVal->line<<" || ";
				}
					else{
				cout<<"Name: "<<(*it)->value.varVal->name<<" || ";
				cout<<"Line: "<<(*it)->value.varVal->line<<" || ";
				cout<<"SCOPESPACE: "<<(*it)->scopespace<<" || ";
				if( (*it)->type!=1 && (*it)->type!=2)
					cout<<"OFFSET: "<<(*it)->offset<<" || ";
				}
				switch( (*it)->type){
				case libraryfunc_s:
					cout<<"Type: "<<"libraryfunc_s"<<endl;
					break;
				case var_s:
					cout<<"Type: "<<"var_s"<<endl;
					break;
			/*	case var_s:
					cout<<"Type: "<<"LOCAL"<<endl;
					break;*/
				case programfunc_s:
					cout<<"Type: "<<"programfunc_s || ";
						if( (*it)->value.funcVal->headArgument ==NULL )
								cout<<"No args";
						if( (*it)->value.funcVal->headArgument !=NULL ){
							Variable* tmp= (*it)->value.funcVal->headArgument;
							cout<<"Arguments: ";
							for(;tmp!=NULL;tmp=tmp->nextArgument){
									if(tmp->nextArgument!= NULL)
										cout<<tmp->name<<" , ";
									else
										cout<<tmp->name;
							}
					}
						cout<<endl;
					break;
				//case var_s:
				//cout<<"Type: "<<"var_s "<<endl;
				//break;
				}
			}
		}
	}

int main(int argc, char **argv ){
if(argc>1){
	if(!(yyin = fopen(argv[1],"r") )){
		fprintf(stderr , "Cannot read file %s ",argv[1]);
		return 1;
	}
}
else
yyin =  stdin;
pray_start();
yyparse();
printQuads();
print_table();
generate();
patch_incomplete_jumps();
printInstructions();
WriteBinary();
cout<<"TELOSSSS TO STIBA SIZE EINAI : "<< OffsetStack.size()<<endl;
return 0;
}
