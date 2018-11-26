
#include "header.hpp"

typedef struct Variable {	
	string name;
	unsigned int scope;
	unsigned int line;
	Variable *nextArgument;
} Variable;

typedef enum scopespace_t{
	programvar,
	functionlocal,
	formalarg
	}scopespace_t;

typedef enum symbol_t {var_s , programfunc_s , libraryfunc_s}
symbol_t;
	
typedef struct Function{	
	//const char * name;
	string name;
	//list of argumetns
	Variable* headArgument;  
	 int scope;
	unsigned int line;
} Function;
/*
enum SymbolTableType{
	GLOBAL,LOCAL2,FORMAL,USERFUNC,LIBFUNC
};
*/
typedef struct SymbolTableEntry{
	bool isActive;
	int iaddress;
	int totalLocals;
	symbol_t type;
	unsigned offset;
	unsigned taddress;
	scopespace_t scopespace;	
	list <int> returnList;
	union{
		Variable *varVal;
		Function *funcVal;
	}value;
	
	struct SymbolTableEntry *nextlist;
	struct SymbolTableEntry *nextscope;
} SymbolTableEntry;

typedef struct SymbolTable{         //   the symtable struct			
		unsigned int total;
		SymbolTableEntry  * hassarray[500];	
} SymbolTable;

SymbolTable * create();      // creates a new hashtable(empty)
bool isLibFunc(string name);
void insert2scopetable(SymbolTableEntry* entry);
void hide(int scope);
SymbolTableEntry * lookup_scope(int scope ,string name , enum symbol_t type);
SymbolTableEntry * lookup_all(string name, enum symbol_t type );
SymbolTableEntry * lookup_name(string name,int scope);
SymbolTableEntry* insert_var(string name ,enum symbol_t type );
SymbolTableEntry* insert_fun(string name ,enum symbol_t type );
extern vector<SymbolTableEntry*> scopeTable;
extern SymbolTable * table;
void insertArguments(Function* fun,Variable* var);
bool containsLib(string name);
SymbolTableEntry* lookupFunc(int scope);
void printVar(Variable* var);
void printFunc(Function* fun);
bool checkVisibility(SymbolTableEntry* t);
