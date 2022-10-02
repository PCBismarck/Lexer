#include <iostream>
#include <iomanip>
#include "../Headers/lexer.h"

void print_usage();

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
    //输出测试结果-------------------------------------------------------------------------------
    ofstream markT("MarkTable.txt");
    markT << "File Info:" << endl << "Lines: " << clex.get_lines_num() << endl \
          << "Chars: " << clex.get_chars_num() << endl << "Marks: " \
          << clex.get_marktable().size() << endl << \
          "-----------------------------------------"
          << "Mark Tables" << \
          "-----------------------------------------------------------------------------"
          << endl << endl; 
    for(int i = 0 ; i < clex.get_marktable().size() ; ++i)
    {
        cout << setw(8) << left;
        tuple<string, tuple<int, int>, string> token_params;
        string type , value;
        tuple<int, int> location;
        clex.get_marktable()[i].get_params(token_params);
        markT << left << "No." << setw(5) << i+1 << ' ' << get<0>(get<1>(token_params)) \
              << ':' << setw(4) << get<1>(get<1>(token_params)) \
              << "->  "  << setw(14)<< get<0>(token_params)  \
              <<  ' '  << get<2>(token_params) << endl; 
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