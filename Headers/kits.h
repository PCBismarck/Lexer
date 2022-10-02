#ifndef KITS_H
#define KITS_H

#include <iostream>
#include <string>
#include <set>

using namespace std;

/**
 * @brief determine whether the key is keyword in c
 * 
 * @param key 
 * @return true    
 * @return false 
 */
bool isKeyword(string key);

/**
 * @brief determine whether the key is operator in c 
 * 
 * @param key 
 * @return true 
 * @return false 
 */
bool isOperator(string key);

/**
 * @brief determine whether the key is delimiter in c
 * 
 *  such as operator space 
 * @param key 
 * @return true 
 * @return false 
 */
bool isDelimiter(char key);

/**
 * @brief determine whether the key is alpha or '_' 
 * 
 * @param key 
 * @return true 
 * @return false 
 */
bool isIdentifier(char key);

bool isPunctuator(char key);

/**
 * @brief keywords in c
 * 
 */
extern set<string> KEYWORD;

/**
 * @brief operators in c
 * 
 */
extern set<string> OPERATOR;

extern set<char> PUNCTUATOR;

#endif