#ifndef POINTER_H
#define POINTER_H

#include <iostream>
#include <fstream>
#include <string.h>

#define BUFFER_SIZE 1024

using namespace std;

class pointer
{
public:
    pointer();

    bool cur_inc();
    bool pre_inc();

private:
    int cur;
    int pre;

};

#endif