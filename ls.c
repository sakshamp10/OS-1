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
int main(int agrc, char* argv[])
{
    if(strcmp(argv[1],"")==0)
    {
        struct dirent *dir;
        DIR *dhthis=opendir(".");
        if(dhthis==0)
        {
            if(errno==ENOENT)
            {
                perror("No such directory exists\n");
            }
            else
            {
                perror("Unable to read directory");
            }
            exit(EXIT_FAILURE);
        }
        dir=readdir(dhthis);
        while(dir!=NULL)
        {
            if(dir->d_name[0]!='.')
            {
                printf("%s ",dir->d_name);
            }
            dir=readdir(dhthis);
        }
        printf("\n");
    }
    else
    if(strcmp(argv[1],"-a ")==0)
    {
        struct dirent *dir;
        DIR *dhthis=opendir(".");
        if(dhthis==0)
        {
            if(errno==ENOENT)
            {
                perror("No such directory exists\n");
            }
            else
            {
                perror("Unable to read directory");
            }
        
            exit(EXIT_FAILURE);
        }
        dir=readdir(dhthis);
        while(dir!=NULL)
        {
            printf("%s ",dir->d_name);
            dir=readdir(dhthis);
        }
        printf("\n");
    }
    else
    if(strcmp(argv[1],"-p ")==0)
    {
        struct dirent *dir;
        DIR *dhthis=opendir(".");
        struct stat st;
        if(dhthis==0)
        {
            if(errno==ENOENT)
            {
                perror("No such directory exists\n");
            }
            else
            {
                perror("Unable to read directory");
            }
        
            exit(EXIT_FAILURE);
        }
        dir=readdir(dhthis);
        while(dir!=NULL)
        {
            stat(dir->d_name,&st);
            if(S_ISDIR(st.st_mode) && dir->d_name[0]!='.')
            {
                printf("%s/ ",dir->d_name);
            }
            else
            if(dir->d_name[0]!='.')
            {
                printf("%s ",dir->d_name);
            }
            dir=readdir(dhthis);
        }
        printf("\n");
    }
}
