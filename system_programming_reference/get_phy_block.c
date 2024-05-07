/*
파일의 물리 블록 구하기.
1. 주어진 파일의 블록 개수를 구한다. stat() 사용
2. 각 논리 블록을 가지고 ioctl()요청을 해서 이에 상응하는 물리 블록을 구한다.
*/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/ioctl.h>
#include<linux/fs.h>

// get_block : 파일 디스크립터 fd와 관련된 파일의 논리 블록과 맵핑된 물리 블록을 반환한다.

int get_block(int fd, int logical_block) {
    int ret;

    ret = ioctl(fd,FIBMAP, &logical_block);
    if(ret < 0) {
        perror("ioctl");
        return -1;
    }   
    return logical_block;
}

// get_nr_blocks - 파일 디스크립터 fd와 관련된 파일이 차지하고 있는 논리 블록의 개수를 반환한다.

int get_nr_blocks(int fd) {
    struct stat buf;
    int ret;

    ret = fstat(fd, &buf);
    if(ret <0) {
        perror("fstat");
        return -2;
    }

    return buf.st_blocks;
}

// printf_blocks - fd 와 관련된 파일이 차지하고 있는 각 논리 블록과 맵핑된 물리 블록의 정보를
// (논리 블록, 물리 블록) 튜플 자료형으로 출력한다.

void print_blocks(int fd) {
    int nr_blocks, i;

    nr_blocks = get_nr_blocks(fd);
    if(nr_blocks < 0) {
        fprintf(stderr, "get_nr_blocks failed!\n");
        return;
    }

    if(nr_blocks == 0) {
        printf("no allocated blocks\n");
        return;
    } else if(nr_blocks ==1){
        printf("1 block\n\n");
    } else {
        printf("%d blocks(logical)\n\n", nr_blocks);
    }

    for(i = 0; i < nr_blocks; i++) {
        int phys_block;
        phys_block = get_block(fd, i);
        if(phys_block < 0) {
            fprintf(stderr, "get_block failed!\n");
            return;
        }
        if(!phys_block) {
            continue;      
        }

        printf("(%u, %u)", i, phys_block);
    }

    putchar('\n');
}

int main(int argc, char** argv) {
    int fd;

    if(argc <2) {
        fprintf(stderr, "usage: %s <file>", argv[0]);
        return 1;
    }

    fd = open(argv[1], O_RDONLY);
    if(fd < 0) {
        perror ("open");
        return -5;
    }

    print_blocks (fd);

    return 0;
}