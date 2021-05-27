#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define MODE_LEN 12

void useage();
void PrintTitle(void);
void PrintInfo(char*Path);
void PrintMode(mode_t mode);

int main(int argc,char **argv){
    if(argc > 2){
        useage();
        return 0;
    }
    char*pPath;
    if(argc == 1)
            pPath = ".";
    else
            pPath = argv[1];
    if(-1 == chdir(pPath)){
        printf("can't enter directory\n");
        return 0;        
    }
    DIR *pDir;
    struct dirent *pEnt;
    if(NULL == (pDir = opendir("."))){
        printf("opendir fail\n");
        return 0;
    }

    PrintTitle();

    while(NULL != (pEnt = readdir(pDir))){
        if(strcmp(pEnt->d_name,".") && strcmp(pEnt->d_name,".."))
                continue;
        PrintInfo(pEnt->d_name);
        printf("| %s \n",pEnt->d_name);
    }
    
    rewinddir(pDir);

    while(NULL != (pEnt = readdir(pDir))){
        if(!strcmp(pEnt->d_name,".") || !strcmp(pEnt->d_name,".."))
                continue;
        PrintInfo(pEnt->d_name);
        printf("| %s \n",pEnt->d_name);
    }
    return 0;
}

void PrintTitle(void){
    printf(" inode        type         mode        ln  uid  gid   size");
    printf("   bs    bn ");
    printf("    last modify time  ");
    printf("    name  \n");
    return ;
}

void PrintInfo(char*Path){
    struct stat buf;
    lstat(Path,&buf);
    printf("|%7lu",buf.st_ino);
    PrintMode(buf.st_mode);
    printf("%3lu|%5u|%5u|%7lu|",buf.st_nlink,buf.st_uid,buf.st_gid,buf.st_size);
    printf("%4lu|%4lu|",buf.st_blksize,buf.st_blocks);
    struct tm *mytm = localtime(&(buf.st_mtime));
    char* tmstr = asctime(mytm);
    char *temp = malloc(strlen(tmstr));
    memmove(temp,tmstr,strlen(tmstr));
    temp[strlen(tmstr)-1] = '\0';
    printf("%.*s",(unsigned int)strlen(temp),temp);
    free(temp);
    return ;
}

void PrintMode(mode_t mode){
    char modebuf[MODE_LEN+1];
    memset(modebuf,'-',MODE_LEN);
    modebuf[MODE_LEN] = '\0';

    int i = 0;
    if(mode&S_IRUSR)
            modebuf[i] = 'r';
    ++i;
    if(mode&S_IWUSR)
            modebuf[i] = 'w';
    ++i;
    if(mode&S_IXUSR)
           modebuf[i] = 'x';
    ++i;
    if(mode&S_IRGRP)
            modebuf[i] = 'r';
    ++i;
    if(mode&S_IWGRP)
            modebuf[i] = 'w';
    ++i;
    if(mode&S_IXGRP)
            modebuf[i] = 'x';
    ++i;
    if(mode&S_IROTH)
            modebuf[i] = 'r';
    ++i;
    if(mode&S_IWOTH)
            modebuf[i] = 'w';
    ++i;
    if(mode&S_IXOTH)
            modebuf[i] = 'x';
    ++i;
    if(mode&S_ISUID)
            modebuf[i] = 'x';
    ++i;
    if(mode&S_ISGID)
            modebuf[i] = 'x';
    ++i;
    if(mode&S_ISVTX)
            modebuf[i] = 'x';

    char *type;
    if(S_ISDIR(mode))
            type = "directory";
    else if(S_ISREG(mode))
            type = "regular";
    else if(S_ISCHR(mode))
            type = "character dev";
    else if(S_ISBLK(mode))
            type = "block dev";
    else if(S_ISFIFO(mode))
            type = "fifo";
    #ifdef  S_ISLNK
    else if (S_ISLNK(mode))
            type = "symbolic link";
    #endif

    #ifdef  S_ISSOCK
    else if (S_ISSOCK(mode))
            type = "socket";
    #endif
    else
            type = "unkonw";
    printf("|%13s",type);
    printf("|%s|",modebuf);
    return ;
}

void useage(){
    printf("useage: command [DirPath]\n");
    return ;
}
