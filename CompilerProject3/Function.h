//
//  Function.h
//  CompilerProject3
//
//  Created by PatrickDD on 2021/5/17.
//
#include "Defines.h"
#ifndef Function_h
#define Function_h



class Function{
public:
    vector<Parameter> parameters;
    int return_type;
    Function(){}
    Function(const vector<Parameter>& parameters, int return_type):parameters(parameters),return_type(return_type) {}
};

class FunctionManager{
public:
    map<string, Function> functions;
    
    FunctionManager(){}
    
    bool exists_function(string function_name){
        return functions.find(function_name) != functions.end();
    }
    
    void add_function(string function_name, const vector<Parameter>& parameters, int return_type){
        if(!exists_function(function_name)){
            functions[function_name] = Function(parameters, return_type);
        }
        else{
            printf("[ERROR] Function '%s' is already defined\n", function_name.c_str());
        }
        
    }
    
    void print_functions(){
        for(auto function : functions){
            printf("--------------------\n");
            printf("Function Name : %s\t|\n", function.first.c_str());
            printf("-----------------------------------------\n");
            printf("Parameters : ");
            for(auto parameter : function.second.parameters){
                printf("%s(%s)\t",  parameter.second.c_str(), TYPE[parameter.first].c_str());
            }
            printf("\n");
            printf("Return type : %s\n", TYPE[function.second.return_type].c_str());
            
            printf("-----------------------------------------\n\n\n");
        }
    }
    
};

#endif /* Function_h */
