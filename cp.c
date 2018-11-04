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
    struct stat stbuf1, stbuf2;
    stat(argv[1], &stbuf1);
    stat(argv[2], &stbuf2);
    if(stbuf1.st_mode == S_IFDIR)
    {
        write(2,"Error,CP ommiting directory!\n", 29);
        return -1;
    }
    // printf("File1: %s, ino = %ld\n", argv[1], stbuf1.st_ino);
    // printf("File2: %s, ino = %ld\n", argv[2], stbuf2.st_ino);
    if(stbuf1.st_rdev == stbuf2.st_rdev && 
        stbuf1.st_ino == stbuf2.st_ino)
    {
        write(2,"Error,CP same arguments!\n", 25);
        return -1;
    }
    int f1 = open(argv[1], O_RDONLY), f2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, stbuf1.st_mode);
    char buf[100];
    int n = 0;
    while((n = read(f1, buf, 100)) > 0)
        write(f2, buf, n);
    close(f1);
    close(f2);
    return 0;
}