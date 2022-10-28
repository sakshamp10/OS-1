#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <libgen.h>
#include <time.h>
int main(int argc,char* argv[])
{
    char* arr1[12]={"January","February","March","April","May","June","July","August","September","October","November","December"};
    char* arr2[12]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sept","Oct","Nov","Dec"};
    char* arr3[7]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
    char* arr4[7]={"Sun","Mon","Tue","Wed","Thur","Fri","Sat"};
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
    //bigArrayD[currtime.tm_wday],currtime.tm_mday,bigarrayM[currtime.tm_mon],(currtime.tm_year+1900),((currtime.tm_hour>=12?currtime.tm_hour-12:currtime.tm_hour)),currtime.tm_min,currtime.tm_sec,((currtime.tm_hour>=12?"PM":"AM")));
    if(tok[0]==NULL || strcmp(tok[0],"-u")==0 || strcmp(tok[0],"--utc")==0 || strcmp(tok[0],"--universal")==0)
    {
        time_t rawtime=time(NULL);
        struct tm * timeinfo;
        timeinfo = localtime(&rawtime);
        int tnet;
        if(timeinfo->tm_hour>=12)
        tnet=timeinfo->tm_hour-12;
        else
        tnet=timeinfo->tm_hour;
        printf("%s %d %s %d %d:%d:%d %s UTC\n",arr3[timeinfo->tm_wday],timeinfo->tm_mday,arr1[timeinfo->tm_mon],(timeinfo->tm_year+1900),tnet,timeinfo->tm_min,timeinfo->tm_sec,timeinfo->tm_hour>=12?"PM":"AM");
    }
    else
    if(strcmp(tok[0],"-R")==0 || strcmp(tok[0],"--rfc-email")==0)
    {
        time_t rawtime=time(NULL);
        struct tm * timeinfo;
        timeinfo = localtime(&rawtime);
        printf("%s, %d %s %d %d:%d:%d %s +%ld\n ",arr4[timeinfo->tm_wday],timeinfo->tm_mday,arr2[timeinfo->tm_mon],(timeinfo->tm_year+1900),timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec,timeinfo->tm_hour>=12?"PM":"AM",timeinfo->tm_gmtoff);
    }
}
