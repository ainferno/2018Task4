#include <stdio.h>
#include <string.h>
#include <unistd.h>

/*
flags[0] = -n = now newline
flags[1] = -e = enable backslash escapes = 1, -E = disable backslash escapes = 0
*/

int is_oct_digit(char a)
{
    return (a >= '0') && (a <= '7');
}
int is_hex_digit(char a)
{
    return (a >= '0') && (a <= '9') || 
        (a == 'A') || (a == 'a') ||
        (a == 'B') || (a == 'b') ||
        (a == 'C') || (a == 'c') ||
        (a == 'D') || (a == 'd') ||
        (a == 'E') || (a == 'e') ||
        (a == 'F') || (a == 'f');
}

int backslash_seq(char* word)
{
    int word_l = strlen(word), i = 0, c = 0;
    char word2[word_l];

    for(int j = 0;j < word_l;i++)
    {
        if(word[j] == '\\' && (j+1) < word_l)
        {
            switch(word[++j])
            {
                case 'a':
                    word2[i] = '\a';
                    break;
                case 'b':
                    word2[i] = '\b';
                    break;
                case 'c':
                    write(1,word2,i);
                    return 1;
                case 'e':
                    word2[i] = '\e';
                    break;
                case 'f':
                    word2[i] = '\f';
                    break;
                case 'n':
                    word2[i] = '\n';
                    break;
                case 'r':
                    word2[i] = '\r';
                    break;
                case 't':
                    word2[i] = '\t';
                    break;
                case 'v':
                    word2[i] = '\v';
                    break;
                case '0':
                    c = 0;
                    if(is_oct_digit(word[j+1]))
                        c = word[++j] - '0';
                    if(is_oct_digit(word[j+1]))
                        c = c * 8 + word[++j] - '0';
                    if(is_oct_digit(word[j+1]))
                        c = c * 8 + word[++j] - '0';
                    word2[i] = c;
                    break;
                case 'x':
                    c = 0;
                    if(is_hex_digit(word[j+1]))
                        c = word[++j] - '0';
                    if(is_hex_digit(word[j+1]))
                        c = c * 16 + word[++j] - '0';
                    word2[i] = c;
                    break;
                default:
                    word2[i] = '\\';
                    break;
            }
            j++;
        }
        else
            word2[i] = word[j++];
    }
    write(1,word2,i);
    return 0;
}

int main(int argc, char* argv[])
{
    int flags[2] = {0,0}, words[argc-1], words_number = argc-1;

    for(int i = 0;i < argc-1;i++)
        words[i] = 1;
    for(int i = 1;i < argc;i++)
    {
        if(strcmp(argv[i], "-e") == 0)
        {
            words[i-1] = 0;
            words_number--;
            flags[1] = 1;
        }
        else if(strcmp(argv[i], "-E") == 0)
        {
            words[i-1] = 0;
            words_number--;
            flags[1] = 0;
        }
        else if(strcmp(argv[i], "-n") == 0)
        {
            words[i-1] = 0;
            words_number--;
            flags[0] = 1;
        }
        else
            break;
    }
    for(int i = 1, j = 0;i < argc;i++)
    {
        if(words[i-1])
        {
            j++;
            if(flags[1])
            {
                if(backslash_seq(argv[i]))
                    return 0;
            }
            else
                write(1, argv[i], strlen(argv[i]));
            if(j < words_number)
            {
                write(1, " ", 1);
            }
        }
    }
    if(!flags[0])
        write(1, "\n", 1);
    return 0;
}