%{
	#include "header.hpp"
	#include "delete2.tab.h"
	int i,j,nested=0;
%}
%option yylineno
%option noyywrap
%option case-insensitive
%option header-file="./Scanner.h"
%x COMMENT

space			[\r\n \t\v]+
id				[a-zA-Z][a-zA-Z_0-9]*

integer		   	[0-9]*
real			[0-9]+\.[0-9]*

string   		"\""

if				"if"
int 			"int"
else			"else"
while			"while"
for				"for"
function		"function"
return			"return"
break			"break"
continue		"continue"
and				"and"
not				"not"
or 				"or"
local			"local"
true			"true"
false			"false"
nil				"nil"
asgn			"asgn"
add				"add"
sub				"sub"
mul				"mul"
div				"div"
modulo			"modulo"
equal			"equal"
nequal			"nequal"
plusplus		"plusplus"
minusminus		"minusminus"
gt				"gt"
lt				"lt"
ge				"ge"
le				"le"
comments		"comments"

double_anwkatw	"double_anwkatw"

left_bracket	"left_bracket"
right_bracket	"right_bracket"
right_squere_bracket "right_squere_bracket"
left_squere_bracket  "left_squere_bracket"
left_parenthesis	"left_parenthesis"
right_parenthesis	"right_parenthesis"
semicolon			"semicolon"
comma				"comma"
colon				"colon"
point 				"point"
double_point		"double_point"
underscore			"underscore"
nl					"nl"
%%

"/*"            {++nested; BEGIN(COMMENT); }
"//".*			
<COMMENT>[^*/]* 	/* Eat non-comment delimiters */
<COMMENT>"/*"   ++nested;
<COMMENT>"*/"   if (--nested == 0) BEGIN(INITIAL);
<COMMENT><<EOF>> {cout<<"ERROR: Unclosed comment\n"; exit(-5);}
<COMMENT>[*/]    

{space} {}

"::"    {return DOUBLE_ANWKATW;}
"{"		{return LEFT_BRACKET;}
"}"		{return RIGHT_BRACKET;}
"]"		{return RIGHT_SQUERE_BRACKET;}
"["		{return LEFT_SQUERE_BRACKET;}
"("		{return LEFT_PARENTHESIS;}
")"		{return RIGHT_PARENTHESIS;}
";"		{return SEMICOLON;}
","		{return COMMA;}
":"     {return COLON;}
"."		{return POINT;}
".."	{return DOUBLE_POINT;}
 
"="		{return ASGN;}		
"+"		{return PLUS;}
"-"		{return MINUS;}
"*"		{return MUL;}
"/"		{return DIV;}
"%"		{return MODULO;}
"=="	{return EQUAL;}
"!="	{return NEQUAL;}
"++"	{return PLUSPLUS;}
"--"	{return MINUSMINUS;}
">"		{return GT;}
"<"		{return LT;}
">="	{return GE;}
"<="	{return LE;}

{real}		{yylval.realValue = atof(yytext); return REAL; }
{integer}	{yylval.intValue = atoi(yytext); return INTEGER;}
{if}		{return IF;}
{else}		{return ELSE;}
{while}		{return WHILE;}
{for}		{return	FOR;}
{function}	{return	FUNCTION;}
{return}	{return	RETURN;}
{break}		{return	BREAK;}
{continue}	{return	CONTINUE;}
{and}		{return	AND;}
{not}		{return	NOT;}
{or}		{return	OR;}
{local}		{return	LOCAL;}
{true}		{return	TRUE;}
{false}		{return	FALSE;}
{nil}		{return	NIL;}
{id}		{ yylval.stringValue = new string(yytext);return ID;}

