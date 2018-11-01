#define NAME_MAX 14 /* максимальная длина имени файла; */
/* системно-зависимая величина */
typedef struct { /* универс. структура элемента каталога: */
long ino; /* номер inode */
char name[NAME_MAX+1]; /* имя + завершающий '\0' */
} Dirent;
typedef struct { /* минимальный DIR: без буферизации и т.д. */
int fd; /* файловый дескриптор каталога */
Dirent d; /* элемент каталога */
} DIR;
DIR *opendir(char *dirname);
Dirent *readdir(DIR *dfd);
void closedir(DIR *dfd);