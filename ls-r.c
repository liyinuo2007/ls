#include<stdio.h>
#include<dirent.h>
#include<string.h>
#include<stdlib.h>
int global_reverse=0;
int compare_str(const void *a,const void*b)
{
    int result=strcmp((const char*)a,(const char*)b);
    if(global_reverse)
    return -result;
    return result;
}
int main(int argc,char*argv[])
{
    int opt_r=0;
    const char * path=".";
    for(int j=1;j<argc;j++)
    {
        if(strcmp(argv[j],"-r")==0)
        {
            opt_r=1;
        }
        else
        {
            path=argv[j];
        }
    }
    global_reverse=opt_r;
    DIR*dp=opendir(path);
    char name[1000][256];
    int i=0;
    struct dirent*entry;
    while((entry=readdir(dp))!=NULL)
    {
        strcpy(name[i],entry->d_name);
        i++;
    }
    closedir(dp);
    qsort(name,i,sizeof(name[0]),compare_str);
    for(int k=0;k<i;k++)
    printf("%s\n",name[k]);
    return 0;
}