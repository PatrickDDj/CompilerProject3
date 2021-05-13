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
    void set_val(int val){ this->val  =val; }
};

class BoolVariable:public Variable{
public:
    bool val;
    BoolVariable(){}
    BoolVariable(string type, bool val):Variable(type), val(val){}
    void set_val(bool val){ this->val  =val; }
};

class FloatVariable:public Variable{
public:
    float val;
    FloatVariable(){}
    FloatVariable(string type, float val):Variable(type), val(val){}
    void set_val(float val){ this->val  =val; }
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
    map<int, Variables> variables;

    Variabls_MAP(){}
    
    void print_variables(){
        for(auto i : variables){
            printf("scope: %d\n", i.first);
            for(auto v:i.second.IntVariables){
                printf("name : %s, type : %s, val : %d\n", v.first.c_str(),v.second.type.c_str(), v.second.val);
            }
            for(auto v:i.second.BoolVariables){
                printf("name : %s, type : %s, val : %d\n", v.first.c_str(),v.second.type.c_str(), v.second.val);
            }
            for(auto v:i.second.FloatVariables){
                printf("name : %s, type : %s, val : %f\n", v.first.c_str(),v.second.type.c_str(), v.second.val);
            }
        }
    }
    
    string get_variable(int scope, string variable_name){
        if(variables.find(scope) != variables.end()){
            Variables v = variables[scope];
            if(v.IntVariables.find(variable_name)!=v.IntVariables.end()){
                return INT;
            }
            if(v.BoolVariables.find(variable_name)!=v.BoolVariables.end()){
                return BOOL;
            }
            if(v.FloatVariables.find(variable_name)!=v.FloatVariables.end()){
                return FLOAT;
            }
        }
        return "";
    }
    
    IntVariable& get_int_variable(int scope, string variable_name){
        return variables[scope].IntVariables[variable_name];
    }
    
    FloatVariable& get_float_variable(int scope, string variable_name){
        return variables[scope].FloatVariables[variable_name];
    }
    
    BoolVariable& get_bool_variable(int scope, string variable_name){
        return variables[scope].BoolVariables[variable_name];
    }
    
    // check redefined variables
    // if this variable doesn't exist in the current scope, declare it and set default value
    void set_variable_default_value(int scope, string variable_name, string type){
        if(type == INT){
            set_variable(scope, variable_name, type, 0);
        }
        
        // avoid ambiguous calling
        else if(type == FLOAT){
            set_variable(scope, variable_name, 0.0, type);
        }
        else if(type == BOOL){
            set_variable(scope, variable_name, type, false);
        }
    }

    void set_variable(int scope, string variable_name, string type, int val){
        IntVariable v(type, val);
        variables[scope].IntVariables[variable_name] = v;

    }

    void set_variable(int scope, string variable_name, string type, bool val){
        BoolVariable v(type, val);
        variables[scope].BoolVariables[variable_name] = v;
    }

    void set_variable(int scope, string variable_name, float val, string type){
        FloatVariable v(type, val);
        variables[scope].FloatVariables[variable_name] = v;
    }

};

class SemanticAnalyzer {
public:
    
    Node root;
    Variabls_MAP variables;
    
    vector<int> usable_scopes;
    
    int HEADER_scope;
    int cur_scope;
    
    void set_cur_scope(int scope){
        cur_scope = scope;
    }
    
    void set_HEADER_scope(int HEADER_scope){
        this->HEADER_scope = HEADER_scope;
    }
    
    vector<int>& cur_usable_scopes(){
        return usable_scopes;
    }
    
    void jump_into_Block(int Block_id){
        set_cur_scope(Block_id);
        cur_usable_scopes().push_back(Block_id);
    }
    
    void jump_out_Block(){
        cur_usable_scopes().pop_back();
        set_cur_scope(cur_usable_scopes().back());
    }
    
    SemanticAnalyzer(const Node& root):root(root){}
    
    void semantic_analysis(){
        Node& HEADER = root.sons[0];
        
        // jump into HEADER
        set_HEADER_scope(HEADER.id);
        jump_into_Block(HEADER.id);
        
        proc_HEADER(HEADER);
        
        
        Node& MAIN = root.sons[1];
        
        
        proc_MAIN(MAIN);
        
        
        variables.print_variables();
    }
    
