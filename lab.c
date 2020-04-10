#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include <stdlib.h>

#define ERR_NO_FILE 1
#define ERR_NOT_FOUND 2
#define ERR_BAD_ARGS 3
#define ERR_BAD_MODE 4

#define PUNCT   "!,?.;"

FILE* open_file(char* file_name, char* mode)    // function open files and check them
{
    if(mode[0] != 'w' && mode[0] != 'r')
    {
        perror("Error\n");
        exit(ERR_BAD_MODE);
    }
    FILE *file = fopen(file_name, mode);

    if (file == NULL)
    {
        perror("Error\n");
        exit(ERR_NO_FILE);
    }
    return file;
}

void context(char *set_of_key, char *end_of_key, int len, FILE* f, int temp)
{
    fgets(set_of_key, 20 + len, f);
    printf("%s", set_of_key);
    fseek(f, 0, SEEK_CUR);
    fgets(end_of_key, 26, f);
    printf("%s\n", end_of_key);
    temp++;
}

int check(FILE* f, int temp)        // func check existence word
{
   if (!temp)
    {
       // printf("Not found\n");
        return ERR_NOT_FOUND;
    }
    fclose(f); 
    return 0;
}

void getResult(char* file_name2, char* flag)        // func find key word
{
    int temp = 0;
    char array[255];
    char *var;
    var = flag;
    char *key = var;

    FILE *f = open_file(file_name2, "r");

    printf("\n");
    int len = strlen(key);
    char *end_of_key = (char*)calloc(20, sizeof(char));
    char *set_of_key = (char*)calloc(20, sizeof(char));

    while (!feof(f))
    {
        fscanf(f, "%s", array);
        char *pch = strtok(array, PUNCT);
        if (!strcmp(pch, key)) 
        {
            int si = fseek(f, -20 - len, SEEK_CUR);
            if (si >= 0) 
            {
                context(set_of_key, end_of_key,len,f,temp);
            } 
            else 
            {
                fseek(f, 0, SEEK_SET);
                context(set_of_key,end_of_key,len,f,temp);
            }
        }
    }
    check(f, temp);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("%s\n", "Bad args");
        return ERR_BAD_ARGS;
    }
    getResult(argv[1], argv[2]);        // argv[1] - file.name argv[2] - key word
}