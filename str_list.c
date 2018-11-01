#include "sh.h"
// #include "str_list.h"

void copy_str(char *a, char *b)
{
    for(;*b != '\0';a++, b++)
        *a = *b;
    *a = '\0';
}
int copy_int(char *a, int b)
{
    int i = 0, j = 0, k = 1;
    char c[100] = "\0";
    if(b < 0)
    {
        b = -b;
        k = -1;
    }
    if(b == 0)
    {
        a[0] = '0';
        a[1] = '\0';
        i = 1;
    }
    else
    {
        for(;b > 0;b/=10,j++)
        c[j] = b%10 + '0';
        c[j--] = '\0';
        if(k == -1)
            a[i++] = '-';
        for(;j >= 0;i++,j--)
            a[i] = c[j];
        a[i] = '\0';
    }
    return i;
}
// -1 if a < b
//  0 if a = b
// +1 if a > b
char down_char(char a)
{
    return (a >= 'A' && a <= 'Z') ? a : a - ('a' - 'A');
}
int str_cmp (char *a, char *b, int r, int f, int n) /*string comparison with -f inclusion*/
{
    int i = 0;
    if(f)
    {
        for(;(unsigned)down_char(a[i]) == (unsigned)down_char(b[i]); i++)
            if (a[i] == '\0')
                return 0;
        return (((unsigned)down_char(a[i]))-((unsigned)down_char(b[i]))) * (1 - 2 * r);
    }
    else if(n)
    {
        for(; a[i] == b[i]; i++)
            if (a[i] == '\0')
                return 0;
        return (unsigned)(a[i] - b[i]) * (1 - 2 * r);    
    }
    else
        return strcmp(a,b) * (1 - 2 * r);
}

string_struct add_string_list(string_struct str, char *elem, int elem_size)
{
    if(str.size_current+1 == str.size)//Если выходим за пределы массива то перевыделяем память под него
    {
        str.size*=2;
        str.array = realloc(str.array, sizeof(char*) * str.size);
    }
    str.array[str.size_current] = (char*)malloc(sizeof(char) * elem_size);
    copy_str(str.array[str.size_current], elem);//Нельзя делать простое приравнивание так как в таком случае
    str.array[++str.size_current] = NULL;//если вне функции очистить то что передали очистим, то и тут пропадет
    return str;//А мы хотим функцию которая работает корректно не зависимо от реализации программы ее вызывающей
}
string_struct clean_string_list(string_struct str)
{
    for(int i = 0;i < str.size_current;i++)
        free(str.array[i]);
    free(str.array);
    str.size = array_size;
    str.size_current = 0;
    return str;
}
void print_string_list(string_struct str)
{
    for(int i = 0;i < str.size_current;i++)
        write(1, str.array[i],strlen(str.array[i]));
}

void tail_print_string(string_struct str, int n, int* flags)
{
    // printf("N = %d, Flags[0,1] = [%d, %d]\n", n, flags[0], flags[1]);
    int i = 0;
    if(flags[0] == 0)
    {
        if(str.size_current > 10)
            i = str.size_current-10;
    }
    else
    {
        if(flags[1] == 0)
            if(str.size_current > 10)
                i = str.size_current-n;
        if(flags[1] == 1)
            i = n-1;
    }
    for(;i < str.size_current;i++)
    {
        write(1, str.array[i],strlen(str.array[i]));
    }
}

void sort_string_list(string_struct str)
{
    char *buff = NULL;
    int max = 0;

    for(int i = 0;i < str.size_current;i++)
    {
        max = i;
        for(int j = i+1;j < str.size_current;j++)
        {
            if(strcmp(str.array[max], str.array[j]) > 0)
                max = j;
        }
        if(max != i)
        {
            buff = str.array[max];
            str.array[max] = str.array[i];
            str.array[i] = buff;
        }
    }
}

void sort_sort_list(string_struct str, int n, int* flags)
{
    char *buff = NULL;
    int max = 0, i = 0;
    if(flags[3])
        i = n;
    for(;i < str.size_current;i++)
    {
        max = i;
        for(int j = i+1;j < str.size_current;j++)
        {
            if(str_cmp(str.array[max], str.array[j], flags[0], flags[1], flags[2]) > 0)
                max = j;
        }
        if(max != i)
        {
            buff = str.array[max];
            str.array[max] = str.array[i];
            str.array[i] = buff;
        }
    }
}

string_struct init_string_list()
{
    string_struct str_list;
    str_list.array = (char**)malloc(10 * sizeof(char*));
    str_list.array[0] = NULL;

    str_list.size = array_size;
    str_list.size_current = 0;
    
    return str_list;
}
