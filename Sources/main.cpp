#include <iostream>
#include <iomanip>
#include "../Headers/lexer.h"

void print_usage();

void write_to_file(tuple<string, tuple<int, int>, string> token_params, ofstream &markT, int N0);


int main(int argc, char** argv) {
    lexer clex;
    if(argc < 2)
    {
        print_usage();
        return -1;
    }
    
    if(!clex.lexical_analysis(argv[1]))
    {
        cout << "Open file fail!" << endl;
        return -1;
    }
    std::cout << "Chars:" << clex.get_chars_num() << std::endl;
    std::cout << "Lines:" << clex.get_lines_num() << std::endl;
    std::cout << "Keywords: " << clex.get_keyword_num() << std::endl;
    std::cout << "Identifiers: " << clex.get_identifier_num() << std::endl;    
    std::cout << "Constants: " << clex.get_constant_num() << std::endl;
    std::cout << "Strings: " << clex.get_string_num() << std::endl;
    std::cout << "Punctuators: " << clex.get_punctuator_num() << std::endl;
    //输出测试结果-------------------------------------------------------------------------------
    ofstream markT("MarkTable.txt");
    markT << "File Info:" << endl << "Lines: " << clex.get_lines_num() << endl \
          << "Chars: " << clex.get_chars_num() << endl \
          << "Keywords: " << clex.get_keyword_num() << endl \
          << "Identifiers: " << clex.get_identifier_num() << endl  \
          << "Constants: " << clex.get_constant_num() << endl  \
          << "Strings: " << clex.get_string_num() << endl  \
          << "Punctuators: " << clex.get_punctuator_num() << endl  \
          << "Marks: " \
          << clex.get_marktable().size() << endl;

    markT << endl << "Error Info: " << clex.get_error_table().size() \
          << " errors or unknowns" << endl <<"Error Tables: " << endl;
    for(int i = 0 ; i < clex.get_error_table().size(); i++)
    {
        tuple<string, tuple<int, int>, string> token_params;
        clex.get_error_table()[i].get_params(token_params);
        write_to_file(token_params, markT, i);
    }
    markT << endl;

    markT <<"-----------------------------------------"
          << "Mark Tables" << \
          "-----------------------------------------------------------------------------"
          << endl << endl; 
    

    for(int i = 0 ; i < clex.get_marktable().size() ; ++i)
    {
        cout << setw(8) << left;
        tuple<string, tuple<int, int>, string> token_params;
        clex.get_marktable()[i].get_params(token_params);
        write_to_file(token_params, markT, i);
    }
    markT.close();
    //--------------------------------------------------------------------------------------
    return 0;
}


void print_usage()
{
    cout << "usage: lexcer <file name>" << endl;
    cout << "The mark table will store in <MarkTable.txt>" << endl;
}

void write_to_file(tuple<string, tuple<int, int>, string> token_params, ofstream &markT, int N0)
{
    markT << left << "No." << setw(5) << N0+1 << ' ' << get<0>(get<1>(token_params)) \
        << ':' << setw(4) << get<1>(get<1>(token_params)) \
        << "->  "  << setw(14)<< get<0>(token_params)  \
        <<  ' '  << get<2>(token_params) << endl; 
}