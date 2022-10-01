#include "../Headers/buffer.h"

buffer::buffer(string file_name)
{
    cur = 0;
    pre = 0;
    memset(mem, 0, MEM_SIZE);

}