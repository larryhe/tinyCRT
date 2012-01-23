/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  test our tiny CRT library
 *
 *        Version:  1.0
 *        Created:  01/17/2012 02:54:44 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include "tinycrt.h"

int main(int argc, char* argv[])
{
    int i;
    FILE* fp;
    char** v = malloc(argc * sizeof(char*));
    for(i = 0; i < argc; ++i){
        v[i] = malloc(strlen(argv[i]) + 1);
        strcpy(v[i], argv[i]);
    }

    fp = fopen("test.txt", "w");
    for(i = 0; i < argc; ++i){
        int len = strlen(v[i]);
        fwrite(&len, 1, sizeof(int), fp);
        fwrite(v[i], 1, len, fp);
    }
    fclose(fp);

    fp = fopen("test.txt", "r");
    for(i=0; i < argc; ++i){
        int len;
        char* buf;
        fread(&len, 1, sizeof(int), fp);
        buf = malloc(len + 1);
        fread(buf, 1, len, fp);
        buf[len] = '\0';
        printf("%d %s\n", len, buf);
        free(buf);
        free(v[i]);
    }
    fclose(fp);
    printf("size of int=%d and size of char*=%d size of unsigned=%d size of double=%d size of char=%d\n", sizeof(int), sizeof(char*), sizeof(unsigned), sizeof(double), sizeof(char));
    int a[] = {2, 3};
    char* str[] = {"string1 helloworld long text","string2"};
    char as[] = {'a','b'};
    for (i = 0; i < 2; i++) {
        printf("address of int=%d and addr of string=%d and char=%d\n",(a+i),(str+i),(as+i));
    }
}
