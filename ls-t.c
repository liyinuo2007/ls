#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<time.h>
#include <sys/stat.h>
int compare_name(const void*a,const void*b)
{
    return strcmp((const char*)a,(const char*)b);
}
struct file_info
{
    time_t mtime;
    char names[256];
};
int compare_time(const void*a,const void*b)
{
    const struct file_info*fa=(const struct file_info*)a;
    const struct file_info*fb=(const struct file_info*)b;
    if(fa->mtime>fb->mtime)
    return -1;
    if(fa->mtime<fb->mtime)
    return 1;
    return 0;

}
int main(int argc,char*argv[])
{
    int opt_t=0;
    const char *path = ".";
        for (int j = 1; j < argc; j++) {
        if (argv[j][0] == '-') {
            if (strstr(argv[j], "t")) opt_t = 1;
        } else {
            path = argv[j];
        }
    }
    struct file_info file[10000];
    DIR * dp=opendir(path);
    if (dp == NULL)
        {
        perror("opendir");
            return 1;
        }
    struct dirent * entry;
    int i=0;
    while((entry=readdir(dp))!=NULL)
    {
        strcpy(file[i].names, entry->d_name);
        char full_path[1024];
        sprintf(full_path, "%s/%s", path, entry->d_name);
        struct stat st;
        if (stat(full_path, &st) == 0) 
        {
            file[i].mtime = st.st_mtime; 
        } else 
        {
            file[i].mtime = 0; 
        }
        i++;
    }
    closedir(dp);
    if(opt_t)
    qsort(file,i,sizeof(file[0]),compare_time);\
    else
    qsort(file,i,sizeof(file[0]),compare_name);
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
        printf("%-*s",max_len+2, file[k].names);
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
    