{string}	{

	int tmp=yyinput();
	string s;	
	while(TRUE){
		if(tmp==EOF)
		{cout<<"String doesn't close at line "<<yylineno<<endl;
			break;
			}
		if(tmp == '\\' || tmp == '"' ){
					if(tmp=='\\'){
						
						tmp = yyinput();						
						
						if(tmp=='\\'){
							s+='\\';
						}else if(tmp=='n'){
							s+='\n';
						}else if(tmp=='t'){
							s+='\t';
						}else if(tmp=='"'){
							s+='"';
						}else{
							s+='\\';
							s+=tmp;
						}					
					}else{
						s+='\0';
						s.copy(yytext,s.length(),0);
						/*
						size_t copy (char* s, size_t len, size_t pos = 0) const;
						strcpy(yytext,(char *)&string[0]);
						*/
						yylval.stringValue = new string(s);
						return STRING;
					}							
				}else {
					s+=tmp;				
				}									
				tmp=yyinput();					
			}
		//return  yy error====================
}
.			{}
<<EOF>>		{return 0;}

%%
/*
vector<token*> tokens_list ;

void display_vector(const vector<token*> &tokens_list)
{
	string s;
    std::copy(tokens_list.begin(), tokens_list.end(),
    std::ostream_iterator<token*>(cout, " "));
	
	cout<<endl;
}

 struct token * create_token (string category){
					
		static int token_num=0;

		string tmp_string=category;
			
		string tmp_key(yytext);
		
		token *tmp = new token();
		
		tmp->line = yylineno;
		tmp->token_number=++token_num;
		tmp->category=tmp_string;
		tmp->key=tmp_key;
	
		return tmp;			
	}

int alpha_yylex (void* ylval) {
	
		struct token *tmp= NULL; 

		int index =  yylex();
		while( index !=0){
		
		switch(index){
		
		case IF:
		tmp = create_token("keyword");
		tokens_list.push_back(tmp);
		break;
		
		case INT:
		tmp = create_token("keyword");
		//cout<<yyinput();
		tokens_list.push_back(tmp);
		break;
				
		case NL:
		if(yylineno>1)
		yylineno--;
		yylineno++;
		break;
				
		case RIGHT_SQUERE_BRACKET:
		tmp =  create_token("stijhs ");
		tokens_list.push_back(tmp);
		break;
		
		case LEFT_PARENTHESIS:
		tmp =  create_token("stijhs ");
		tokens_list.push_back(tmp);
		break;
		
		case COMMA:
		tmp =  create_token("stijhs ");
		tokens_list.push_back(tmp);
		break;
			
		case SEMICOLON:
		tmp =  create_token("stijhs ");
		tokens_list.push_back(tmp);
		break;
		
		case COLON:
		tmp =  create_token("stijhs ");
		tokens_list.push_back(tmp);
		break;
	
		case DOUBLE_POINT:
		tmp =  create_token("stijhs ");
		tokens_list.push_back(tmp);
		break;
			
		case POINT:
		tmp =  create_token("stijhs ");
		tokens_list.push_back(tmp);
		break;
		
		case NOT:
		tmp = create_token("keyword");
		tokens_list.push_back(tmp);
		break;
		
		case OR:
		tmp = create_token("keyword");
		tokens_list.push_back(tmp);
		break;
		
		case AND:
		tmp = create_token("keyword");
		tokens_list.push_back(tmp);
		break;
		
		case RIGHT_PARENTHESIS:
		tmp =  create_token("stijhs ");
		tokens_list.push_back(tmp);
		break;
		
		case LEFT_SQUERE_BRACKET:
		tmp =  create_token("stijhs ");
		tokens_list.push_back(tmp);
		break;
			
		case  LEFT_BRACKET:
		tmp =  create_token("stijhs ");
		tokens_list.push_back(tmp);
		break;
		
		case RIGHT_BRACKET:
		tmp =  create_token("stijhs ");
		tokens_list.push_back(tmp);
		break;
		
		case DOUBLE_ANWKATW:
		tmp =  create_token("stijhs ");
		tokens_list.push_back(tmp);
		break;
	
		case WHILE:
		tmp = create_token("keyword");
		tokens_list.push_back(tmp);
		break;
		
		case ELSE:
		tmp = create_token("keyword");
		tokens_list.push_back(tmp);
		break;
				
		case COMMENTS:
		tmp =  create_token("COMMENTS");
		break;
			
		case FOR:
		tmp = create_token("keyword");
		tokens_list.push_back(tmp);
		break;
		
		case FUNCTION:
		tmp = create_token("keyword");
		tokens_list.push_back(tmp);
		break;
		
		case RETURN:
		tmp = create_token("keyword");
		tokens_list.push_back(tmp);
		break;
		
		case BREAK:
		tmp = create_token("keyword");
		tokens_list.push_back(tmp);
		break;
		
		case CONTINUE:
		tmp = create_token("keyword");
		tokens_list.push_back(tmp);
		break;
		
		case NIL:
		tmp = create_token("keyword");
		tokens_list.push_back(tmp);
		break;
		
		case LOCAL:
		tmp = create_token("keyword");
		tokens_list.push_back(tmp);
		break;
		
		case TRUE:
		tmp = create_token("keyword");
		tokens_list.push_back(tmp);
		break;
		
		case FALSE:
		tmp = create_token("keyword");
		tokens_list.push_back(tmp);
		break;
		
		case LT:
		tmp = create_token("comparator");
		tokens_list.push_back(tmp);
		break;
		
		case GT:
		tmp = create_token("comparator");
		tokens_list.push_back(tmp);
		break;
		
		case LE:
		tmp = create_token("comparator");
		tokens_list.push_back(tmp);
		break;
		
		case GE:
		tmp = create_token("comparator");
		tokens_list.push_back(tmp);
		break;
		
		case PLUSPLUS:
		tmp = create_token("comparator");
		tokens_list.push_back(tmp);
		break;
		
		case MINUSMINUS:
		tmp = create_token("comparator");
		tokens_list.push_back(tmp);
		break;
		
		case EQUAL:
		tmp = create_token("comparator");
		tokens_list.push_back(tmp);
		break;
		
		case NEQUAL:
		tmp = create_token("comparator");
		tokens_list.push_back(tmp);
		break;
		
		case ASGN:
		tmp = create_token("operator");
		tokens_list.push_back(tmp);
		break;
		
		case ADD:
		tmp = create_token("operator");
		tokens_list.push_back(tmp);
		break;
		
		case SUB:
		tmp = create_token("operator");
		tokens_list.push_back(tmp);
		break;
		
		case MUL:
		tmp = create_token("operator");
		tokens_list.push_back(tmp);
		break;
		
		case DIV:
		tmp = create_token("operator");
		tokens_list.push_back(tmp);
		break;
		
		case MODULO:
		tmp = create_token("operator");
		tokens_list.push_back(tmp);
		break;
			
		case STRING:
		tmp=create_token("string");
		tokens_list.push_back(tmp);
		break;
		
		case ID:
		tmp =  create_token("ident");
		tokens_list.push_back(tmp);
		break;

		case INTEGER:
		tmp =  create_token("INTCONST");
		tokens_list.push_back(tmp);
		break;
			
		case REAL:
		tmp =  create_token("REALCONST");
		tokens_list.push_back(tmp);
		break;
		
		case SPACE:
		//tmp =  create_token("for_delete");
		//tokens_list.push_back(tmp);
		cout<<"bike keno\n";
		break;
		
		default:		
		cout<<index<<endl;
		cout<<"Error unknown char "<< (char)yyinput()<<" at line  " <<yylineno<<endl;	
		exit(-1);
		break;
	
		}//ths switch
	index=yylex();
	}  // this while
}
int main(int argc, char **argv ){

if(argc>1){
	
	if(!(yyin = fopen(argv[1],"r") )){	
		fprintf(stderr , "Cannot read file %s ",argv[1]);
		return 1;	
	}
}

else 
	yyin = stdin;

	alpha_yylex(NULL);
		
	for(auto it = tokens_list.begin(); it != tokens_list.end();it++){	
		cout<<(*it)->line<<":"<<" #"<<(*it)->token_number<<"  "<<(*it)->key<<" "<<(*it)-> category<<"   \n";
	}
}
*/
