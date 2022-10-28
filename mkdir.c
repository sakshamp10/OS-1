#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <libgen.h>
#include <dirent.h>
#include <errno.h>
int main(int argc,char* argv[])
{
    char *yelo=argv[1];
    /*int len=0;
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
    tok[len]=NULL;*/
    char *comp;
    comp=(char *)malloc(2*sizeof(char));
    comp[0]=argv[1][0];
    comp[1]=argv[1][1];
    if(strcmp(comp,"-p")!=0 && strcmp(comp,"-v")!=0)
    {
        int flag=0;
        for(int i=0;argv[1][i]!='\0';i++)
        {
            if(argv[1][i]=='/')
            {
                printf("mkdir: cannot create directory '%s': No such file or directory",argv[1]);
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            int check;
            char *newdirectory=argv[1];
            check=mkdir(newdirectory,0777);
        }
    }
    else
    if(strcmp(comp,"-p")==0)
    {
        //har *args[2]={" ","hi hi hi/hi"};
        char *newstr;
        newstr=(char*)malloc(256*sizeof(char));int ind=0;
        for(int i=3;argv[1][i]!='\0';i++)
        {
            newstr[ind++]=argv[1][i];
        }
        char * listoffolders[256];int ind2=0;char *folderthis;int ind3=0;
        folderthis=(char *)malloc(256*sizeof(char));
        for(int i=0;i<strlen(newstr);i++)
        {
            if(newstr[i]=='/')
            {
                char *newfolder;
                newfolder=(char *)malloc(256*sizeof(char));
                listoffolders[ind2++]=folderthis;
                folderthis=newfolder;
                ind3=0;
            }
            else
            {
                folderthis[ind3++]=newstr[i];
            }
        }
        listoffolders[ind2++]=folderthis;
        //for(int i=0;i<ind2;i++)
        //{
        //    printf("%s\n",listoffolders[i]);
        //}
        int indcap;
        /*for(int i=0;i<ind2;i++)
        {
            DIR* dir=opendir(listoffolders[i]);
            if(ENOENT==errno)
            {
                indcap=i;
                break;
            }
            else
            {
                int check;
                char *newdirectory=listoffolders[i];
                check=mkdir(newdirectory,0777);
            }
        }
        for(int i=indcap;i<ind2-1;i++)
        {
            chdir(listoffolders[i]);
            int check;
            char *newdirectory=listoffolders[i+1];
            check=mkdir(newdirectory,0777);
        }*/
        for(int i=0;i<ind2;i++)
        {
            int check;
            char *newdirectory=listoffolders[i];
            check=mkdir(newdirectory,0777);
            chdir(newdirectory);
        }
    }
    else
    if(strcmp(comp,"-v")==0)
    {
        //har *args[2]={" ","hi hi hi/hi"};
        char *newstr;
        newstr=(char*)malloc(256*sizeof(char));int ind=0;
        for(int i=3;argv[1][i]!='\0';i++)
        {
            newstr[ind++]=argv[1][i];
        }
        char * listoffolders[256];int ind2=0;char *folderthis;int ind3=0;
        folderthis=(char *)malloc(256*sizeof(char));
        for(int i=0;i<strlen(newstr);i++)
        {
            if(newstr[i]=='/')
            {
                char *newfolder;
                newfolder=(char *)malloc(256*sizeof(char));
                listoffolders[ind2++]=folderthis;
                folderthis=newfolder;
                ind3=0;
            }
            else
            {
                folderthis[ind3++]=newstr[i];
            }
        }
        listoffolders[ind2++]=folderthis;
        //for(int i=0;i<ind2;i++)
        //{
        //    printf("%s\n",listoffolders[i]);
        //}
        int indcap;
        /*for(int i=0;i<ind2;i++)
        {
            DIR* dir=opendir(listoffolders[i]);
            if(ENOENT==errno)
            {
                indcap=i;
                break;
            }
            else
            {
                int check;
                char *newdirectory=listoffolders[i];
                check=mkdir(newdirectory,0777);
            }
        }
        for(int i=indcap;i<ind2-1;i++)
        {
            chdir(listoffolders[i]);
            int check;
            char *newdirectory=listoffolders[i+1];
            check=mkdir(newdirectory,0777);
        }*/
        int flag=0;
        for(int i=0;i<ind2-1;i++)
        {
            DIR* dir=opendir(listoffolders[i]);
            if(ENOENT==errno)
            {
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            for(int i=0;i<ind2-1;i++)
            {
                char *newdirectory2=listoffolders[i];
                chdir(newdirectory2);
            }
            int check;
            char *newdirectory=listoffolders[ind2-1];
            check=mkdir(newdirectory,0777);
            if(check==0)
            {
                printf("mkdir: created directory ");
                for(int i=0;i<ind2-1;i++)
                {
                    printf("%s/",listoffolders[i]);
                }
                printf("%s",listoffolders[ind2-1]);
                chdir(newdirectory);
            }
        }
        else
        {
            printf("mkdir: cannot create directory '");
            for(int i=0;i<ind2-1;i++)
                {
                    printf("%s/",listoffolders[i]);
                }
            printf("%s'",listoffolders[ind2-1]);
            printf(": No such file or directory exists");
        }
    }
}
