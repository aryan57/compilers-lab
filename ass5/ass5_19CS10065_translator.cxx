#include <bits/stdc++.h>

#include "ass5_19CS10065_translator.h"

using namespace std;
                                                                         

symboltype::symboltype(string type,symboltype* arrtype,int width)                                 
{
    (*this).type   = type;
    (*this).width  = width;
    (*this).arrtype= arrtype;
}


sym::sym(string name, string t, symboltype* arrtype, int width) 
{
    this->name = name;
    // Generate type of symbol
    type = new symboltype(t,arrtype,width);         
    // find the size from the type                                               
    size = computeSize(type);                                                                      
    offset = 0;                                                                                    
    val = "-";                                                                                     
    nested = NULL;                                                                                 
}

quad::quad(string res,string arg1,string op,string arg2)
{
    (*this).op=op;
    (*this).arg1=arg1;
    (*this).arg2=arg2;
    (*this).res=res;
}


quad::quad(string res,int arg1,string op,string arg2)
{   
    (*this).op=op;
    (*this).arg1=convertIntToString(arg1);
    (*this).arg2=arg2;
    (*this).res=res;    
}


quad::quad(string res,float arg1,string op,string arg2)
{
    (*this).op=op;
    (*this).arg1=convertFloatToString(arg1);
    (*this).arg2=arg2;
    (*this).res=res;
}

void quad::print() 
{


    int next_instr=0;   
    if(op=="+") (*this).type1();
    else if(op=="-") (*this).type1();
    else if(op=="*") (*this).type1();
    else if(op=="/") (*this).type1();
    else if(op=="%") (*this).type1();
    else if(op=="|") (*this).type1();
    else if(op=="^") (*this).type1();
    else if(op=="&") (*this).type1();



    else if(op=="==") (*this).type2();
    else if(op=="!=") (*this).type2();
    else if(op=="<=") (*this).type2();
    else if(op=="<") (*this).type2();
    else if(op==">") (*this).type2();
    else if(op==">=") (*this).type2();
    else if(op=="goto") std::cout<<"goto "<<res;



    else if(op==">>") (*this).type1();
    else if(op=="<<") (*this).type1();


    else if(op=="=") std::cout<<res<<" = "<<arg1 ;  



    else if(op=="=&") std::cout<<res<<" = &"<<arg1;
    else if(op=="=*") std::cout<<res<<" = *"<<arg1;
    else if(op=="*=") std::cout<<"*"<<res<<" = "<<arg1;
    else if(op=="uminus") std::cout<<res<<" = -"<<arg1;
    else if(op=="~") std::cout<<res<<" = ~"<<arg1;
    else if(op=="!") std::cout<<res<<" = !"<<arg1;


    else if(op=="=[]") std::cout<<res<<" = "<<arg1<<"["<<arg2<<"]";
    else if(op=="[]=") std::cout<<res<<"["<<arg1<<"]"<<" = "<< arg2;
    else if(op=="return") std::cout<<"return "<<res;
    else if(op=="param") std::cout<<"param "<<res;
    else if(op=="call") std::cout<<res<<" = "<<"call "<<arg1<<", "<<arg2;
    else if(op=="label") std::cout<<res<<": ";
    else std::cout<<"Can't find the operator"<<op;      
    std::cout<<std::endl;
}

void quad::type1()                                                                           
{
    std::cout<<res<<" = "<<arg1<<" "<<op<<" "<<arg2;    
}

void quad::type2()                                                                               
{
    std::cout<<"if "<<arg1<< " "<<op<<" "<<arg2<<" goto "<<res; 
}


void basicType::addType(string t, int s)                                                             
{
    type.push_back(t);  
    size.push_back(s);
}

// Quad Array
quadArray Q;      
// Points to current symbol table                                                                                 
symtable* ST;                                                                                      
basicType bt;                                                                                      
bool debug_on;                                                                                     
string var_type;                                                                                   
symtable* globalST;                                                                                
symtable* parST;                                                                                   
sym* currSymbolPtr;                                                                                
long long int table_count;                                                                         
string loop_name;                                                                                  
vector<label>label_table; 

