#include <stdio.h> 
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>

void display_permission (int);
void display_file_type (int);
void Directions(DIR*,int, int);
int flags(int ,char**, int*, int*);

char* int_to_char(long int a)
{
    char c1[30];
    char* c2;
    c2 = (char*)malloc(sizeof(char) * 30);
    int i = 0, j = 0, n;
    if(a == 0)
    {
        c2[0] = '0';
        c2[1] = '\0';
    }
    else
    {
        for(;a > 0;i++,a/=10)
            c1[i] = a%10 + '0';
        n = i--;
        for(;j < n;j++,i--)
            c2[j] = c1[i];
        c2[j] = '\0';
    }
    return c2;
}

void display_permission ( int st_mode )  //Процедура, которая выписывает права
{
    static const char xtbl[10] = "rwxrwxrwx";
    char amode[10];
    for (int i = 0, j = (1 << 8); i < 9;i++, j >>= 1) //Сдвигаем число(набор битов - прав) влево и смотрим, 1 или 0
        amode[i] = (st_mode & j) ? xtbl[i]: '-'; //Если 0 - пишем '-', если 1 - пишем букву из списка xtbl
    if (st_mode & S_ISUID)
        amode[2] = 's'; //S_ISUID - имя пользователя.
    if (st_mode & S_ISGID)
        amode[5] = 's';  //S_ISGID - имя группы.
    if (st_mode & S_ISVTX)
        amode[8] = 't'; //S_ISVTX - принадлежность.
    amode[9] = '\0'; //Чтобы вывести строку.
    write(1, amode, 10);
}

void display_file_type (int st_mode) //Процедура, которая определяет тип файла
{                                   
    switch (st_mode & S_IFMT) 
    {
        case S_IFDIR:
            write(1, "d", 1);
            return; //Директория.
        case S_IFCHR:
            write(1, "c", 1);
            return;
        case S_IFBLK:
            write(1, "b", 1);
            return;
        case S_IFREG:
            write(1, "-", 1);
            return; //Файл.
        case S_IFLNK:
            write(1, "l", 1);
            return;
        case S_IFSOCK:
            write(1, "s", 1);
            return;
    }
} 

void Directions(DIR *dir,int l,int g) //Рекурсивная процедура обхода директорий, и печати содержимого
{
    struct dirent *entry;
    struct stat buf;
    struct passwd  *pw_d;
    int i,j = 0,k = 0;
    char* name[1000];
    char* num;

    while ( (entry = readdir(dir)) != NULL) 
    {
        if(entry->d_name[0]!='.')
        {
            name[j] = entry->d_name;
            j++;
        }
    }
    for(k = 0;k < j;k++)
    {
        stat(name[k],&buf);
        if(l || g)
        {
            display_file_type(buf.st_mode); //Выводим тип файла.
            display_permission (buf.st_mode); //Выводим права пользователя.
            pw_d = getpwuid ( buf.st_uid ); //Получаем и выводим имя пользователя.
            write(1, pw_d->pw_name, strlen(pw_d->pw_name));
            if(g) 
            {
                pw_d = getpwuid ( buf.st_gid ); //Если -g = 1 получаем и выводим имя группы.
                write(1, " ", 1);
                write(1, pw_d->pw_name, strlen(pw_d->pw_name));
            }
            num = int_to_char(buf.st_size);
            write(1, " ", 1);
            write(1, num, strlen(num));
            free(num);
        }
        write(1, " ", 1);
        write(1, name[k], strlen(name[k]));
        write(1, "\n", 1);
        if((buf.st_mode & S_IFMT) == S_IFDIR) //Рекурсивно обходим директории.
        {
            dir = opendir(name[k]);
            chdir(name[k]);
            Directions(dir,l,g);
            chdir("..");
            closedir(dir);
        }
    }
    return;
}

int get_flags(int argc,char* argv[],int* flags) //Функция, которая определяет флаги, и передаёт номер следующего аргумента
{
    int i = 1, flags_check = 1;
    while(flags_check && i < argc)
    {
        if(!strcmp(argv[i],"-R")) 
        {
            flags[0] = 1;
            i++;
        }
        else if(!strcmp(argv[i],"-l"))
        {
            flags[1] = 1;
            i++;
        }
        else if(!strcmp(argv[i],"-g")) 
        {
            flags[2]=1;
            i++;
        }
        else
            flags = 0;
    }
    return i;
}

//flags[0] = -R
//flags[1] = -l
//flags[2] = -g

int main(int argc,char *argv[])
{
    DIR *dir;
    struct dirent *entry;
    struct stat buf;
    struct passwd  *pw_d;
    int i,flags[3] = {0, 0, 0}, j = 0, k = 0;
    char c;
    char* s;
    char* num;
    char** name = (char**)malloc(sizeof(char)*BUFSIZ);

    i = get_flags(argc,argv,flags);
    if(argv[i] == NULL)
    {
        argv[i]=".";
        argc++;
    }
    for(;i < argc;i++)
    {
        if(flags[0] == 0 && flags[1] == 0 && flags[2] == 0)
        {
            dir = opendir(argv[i]);
            stat(argv[i], &buf);
            if((buf.st_mode & S_IFMT) == S_IFDIR)
            {
                while ((entry = readdir(dir)) != NULL) 
                {
                    if(entry->d_name[0] != '.')
                    {
                        write(1, entry->d_name, strlen(entry->d_name));
                        write(1, "\n", 1);
                    }
                }
                closedir(dir);
            }
            else
            {
                write(1, argv[i], strlen(argv[i]));
                write(1, "\n", 1);
            }
        }
        if(flags[0])
        {
            dir = opendir(argv[i]);
            chdir(argv[i]);
            Directions(dir,flags[1],flags[2]);
            chdir("..");
            closedir(dir);
        }
        if((flags[1] || flags[2]) && !flags[0])
        {
            dir = opendir(argv[i]);
            stat(argv[i],&buf);
            if((buf.st_mode & S_IFMT) == S_IFDIR)
            {
                chdir(argv[i]);
                while ( (entry = readdir(dir)) != NULL) 
                {
                    if(entry->d_name[0] != '.')
                    {
                        stat(entry->d_name,&buf);
                        display_file_type(buf.st_mode); //Выводим тип файла.
                        display_permission (buf.st_mode); //Выводим права пользователя.
                        pw_d = getpwuid ( buf.st_uid ); //Выводим имя пользователя.
                        write(1, " ", 1);
                        write(1, pw_d->pw_name, strlen(pw_d->pw_name));
                        if(flags[2]) 
                        {
                            pw_d = getpwuid (buf.st_gid); //Если поднят -g выводим имя группы.
                            write(1, " ", 1);
                            write(1, pw_d->pw_name, strlen(pw_d->pw_name));
                        }
                        num = int_to_char(buf.st_size);
                        write(1, " ", 1);
                        write(1, num, strlen(num));
                        write(1, " ", 1);
                        write(1, entry->d_name, strlen(entry->d_name));
                        write(1, "\n", 1);
                        free(num);
                    }
                }
                chdir("..");
            }
            else
            {
                write(1, argv[i], strlen(argv[i]));
                write(1, "\n", 1);
            }
            closedir(dir);
        }
    }
    return 0;
}