// "This program uses three threads to perform the different case conversions. The input string and the desired case conversion type are passed as command line arguments. The program creates the appropriate thread based on the case conversion argument and waits for the thread to finish using `pthread_exit`.  Copy the below code and save as threads_strings.c". Fill in the appropriate code and upload to Gradescope (will be auto-graded).
// To compile this program use gcc -lpthread -o threads_strings threads_strings.c
// Once the program has been compiled, you can run it by typing the following command in the terminal or command prompt:

// ./threads_strings string_to_convert case_conversion
// Replace "string_to_convert" with the actual string you want to convert and replace "case_conversion" with either "lower", "sentence", or "upper" depending on the desired case conversion.

// ##########################NOT FOR GRADES#################

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#include<string.h>

char* str;
int case_flag;

void* to_lower_case(void* arg)
{
    char* p = str;
    while(*p)
    {
        *p = tolower(*p);
        p++;
    }
    case_flag = 1;
    pthread_exit(NULL);
}

void* to_sentence_case(void* arg)
{
    char* p = str;
    *p = toupper(*p);
    p++;
    while(*p)
    {
        if(*p == '.')
        {
            p++;
            if (*p == ' ') {
                while (*p == ' ') {
                    p++;
                }
            }
            
            if(*p) *p = toupper(*p);
        }
        else *p = tolower(*p);

        p++;
    }
    case_flag = 2;
    pthread_exit(NULL);
}

void* to_upper_case(void* arg)
{
    char* p = str;
    while(*p)
    {
        *p = toupper(*p);
        p++;
    }
    case_flag = 3;
    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Usage: ./program_name string_to_convert case_conversion\n");
        return 1;
    }

    str = argv[1];
    pthread_t thread1, thread2, thread3;
    int rc;

    if(strcmp(argv[2], "lower") == 0)
    {
        rc = pthread_create(&thread1, NULL, to_lower_case, (void *)str);
        if(rc)
        {
            printf("Error creating thread\n");
            return 1;
        }
    }
    else if(strcmp(argv[2], "sentence") == 0)
    {
        rc = pthread_create(&thread2, NULL, to_sentence_case, (void *)str);
        if(rc)
        {
            printf("Error creating thread\n");
            return 1;
        }
    }
    else if(strcmp(argv[2], "upper") == 0)
    {
        rc = pthread_create(&thread3, NULL, to_upper_case, (void *)str);
        if(rc)
        {
            printf("Error creating thread\n");
            return 1;
        }
    }
    else
    {
        printf("Invalid case conversion argument.\n");
        return 1;
    }
    printf("Converted string: %s\n", str);
    pthread_exit(NULL);
 
    return 0;
}