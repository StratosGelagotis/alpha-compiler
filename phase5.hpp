#include "phase4.hpp"

#define AVM_TABLE_HASHSIZE 211
#define AVM_WIPEOUT(m) memset(&(m),0,sizeof(m))
#define AVM_MAX_INSTRUCTIONS (unsigned)jump_v
#define AVM_NUMACTUALS_OFFSET 4

double consts_getnumber (unsigned index);
string* consts_getstring (unsigned index);
string* libfuncs_getused (unsigned index);

typedef void (*execute_func_t)(instruction*);

typedef void (*library_func_t) (void);

typedef struct avm_table avm_table;
typedef struct avm_table_bucket avm_table_bucket;

typedef double (*arithmetic_func_t) (double x , double y);


typedef enum avm_memcell_t {

	number_m,
	string_m,
	bool_m,
	table_m,
	userfunc_m,
	libfunc_m,
	nil_m,
	undef_m
}avm_memcell_t;

typedef struct avm_memcell{
	avm_memcell_t type;

	union{
		double numVal;
		string* strVal;
		//unsigned char boolVal;
		bool boolVal;
		avm_table *tableVal;
		unsigned funcVal;
		string* libfuncVal;
	}data;

}avm_memcell;

 struct avm_table_bucket{
	avm_memcell key;
	avm_memcell value;
	avm_table_bucket *next;
};

 struct avm_table{
	unsigned refCounter;
	avm_table_bucket* strIndexed[AVM_TABLE_HASHSIZE];
	avm_table_bucket* numIndexed[AVM_TABLE_HASHSIZE];
	unsigned total;
};

avm_memcell* avm_tablegetelem(avm_table* table,avm_memcell* index);

void avm_tablesetelem(avm_table* table,avm_memcell* index,avm_memcell* content);

void avm_memcellclear( avm_memcell* m);

avm_memcell * avm_translate_operand(vmarg * arg , avm_memcell *reg);

string avm_tostring(avm_memcell* m);
void avm_initialize();

void avm_initialize();

void avm_registerlibfunc(string id, library_func_t addr);