#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "sh.h"
#include "help.h"

/*
flags(0,0,0,0) - no flags
flags[0] - -r reverse order
flags[1] - -f A = a
flags[2] - -n in length order
flags[3] - +<n> = fron n string
*/
int main(int argc, char* argv[])
{
    int words[(argc > 1) ? argc-1 : 1], words_number = argc - 1, flags[4] = {0, 0, 0, 0}, n_argument= 0;
    for(int i = 0;i < argc-1;i++)
        words[i] = 1;
    for(int i = 1;i < argc;i++)
    {
        if(strcmp(argv[i], "-r") == 0)
        {
            words[i-1] = 0;
            words_number--;
            flags[0] = 1;
        }
        if(strcmp(argv[i], "-f") == 0)
        {
            words[i-1] = 0;
            words_number--;
            flags[1] = 1;
        }
        if(strcmp(argv[i], "-n") == 0)
        {
            words[i-1] = 0;
            words_number--;
            flags[2] = 1;
        }
        if(argv[i][0] == '+')
        {
            words[i-1] = 0;
            words_number--;
            flags[3] = 1;
            if((n_argument = is_nat(argv[i])) == -1)
            {
                write(2,"Error, Tail: option require an argument -- 'n'\n", 47); 
                return -1;
            }
        }
    }
    // printf("Flags[0,1,2,3] = [%d, %d, %d, %d], n = %d\n", flags[0], flags[1], flags[2], flags[3], n_argument);
    int f, a;
    string_struct str_lst;
    int c;
    if(words_number == 0)
    {
        str_lst = init_string_list();
        str_lst = input(str_lst);
        sort_sort_list(str_lst, n_argument, flags);
        print_string_list(str_lst);
        clean_string_list(str_lst);
        return 1;
    }
    for(int i = 1;i < argc;i++)
    {
        if(words[i-1])
        {
            str_lst = init_string_list();
            f = open(argv[i], O_RDONLY);
            if(f < 0)
            {
                write(2,"Error! Tail: cannot open 'test2' for reading: No such file or directory\n", 72);
                return -1;
            }
            dup2(f, 0);
            close(f);
            str_lst = input(str_lst);
        }
    }
    sort_sort_list(str_lst, n_argument, flags);
    print_string_list(str_lst);
    clean_string_list(str_lst);
    return 0;
}