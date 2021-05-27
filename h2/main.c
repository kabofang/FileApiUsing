#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

void useage();
int PrintFileName(const char *DirPath);
void PathCat(char**ppNewName,const char*DirPath,const char*Name);

int main(int argc,char **argv){
    if(argc != 2){
        useage();
        return 0;
    }

    if(-1 == PrintFileName(argv[1])){
        printf("printf fail,can't open some dir\n");
        return 0;
    }
    return 0;
}

int PrintFileName(const char *DirPath){
    DIR *pDir;
    struct dirent *pEnt;

    if(NULL == (pDir = opendir(DirPath))){
        printf("printf fail,can't open some dir\n");
        return -1;//唯一错误出口，可保证即使错误也继续遍历
    }

    while(NULL != (pEnt = readdir(pDir))){
        char *pNewName;
        PathCat(&pNewName,DirPath,pEnt->d_name);
        printf("%s\n",pNewName);

        if(pEnt->d_type != DT_DIR){
            free(pNewName);
            continue;
        }

        if(!strcmp(pEnt->d_name,".") || !strcmp(pEnt->d_name,".."))
                continue;

        PrintFileName(pNewName);
        free(pNewName);
        continue;
    }
    return 0;
}

void PathCat(char**ppNewName,const char*DirPath,const char*Name){
    int Dirlen = strlen(DirPath);
    int Namelen = strlen(Name);

    *ppNewName = malloc(Dirlen+Namelen+2);
    memmove(*ppNewName,DirPath,strlen(DirPath));
    (*ppNewName)[Dirlen] = '/';
    memmove(*ppNewName+Dirlen+1,Name,Namelen);
    (*ppNewName)[Dirlen+Namelen+1] = '\0';

    return ;
}

void useage(){
    printf("useage:command DirPath");
    return ;
}
