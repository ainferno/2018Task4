#include <stdio.h>
#include <unistd.h>

int main()
{
    char* path = getcwd(NULL, 1024);
    write(1, path, 1024);
    write(1, "\n", 1);
    return 0;
}