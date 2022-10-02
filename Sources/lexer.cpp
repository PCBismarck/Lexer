#include "../Headers/lexer.h"

#define LEFT_BUFF 0
#define RIGH_BUFF 1

lexer::lexer()
{
    //清空存储
    line_count = 1;
    char_count = 0;
    pos_in_line = 1;
    mark_table.clear();
    error_table.clear();
    memset(buffer, 0, sizeof(buffer));
    keyword_num = 0;
    identifier_num = 0;
    constant_num = 0;
    string_num = 0;
    punctuator_num = 0;

}


int lexer::get_keyword_num()
{
    return keyword_num;
}

int lexer::get_identifier_num()
{
    return identifier_num;
}

int lexer::get_constant_num()
{
    return constant_num;
}

int lexer::get_string_num()
{
    return string_num;
}

int lexer::get_punctuator_num()
{
    return punctuator_num;
}


vector<token>& lexer::get_marktable()
{
    return mark_table;
}

vector<token>& lexer::get_error_table()
{
    return error_table;
}

bool lexer::lexical_analysis(string file_name)
{
    ifs.open(file_name, ios::in);
    if (!ifs.is_open())
        return false;
    
    int cur = 0, pre = 0;

    string str_buff;
        
    read_to_buff(LEFT_BUFF);
    
    while (buffer[cur] != EOF)
    {
        //对新开始的第一个字符的检测
        //设置的'\0'分隔符----------------------------------------------------------------------
        if(buffer[cur] == '\0')
            buffer_manage(ptr_inc(cur));

        //空白字符-------------------------------------------------------------------------------
        else if(isblank(buffer[cur]))
        {
            buffer_manage(ptr_inc(cur));
            pos_in_line++;
        }
        
        //换行-----------------------------------------------------------------------------------
        else if(buffer[cur] == '\n')
        {
            buffer_manage(ptr_inc(cur));
            line_count++;
            pos_in_line = 1;
        }

        //接下来执行数字检测流程------------------------------------------------------------------
        else if(isdigit(buffer[cur]))
        {    
            int dot_flag = 0, e_flag = 0, err = 0;
            //pre = cur;
            for(; !isDelimiter(buffer[pre]); buffer_manage(ptr_inc(pre)))
            {
                char_count++;
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
                else if(isalpha(buffer[pre]) || isPunctuator(buffer[pre]))
                    break;
                str_buff.push_back(buffer[pre]);                    
            }
            string type = "Number";
            if (err)
                type = "ErrorType";

            token key(type, tuple<int,int>(line_count, pos_in_line), str_buff);
            if (err)
                error_table.push_back(key);
            else
                constant_num++;
            mark_table.push_back(key);
            cur = pre;
            pos_in_line += str_buff.length();
        }

        //标识符(关键字)流程-------------------------------------------------------------------------------
        else if(isIdentifier(buffer[cur]))
        {
            for(; isIdentifier(buffer[pre]); buffer_manage(ptr_inc(pre)))
            {
                str_buff.push_back(buffer[pre]);
                char_count++;
            }
            string type = "Identifier";
            if(isKeyword(str_buff))
            {
                type = "Keyword";
                keyword_num++;    
            }
            else
                identifier_num++;
                
            token key(type, tuple<int,int>(line_count, pos_in_line), str_buff);
            mark_table.push_back(key);
            cur = pre;
            pos_in_line += str_buff.length();
        }

        //宏定义部分-------------------------------------------------------------------------------
        else if(buffer[cur] == '#')
        {
            buffer_manage(ptr_inc(pre));
            for(; buffer[pre] != '\n' && buffer[pre] != '#'; buffer_manage(ptr_inc(pre)))
            {
                str_buff.push_back(buffer[pre]);
                char_count++;
            }
            string type = "PreprocessPart";
            if (pos_in_line != 1)
                type = "Unknown";

            token key(type, tuple<int,int>(line_count, pos_in_line), str_buff);
            if(pos_in_line != 1)
                error_table.push_back(key);
            mark_table.push_back(key);
            cur = pre;
            pos_in_line += str_buff.length();
        }

        //字符常量-------------------------------------------------------------------------------
        else if(buffer[cur] == '\'')
        {
            ptr_inc(pre);
            str_buff.push_back(buffer[cur]);
            for(; buffer[pre] != '\'' && buffer[pre] != EOF; buffer_manage(ptr_inc(pre)))
            {
                str_buff.push_back(buffer[pre]);
                char_count++;
                if(buffer[pre] == '\n')
                {
                    line_count++;
                    pos_in_line = 1;
                }
                else if(buffer[pre] == '\\')
                {
                    buffer_manage(ptr_inc(pre));                    
                    str_buff.push_back(buffer[pre]);
                }
            }
            str_buff.push_back('\'');
            string type = "Char";
            token key(type, tuple<int,int>(line_count, pos_in_line), str_buff);
            string_num++;
            mark_table.push_back(key);
            buffer_manage(ptr_inc(pre));
            cur = pre;
            pos_in_line += str_buff.length();  
        }

        //字符串常量-------------------------------------------------------------------------------
        else if(buffer[cur] == '"')
        {
            ptr_inc(pre);
            str_buff.push_back(buffer[cur]);
            for(; buffer[pre] != '"' && buffer[pre] != EOF; buffer_manage(ptr_inc(pre)))
            {
                str_buff.push_back(buffer[pre]);
                char_count++;
                if(buffer[pre] == '\n')
                {
                    line_count++;
                    pos_in_line = 1;
                }
                else if(buffer[pre] == '\\')
                {
                    buffer_manage(ptr_inc(pre));                    
                    str_buff.push_back(buffer[pre]);
                }                
            }
            str_buff.push_back('"');
            token key("StringLiteral", tuple<int,int>(line_count, pos_in_line), str_buff);
            string_num++;
            mark_table.push_back(key);
            buffer_manage(ptr_inc(pre));
            cur = pre;
            pos_in_line += str_buff.length();            
        }

        //注释-------------------------------------------------------------------------------
        else if(buffer[cur] == '/')
        {
            int state = 0;
            buffer_manage(ptr_inc(pre));
            if(buffer[pre] == '/')// 进入//处理流程
            {
                for(; buffer[pre] != '\n' && buffer[pre] != EOF; buffer_manage(ptr_inc(pre)))
                    char_count++;
                cur = pre;
            }
            else if(buffer[pre] == '*')// 进入/*处理流程
            {
                state = 1;//处于/*状态
                for(; buffer[pre] != EOF; buffer_manage(ptr_inc(pre)))
                {
                    char_count++;
                    if(buffer[pre] == '*')
                        state = 2;//处于 /*---*状态
                    else if(buffer[pre] == '/' && state == 2)// /**/
                        break;
                    else
                        state = 1;
                }
                if(buffer[pre] != EOF)
                    buffer_manage(ptr_inc(pre));
                cur = pre;
            }
            else //其他情况作为除号进行处理
            {
                str_buff.push_back(buffer[cur]);
                if(buffer[pre] == '=')
                {
                    str_buff.push_back(buffer[pre]);
                    buffer_manage(ptr_inc(pre)); 
                }
                token key("Punctuator", tuple<int,int>(line_count, pos_in_line), str_buff);
                mark_table.push_back(key);
                cur = pre;
                pos_in_line += str_buff.length();
            }
        }

        //操作符(贪心算法，最长串匹配)-------------------------------------------------------------------------------
        else if(isPunctuator(buffer[cur]))
        {
            //未完成
            ptr_inc(pre);
            str_buff.push_back(buffer[cur]);
            for(; isOperator(str_buff+buffer[pre]); buffer_manage(ptr_inc(pre)))
                    str_buff.push_back(buffer[pre]);

            token key("Punctuator", tuple<int,int>(line_count, pos_in_line), str_buff);
            punctuator_num++;
            mark_table.push_back(key);
            cur = pre;
            pos_in_line += str_buff.length();
        }
        
        //其他不明输入字符----------------------------------------------------------------------
        else
        {
            for(; !isDelimiter(buffer[pre]); buffer_manage(ptr_inc(pre)))
            {
                str_buff.push_back(buffer[pre]);
                char_count++;
            }
            token key("Unknown", tuple<int,int>(line_count, pos_in_line), str_buff);
            mark_table.push_back(key);
            error_table.push_back(key);
            cur = pre;
            pos_in_line += str_buff.length();
        }

        str_buff.clear();
        pre = cur;
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
int lexer::ptr_inc(int &ptr)
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

//读取HALE_BUFFER_SIZE-1的字符，末尾填充'\0'，文件结束则填充为EOF
int lexer::read_to_buff(int where)
{
    if (!ifs.eof())
    {
        //LEFT_BUFF = 0  RIGH_BUFF = 1
        char * start_pos;
        if(where == RIGH_BUFF)
            start_pos = &buffer[HALF_BUFFER_SIZE];
        else
            start_pos = buffer;
        ifs.read(start_pos, HALF_BUFFER_SIZE);
        //
        if (ifs.eof())
        {
            int offset = 0;
            if(where == RIGH_BUFF)
                offset == HALF_BUFFER_SIZE;
            buffer[(offset+ifs.gcount())%BUFFER_SIZE] = EOF;
        }
        return ifs.gcount();
    }
    return -1;
}

//控制buffer读取的时机
void lexer::buffer_manage(int buffer_state)
{
    if(buffer_state == -1)//读到左半区结尾，填充右半区
        read_to_buff(RIGH_BUFF);
    else if(buffer_state == 1)//读到右半区结尾，填充左半区
        read_to_buff(LEFT_BUFF);
}


