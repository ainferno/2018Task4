#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef input_size
#define input_size 10u //Определяем размер буффера
#endif
#ifndef array_size
#define array_size 10u //Определяем размер буффера
#endif

//Types
typedef char **string_list;//Массив строк

typedef struct str_lst_struct
{
    string_list array;
    int size, size_current;
}string_struct;

//Functions string list
void copy_str(char*, char*);//Копирует строку 2 в строку 1 посимвольно
int copy_int(char*, int);//Копирует integer 2 в строку 1 посимвольно, возвращает количество символов
string_struct add_string_list(string_struct, char*, int);//Добавляет строку в конец массива строк, возвращает этот массив
string_struct clean_string_list(string_struct);//Отчищает массив. НЕ ВЕРНО ТАК КАК ПРИСУТСВУЕТ УТЕЧКА ПАМЯТИ
void print_string_list(string_struct);//Выводит массив строк в stdout, через пробелы заканчивая \n
void sort_string_list(string_struct);//Сортирует массив строк по возрастанию методом простого выбора
string_struct init_string_list();//Выделяет памят под массив строк, возвращает этот массив

void tail_print_string(string_struct, int, int*);
void sort_sort_list(string_struct, int, int*);
int str_cmp(char*, char*, int, int, int);
char down_char(char);