sym* sym::update(symboltype* t) 
{
    type=t;                                                                                        
    (*this).size=computeSize(t);                                                                   
    return this;                                                                                   
}


label::label(string _name, int _addr):name(_name),addr(_addr){}


symtable::symtable(string name)                                                                   
{
    (*this).name=name;                                                                             
    count=0;                                                                                      
}

sym* symtable::lookup(string name)                                                
{
    sym* symbol;
    list<sym>::iterator it;                                                                        
    it=table.begin();                                                                              
    while(it!=table.end()) 
    {
        if(it->name==name) 
            return &(*it);                                                                         
        it++;                                                                                      
    }

    sym *ptr = nullptr;
    if(this->parent)ptr = this->parent->lookup(name);
    if(ST == this and !ptr){
        symbol = new sym(name);
        table.push_back(*symbol);                                                                  
        return &table.back();                                                                     
    } else if(ptr) return ptr;
    return nullptr;
}

void symtable::update()                                                                           
{
    list<symtable*> tb;                                                                           
    int off;
    list<sym>::iterator it;                                                                        
    it=table.begin();
    while(it!=table.end()) 
    {
        if(it==table.begin()) 
        {
            it->offset=0;                                                                           
            off=it->size;
        }
        else 
        {
            it->offset=off;
            off=it->offset+it->size;                                                                
        }
        if(it->nested!=NULL) 
            tb.push_back(it->nested);
        it++;
    }

    list<symtable*>::iterator it1;                                                                  
    it1=tb.begin();
    while(it1 !=tb.end())                                                                            
    {
        (*it1)->update();
        it1++;
    }
}


void quadArray::print()                                                                               
{

    std::cout<<"THREE ADDRESS CODE : "<<std::endl;                                                       
    for(int i=0;i<60;i++) std::cout<<"**";
    std::cout<<std::endl;    
    
    int j=0;
    vector<quad>::iterator it;                                                                        
    it=Array.begin();
    while(it!=Array.end()) 
    {
        if(it->op=="label")                                                                     
        {
            std::cout<<std::endl<<j<<": ";
            it->print();
        }
        else {                                                                                          
            std::cout<<j<<": ";
            generateSpaces(4);
            it->print();
        }
        it++;j++;
    }
    for(int i=0;i<65;i++) std::cout<<"**";                                                             
    std::cout<<std::endl;
}



void emit(string op, string res, string arg1, string arg2) 
{
	quad *q1= new quad(res,arg1,op,arg2);
	Q.Array.push_back(*q1);
}

void emit(string op, string res, int arg1, string arg2) 
{
    quad *q2= new quad(res,arg1,op,arg2);
    Q.Array.push_back(*q2);
}

void emit(string op, string res, float arg1, string arg2) 
{
    quad *q3= new quad(res,arg1,op,arg2);
    Q.Array.push_back(*q3);
}


sym* gentemp(symboltype* t, string str_new) 
{                                                                                                      
    string tmp_name = "t"+convertIntToString(ST->count++);                                              
    sym* s = new sym(tmp_name);
    (*s).type = t;
    (*s).size=computeSize(t);                                                                          
    (*s).val = str_new;
    ST->table.push_back(*s);                                                                            
    return &ST->table.back();
}


label* find_label(string _name){
    for(vector<label>::iterator it=label_table.begin(); it!=label_table.end(); it++){
        if(it->name==_name)return &(*it);
    }
    return nullptr;
}


void backpatch(list<int> list1,int addr)                                                               
{
    string str=convertIntToString(addr);                                                                
    list<int>::iterator it;
    it=list1.begin();
    
    while( it!=list1.end()) 
    {
        Q.Array[*it].res=str;                                                                          
        it++;
    }
}

