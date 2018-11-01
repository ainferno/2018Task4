#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "sh.h"
#include "help.h"

/*
flags(0,0) - no flags
flags(0,1) - impossible
flags(1,0) - -n <number>
flags(1,1) - -n +<number>
*/
int main(int argc, char* argv[])
{
    int words[(argc > 1) ? argc-1 : 1], words_number = argc - 1, flags[2] = {0, 0}, n_argument;
    for(int i = 0;i < argc-1;i++)
        words[i] = 1;
    for(int i = 1;i < argc;i++)
    {
        if(strcmp(argv[i],"-n") == 0)
        {
            if(flags[0] == 1)
            {
                write(2, "Error, Tail: invalid number of lines\n", 37);
                return -1;
            }
            flags[0] = 1;
            words[i] = 0;
            words_number--;
            i++;
            if(argc == i)
            {
                write(2,"Error, Tail: option require an argument -- 'n'\n", 47); 
                return -1;
            }
            if((n_argument = is_nat(argv[i])) == -1)
            {
                write(2,"Error, Tail: option require an argument -- 'n'\n", 47); 
                return -1;
            }
            if(argv[i][0] == '+')
                flags[1] = 1;
            words[i] = 0;
            words_number--;
        }
    }
    int f, a;
    string_struct str_lst;
    int c;
    if(words_number == 0)
    {
        str_lst = init_string_list();
        str_lst = input(str_lst);
        tail_print_string(str_lst, n_argument, flags);
        clean_string_list(str_lst);
        return 1;
    }
    for(int i = 0;i < words_number;i++)
    {
        if(words[i])
        {
            str_lst = init_string_list();
            f = open(argv[1], O_RDONLY);
            if(f < 0)
            {
                write(2,"Error! Tail: cannot open 'test2' for reading: No such file or directory\n", 72);
                return -1;
            }
            dup2(f, 0);
            close(f);
            str_lst = input(str_lst);
            tail_print_string(str_lst, n_argument, flags);
            clean_string_list(str_lst);
        }
    }
    return 0;
}