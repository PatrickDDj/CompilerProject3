//
//  Defitions.h
//  Compiler_Porject1
//
//  Created by PatrickDD on 2021/3/29.
//

#ifndef Defines_h
#define Defines_h
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

#define _INT_ "int"
#define _FLOAT_ "float"
#define _BOOL_ "bool"
#define _VOID_ "void"

#define __INT__ 1
#define __FLOAT__ 2
#define __BOOL__ 3
#define __Empty__ 0
#define __VOID__ 0

#define __EMPTY_SCOPE__ 0

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
#define _TF_ "TF"
#define _Float_Number_ "Float_Number"
#define _Decimal_Number_ "Decimal_Number"
#define _Factor_ "Factor"
#define _Expr_ "Expr"
#define _LEFT_Bracket_ "("
#define _ADD_ "+"
#define _SUB_ "-"
#define _MUL_ "*"
#define _EQUAL_ "=="
#define _GREATER_ ">"
#define _LESS_ "<"
#define _GREATER_or_EQUAL_ ">="
#define _LESS_or_EQUAL_ "<="
#define _PLUS_PLUS_ "++"
#define _MINUS_MINUS_ "--"
#define _Para_Def_ "ParaDef"
#define _Fun_Def_ "FunDef"


#define __HEADER__ 11
#define __Descs__ 12
#define __Desc__ 13
#define __Id__ 14
#define __Asig_E__ 15
#define __Decl__ 16
#define __IF_Block__ 17
#define __IF__ 18
#define __ELSE_IF__ 19
#define __ELSE__ 20
#define __Factor__ 21
#define __Expr__ 22
#define __LEFT_Bracket__ 23
#define __ADD__ 24
#define __SUB__ 25
#define __MUL__ 26
#define __EQUAL__ 27
#define __GREATER__ 28
#define __LESS__ 29
#define __GREATER_or_EQUAL__ 30
#define __LESS_or_EQUAL__ 31
#define __PLUS_PLUS__ 32
#define __MINUS_MINUS__ 33
#define __Para_Def__ 34
#define __Fun_Def__ 35

using namespace std;

typedef pair<int, string> Parameter;

map<int, string> TYPE = {
    {__INT__, _INT_},
    {__FLOAT__, _FLOAT_},
    {__BOOL__, _BOOL_},
    {__VOID__, _VOID_},
};

map<string, int> TYPE_MAP = {
    {_INT_, __INT__},
    {_FLOAT_, __FLOAT__},
    {_BOOL_, __BOOL__},
    {_VOID_, __VOID__},
};

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
    {_TF_, __BOOL__},
    {_Decimal_Number_, __INT__},
    {_Float_Number_, __FLOAT__},
    {_Factor_, __Factor__},
    {_Expr_, __Expr__},
    {_LEFT_Bracket_, __LEFT_Bracket__},
    {_ADD_, __ADD__},
    {_SUB_, __SUB__},
    {_MUL_, __MUL__},
    {_EQUAL_, __EQUAL__},
    {_GREATER_, __GREATER__},
    {_LESS_, __LESS__},
    {_GREATER_or_EQUAL_, __GREATER_or_EQUAL__},
    {_LESS_or_EQUAL_, __LESS_or_EQUAL__},
    {_PLUS_PLUS_, __PLUS_PLUS__},
    {_MINUS_MINUS_, __MINUS_MINUS__},
    {_Fun_Def_, __Fun_Def__},
    {_Para_Def_, __Para_Def__},
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



