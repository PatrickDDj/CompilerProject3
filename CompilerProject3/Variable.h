//
//  Variable.h
//  CompilerProject3
//
//  Created by PatrickDD on 2021/5/17.
//
#include "Defines.h"


#ifndef Variable_h
#define Variable_h

class Variable{
public:
    int type;
    float val=0;
    
    Variable(){}
    Variable(int type):type(type){}
    Variable(const Variable& v){
        type = v.type;
        val = v.val;
    }
    Variable(int type, float val):type(type), val(val){}
    string get_val() const{
        ostringstream stream;
        switch (type) {
            case __INT__:
                stream << int(val);
                break;
            case __FLOAT__:
                stream << val;
                break;
            case __BOOL__:
                stream << (val>0?"true":"false");
                break;
                
            default:
                break;
        }
        
        return  stream.str();
    }
    
    string get_type() const{
        return TYPE[type];
    }
    
    bool is_valid() const{
        return type != __Empty__;
    }
    
    friend Variable operator+(const Variable& a, const Variable& b){
        Variable v(a.type);
        v.val = a.val + b.val;
        return v;
    }
    
    friend Variable operator-(const Variable& a, const Variable& b){
        Variable v(a.type);
        v.val = a.val - b.val;
        return v;
    }
    
    friend Variable operator*(const Variable& a, const Variable& b){
        Variable v(a.type);
        v.val = a.val * b.val;
        return v;
    }
    
    friend Variable operator==(const Variable& a, const Variable& b){
        Variable v(__BOOL__);
        v.val = (a.val == b.val);
        return v;
    }
    
    friend Variable operator>=(const Variable& a, const Variable& b){
        Variable v(__BOOL__);
        v.val = (a.val >= b.val);
        return v;
    }
    
    friend Variable operator<=(const Variable& a, const Variable& b){
        Variable v(__BOOL__);
        v.val = (a.val <= b.val);
        return v;
    }
    
    friend Variable operator>(const Variable& a, const Variable& b){
        Variable v(__BOOL__);
        v.val = (a.val > b.val);
        return v;
    }
    
    friend Variable operator<(const Variable& a, const Variable& b){
        Variable v(__BOOL__);
        v.val = (a.val < b.val);
        return v;
    }
    
    friend Variable operator++(Variable&a){
        ++a.val;
        return Variable(a);
    }
    
    friend Variable operator++(Variable&a, int){
        Variable v(a);
        a.val++;
        return v;
    }
    
    friend Variable operator--(Variable&a){
        --a.val;
        return Variable(a);
    }
    
    friend Variable operator--(Variable&a, int){
        Variable v(a);
        a.val--;
        return v;
    }
    
    
};



class VariablsManager{
public:
    map<int, map<string, Variable> > variables;

    VariablsManager(){}
    
    bool exists_variable(int scope, string variable_name){
        if(variables.find(scope) != variables.end() &&
           variables[scope].find(variable_name) != variables[scope].end() ){
            return true;
        }
        return false;
    }
    
    void remove_scope(int scope){
        variables.erase(scope);
    }
    
    Variable& get_variable(int scope, string variable_name){
        return variables[scope][variable_name];
    }
    
    bool is_same_type(const Variable& a, const Variable& b){
        return a.type == b.type;
    }
    
    int seek_variable(const vector<int> usable_scopes, string variable_name){
        
        // seek this variable in the nearest scope
        
        for(int i=usable_scopes.size()-1; i>=0; i--){
            int scope = usable_scopes[i];
            if(exists_variable(scope, variable_name)){
                return scope;
            }
        }
        
        printf("[ERROR] Variable '%s' has not been defined.\n", variable_name.c_str());
        return __EMPTY_SCOPE__;
    }
    
    bool add_variable(int scope, string variable_name, int type){
        if(!exists_variable(scope, variable_name)){
            Variable v(type);
            get_variable(scope, variable_name) = v;
            return true;
        }
        printf("[ERROR] Variable '%s' is already defined\n", variable_name.c_str());
        return false;
    }
    
    void set_variable(int scope, string variable_name, const Variable& v){
        Variable& u = get_variable(scope, variable_name);
        if(is_same_type(u, v)){
            u.val = v.val;
        }
        else{
            printf("[ERROR] Cannot assign variable '%s' from '%s' to '%s'\n",
                   variable_name.c_str(), u.get_type().c_str(), v.get_type().c_str());
        }
    }
    
    Variable calculate_variable(const Variable& a, string op, const Variable& b){

        int op_type = SYMBOL_MAP[op];

        if(is_same_type(a, b)){

            switch (op_type) {
                case __ADD__:{
                    return a+b;
                }
                case __SUB__:{
                    return a-b;
                }
                case __MUL__:{
                    return a*b;
                }
                case __EQUAL__:{
                    return a==b;
                }
                case __GREATER__:{
                    return a>b;
                }
                case __LESS__:{
                    return a<b;
                }
                case __GREATER_or_EQUAL__:{
                    return a>=b;
                }
                case __LESS_or_EQUAL__:{
                    return a<=b;
                }
            }
        }
        
        printf("[ERROR] Calculation between '%s' and '%s' is forbidden\n", a.get_type().c_str(), b.get_type().c_str());

        return Variable(__Empty__);
    }
    
    void print_variables(){
        for(auto i : variables){
            printf("-------------\n");
            printf("Scope : %d\t|\n", i.first);
            printf("-----------------------------------------\n");
            for(auto k : i.second){
                string name = k.first;
                Variable &v = k.second;
                printf("Variable : %s(%s), Value : %s\n", name.c_str(), v.get_type().c_str(), v.get_val().c_str());
            }
            printf("-----------------------------------------\n\n\n");
        }
    }
    
};


#endif /* Variable_h */
