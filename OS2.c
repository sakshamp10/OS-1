#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <libgen.h>
char* cd_read_line()
{
    char *line=NULL;
    size_t bufl=0;
    getline(&line,&bufl,stdin);
    return line;
}
char** cd_split_line(char *line)
{
    int len=0;
    int cap=16;
    char **tok=malloc(16*sizeof(char *));
    char *delim=" \t\r\n";
    char *token=strtok(line,delim);
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
    return tok;
}
void pwd()
{
    char cwdarr[256];
    if(getcwd(cwdarr, sizeof(cwdarr))==NULL)
    {
        perror("directory error ");
    }
    else
    {
        printf("The current working directory is: %s\n", cwdarr);
    }
}
void echo(char **args)
{
    int flag=0;
    if(args[1]==NULL)
    {
        printf("\n");
        return;
    }
    if(strcmp(args[1],"-n")==0)
    {
        flag=1;
    }
    int start=1;
    if(flag==1)
    {
        start=2;
    }
    else
    {
        start=1;
    }
    for(int i=start;args[i]!=NULL;i++)
    {
//        char *st=args[i];
        if(args[i+1]==NULL && flag==1)
        {
            args[i]=strtok(args[i],"\n");
        }
        else
        {
            args[i]=args[i];
//            printf("%s",st);
        }
//        printf("%s",st);
        for(int j=0;args[i][j]!='\0';j++)
        {
            if(args[i][j]!='\\')
            {
                if(args[i][j]=='$')
                {
                    int count=0;
                    while(args[i][j]=='$')
                    {
                        count++;
                        j++;
                    }
                    j-=1;
                    int pid=getpid();
                    for(int l=0;l<count/2;l++)
                    printf("%d",pid);
                }
                else
                {
                    printf("%c",args[i][j]);
                }
            }
            else
            if(args[i][j]=='\\')
            {
                while(args[i][j]=='\\' && args[i][j+1]=='\\')
                {
                    printf("%c",'\\');
                    j+=2;
                }
                if(args[i][j]!='\\')
                j-=1;
            }
            else
            {
                printf("%c",args[i][j]);
            }
        }
        printf(" ");
    }
    if(flag!=1)
    printf("\n");
}
void cd(char **args)
{
    int ct=0;
    for(int i=1;args[i]!=NULL;i++)
    {
        ct++;
    }
    if(ct>1)
    {
        printf("too many arguments\n");
        return;
    }
    else
    {
        if(ct==1)
        {
            if(strcmp(args[1],"/")==0)
            {
                chdir("/");
            }
            else
            {
                int suc=chdir(args[1]);
                if(suc==-1 && strcmp(args[1],"~")!=0)
                {
                    printf("No such file or directory");
                }
            }
        }
        else
        if(ct==0)
        {
            chdir("/Users/chaitanyadua");
        }
    }
}
void cd_exec(char **args)
{
    if(strcmp(args[0],"pwd")==0 || strcmp(args[0],"pwd\n")==0)
    {
        pwd();
        return;
    }
    else
    if(strcmp(args[0],"echo")==0)
    {
        echo(args);
        return;
    }
    else
    if(strcmp(args[0],"cd")==0)
    {
        cd(args);
        return;
    }
    /*pid_t child_pid=fork();
    if(child_pid==0)
    {
        execvp(args[0],args);
        perror("cd");
        exit(1);
    }
    else
    if(child_pid>0)
    {
        int status;
        do
        {
            waitpid(child_pid, &status,WUNTRACED);
        }
        while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    else
    {
        perror("cd");
    }*/
}
int main()
{
    printf("Chaitanya's shell...........\n");
    while(1)
    {
        //printf("Chaitanya's shell.........\n");
        char *a=NULL;
        char *i=getcwd(a,0);
        printf("[ %s ]$ ",basename(i));
        char *line=cd_read_line();
        char **tok=cd_split_line(line);
        if(strcmp(tok[0],"exit")==0)
        {
            break;
        }
        if(tok[0]!=NULL)
        {
            cd_exec(tok);
        }
        free(tok);
        free(line);
    }
    return 0;
}
