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
    
    int int_val=0;
    float float_val=0.0;
    bool bool_val=false;
    
    Variable(){}
    Variable(string type):type(type){}
    string get_val(){
        ostringstream stream;
        
        if(type == INT){
            stream << int_val;
        }
        else if(type == FLOAT){
            stream << float_val;
        }
        else if(type == BOOL){
            stream << bool_val;
        }

        return  stream.str();
    }
    
    string get_type(){
        return type;
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
    
    const Variable& get_variable(int scope, string variable_name){
        return variables[scope][variable_name];
    }
    
    int seek_variable(const vector<int> usable_scopes, string variable_name){
        for(int i=usable_scopes.size()-1; i>=0; i--){
            int scope = usable_scopes[i];
            if(exists_variable(scope, variable_name)){
                return scope;
            }
        }
        return 0;
    }
    
    void add_variable(int scope, string variable_name, string type){
        Variable v(type);
        get(scope, variable_name) = v;
    }
    
    void set_variable(int scope, string variable_name, bool val){
        get(scope, variable_name).bool_val = val;
    }
    
    void set_variable(int scope, string variable_name, int val){
        get(scope, variable_name).int_val = val;
    }
    
    void set_variable(int scope, string variable_name, float val){
        get(scope, variable_name).float_val = val;
    }
    
    void print_variables(){
        for(auto i : variables){
            printf("Scope : %d\n", i.first);
            for(auto k : i.second){
                string name = k.first;
                Variable &v = k.second;
                printf("Variable : %s, Type : %s, Val : %s\n", name.c_str(), v.get_type().c_str(), v.get_val().c_str());
            }
        }
    }
private:
    Variable& get(int scope, string variable_name){
        return variables[scope][variable_name];
    }
};


class ScopeManager{
private:
    vector<int> usable_scopes;
    
    int HEADER_scope;
    int cur_scope;

public:
    ScopeManager(){}
    
    void set_cur_scope(int scope){
        cur_scope = scope;
    }
    
    void set_HEADER_scope(int HEADER_scope){
        this->HEADER_scope = HEADER_scope;
    }
    
    const vector<int>& get_cur_usable_scopes(){
        return usable_scopes;
    }
    
    int get_cur_scope(){
        return cur_scope;
    }
    
    int get_HEADER_scope(){
        return HEADER_scope;
    }
    
    void jump_into_Block(int Block_id){
        set_cur_scope(Block_id);
        usable_scopes.push_back(Block_id);
    }
    
    void jump_out_Block(){
        usable_scopes.pop_back();
        set_cur_scope(get_cur_usable_scopes().back());
    }
};

class SemanticAnalyzer {
public:
    
    Node root;
    
    VariablsManager variables;
    ScopeManager scopes;
    
    SemanticAnalyzer(const Node& root):root(root){}
    
    void semantic_analysis(){
        Node& HEADER = root.sons[0];
        
        // jump into HEADER
        scopes.set_HEADER_scope(HEADER.id);
        scopes.jump_into_Block(HEADER.id);
        
        proc_HEADER(HEADER);
        
        
        Node& MAIN = root.sons[1];
        
        
        proc_MAIN(MAIN);
        
        variables.print_variables();
        
    }
    
    void proc_Block(const Node& Block){
        scopes.jump_into_Block(Block.id);
        
        const Node& Stmts = Block.sons[1];
        for(auto Stmt : Stmts.sons){
            proc_Stmt(Stmt.sons[0]);
        }
        
        scopes.jump_out_Block();
    }
    
    void proc_MAIN(const Node& MAIN){
        proc_Block(MAIN.sons[4]);
    }
    
    void proc_Stmt(const Node& Stmt){
        string stmt = Stmt.Component;
        int symbol = SYMBOL_MAP[Stmt.Component];
        
        
        switch (symbol) {
            case __Asig_E__:
                proc_Asig_E(Stmt);
                break;
            case __Decl__:
                proc_Decl(Stmt);
                break;
            case __IF_Block__:
                proc_IF_Block(Stmt);
                break;
                
            default:
                break;
        }
//        if(stmt == _Asig_E_){
//            proc_Asig_E(Stmt);
//        }
//        else if(stmt == _Decl_){
//            proc_Decl(Stmt);
//        }
//        else if(stmt == _IF_Block_){
//            proc_IF_Block(Stmt);
//        }
    }
    
    void proc_IF_Block(const Node& IF_Block){
        for(auto i : IF_Block.sons){
            int symbol = SYMBOL_MAP[i.Component];
            
            
            switch (symbol) {
                case __IF__:
                    proc_IF(i);
                    break;
                case __ELSE_IF__:
                    proc_ELSE_IF(i);
                    break;
                case __ELSE__:
                    proc_ELSE(i);
                    break;
                    
                default:
                    break;
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
        if(!variables.exists_variable(scopes.get_cur_scope(), variable_name)){
            variables.add_variable(scopes.get_cur_scope() , variable_name, type);
            return true;
        }
        
        printf("[ERROR] Variable '%s' redefined\n", variable_name.c_str());
        return false;
    }
    
    void proc_Asig_E(const Node& Asig_E){
        
        string variable_name = Asig_E.sons[0].sons[0].Component;
        
        // seek this variable(type value) through the current usable scopes and its name
        int scope = variables.seek_variable(scopes.get_cur_usable_scopes(), variable_name);
        
        if(scope){
            // TODO: calculate the value of expression/factor
            variables.set_variable(scope, variable_name, 99);
            float i = 9.9l;
            variables.set_variable(scope, variable_name, i);
            
        }
        else{
            printf("[ERROR] Variable '%s' has not been defined.\n", variable_name.c_str());
        }
    }
    
    void proc_Decl(const Node& Decl){
        string type = Decl.sons[0].sons[0].Component;
        
        
        for(auto Desc : Decl.sons[1].sons){
            if(Desc.Component == _Desc_){

                int desc_type = SYMBOL_MAP[Desc.sons[0].Component];
                
                
                switch (desc_type) {
                    case __Id__:
                        declare_variable(Desc.sons[0], type);
                        break;
                        
                    case __Asig_E__:
                        if(declare_variable(Desc.sons[0].sons[0], type)){
                            proc_Asig_E(Desc.sons[0]);
                        }
                        break;
                        
                    default:
                        break;
                }
                
                
            }
        }
    }
    
    void proc_H_Stmt(const Node& H_Stmt){
        int symbol = SYMBOL_MAP[H_Stmt.Component];
        
        switch (symbol) {
            case __Decl__:
                proc_Decl(H_Stmt);
                break;
                
            default:
                break;
        }
    }
    
};


#endif /* SemanticAnalyzer_h */