list<int> makelist(int init) 
{
    list<int> newlist(1,init);                                                                          
    return newlist;                                                                                     
}

list<int> merge(list<int> &a,list<int> &b)
{
    a.merge(b);                                                                                        
    return a;                                                                                           
}


string convertIntToString(int a)     
{
    return to_string(a);
}

string convertFloatToString(float x)                                                                    
{
    std::ostringstream buff;
    buff<<x;
    return buff.str();
}

Expression* convertBoolToInt(Expression* e)                                                           
{	
	if(e->type=="bool") 
    {
        e->loc=gentemp(new symboltype("int"));                                                        
        backpatch(e->truelist,nextinstr());
        emit("=",e->loc->name,"true");
        int p=nextinstr()+1;
        string str=convertIntToString(p);
        emit("goto",str);
        backpatch(e->falselist,nextinstr());
        emit("=",e->loc->name,"false");
    }
    return e;
}

Expression* convertIntToBool(Expression* e)                                                          
{
    if(e->type!="bool")                
    {
        e->falselist=makelist(nextinstr());                                                             
        emit("==","",e->loc->name,"0");                                                                 
        e->truelist=makelist(nextinstr());                                                              
        emit("goto","");
    }
    return e;
}

sym* convertType(sym* s, string rettype)                                                                
{
	sym* temp=gentemp(new symboltype(rettype));	
    if((*s).type->type=="float")                                                                        
    {
        if(rettype=="int")                                                                              
        {
            emit("=",temp->name,"float2int("+(*s).name+")");
            return temp;
        }
        else if(rettype=="char")                                                                       
        {
            emit("=",temp->name,"float2char("+(*s).name+")");
            return temp;
        }
        return s;
    }
    else if((*s).type->type=="int")                                                                    
    {
        if(rettype=="float")                                                                          
        {
            emit("=",temp->name,"int2float("+(*s).name+")");
            return temp;
        }
        else if(rettype=="char")                                                                        
        {
            emit("=",temp->name,"int2char("+(*s).name+")");
            return temp;
        }
        return s;
    }
    else if((*s).type->type=="char")                                                                   
    {
        if(rettype=="int")                                                                             
        {
            emit("=",temp->name,"char2int("+(*s).name+")");
            return temp;
        }
        if(rettype=="double")                                                                           
        {
            emit("=",temp->name,"char2double("+(*s).name+")");
            return temp;
        }
        return s;
    }
    return s;
}

void changeTable(symtable* newtable)                                                                   
{
    ST = newtable;
} 

bool compareSymbolType(sym*& s1,sym*& s2)                                                              
{
    symboltype* type1=s1->type;                                                                        
    symboltype* type2=s2->type;                                                                         
    int flag=0;
    
    if(compareSymbolType(type1,type2)) flag=1;                                                          
    else if(s1=convertType(s1,type2->type)) flag=1;                                                     
    else if(s2=convertType(s2,type1->type)) flag=1;                                                     
    
    if(flag)return true;                                                                               
    else return false;                                                                                  
}

bool compareSymbolType(symboltype* t1,symboltype* t2)                                                   
{
    int flag=0;
    if(t1==NULL && t2==NULL) flag=1;                                                                  
    else if(t1==NULL || t2==NULL || t1->type!=t2->type) flag=2;                                        
    
    if(flag==1) return true;
    else if(flag==2) return false;
    else return compareSymbolType(t1->arrtype,t2->arrtype);                                            
}



void generateSpaces(int n)                                                                              
{
    while(n--) std::cout<<" ";
}

int nextinstr() 
{
    return Q.Array.size();                                                                              
}

int computeSize(symboltype* t)                                                                          
{
    if(t->type.compare("void")==0) return bt.size[1];
    else if(t->type.compare("char")==0) return bt.size[2];
    else if(t->type.compare("int")==0) return bt.size[3];
    else if(t->type.compare("float")==0) return bt.size[4];
    else if(t->type.compare("ptr")==0) return bt.size[5];
    else if(t->type.compare("func")==0) return bt.size[6];
    else if(t->type.compare("arr")==0) return t->width*computeSize(t->arrtype);                         
    else return -1;
}

