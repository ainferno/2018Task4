#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
    char *name;
    struct stat stbuf;
    int stat(char *, struct stat *);
    stat(name, &stbuf);
    return 0;
}