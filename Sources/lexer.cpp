#include "../Headers/lexer.h"

int ptr_inc(int &ptr);

lexer::lexer()
{
    //清空存储
    line_count = 0;
    char_count = 0;
    pos_in_line = 0;
    mark_table.clear();
    memset(buffer, 0, sizeof(buffer));
}


bool lexer::lexical_analysis(string file_name)
{
    ifstream ifs(file_name, ios::in);
    if (!ifs.is_open())
        return false;
    
    int cur = 0, pre = 0;
    ifs.read(buffer, HALF_BUFFER_SIZE-1);
    buffer[ifs.gcount()] = EOF;
    cout << buffer << endl;
    string str_buff;
        
    while (buffer[cur] != EOF)
    {
        //对新开始的第一个字符的检测
        //空白字符-------------------------------------------------------------------------------
        if(isblank(buffer[cur]))
        {
            ptr_inc(cur);
            pos_in_line++;
        }
        else if(buffer[cur] == '\n')
        {
            line_count++;
            pos_in_line = 0;
        }
        //接下来执行数字检测流程------------------------------------------------------------------
        else if(isdigit(buffer[cur]))
        {    
            int dot_flag = 0, e_flag = 0, err = 0;
            pre = cur;
            for(; !isDelimiter(buffer[pre]); ptr_inc(pre))
            {
                str_buff += buffer[pre];
                if(buffer[pre] == '.')
                {
                    if(dot_flag == 1 || e_flag == 1)
                        err = 1;
                    else
                        dot_flag = 1;
                }
                else if(buffer[pre] == 'e')
                {
                    if(e_flag == 1)
                        err = 1;
                    else
                        e_flag = 1;
                }
                char_count++;
                pos_in_line++;                
            }
            if(buffer[pre] == '\n')
            {
                line_count++;
                pos_in_line = 0;
            }
            string type = "Number";
            if (err)
                type = "ErrorType";
            token key(type, tuple<int,int>(line_count, pos_in_line), str_buff);
            mark_table.push_back(key);
        }

        //标识符流程-------------------------------------------------------------------------------
        else if(isalpha(buffer[cur]) || buffer[cur] == '_')
        {
            
        }

        //宏定义部分-------------------------------------------------------------------------------
        else if(buffer[cur] == '#')
        {
            
        }

        //字符常量-------------------------------------------------------------------------------
        else if(buffer[cur] == '\'')
        {

        }

        //字符串常量-------------------------------------------------------------------------------
        else if(buffer[cur] == '"')
        {

        }

        //注释-------------------------------------------------------------------------------
        else if(buffer[cur] == '/')
        {
            
        }

        //操作符-------------------------------------------------------------------------------
        else if(isOperator(to_string(buffer[cur])))
        {
            
        }
        if(buffer[pre] == EOF)
            break;
        ptr_inc(pre);
        cur = pre;
        str_buff.clear();
        //更新buffer
    }
    

    ifs.close();
    return true;
}


int lexer::get_lines_num()
{
    return line_count;
}

int lexer::get_chars_num()
{
    return char_count;
}


//指针自增，到左半区结尾返回-1，右半区结尾返回1，否则返回0
int ptr_inc(int &ptr)
{
    if(ptr == BUFFER_SIZE / 2 - 1)//前半区结尾
    {
        ptr++;
        return -1;
    }
    else if(ptr == BUFFER_SIZE - 1)//后半区结尾
    {
        ptr = 0;
        return 1;
    }
    ptr++;
    return 0;
}




