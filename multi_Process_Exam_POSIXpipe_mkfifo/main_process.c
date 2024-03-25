#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char** argv) {

    if(argc < 2) {      // 실행파일 실행할 때 입력값이 없으면 기본값 1이다. 메인프로세서는 입력값이 없는 걸로 하자.
        int mk = mkfifo("/home/sodami/tmp/myfifo", O_CREAT|S_IRUSR|S_IWUSR);
        int fd;
        if (errno) {
            fprintf(stderr,"ERROR! failed make file : %s\n",strerror(errno));
            exit(1);
        }
        if((fd = open("/home/sodami/tmp/myfifo",O_RDWR,0600)) <0 ) {
            fprintf(stderr,"fifo file open error : %s\n",strerror(errno));
            exit(1);
        }
        
        char str[] = "multi process POSIX pipe!";
        write(fd,str,strlen(str)+1);
        while(1){
            printf("...\n");
            sleep(1);
        }
    } else {            // 메인 프로세서 아닌 프로세서들 실행시 입력값 있다.
        int fd;
        if((fd = open("/home/sodami/tmp/myfifo",O_RDONLY)) <0 ) {
            fprintf(stderr,"fifo file open error : %s\n",strerror(errno));
            exit(1);
        }
        char buff[50];
        int num_of_read_bytes = read(fd,buff,50);
        fprintf(stdout, "output myfifo : %s\n", buff);
    }
    return 0;
}
