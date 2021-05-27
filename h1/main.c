#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(){
    int fd;
    char buf[1024];
    if(-1 == (fd = open("a.txt",O_CREAT|O_RDWR|O_APPEND,00600))){
        printf("open fail\n");
        return 0;
    }
    if(-1 == lseek(fd,0L,SEEK_SET)){
        printf("can't lseek\n");
        return 0;
    }
    if(-1 == write(fd,"where",strlen("where"))){
        printf("write fail\n");
        return 0;
    }
    /*
    sync();
    memset(buf,0,1024);
    read(fd,buf,1024);
    printf("no lseek:\n%s\n",buf);

    lseek(fd,-5,SEEK_CUR);
    sync();
    memset(buf,0,1024);
    read(fd,buf,1024);
    printf("lseek:\n%s\n",buf);*/

    close(fd);
    return 0;
}
