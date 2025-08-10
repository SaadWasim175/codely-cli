#include <stdio.h>
#include <string.h>
#include "include/file_info.h"
#include "include/preset.h"
#include "include/git.h"

int main (int argc, char *argv[]) {
    
    if(argc >= 3){
        if ((strcmp(argv[1], "-f") == 0 || strcmp(argv[1], "--file") == 0) && argv[2] != NULL){
            print_file_info(argv[2]);
        }else if (strcmp (argv[1], "-p") == 0 || strcmp(argv[1], "--preset") == 0 && argv[2] != NULL) {
            preset(argv[2]);
        } else if(strcmp(argv[1], "-g") == 0 || strcmp(argv[1], "--git") == 0){
            git(argv[2], argv[3], argv[4]);
        }
}

    return 2;
}