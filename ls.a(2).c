#include <stdio.h>
#include <dirent.h>
#include <string.h> 
#include<stdlib.h>
int compare_str(const void*a,const void*b)
{
    return strcmp((const char*)a,(const char*)b);
}
int main(int argc,char*argv[])
{
    if(argc!=2)
    {
        return 0;
    }
    char names[10000][256];
    DIR *dp = opendir(argv[1]);
    if (dp == NULL)
    {
        perror("opendir");
        return 1;
    }
    int i = 0;
    struct dirent *entry;
    while ((entry = readdir(dp)) != NULL)
    {
        strcpy(names[i], entry->d_name);
        i++;
    }
    closedir(dp); 
    qsort(names,i,sizeof(names[0]),compare_str);
    int max_len=0;
    for(int k=0;k<i;k++)
    {
        int len=strlen(names[k]);
        if(len>max_len)
        max_len=len;
    }
    for (int k = 0; k < i; k++)
    {
        printf("%-*s",max_len+2, names[k]);
    }
    printf("\n");
    return 0;
}