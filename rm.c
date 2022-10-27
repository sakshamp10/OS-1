#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <libgen.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
int main(int agrc,char *argv[])
{
    int len=0;
    int cap=16;
    char **tok=malloc(16*sizeof(char *));
    char *delim=" \t\r\n";
    char *token=strtok(argv[1],delim);
    while(token!=NULL)
    {
        tok[len]=token;
        len++;
        if(len>=cap)
        {
            cap=(int)(cap*1.5);
            tok=realloc(tok,cap*sizeof(char*));
        }
        token=strtok(NULL,delim);
    }
    tok[len]=NULL;
    if(strcmp(tok[0],"-i")!=0 && strcmp(tok[0],"-v")!=0)
    {
        int checkrem=0;
        DIR *dir=opendir(".");
        struct stat st;
        struct dirent *dir;
        dir=readdir(dirr);
        while(dir!=NULL)
        {
            if(strcmp(dir->d_name,tok[1])==0)
            {
                stat(dir->d_name,&st);
                if(!(S_ISREG(st.st_mode)))
                {
                    printf("Cannot delete the directory\n");
                }
            }
            int r=remove(dir->d_name);
            dir=readdir(dirr);
        }
    }
    if(strcmp(tok[0],"-i")==0)
    {
        int checkrem=0;
        DIR *dir=opendir(".");
        struct stat st;
        struct dirent *dirr;
        dir=readdir(dirr);
        while(dir!=NULL)
        {
            if(strcmp(dir->d_name,tok[1])==0)
            {
                stat(dir->d_name,&st);
                if(!(S_ISREG(st.st_mode)))
                {
                    printf("Cannot delete the directory\n");
                }
            }
            char inp;
            printf("Do you want to remove the file: %s?[Y/n] ",tok[1]);
            scanf("%c",&inp);
            if(c=='Y' || c=='y')
            {
                int r=remove(dir->d_name);
                if(r==0)
                {
                    checkrem=1;
                    break;
                }
            }
            dir=readdir(dirr);
        }
        if(checkrem==0)
        {
            printf("Could not delete directory");
        }
    }
    else
    if(strcmp(tok[0],"-v")==0)
    {
        int checkrem=0;
        DIR *dir=opendir(".");
        struct stat st;
        struct dirent *dirr;
        dir=readdir(dirr);
        while(dir!=NULL)
        {
            if(strcmp(dir->d_name,tok[1])==0)
            {
                stat(dir->d_name,&st);
                if(!(S_ISREG(st.st_mode)))
                {
                    printf("Cannot delete the directory\n");
                }
            }
            int r=remove(dir->d_name);
            if(r==0)
            {
                printf("Directory deleted successfully");
                chrckrem=1;
                break;
            }
            dir=readdir(dirr);
        }
        if(checkrem==0)
        {
            printf("Could not delete directory");
        }
    }
}
