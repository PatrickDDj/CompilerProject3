//
//  SemanticAnalyzer.h
//  CompilerProject3
//
//  Created by PatrickDD on 2021/5/12.
//

#include "Defitions.h"
#include "Node.h"

#ifndef SemanticAnalyzer_h
#define SemanticAnalyzer_h


class Variable{
public:
    string type;
    Variable(){}
    Variable(string type):type(type){}
};

class IntVariable:public Variable{
public:
    int val;
    IntVariable(){}
    IntVariable(string type, int val):Variable(type), val(val){}
};

class BoolVariable:public Variable{
public:
    bool val;
    BoolVariable(){}
    BoolVariable(string type, bool val):Variable(type), val(val){}
};

class FloatVariable:public Variable{
public:
    float val;
    FloatVariable(){}
    FloatVariable(string type, float val):Variable(type), val(val){}
};


class Variables{
public:
    map<string, IntVariable> IntVariables;
    map<string, BoolVariable> BoolVariables;
    map<string, FloatVariable> FloatVariables;
    Variables(){}
};

class Variabls_MAP{
public:
    map<int, Variables> Variables_map;

    Variabls_MAP(){}

    void add_Variable(int scope, string VariableName, string type, int val){
        if(type == INT){
            IntVariable v(type, val);
            Variables_map[scope].IntVariables[VariableName] = v;
        }
    }

    void add_Variable(int scope, string VariableName, string type, bool val){
        if(type == BOOL){
            BoolVariable v(type, val);
            Variables_map[scope].BoolVariables[VariableName] = v;
        }
    }

    void add_Variable(int scope, string VariableName, string type, float val){
        if(type == FLOAT){
            FloatVariable v(type, val);
            Variables_map[scope].FloatVariables[VariableName] = v;
        }
    }

};

class SemanticAnalyzer {
public:
    
};


#endif /* SemanticAnalyzer_h */