string printType(symboltype* t)                                                                         
{
    if(t==NULL) return bt.type[0];
    if(t->type.compare("void")==0)	return bt.type[1];
    else if(t->type.compare("char")==0) return bt.type[2];
    else if(t->type.compare("int")==0) return bt.type[3];
    else if(t->type.compare("float")==0) return bt.type[4];
    else if(t->type.compare("ptr")==0) return bt.type[5]+"("+printType(t->arrtype)+")";                
    else if(t->type.compare("arr")==0) 
    {
        string str=convertIntToString(t->width);                                                        
        return bt.type[6]+"("+str+","+printType(t->arrtype)+")";
    }
    else if(t->type.compare("func")==0) return bt.type[7];
    else if(t->type.compare("block")==0) return bt.type[8];
    else return "NA";
}

void symtable::print()                                                                               
{
    int next_instr=0;
    list<symtable*> tb;                                                                               
    for(int t1=0;t1<60;t1++) std::cout<<"**";                                                        
    std::cout<<std::endl;

    std::cout << "Name: " << (*this).name ;
    generateSpaces(53-this->name.length());
    std::cout << " Parent Table: ";                                                                    
    if(((*this).parent==NULL)) std::cout<<"NULL"<<std::endl;                                           
    else std::cout<<(*this).parent->name<<std::endl;                                                  
    for(int x=0; x<60; x++) std::cout<<"__";                                                          
    std::cout<<std::endl;
    
    //Print the filed names for the table
    std::cout<<"Name";                                                                               
    generateSpaces(36);

    std::cout<<"Type";                                                                                
    generateSpaces(16);

    std::cout<<"Init Value";                                                                     
    generateSpaces(7);

    std::cout<<"Size";                                                                                
    generateSpaces(11);

    std::cout<<"Offset";                                                                              
    generateSpaces(9);

    std::cout<<"Nested"<<std::endl;                                                                   
    generateSpaces(100);
    std::cout<<std::endl;

    for(list<sym>::iterator it=table.begin(); it!=table.end(); it++) {                               
    
        std::cout << it->name;                                                                      
        generateSpaces(40-it->name.length());

        string rec_type=printType(it->type);                                                          
        std::cout << rec_type;
        generateSpaces(20-rec_type.length());

        std::cout << it->val;                                                                         
        generateSpaces(20-it->val.length());

        std::cout<<it->size;                                                                         
        generateSpaces(15-to_string(it->size).length());

        std::cout<<it->offset;                                                                       
        generateSpaces(15-to_string(it->offset).length());

        if(it->nested==NULL) {                                                                       
            std::cout<<"NULL"<<std::endl;
        }
        else {
            std::cout<<it->nested->name<<std::endl; 
            tb.push_back(it->nested);                                                                 
        }
    }
 
    for(int i=0;i<60;i++) std::cout<<"--";
    std::cout<<"\n\n";
    for(list<symtable*>::iterator it=tb.begin(); it !=tb.end();++it) 
    {
        (*it)->print();
    }
}

int main()
{

    
    bt.addType("null",0);                                                                              
    bt.addType("void",0);
    bt.addType("char",1);
    bt.addType("int",4);
    bt.addType("float",8);
    bt.addType("ptr",4);
    bt.addType("arr",0);
    bt.addType("func",0);
    bt.addType("block",0);

    label_table.clear();

    table_count = 0;                                                                                    
    debug_on= 0;                                                                                        
    globalST=new symtable("Global");                                                                    
    ST=globalST;
    parST=nullptr;
    loop_name = "";

    yyparse();                                                                                         
    globalST->update();                                                                                
    std::cout<<"\n";

    Q.print();                                                                                         
    globalST->print();                                                                                 
};
