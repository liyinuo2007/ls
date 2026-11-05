#include <stdio.h>
#include <dirent.h>
#include <string.h> 

int main(void)
{
    char names[100][256];
    DIR *dp = opendir(".");
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
    for (int k = 0; k < i; k++)
    {
        printf("%s ", names[k]);
    }

    return 0;
}