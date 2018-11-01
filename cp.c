#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int str_eq(char* a, char* b)
{
    for(;*a == *b;*a++,*b++)
        if(*b == '\0')
            return 1;
    return 0;
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        switch(argc)
        {
            case 1:
                write(2,"Error, CP no arguments!\n", 25);
                break;
            case 2:
                write(2,"Error, CP too few arguments!\n", 29);
                break;
            default:
                write(2,"Error, CP too many arguments!\n", 30);
                break;
        }
        return -1;
    }
    if(str_eq(argv[1], argv[2]))
    {
        write(2,"Error,CP same arguments!\n", 25);
        return -1;
    }
    struct stat stbuf;
    stat(argv[1], &stbuf);
    int f1 = open(argv[1], O_RDONLY), f2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, stbuf.st_mode);
    char buf[100];
    int n = 0;
    while((n = read(f1, buf, 100)) > 0)
        write(f2, buf, n);
    close(f1);
    close(f2);
    return 0;
}