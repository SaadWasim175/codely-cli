#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/colors.h"
#ifdef __linux__
    #include <sys/wait.h>
#endif

void get_repo_name(const char *url, char *repo_name) {
    const char *last_slash = strrchr(url, '/');
    if (last_slash) {
        strcpy(repo_name, last_slash + 1);
        size_t len = strlen(repo_name);
        if (len > 4 && strcmp(repo_name + len - 4, ".git") == 0) {
            repo_name[len - 4] = '\0';
        }
    } else {
        repo_name[0] = '\0';
    }

}

int git(char *arg, char* link, char* dir){
    if (strcmp(arg, "get") == 0){
        printf(C_BR_MAGENTA"Initializing Git-Management System\n"SGR_RESET);
        printf(C_CYAN"Fetching repository...\n"SGR_RESET);

        if (dir != NULL) {
            char clonecmd[512];
            sprintf(clonecmd, "git clone %s %s", link, dir);
            system(clonecmd);
        } else if (dir == NULL) {
            #ifdef _WIN32
                char repo_name[256];
                char windowscmd[512];
                get_repo_name(link, repo_name);

                char *username = getenv("USERNAME");
                printf(C_YELLOW"Cloning to C:\\%s\\%s"SGR_RESET, username, repo_name);

                char windir[128];
                sprintf(windir, "C:\\Users\\%s\\%s", username, repo_name);

                sprintf(windowscmd, "git clone %s %s", link, windir);

                system(windowscmd);
            #endif
            #ifdef __linux__
                char reponame[256];
                char linuxcmd[512];

                get_repo_name(link, reponame);

                char *user = getenv("USER");
                printf(C_GREEN"Cloning to ~/home/%s"SGR_RESET, user);

                char directory[128];
                sprintf(directory, "/home/%s/%s", user, reponame);

                sprintf(linuxcmd, "git clone %s %s", link, directory);
                system(linuxcmd);
            #endif
        }
    } else if (strcmp(arg, "push-repo") == 0){
        char choice[5];
        printf(C_RED"This command is only for pushing to empty repositories! Proceed(y/n): "SGR_RESET);
        fgets(choice, sizeof(choice), stdin);

        choice[strcspn(choice, "\n")] = 0;

        if (strcmp(choice, "y") == 0 || strcmp(choice, "yes") == 0 || strcmp(choice, "Y") == 0){

            if (strcmp(link, "") != 0) {
                char pushcmd[1024];
                char desc[129];
                int ret;
                int numchoice;
                printf(C_GREEN"Enter commit description (128 chars only): "SGR_RESET);
                fgets(desc, sizeof(desc) - 1, stdin);
                desc[strcspn(desc, "\n")] = 0;

                printf(C_BLUE"Branch to push (default = main): \n"SGR_RESET);
                printf(C_CYAN"[1] => master\n"SGR_RESET);
                printf(C_BR_CYAN"[2] => main\n"SGR_RESET);
                printf("Choice: ");
                scanf("%d", &numchoice);

                printf(C_BR_BLUE"Pushing to Github Repo...\n"SGR_RESET);
                if (numchoice == 1){                
                    sprintf(pushcmd, "git init && git add . && git commit -m \"%s\" && git remote add origin %s && git push -u origin master", desc, link);
                    ret = system(pushcmd);
                } else if (numchoice == 2){
                    sprintf(pushcmd, "git init && git add . && git commit -m \"%s\" && git remote add origin %s && git push -u origin main", desc, link);
                    ret = system(pushcmd);
                }

            if (ret == -1) {
                perror("system");
            } else {
                // Extract the actual exit status
            if (WIFEXITED(ret)) {
                int exit_status = WEXITSTATUS(ret);
                if (exit_status == 0) {
                    printf("Command succeeded\n");
                } else {
                    printf("Command failed with exit status %d\n", exit_status);                    }
                } else {
                    printf("Command did not terminate normally\n");
                }
}
            }
        } else{
            printf(C_BR_MAGENTA"Exiting Repo deployment.\n"SGR_RESET);
        } 

    } else if (strcmp(arg, "commit-info") == 0) {
        printf(C_MAGENTA"Fetching commit history...\n\n"SGR_RESET);

        char gitcmd[1024];

        #if defined(__linux__) || defined(__APPLE__)
            printf(C_BR_MAGENTA"\n");
            system("rm -rf \"$HOME/repo_temp123\"");

            sprintf(gitcmd, "git clone --quiet --bare --filter=blob:none \"%s\" \"$HOME/repo_temp123\"", link);
            system(gitcmd);

            system("cd \"$HOME/repo_temp123\" && git --no-pager log --pretty=format:\"%h | %an | %ad | %s\" --date=short");

            system("rm -rf \"$HOME/repo_temp123\"");
        #endif
        #ifdef _WIN32
            printf(C_BR_MAGENTA"\n");
            system("rmdir /S /Q \"%USERPROFILE%\\repo_temp123\"");

            sprintf(gitcmd, "git clone --quiet --bare --filter=blob:none \"%s\" \"%USERPROFILE%\\repo_temp123\"", link);
            system(gitcmd);

            system("cd /D \"%USERPROFILE%\\repo_temp123\" && git --no-pager log --pretty=format:\"%%h | %%an | %%ad | %%s\" --date=short");
            
            system("rmdir /S /Q \"%USERPROFILE%\\repo_temp123\"");
        #endif

}


    return 1;
}