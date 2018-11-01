#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/limits.h>

int main()
{
    char* path = getcwd(NULL, PATH_MAX);
    write(1, path, PATH_MAX);
    write(1, "\n", 1);
    free(path);
    return 0;
}