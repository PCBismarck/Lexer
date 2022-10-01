#include <iostream>
#include "../Headers/lexer.h"

int main(int, char**) {
    lexer clex;
    clex.lexical_analysis("test.txt");
    return 0;
}
