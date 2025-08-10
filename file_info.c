#include <sys/stat.h>
#include <stdio.h>
#include <time.h> 
#include <string.h>
#include "./include/colors.h"

int print_file_info(char *filename) {
    struct stat fileStat; 

    char *extension_ptr = strrchr(filename, '.');

    if (stat(filename, &fileStat) == -1) {
        perror("stat");
        return 1;
    }

    if(filename){

        printf( C_MAGENTA "File Name: %s\n"SGR_RESET, filename);
        printf(C_GREEN"File Size: %lld bytes\n"SGR_RESET, (long long)fileStat.st_size);
        printf(C_BLUE"Number of Links: %ld\n"SGR_RESET, (long)fileStat.st_nlink);
        printf(C_CYAN"File Owner (UID): %d\n"SGR_RESET, fileStat.st_uid);
        printf(C_WHITE"File Group (GID): %d\n"SGR_RESET, fileStat.st_gid);
        printf(C_YELLOW"File Permissions: %o\n"SGR_RESET, fileStat.st_mode & 0777);
        printf(C_RED"Last Modified: %s"SGR_RESET, ctime(&fileStat.st_mtime));
        printf(C_BLUE"Last Accessed: %s"SGR_RESET, ctime(&fileStat.st_atime));
        printf(C_GREEN"Last Status Change: %s"SGR_RESET, ctime(&fileStat.st_ctime));
        
        if(extension_ptr!=NULL){
            printf(C_CYAN"Extension of %s: %s\n"SGR_RESET, filename, extension_ptr);
        } else{
            printf("Extension unknown\n");
        }


        if (S_ISREG(fileStat.st_mode)) {
            printf(SGR_ITALIC"File Type: Regular File\n"SGR_RESET);
        } else if (S_ISDIR(fileStat.st_mode)) {
            printf("File Type: Directory\n");
        }
} else{
    printf("Could not find file");
}
    return 0;
}