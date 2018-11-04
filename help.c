#include "help.h"

int is_nat(char* a)
{
    int n = strlen(a), num = 0, sign, i = 0;

    if(a[0] == '-' || a[0] == '+')
        i = 1;
    else
        if(!(a[0] > '0' && a[0] < '9'))
            return -1;
    for(;i < n;i++)
    {
        if(!(a[i] >= '0' && a[i] <= '9'))
            return -1;
        if(num >= 2000000000 && a[i] != '\0')
            return -1;
        num = num * 10 + a[i] - '0';
    }
    return num;
}

string_struct input(string_struct lst)
{
    char *str = NULL;//Текущая строка
    int n = 0;//Текущий символ
    char c;
    int N = input_size, i = 0;//N - макс размер текущей строки, i - размер текущей строки
    str = (char*)malloc(N*sizeof(char));//Выделяем память
    n = read(0, &c, 1);
    while(n > 0)
    {
        while(n > 0 && c != '\n')
        {
            if(i+2 == N)//Если считанная строка не укладывается в нашу строку то перевыделяем память увеличивая в 2 раза место
            {
                N*=2;
                str = (char*)realloc(str, N*sizeof(char));
            }
            str[i++] = c;
            n = read(0,&c, 1);
        }
        if(c == '\n')
            str[i++] = c;
        // if((n = read(0, &c, 1)) = 0)
        //     str[i++] = '\n';
        if(i > 0)
        {
            str[i] = '\0';
            lst = add_string_list(lst,str,i+1);
        }
        free(str);
        N = input_size;
        i = 0;
        str = (char*)malloc(N*sizeof(char));
        n = read(0, &c, 1);
    }
    free(str);//Отчистка памяти выделенной под строку
    return lst;
}