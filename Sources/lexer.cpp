#include "../Headers/lexer.h"

lexer::lexer()
{
    line_count = 0;
    char_count = 0;
}


bool lexer::lexical_analysis(string file_name)
{
    ifstream ifs(file_name, ios::in);
    if (!ifs.is_open())
        return false;
    
    return true;
}