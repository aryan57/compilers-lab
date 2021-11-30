
#ifndef _TRANSLATOR_H
#define _TRANSLATOR_H

#include <bits/stdc++.h>

extern  char* yytext;
extern  int yyparse();

using namespace std;


//Class Declarations


class sym;
class label; 
class symtable;                                                                                                                                        
     
class quad;                                                                       
class quadArray;

class basicType;                                                                        
class symboltype;                                                                          
class Expression;  
                                                                       

typedef sym s;
typedef symboltype symtyp;
typedef Expression* Exps;


// external global variables

// current Symbol Table
extern symtable* ST;                
// Global Symbol Table                                                       
extern symtable* globalST;      
// Parent of the current Symbol Table                                                           
extern symtable* parST;                  
// latest encountered symbol                                                  
extern s* currSymbolPtr;                                                                  
extern quadArray Q;                                                                        
extern basicType bt;         
// count of nested tables                                                             
extern long long int table_count;                                                          
extern bool debug_on;                                                                      
extern string loop_name;             
// table to store the labels                                                      
extern vector<label>label_table;          

//  basic type

class basicType 
{                                                                                            
    public:
        vector<int> size;
        vector<string> type;                                                                 
                                                                           
        void addType(string ,int );
};                                                 


// label symbol 

class label                                                                                
{
    public:
        int addr;                                                                          
        list<int> nextlist; 
        string name;                                                                       
                                                                       

        label(string _name, int _addr = -1);                                               
};


// Structure of any element of the symbol table

class sym 
{                                                                                          
    public:
        int size;                                                                          
        int offset; 
        string name;                                                                       
        symboltype *type;                                                                                                                                         
        symtable* nested;        
        // initial value if given                                                          
        string val;         

        sym* update(symboltype*);                                                               
          
        sym (string , string t="int", symboltype* ptr = NULL, int width = 0);              
                                                                  
};

//      symbol type class

class symboltype 
{                                                                                           
    public:
        string type;              
        // size of Array if found else 1 by default                                                          
        int width;                                                                          
        symboltype* arrtype;                                                               
        
        symboltype(string , symboltype* ptr = NULL, int width = 1);                         
};


// The actual Symbol Table

class symtable 
{                                                                                           
    public:
        string name;           
        //count of temps                                                            
        int count;                                                                          
        list<sym> table;                                                                    
        symtable* parent;                                                                   
        
        symtable (string name="NULL");                                                      
        s* lookup (string);                                                                
        void print();                                                                      
        void update();                                                                      
};



//  structure of quad element

class quad 
{                                                                                            
    public:
        string res;                                                                         
        string op;                                                                           
        string arg1;                                                                         
        string arg2;                                                                           

        //constructors                  
        quad (string , string , string op = "=", string arg2 = "");         
        quad (string , int , string op = "=", string arg2 = "");                
        quad (string , float , string op = "=", string arg2 = "");  

	    //for printing
        void print();	
        void type1();                                                                       
        void type2();                                                                        

		
};

// Defination of the quad array type

class quadArray 
{                                                                                            
    public:
        vector<quad> Array;                                                                 
        void print();                                                                        
};





//  expression type

struct Expression {
    // pointer to the symbol table entry
    s* loc;                                                                                  
    string type;                                                                             
    list<int> truelist;                                                                     
    list<int> falselist;                                                                   
    list<int> nextlist;                                                                      
};


//  array type

struct Array {
    //either ptr or array
    string atype;        
    // Location used to compute address of Array                                                                    
    s* loc;      
     // pointer to the symbol table entry                                                                            
    s* Array;                                                                               
    symboltype* type;                                                                        
};

struct Statement {
    list<int> nextlist;                                                                     
};


//Type checking and conversion
string convertIntToString(int);                                                              
string convertFloatToString(float);                                                          
Exps convertIntToBool(Exps);                                                                 
Exps convertBoolToInt(Exps);  

//    Overloaded emit functions

void emit(string , string , string arg1="", string arg2 = "");  
void emit(string , string , int, string arg2 = "");		  
void emit(string , string , float , string arg2 = "");   


//generates a temporary variable in a sybol table and return a ponter to it

s* gentemp (symboltype* , string init = "");


//  Backpatching

void backpatch (list <int> , int );                                                           
list<int> makelist (int );                                                                   
list<int> merge (list<int> &l1, list <int> &l2);                                             


//  Other helper functions required for TAC generation

string printType(symboltype *);                                                              
void generateSpaces(int);


label* find_label(string name);

                                                               

// type conversion
s* convertType(sym*, string);            
//calculate size of symbol type                                                    
int computeSize (symboltype *);                                                             
// change current table
void changeTable (symtable* );      

bool compareSymbolType(sym* &s1, sym* &s2);                                                 
bool compareSymbolType(symboltype*, symboltype*);                                          

int nextinstr();                                                                             




#endif