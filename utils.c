extern char *strdup(const char *);
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

bool is_number(char *str)
{
    for (int i = 0; i < strlen(str); ++i)
    {
        if (!isdigit(str[i]))
        {
            if (i == 0 && str[i] == '-')
            {
                ++i;
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

answer_t ask_question(char *question, check_func check, convert_func convert)
{
    int buf_size = 255;
    char result[255];
    do 
    {
        printf("%s\n", question);
        read_string(result, buf_size);
    }
    while (check(result) == false);
    return convert(result);
}

int ask_question_int(char *question)
{
  answer_t answer = ask_question(question, is_number, (convert_func) atoi);
  return answer.int_value; // svaret som ett heltal
}

int read_string(char *buf, int buf_size)
{
    char c;
    for (int i = 0; i < buf_size; ++i)
    {
        c = getchar();
        if (c == '\n')
        {
            buf[i] = '\0';
            return i;
        }
        buf[i] = c;
    }
    return buf_size;
}

bool not_empty(char *str)
{
  return strlen(str) > 0;
}

char *ask_question_string(char *question)
{
  return ask_question(question, not_empty, (convert_func) strdup).string_value;
}