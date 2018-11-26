#include "Phase3.hpp"

extern int scope;
extern int yylineno;
extern unsigned int currQuad;
extern int yyerror(string yaccProvidedMessage);
extern int scope;
extern int yylineno;

typedef enum vmopcode{
	assign_v,add_v,sub_v,mul_v,div_v,mod_v,
	uminus_v,and_v,or_v,not_v,jeq_v,jne_v,
	jle_v,jge_v,jlt_v,jgt_v,call_v,pusharg_v,
	funcenter_v,funcexit_v,
	newtable_v,tablegetelem_v,tablesetelem_v,
	nop_v,jump_v
}vmopcode;

typedef enum vmarg_t{
	label_a,
	global_a,
	formal_a,
	local_a,
	number_a,
	string_a,
	bool_a,
	nil_a,
	userfunc_a,
	libfunc_a,
	retval_a,
	ignore_a
}vmarg_t;

typedef struct vmarg{
	vmarg_t type;
	unsigned val;
	unsigned int line;
}vmarg;

typedef struct instruction{
	vmopcode opcode;
	vmarg result;
	vmarg arg1;
	vmarg arg2;
	unsigned srcLine;
}instruction;

typedef struct userfunc{
	unsigned	address;
	unsigned	localsize;
	string id;
}userfunc;

//stack environment(vector<SymbolTableEntry>* scopetable);
unsigned consts_newstring(string s);
unsigned consts_newnumber(double n);
unsigned libfuncs_newused(string s);
//unsigned userfuncs_newfunc(userfunc* sym);
void make_operand(expr* e,vmarg* arg);
void reset_operand(vmarg* arg);

typedef struct incomplete_jump{
	unsigned instrNo;
	unsigned iaddress;
}incomplete_jump;

void patch_incomplete_jumps();
void add_incomplete_jump(unsigned instrNo , unsigned iaddress);

void generate_arithmetic(vmopcode op,quad* q);
void generate_relational(vmopcode op,quad* q);
void generate_ADD(quad* q);
void generate_SUB(quad* q);
void generate_MUL(quad* q);
void generate_DIV(quad* q);
void generate_MOD(quad* q);
void generate_UMINUS(quad* q);
void generate_NEWTABLE(quad* q);
void generate_TABLEGETELEM(quad* q);
void generate_TABLESETELEM(quad* q);
void generate_ASSIGN(quad* q);
void generate_NOP(quad * p);
void generate_JUMP(quad* q);
void generate_IF_EQ(quad* q);
void generate_IF_NOTEQ(quad* q);
void generate_IF_GREATER(quad* q);
void generate_IF_GREATEREQ(quad* q);
void generate_IF_LESS(quad* q);
void generate_IF_LESSEQ(quad* q);
void generate_NOT(quad* q);
void generate_AND(quad* q);
void generate_OR(quad* q);
void generate_PARAM(quad* q);
void generate_CALL(quad* q);
void generate_GETRETVAL(quad* q);
void generate_FUNCSTART(quad* q);
void generate_RETURN(quad* q);
void generate_FUNCEND(quad* q);
void generate(void);

typedef void (*generator_func_t)(quad* );

void printInstructions();
//void backpatch(list<int> returnList,int i);
void WriteBinary();
