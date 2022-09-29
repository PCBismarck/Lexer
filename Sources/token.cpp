#include "../Headers/token.h"

token::token(string type, tuple<int, int> location, string value)
{
    this->type = type;
    this->location = location;
    this->value = value;
}

void token::get_params(tuple<string, tuple<int, int>, string> token_params)
{
    get<0>(token_params) = this->type;
    get<1>(token_params) = this->location;
    get<2>(token_params) = this->value;
}

