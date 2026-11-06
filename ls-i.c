#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
struct file_info
{
    unsigned long ino;
    char names[256];
};
int compare_str(const void*a,const void*b)
{
    const struct file_info*fa=(const struct file_info*)a;
    const struct file_info*fb=(const struct file_info*)b;
    return strcmp(fa->names,fb->names);
}
int main(int argc,char*argv[])
{
    if(argc!=2)
    {
        return 0;
    }
    struct file_info file[10000];
    DIR * dp=opendir(argv[1]);
    if (dp == NULL)
        {
        perror("opendir");
            return 1;
        }
    struct dirent * entry;
    int i=0;
    while((entry=readdir(dp))!=NULL)
    {
        file[i].ino=entry->d_ino;
        strcpy(file[i].names,entry->d_name);
        i++;
    }
    closedir(dp);
    qsort(file,i,sizeof(file[0]),compare_str);
    int max_len=0;
    for(int k=0;k<i;k++)
    {
        int len=strlen(file[k].names);
        if(len>max_len)
        max_len=len;
    }
    int cols=5;
    int count=0;
    for (int k = 0; k < i; k++)
    {
        printf("%lu %-*s",file[k].ino,max_len+2, file[k].names);
        count++;
        if(count==cols)
        {
            printf("\n");
            count=0;
        }
    }
    printf("\n");
    return 0;
}