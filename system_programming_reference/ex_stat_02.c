#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>

int main(int argc, char** argv) {
    struct stat sb;
    int ret;

    if (argc<2) {
        fprintf(stderr,"usage: %s <file>\n\n", argv[0]);
        return 1;
    }

    ret = stat(argv[1], &sb);
    if(ret) {
        perror("stat");
        return 1;
    }

    printf("File type : ");
    switch(sb.st_mode & S_IFMT) {
        case S_IFBLK:
            printf("block device node\n\n");
            break;
        case S_IFCHR:
            printf("character device node\n\n");
            break;
        case S_IFDIR:
            printf("directory\n\n");
            break;
        case S_IFIFO:
            printf("FIFO\n\n");
            break;
        case S_IFLNK:
            printf("symbolic link\n\n");
            break;
        case S_IFREG:
            printf("regular file\n\n");
            break;
        case S_IFSOCK:
            printf("socket\n\n");
            break;
        default:
            printf("unknown\n\n");
            break;  
    }
    return 0;
}