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
    int type;
    
    int int_val=0;
    float float_val=0.0;
    bool bool_val=false;
    
    Variable(){}
    Variable(int type):type(type){}
    Variable(const Variable &v){
        type = v.type;
        int_val = v.int_val;
        float_val = v.float_val;
        bool_val = v.bool_val;
    }
    Variable(int type, int val):type(type), int_val(val){}
    Variable(int type, float val):type(type), float_val(val){}
    Variable(int type, bool val):type(type), bool_val(val){}
    string get_val() const{
        ostringstream stream;
        switch (type) {
            case __INT__:
                stream << int_val;
                break;
            case __FLOAT__:
                stream << float_val;
                break;
            case __BOOL__:
                stream << bool_val;
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
    
    void set_val(int val){int_val = val;}
    void set_val(bool val){bool_val = val;};
    void set_val(float val){float_val = val;}
    
    friend Variable operator+(const Variable& a, const Variable& b){
        Variable v(a.type);
        v.int_val = b.int_val + a.int_val;
        v.float_val = b.float_val + a.float_val;
        v.bool_val = b.bool_val + a.bool_val;
        return v;
    }
    
    friend Variable operator-(const Variable& a, const Variable& b){
        Variable v(a.type);
        v.int_val = a.int_val - b.int_val;
        v.float_val = a.float_val - b.float_val;
        v.bool_val = a.bool_val - b.bool_val;
        return v;
    }
    
    friend Variable operator*(const Variable& a, const Variable& b){
        Variable v(a.type);
        v.int_val = b.int_val * a.int_val;
        v.float_val = b.float_val * a.float_val;
        v.bool_val = b.bool_val * a.bool_val;
        return v;
    }
    
    friend Variable operator==(const Variable& a, const Variable& b){
        Variable v(__BOOL__);
        v.bool_val = (a.type==__INT__?a.int_val==b.int_val:(a.type == __FLOAT__? a.float_val==b.float_val:a.bool_val==b.bool_val));
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
    
    const Variable& get_variable(int scope, string variable_name){
        return variables[scope][variable_name];
    }
    
    bool is_same_type(const Variable& a, const Variable& b){
        return a.type == b.type;
    }
    
    int seek_variable(const vector<int> usable_scopes, string variable_name){
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
            get(scope, variable_name) = v;
            return true;
        }
        printf("[ERROR] Variable '%s' redefined\n", variable_name.c_str());
        return false;
    }
    
    void set_variable(int scope, string variable_name, const Variable& v){
        Variable& u = get(scope, variable_name);
        if(is_same_type(u, v)){
            u = v;
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
            }
        }
        else{
            printf("[ERROR] Calculation between '%s' and '%s' is forbidden\n", a.get_type().c_str(), b.get_type().c_str());
        }

        return Variable(__Empty__);
    }
    
    void print_variables(){
        for(auto i : variables){
            printf("Scope : %d\n", i.first);
            for(auto k : i.second){
                string name = k.first;
                Variable &v = k.second;
                printf("Variable : %s(%s), Value : %s\n", name.c_str(), v.get_type().c_str(), v.get_val().c_str());
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
    
    void proc_Asig_E(const Node& Asig_E){
        
        string variable_name = Asig_E.sons[0].sons[0].Component;
        
        // seek this variable through the current usable scopes and its name
        int scope = variables.seek_variable(scopes.get_cur_usable_scopes(), variable_name);
        
        if(scope){
            // TODO: calculate the value of expression
            Variable t = get_Unit(Asig_E.sons[2]);
            if(t.is_valid()){
                variables.set_variable(scope, variable_name, t);
            }
            
        }
    }
    
    Variable get_Unit(const Node& node){
        int unit = SYMBOL_MAP[node.Component];
        switch (unit) {
            case __Factor__:{
                return proc_Factor(node);
            }
            case __Expr__:{
                return proc_Expr(node);
            }
        }
        return Variable(__Empty__);
        
    }
    
    Variable proc_Expr(const Node& Expr){
        Variable a = get_Unit(Expr.sons[0]), b = get_Unit(Expr.sons[2]);
        if(a.is_valid() && b.is_valid()){
            string op = Expr.sons[1].Component;
            return variables.calculate_variable(a, op, b);
        }
        return Variable(__Empty__);
    }
    

    Variable proc_Factor(const Node& Factor){
        
        int symbol = SYMBOL_MAP[Factor.sons[0].Component];
        
        
        switch (symbol) {
            case __INT__:{
                string val = Factor.sons[0].sons[0].Component;
                int int_val = stoi(val);
                return Variable(__INT__, int_val);
            }
            case __FLOAT__:{
                string val = Factor.sons[0].sons[0].Component;
                float float_val = stof(val);
                return Variable(__FLOAT__, float_val);
            }
            case __BOOL__:{
                string val = Factor.sons[0].sons[0].Component;
                bool bool_val = (val == "true" ? true : false);
                return Variable(__BOOL__, bool_val);
            }
            case __Id__:{
                string variable_name = Factor.sons[0].sons[0].Component;
                int scope = variables.seek_variable(scopes.get_cur_usable_scopes(), variable_name);
                if(scope){
                    return Variable(variables.get_variable(scope, variable_name));
                }
                break;
            }
            case __LEFT_Bracket__:{
                return get_Unit(Factor.sons[1]);
            }
        }
        return Variable(__Empty__);
    }
    
    void proc_Decl(const Node& Decl){
        int type = TYPE_MAP[Decl.sons[0].sons[0].Component];
        string variable_name;
        
        for(auto Desc : Decl.sons[1].sons){
            if(Desc.Component == _Desc_){

                int desc_type = SYMBOL_MAP[Desc.sons[0].Component];
                
                
                switch (desc_type) {
                    case __Id__:
                        // Desc - Id - t
                        variable_name = Desc.sons[0].sons[0].Component;
                        variables.add_variable(scopes.get_cur_scope(), variable_name, type);
                        break;
                        
                    case __Asig_E__:
                        // Desc - Asig_E - Id - t
                        variable_name = Desc.sons[0].sons[0].sons[0].Component;
                        if(variables.add_variable(scopes.get_cur_scope(), variable_name, type)){
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
