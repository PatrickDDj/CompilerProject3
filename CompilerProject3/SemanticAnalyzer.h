//
//  SemanticAnalyzer.h
//  CompilerProject3
//
//  Created by PatrickDD on 2021/5/12.
//

#include "Defines.h"
#include "Variable.h"
#include "Function.h"
#include "ScopeManager.h"
#include "Node.h"

#ifndef SemanticAnalyzer_h
#define SemanticAnalyzer_h



class SemanticAnalyzer {
public:
    
    Node root;
    
    VariablsManager variables;
    FunctionManager functions;
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
        functions.print_functions();
        
    }
    
    void proc_Block(const Node& Block){
        int scope = Block.id;
        scopes.jump_into_Block(scope);
        
        const Node& Stmts = Block.sons[1];
        for(auto Stmt : Stmts.sons){
            proc_Stmt(Stmt.sons[0]);
        }
        
        scopes.jump_out_Block();
//        variables.print_variables();
//        variables.remove_scope(scope);
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
            // calculate the value of expression
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
                    Variable& v = variables.get_variable(scope, variable_name);
                    
                    // a++ a--
                    if (Factor.sons.size()>1){
                        
                        if(!(v.get_type()==_INT_ || v.get_type()==_FLOAT_)){
                            printf("[ERROE] Only 'int' or 'float' variables can do '++'/'--' calucalation\n");
                            break;
                        }
                        
                        int single_op = SYMBOL_MAP[Factor.sons[1].Component];
                        
                        switch (single_op) {
                            case __PLUS_PLUS__:
                                return v++;
                                
                            case __MINUS_MINUS__:
                                return v--;
                        }
                    }
                    
                    else{
                        return Variable(v);
                    }
                    
                }
                break;
            }
            case __PLUS_PLUS__:{
                string variable_name = Factor.sons[1].sons[0].Component;
                int scope = variables.seek_variable(scopes.get_cur_usable_scopes(), variable_name);
                if(scope){
                    Variable& v = variables.get_variable(scope, variable_name);
                    return ++v;
                }
                break;
            }
            case __MINUS_MINUS__:{
                string variable_name = Factor.sons[1].sons[0].Component;
                int scope = variables.seek_variable(scopes.get_cur_usable_scopes(), variable_name);
                if(scope){
                    Variable& v = variables.get_variable(scope, variable_name);
                    return --v;
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
    
    void proc_FunDef(const Node& FunDef){
        int return_type = TYPE_MAP[FunDef.sons[0].sons[0].Component];
        string function_name = FunDef.sons[1].sons[0].Component;
        
        vector<Parameter> parameters;
        for(auto ParaDef : FunDef.sons[3].sons){
            if(ParaDef.Component == _Para_Def_){
                parameters.push_back(make_pair(TYPE_MAP[ParaDef.sons[0].sons[0].Component], ParaDef.sons[1].sons[0].Component));
            }
        }
        
        functions.add_function(function_name, parameters, return_type);
    }
    
    void proc_H_Stmt(const Node& H_Stmt){
        int symbol = SYMBOL_MAP[H_Stmt.Component];
        
        switch (symbol) {
            case __Decl__:{
                proc_Decl(H_Stmt);
                break;
            }
                
            case __Fun_Def__:{
                proc_FunDef(H_Stmt);
                break;
            }
            default:
                break;
            
        }
    }
    
};


#endif /* SemanticAnalyzer_h */
