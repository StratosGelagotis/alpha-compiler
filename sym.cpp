#include "sym.hpp"
#define HASH_MULTIPLIER 65599
extern int scope;
vector<SymbolTableEntry*> scopeTable;
extern int yylineno;
SymbolTable *table;

static unsigned int hashfunction(string str)
{
	int  i;
	unsigned int hasnumber = 0;
	for (i = 0; str[i] != '\0'; i++)
		hasnumber = hasnumber * HASH_MULTIPLIER + str[i];
	return hasnumber%500 ;
}
// dhmiourgei to table
SymbolTable * create(){	
	SymbolTableEntry * newEntry ;
	SymbolTable *newTable;
	
	newEntry = new SymbolTableEntry();
	newTable = new SymbolTable();
	
	newTable->total=0;

	for(int i=0;i<500;i++){
			//cout<<i<<endl;
			newTable->hassarray[i]=NULL;		
	}
	return newTable;
}
/*
Variable* createVar(string s){
	Variable* tmp=new Variable();
	tmp->name=s;
	tmp->scope=scope;
	tmp->line=yylineno;
	tmp->nextArgument=NULL;
	return tmp;
}
Function* createFun(string s){
	Function* tmp=new Function();
	tmp->name=s;
	tmp->scope=scope;
	tmp->line=yylineno;
	tmp->headArgument=NULL;
	return tmp;
}
*/

void insert2scopetable(SymbolTableEntry* entry){
	int pos;
			pos=scope;
			if(pos<100){
			entry->nextscope=scopeTable[pos];
			scopeTable[pos]=entry;
	}
}

SymbolTableEntry* insert_var(string name ,enum symbol_t type ){		
	Variable *add =  new Variable();
	add->name=name;
	add->line=yylineno;
	add->scope=scope;
	add->nextArgument=NULL;
	SymbolTableEntry *full = new SymbolTableEntry();
	
	full->value.varVal=add;	
	full->type=type;	
	full->nextlist=NULL;
	full->nextscope=NULL;
	full->isActive=true;
	unsigned int hashnum = hashfunction(name);

	if(table->hassarray[hashnum]==NULL){	
		table->hassarray[hashnum]=full;
	}else{				
		SymbolTableEntry *newEntry = table->hassarray[hashnum];
		while(newEntry->nextlist!=NULL){
			newEntry=newEntry->nextlist;
		}		
		newEntry->nextlist=full;			
	}			
	insert2scopetable(full);	
	return full;
}

SymbolTableEntry * insert_fun(string name ,enum symbol_t type ){		
	//if chech me look up else	
	Function *add =  new Function();
	add->name=name;
	add->line=yylineno;
	add->scope=scope;
	add->headArgument=NULL; 
	
	SymbolTableEntry *full = new SymbolTableEntry();
	full->value.funcVal=add;	
	full->type=type;	
	full->nextlist=NULL;
	full->nextscope=NULL;
	full->isActive=true;
	
	unsigned int hashnum = hashfunction(name);

	if(table->hassarray[hashnum]==NULL){	
		table->hassarray[hashnum]=full;
		//table->total++;				
	}else{				
		SymbolTableEntry *newEntry = table->hassarray[hashnum];
		while(newEntry->nextlist!=NULL){
			newEntry=newEntry->nextlist;
		}		
		newEntry->nextlist=full;	
	}
	insert2scopetable(full);		
	return full;	
}

void hide(int scope){
	SymbolTableEntry* tmp=scopeTable[scope];
	for(;tmp!=NULL;tmp=tmp->nextscope)	
		tmp->isActive=false;
}

SymbolTableEntry *lookup_scope(int scope ,string name , enum symbol_t type){	
		if(scope>=scopeTable.size()){
			return NULL;
		}else {
			SymbolTableEntry* tmp=scopeTable[scope];
			for(;tmp!=NULL;tmp=tmp->nextscope)	
				if(tmp->isActive==true && (tmp->type==type || type==666) && tmp->value.varVal->name == name )
					return tmp;
	}				
			return NULL;		
}

SymbolTableEntry * lookup_all(string name, enum symbol_t type ){	
		for(int i = scope ; i>=0 ; i--){
			SymbolTableEntry *tmp= lookup_scope(i,name,type);
			if(tmp!=NULL)
				return tmp;
			}
		return NULL;
}

SymbolTableEntry* lookup_name(string name,int scope){
		if(scope>=scopeTable.size()){
			return NULL;
		}else{
			SymbolTableEntry* tmp = scopeTable[scope];
			while(tmp!=NULL){
				if(tmp->isActive==true && tmp->value.varVal->name==name)
					return tmp;
				tmp=tmp->nextscope;
			}						
		}
		return NULL;
	}

/*
void insertArguments(Function* fun,Variable* var){
	if(fun->headArgument==NULL)fun->headArgument=var;
	else{
		Variable* tmp=fun->headArgument;
		for(;tmp->nextArgument!=NULL;tmp=tmp->nextArgument);
		if(tmp->nextArgument==NULL){
			tmp->nextArgument=var;
		}
	}
}
*/

void insertArguments(Function* fun,Variable* var){
	if(fun->headArgument==NULL)
		fun->headArgument=var;
	else{
	//	cout<<"AEKKKKKKKK"<<endl;
		//cout<<fun->name;
		Variable* tmp=fun->headArgument;
		//cout<<"lola";

		for(;tmp->nextArgument!=NULL;tmp=tmp->nextArgument);
			if(tmp->nextArgument==NULL){
				tmp->nextArgument=var;
		}
	}
}
	
bool containsLib(string name){	
	vector<string> v = { "print","input","objectmemberkeys","objecttotalmembers",
		"objectcopy","totalarguments","argument","typeof","strtonum","sqrt","cos","sin"};
			
	auto it= std::find(v.begin(),v.end(),name );
	
	if(it != v.end())
		return true;
	else 
		return false;	
}

SymbolTableEntry* lookupFunc(int scope){
	int pos;
	pos=scope;
	if(scopeTable[pos]->type == 3){
		return scopeTable[pos];}
	else 
		return NULL;
}

void printVar(Variable* var){
	cout<<"Var name: "<<var->name<<" || ";
	cout<<"Var scope: "<<var->scope<<" || ";
	cout<<"Var line: "<<var->line<<endl;
}

void printFunc(Function* fun){
	cout<<"Func name: "<<fun->name<<" || ";
	cout<<"Func scope: "<<fun->scope<<" || ";
	cout<<"Func Line: "<<fun->line<<endl;
	if(fun->headArgument!=NULL){
	Variable* tmp=fun->headArgument;
	for(;tmp!=NULL;tmp=tmp->nextArgument)	printVar(tmp);
	}
	cout<<"=====================\n";
}

bool checkVisibility(SymbolTableEntry* t){	

	if (t==NULL || (t->type==libraryfunc_s || t->type==programfunc_s)  || t->scopespace==formalarg     )	
		return true;
	
	int k=scope;
	
	SymbolTableEntry* tmp=NULL;
	
	for(k=t->value.varVal->scope;k<=scope;k++){		
		tmp=scopeTable[k];
		if(tmp!=NULL && tmp->type==programfunc_s)	
			return false;
		}
	return true;
	}
