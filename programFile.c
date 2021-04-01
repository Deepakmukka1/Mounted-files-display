#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/vfs.h>
char filePaths[100][200];
int mainCount = 0;
int extractWords(char str[])
{

    char splitLines[100][100];
    int j = 0, i = 0, cnt = 0;
    for (i = 0; i <= (strlen(str)); i++)
    {

        if (str[i] == ' ' || str[i] == '\0')
        {
            splitLines[cnt][j] = '\0';
            cnt++;
            j = 0;
        }
        else
        {
            splitLines[cnt][j] = str[i];
            j++;
        }
    }
    strcpy(filePaths[mainCount], splitLines[1]);
    mainCount++;
}
int main()
{
    FILE *fptr;
    char lineList[100][300];
    char line[300];
    fptr = fopen("/proc/mounts", "r");
    if (fptr == NULL)
    {
        printf("There is error in opening file\n");
    }
    else
    {
        int i = 0, j = 0, count = 0, k = 0;
        while (fgets(line, sizeof(line), fptr) != NULL)
        {
            strcpy(lineList[i], line);
            i++;
        }

        for (j = 0; j < i; j++)
        {
            extractWords(lineList[j]);
        }
    }
    int i = 0;
    struct statfs maxFree;
    maxFree.f_bfree = 0;
    char path[30];
    for (i = 0; i < mainCount; i++)
    {

        struct statfs sts1;
        long long pid1;
        pid1 = statfs(filePaths[i], &sts1);
        if (sts1.f_bfree > maxFree.f_bfree)
        {
            maxFree = sts1;
            strcpy(path, filePaths[i]);
        }
    }

    printf("\nTotal mounted file systems available = %d\n\n", mainCount);
    printf("The file system details\n\n");
    system("findmnt -l");
    printf("\nThe following information is about the filesystem that has highest free blocks\n\n");
    printf("Path of the file system that has highest free blocks is  %s \n", path);
    printf("Optimal transfer block size = %ld\n", maxFree.f_bsize);
    printf("Number of free blocks = %ld\n", maxFree.f_bfree);
    printf("Total data blocks = %ld\n", maxFree.f_blocks);
    printf("Total file nodes = %ld\n", maxFree.f_files);
    printf("Free blocks avilable to non super user = %ld\n", maxFree.f_bavail);
    fclose(fptr);
}
