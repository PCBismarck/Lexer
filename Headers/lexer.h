#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../Headers/token.h"

#ifndef LEXER_H
#define LEXER_H

using namespace std;

/**
 * @class lexer
 * 
 * To analyze the c file, and print the token in file
 */
class lexer
{
public:
    /**
     * @brief Construct a new lexer object
     * 
     * assign default value(0) to params
     */
    lexer();

    /**
     * @brief   lexical analysis the file 
     * 
     * @param file_name the file to analysis
     * @return true     if the file was analysised
     * @return false    if the file does not exist
     */
    bool lexical_analysis(string file_name);
    
private:
    int line_count;///< the num of lines in file
    int char_count;///< the num of chars in file
    vector<token> mark_table;///< the mark table of file
};

#endif