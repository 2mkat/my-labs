#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include <stdlib.h>

#define ERR_NO_FILE 1
#define ERR_NOT_FOUND 2
#define ERR_BAD_ARGS 3

void print_context(char *set_of_key, char *end_of_key, int len_context, int len, FILE* f)
{
    fgets(set_of_key, len_context + len, f);
    printf("%s", set_of_key);
    fseek(f, 0, SEEK_CUR);
    fgets(end_of_key, len_context, f);
    printf("%s\n", end_of_key);
}

int getResult(FILE* f, char* flag, int temp)        // func find key word
{
    int len = strlen(flag);
    char *end_of_key = (char*)calloc(20, sizeof(char));
    char *set_of_key = (char*)calloc(20 + len, sizeof(char));
    int count = 0;
    char *trafaret = (char*)calloc(len, sizeof(char));
    int len_context = 20;
    int pos = 0;
    while (!feof(f))
    {
        trafaret[count] = (char)fgetc(f);
        count++;
        if (count == len)
        {
            count = 0;
            pos++;
            if (!strcmp(trafaret, flag))
            {
                int si = fseek(f, -20 - len, SEEK_CUR);
                if(si >=0)
                {
                    print_context(set_of_key, end_of_key, len_context, len, f);
                    temp++;
                }
                 else
                {
                    int cur_pos = ftell(f);
                    len_context = len_context + (cur_pos - len_context);
                    fseek(f, 0, SEEK_SET);
                    print_context(set_of_key, end_of_key, len_context, len, f);
                    temp++;
                }
            }

            fseek(f, pos, SEEK_SET);
        }
    }
    return temp;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <FILE> <KEY>\n\twhere <FILE> is path to the file you want to grep", argv[0]);
        return ERR_BAD_ARGS;
    }

    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        perror("Error\n");
        return ERR_NO_FILE;
    }
    int temp = 0;
    temp = getResult( f, argv[2], temp);        // argv[1] - file.name argv[2] - key word
    if (!temp)
    { 
        printf("Usage: %s <KEY>\n\tI can't find\n", argv[0]);
        return ERR_NOT_FOUND;
    }
    fclose(f);
    return 0;
}   