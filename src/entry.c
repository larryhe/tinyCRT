/*
 * =====================================================================================
 *
 *       Filename:  entry.c
 *
 *    Description:  this is entry function of tiny CRT
 *
 *        Version:  1.0
 *        Created:  01/16/2012 12:46:37 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Larry He
 *        Company:  
 *
 * =====================================================================================
 */
#include "tinycrt.h"

#ifdef WIN32
#include <Windows.h>
#endif

extern int main(int argc, char* argv[]);
void exit(int);

static void crt_fatal_error(const char* msg)
{
    printf("fatal error: %s",msg);
    exit(1);
}

void tiny_crt_entry(void)
{
    int ret;

#ifdef WIN32
    int flag = 0;
    int argc = 0;
    char* argv[16];//max 16 arguments contrains
    char* cl = GetCommandLineA();
    //parse commnad line
    argv[0] = cl;
    argc++;
    while(*cl){
        if(*cl == '\"')
            if(flag == 0) flag = 1;
            else flag = 0;
        else if(*cl == ' ' && flag == 0) {
            if(*(cl+1)) {
                argv[argc] = cl + 1;
                argc++;
            }
            *cl = '\0';
        }
        cl++;
    }
#else
    int argc;
    char ** argv;

    char* ebp_reg = 0;
    //ebp_reg = %ebp
    asm("movl %%ebp,%0 \n":"=r"(ebp_reg));

    argc = *(int*)(ebp_reg + 4);
    argv = (char**)(ebp_reg + 8);
#endif
    if(!tiny_crt_heap_init())
        crt_fatal_error("heap initialize failed");

    if(!tiny_crt_io_init())
        crt_fatal_error("IO initialize failed");

    ret = main(argc, argv);
    exit(ret);
}

void exit(int exitCode)
{
#ifdef WIN32
    ExitProcess(exitCode);
#else
    asm( "movl %0,%%ebx \n\t"
         "movl $1,%%eax \n\t"
         "int $0x80     \n\t"
         "hlt           \n\t"::"m"(exitCode));
#endif
}
