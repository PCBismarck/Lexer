#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include "../Headers/token.h"
#include "../Headers/kits.h"


#define BUFFER_SIZE 2048
#define HALF_BUFFER_SIZE 1024

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
    
    /**
     * @brief Get the lines of file
     * 
     */
    int get_lines_num();

    /**
     * @brief Get the chars num of file
     * 
     */
    int get_chars_num();

    int get_keyword_num();

    int get_identifier_num();

    int get_constant_num();

    int get_string_num();

    int get_punctuator_num();


    vector<token>& get_marktable();
    
    vector<token>& get_error_table();

private:
    int read_to_buff(int where);
    int ptr_inc(int &ptr);
    void buffer_manage(int buffer_state);


private:
    int line_count;///< the num of lines in file
    int char_count;///< the num of chars in file
    int pos_in_line;

    int keyword_num;
    int identifier_num;
    int constant_num;
    int string_num;
    int punctuator_num;

    vector<token> mark_table;///< the mark table of file
    vector<token> error_table;
    char buffer[BUFFER_SIZE];
    ifstream ifs;
};

#endif