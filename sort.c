#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int str_eq(char* a, char* b)
{
    for(;*a == *b;*a++,*b++)
        if(*b == '\0')
            return 1;
    return 0;
}

int main(int argc, char* argv[])
{
    int flags[4] = {0,0,0,o}, words[argc-1], words_number = argc-1;

    for(int i = 0;i < argc-1;i++)
        words[i] = 1;
    for(int i = 1;i < argc;i++)
    {
        if(str_eq(argv[i], "-r"))
        {
            words[i-1] = 0;
            words_number--;
            flags[1] = 1;
        }
        if(str_eq(argv[i], "-f"))
        {
            words[i-1] = 0;
            words_number--;
            flags[1] = 0;
        }
        if(str_eq(argv[i], "-n"))
        {
            words[i-1] = 0;
            words_number--;
            flags[0] = 1;
        }
        // if(str_eq(argv[i], "-n"))
        // {
        //     words[i-1] = 0;
        //     words_number--;
        //     flags[0] = 1;
        // }
    }

    /*if(argc != 2)
    {
        switch(argc)
        {
            case 1:
                write(2,"Error, CP no arguments!\n", 25);
                break;
            default:
                write(2,"Error, CP too many arguments!\n", 30);
                break;
        }
        return -1;
    }*/
    // int f1 = open(argv[1], O_RDONLY), f2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    // char buf[100];
    // int n = 0;
    // while((n = read(f1, buf, 100)) > 0)
    //     write(f2, buf, n);
    // close(f1);
    // close(f2);
    return 0;
}