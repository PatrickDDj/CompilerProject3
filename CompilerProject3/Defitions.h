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
#define _IF_Block_ "IF_Block"
#define _IF_ "IF"
#define _ELSE_IF_ "IF_ELSE"
#define _ELSE_ "ELSE"

#define __HEADER__ 1
#define __Descs__ 2
#define __Desc__ 3
#define __Id__ 4
#define __Asig_E__ 5
#define __Decl__ 6
#define __IF_Block__ 7
#define __IF__ 8
#define __ELSE_IF__ 9
#define __ELSE__ 10

using namespace std;

map<string, int> SYMBOL_MAP = {
    {_HEADER_, __HEADER__},
    {_Descs_, __Descs__},
    {_Desc_, __Desc__},
    {_Id_, __Id__},
    {_Asig_E_, __Asig_E__},
    {_Decl_, __Decl__},
    {_IF_Block_, __IF_Block__},
    {_IF_, __IF__},
    {_ELSE_IF_, __ELSE_IF__},
    {_ELSE_, __ELSE__},
};

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



