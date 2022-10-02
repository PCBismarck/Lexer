#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <tuple>

using namespace std;

/**
 * @class token
 * 
 * To record the information of the words
 * 
 */
class token
{
public:
    /**
     * @brief Construct a new token object
     * 
     * @param type      a string, the type of the token
     * @param location  a tuple<row, col>, location of the token in the file
     * @param value     a string, the real value of the token
     */
    token(string type, tuple<int, int> location,  string value);

    /**
     * @brief Get the params of the token
     * 
     * @param token_params  a 4 params tuple to store the result
     */
    void get_params(tuple<string, tuple<int, int>, string>& token_params);

private: 
    string type;
    tuple<int, int> location;
    string value;
};

#endif