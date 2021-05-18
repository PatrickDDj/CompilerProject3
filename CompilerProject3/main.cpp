//
//  main.cpp
//  CompilerProject3
//
//  Created by PatrickDD on 2021/5/10.
//

#include "LexicalAnalyzer.h"
#include "GrammarAnalyzer.h"
#include "SemanticAnalyzer.h"



int main(int argc, const char * argv[]) {
    LexicalAnalyzer lex("p2.txt");
    GrammarAnalyzer grammar(lex.lex_result);
    grammar.draw_AST("AST.txt");

    SemanticAnalyzer se(grammar.get_root());
    se.semantic_analysis();
}