    void proc_Block(const Node& Block){
        jump_into_Block(Block.id);
        
        const Node& Stmts = Block.sons[1];
        for(auto Stmt : Stmts.sons){
            proc_Stmt(Stmt.sons[0]);
        }
        
        jump_out_Block();
    }
    
    void proc_MAIN(const Node& MAIN){
        proc_Block(MAIN.sons[4]);
    }
    
    void proc_Stmt(const Node& Stmt){
        string stmt = Stmt.Component;
        if(stmt == _Asig_E_){
            proc_Asig_E(Stmt);
        }
        else if(stmt == _Decl_){
            proc_Decl(Stmt);
        }
        else if(stmt == _IF_Block){
            proc_IF_Block(Stmt);
        }
    }
    
    void proc_IF_Block(const Node& IF_Block){
        for(auto i : IF_Block.sons){
            string t = i.Component;
            if(t==_IF){
                proc_IF(i);
            }
            else if(t == _ELSE_IF){
                proc_ELSE_IF(i);
            }
            else if(t == _ELSE){
                proc_ELSE(i);
            }
        }
    }
    
    void proc_IF(const Node& IF){
        proc_Block(IF.sons[4]);
    }
    
    void proc_ELSE_IF(const Node& ELSE_IF){
        proc_Block(ELSE_IF.sons[4]);
    }
    
    void proc_ELSE(const Node& ELSE){
        proc_Block(ELSE.sons[1]);
    }
    
    void proc_HEADER(const Node& HEADER){
        const Node& H_Stmts = HEADER.sons[0];
        for(auto H_Stmt : H_Stmts.sons){
            proc_H_Stmt(H_Stmt.sons[0]);
        }
    }
    
    // Declaration of variables can only be done here
    // initialize this variable by assigning default value
    bool declare_variable(const Node& Id, string type){
        string variable_name = Id.sons[0].Component;
        if(variables.get_variable(cur_scope, variable_name).empty()){
            variables.set_variable_default_value(cur_scope, variable_name, type);
            return true;
        }
        
        printf("[ERROR] Variable '%s' redefined\n", variable_name.c_str());
        return false;
        
        
    }
    
    
    pair<int, string> seek_variable(string variable_name){
        for(auto i=usable_scopes.size()-1; i>=0; i--){
            int scope = usable_scopes[i];
            string type = variables.get_variable(scope, variable_name);
            if(!type.empty()){
                return make_pair(scope, type);
            }
        }

        return make_pair(0, "");
    }
    
    void proc_Asig_E(const Node& Asig_E){
        // seek this variable(type value) through the current usable scopes and its name
        string variable_name = Asig_E.sons[0].sons[0].Component;
        
        pair<int, string> v = seek_variable(variable_name);
        
        if(!v.second.empty()){
            
            // TODO: calculate the value of expression/factor
            int scope = v.first;
            string type = v.second;
            
            
            if(type == INT){
//                variables.set_variable(scope, variable_name, type, 99);
                variables.get_int_variable(scope, variable_name).val ++;
            }
            else if(type == FLOAT){
//                variables.set_variable(scope, variable_name, 9.9, type);
                variables.get_float_variable(scope, variable_name).val += 1;
            }
            else if(type == BOOL){
//                variables.set_variable(scope, variable_name, type, true);
                variables.get_bool_variable(scope, variable_name).val = false;
            }
            
        }
        else{
            printf("[ERROR] Variable '%s' has not been defined.\n", variable_name.c_str());
        }
    }
    
    void proc_Decl(const Node& Decl){
//        string type = get_type(Decl);
        string type = Decl.sons[0].sons[0].Component;
        
        
        for(auto Desc : Decl.sons[1].sons){
            if(Desc.Component == _Desc_){
                
                string Desc_type = Desc.sons[0].Component;
                
                // Desc -> Id
                if(Desc_type == _Id_){
                    declare_variable(Desc.sons[0], type);
                }
                
                //Desc -> Asig_E
                else if(Desc_type == _Asig_E_){
                    if(declare_variable(Desc.sons[0].sons[0], type)){
                        proc_Asig_E(Desc.sons[0]);
                    }
                    
                }
            }
        }
    }
    
    void proc_H_Stmt(const Node& H_Stmt){
        
        if(H_Stmt.Component == _Decl_){
            proc_Decl(H_Stmt);
        }
    }
    
//    string get_type(const Node& Stmt){
//        return Stmt.sons[0].sons[0].Component;
//    }
    
};


#endif /* SemanticAnalyzer_h */
