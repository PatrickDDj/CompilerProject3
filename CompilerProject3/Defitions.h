//
//  Defitions.h
//  Compiler_Porject1
//
//  Created by PatrickDD on 2021/3/29.
//

#ifndef Defitions_h
#define Defitions_h
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

#define INT "int"
#define FLOAT "float"
#define BOOL "bool"

#define _HEADER_ "HEADER"
#define _Descs_ "Descs"
#define _Desc_ "Desc"
#define _Id_ "Id"
#define _Asig_E_ "Asig_E"
#define _Decl_ "Decl"
#define _IF_Block "IF_Block"
#define _IF "IF"
#define _ELSE_IF "IF_ELSE"
#define _ELSE "ELSE"



using namespace std;


const vector<string> KEY_WORDS = {
    "main", "include", "void", "return",
    "int", "bool", "float", "double","char","string",
    
    "(", ")", "[", "]", "{", "}", ".", "#", "_", ",", ";", "'", "\"",":",
    
    "!", "&", "~", "^","|",
    "+", "-", "*", "/", "%",
    ">", "<", "=",
    "->", "++", "--",
    "<<", ">>",
    "<=", ">=", "==", "!=",
    "&&", "||",
    "+=", "-=", "/=","*=", "^=", "&=", "|=", "%=", "~=",
    
    "//",
    
    "Id",
    "Decimal_Number", //十进制
    "Hexademical_Number", //十六进制
    "Octal_Number", //八进制
    "Float_Number",
    "String_Constant",
    
    "if", "else", "while", "for", "else if","break", "continue", "do","switch", "case", "default",
//    "get", "put",
    "true", "false"
    
};

map<string, int> KEY_WORDS_MAP;

map<string, int> Op_Precedence = {
    {"||", 10},
    {"&&", 20},
    {"|", 30},
    {"^", 40},
    {"&", 50},
    {"!=", 60},
    {"==", 60},
    {">", 70},
    {">=", 70},
    {"<=", 70},
    {"<", 70},
    {"<<", 80},
    {">>", 80},
    {"+", 90},
    {"-", 90},
    {"*", 100},
    {"/", 100},
    {"%", 100}
};


#endif /* Defitions_h */



