#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() 
{
    int fd;
    char buf[100];
    fd = open("/dev/test",O_RDONLY);
    if (!fd)
        printf("Error open!!!\n");
    if (!read(fd,buf,1))
        printf("Error read!!!\n");
    buf[20]=0;
    printf("Input: >>> %d <<<\n",*buf);
    close(fd);

    return 0;
}
