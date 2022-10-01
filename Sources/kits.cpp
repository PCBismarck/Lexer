#include "../Headers/kits.h"

bool isKeyword(string key)
{
    return KEYWORD.count(key);
}

bool isOperator(string key)
{
    return OPERATOR.count(key);
}

bool isDelimiter(char key)
{
    if(OPERATOR.count(to_string(key)) || isblank(key) || key == '\n' || key == EOF)
        return true;
    return false;
}

set<string> KEYWORD = {
    "auto",         "break",        "case",         "char",         "const",
    "continue",     "default",      "do",           "double",       "else", 
    "enum",         "extern",       "float",        "for",          "goto",
    "if",           "inline",       "int",          "long",         "register",
    "restrict",     "return",       "short",        "signed",       "sizeof",
    "static",       "struct",       "switch",       "typedef",      "union",        
    "unsigned",     "void",         "volatile",     "while",        "_Bool",        
    "_Complex",     "Imaginary"
};

set<string> OPERATOR = {
    "+",        "-",        "*",        "/",
    "++",       "--",       "%",        "&",
    "|",        "!",        "&&",       "||"
    ">",        "<",        "=",        "<=",
    ">=",       "==",       
    "(",        ")",        "[",        "]",        
    "{",        "}",        ",",        ";",
};