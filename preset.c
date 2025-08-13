//TODO: CLEANUP TEMPLATE HANDLING, I WAS TOO LAZY
#include "include/colors.h"
#include <stdlib.h>  
#include <stdio.h>
#include <string.h>

int command_exists(const char *cmd) {
    char buffer[256];
#ifdef _WIN32
    snprintf(buffer, sizeof(buffer), "where %s >nul 2>nul", cmd);
#else
    // On Linux/macOS, use `command -v`
    snprintf(buffer, sizeof(buffer), "command -v %s >/dev/null 2>&1", cmd);
#endif
    return system(buffer) == 0;
}

int preset (char *preset_name) {
    if(strcmp(preset_name, "js") == 0 || strcmp(preset_name, "javascript") == 0){
        FILE *jsptr;
        FILE *htmlptr;
        FILE *cssptr;
        
        //cssptr = fopen("style.css", "w");
        jsptr = fopen("index.js", "w");
        //htmlptr = fopen("index.html", "w");

        //char strhtml[] = "<!DOCTYPE html>\n<html lang= \"en \">\n<head>\n<meta charset= \"UTF-8 \">\n<meta name= \"viewport \" content= \"width=device-width, initial-scale=1.0 \">\n<title>My Basic JS App</title>\n<link rel= \"stylesheet \" href= \"style.css \">\n</head>\n<body>\n<h1>Hello, JavaScript!</h1>\n<p id= \"output \">This text will be changed by JavaScript.</p>\n\n<script src= \"script.js \"></script>\n</body>\n</html>\n";

        char strjs[] = "console.log( \"Hello world \");\n";

        //char strcss[] = "body {\n    font-family: Arial, sans-serif;\n    margin: 20px;\n    background-color: #f4f4f4;\n}\n\nh1 {\n    color: #333;\n}\n";

        // fputs(strhtml, htmlptr);
        fputs(strjs, jsptr);
        // fputs(strcss, cssptr);
        // fclose(htmlptr);
        fclose(jsptr);
        // fclose(cssptr);

        char packages[256];
        char devpackages[256];
        char command[512];
        char devcommand[512];

        printf(C_BLUE "Enter packages to install (default = none): " SGR_RESET);
        fgets(packages, sizeof(packages), stdin);

        printf(C_CYAN"Enter dev dependencies to install (default = none): "SGR_RESET);
        fgets(devpackages, sizeof(devpackages), stdin);

        //removing newline
        packages[strcspn(packages, "\n")] = 0;
        devpackages[strcspn(devpackages, "\n")] = 0;

        if (strcmp(packages, "") != 0) {
            sprintf(command, "npm install %s", packages);
            printf("Executing command: %s\n", command);
            system(command);
        } 
        if( strcmp(devpackages, "") != 0 ) {
            sprintf(devcommand ,"npm install %s --save-dev", devpackages);
            printf("Executing command: %s\n", devcommand);
            system(devcommand);
        } else {
            printf(C_RED"No packages specified. Executing 'npm install && npm init'\n"SGR_RESET);
            system("npm init && npm install");
        }
        printf(C_CYAN"Successfully made boilerplate template of JS at current path."SGR_RESET);
    } 
    else if(strcmp(preset_name, "py") == 0 || strcmp(preset_name, "python") == 0){
        FILE *pyptr;
        FILE *reqptr;

        pyptr = fopen("main.py", "w");
        char pystr[] = "#!/usr/bin/env python3\n\"\"\"\nProject: <your_project_name>\nDescription: <short_description_here>\nAuthor: <your_name>\n\"\"\"\n\nimport sys\n\n\ndef main():\n    # TODO: Write your code here\n    print(\"Hello, Python!\")\n\n\nif __name__ == \"__main__\":\n    try:\n        main()\n    except KeyboardInterrupt:\n        sys.exit(\"Execution stopped by user.\")\n";

        fputs(pystr, pyptr);
        fclose(pyptr);

        char pips[256];
        char pycmd[512];

        printf("Enter pip packages to install(default = none) : ");
        fgets(pips, sizeof(pips), stdin);

        pips[strcspn(pips, "\n")] = 0;

        if(strcmp(pips, "") != 0){
            sprintf(pycmd, "python -m venv venv && source venv/bin/activate && venv/bin/python -m pip install %s", pips);
            printf(C_GREEN"Executing command: %s\n"SGR_RESET, pycmd);
            system(pycmd);
        } else{
            system("python -m venv venv && source venv/bin/activate");
            printf(C_RED"No pip packages specified, setting up defaults.\n"SGR_RESET);
        }
        printf(C_BR_BLUE"Successfully made boilerplate template of Python at current path. Run:\nsource venv/bin/activate for bash/zsh/shs\nsource venv/bin/activate.fish for fish\nsource venv/bin/activate.csh for csh/tcsh"SGR_RESET);
    }
    else if(strcmp(preset_name, "react") == 0){
        int choice;

        printf(C_MAGENTA"Select React flavor: \n"SGR_RESET);
        printf(C_CYAN"[1] => Vite\n"SGR_RESET);
        printf(C_BR_CYAN"[2] => CRA (create-react-app)\n"SGR_RESET);
        printf(C_GRAY"Enter selection (default = 1): "SGR_RESET);
        scanf("%d", &choice);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if(choice == 1){
            char tschoice[10];

            printf(C_GREEN"Executing npm create vite@latest for React...\n"SGR_RESET);

            printf(C_BR_CYAN"Do you want to use Typescript(y / n): "SGR_RESET);
            fgets(tschoice, sizeof(tschoice), stdin);
            tschoice[strcspn(tschoice, "\n")] = 0;
            
            if(strcmp(tschoice, "y") == 0 || strcmp(tschoice, "yes") == 0 || strcmp(tschoice, "Y") == 0){
                system("npm create vite@latest . -- --template react-ts");
            } else if (strcmp(tschoice, "n") == 0 || strcmp(tschoice, "no") == 0 || strcmp(tschoice, "N") == 0) {
                system("npm create vite@latest --template react-js");
            } else{
                printf(C_RED"Unknown option, exiting..."SGR_RESET);
                return 0;
            }

            char vitecmd[100];
            char vitepkg[256];
            char vitepkgcmd[512];

            printf(C_CYAN"Enter extra packages to install(default = none): "SGR_RESET);
            fgets(vitepkg, sizeof(vitepkg), stdin);

            vitepkg[strcspn(vitepkg, "\n")] = 0;

            if(strcmp(vitepkg, "") != 0){
                sprintf(vitepkgcmd, "npm install %s", vitepkg);
                system(vitepkgcmd);
                printf(C_BLUE"Successfully made project at current path."SGR_RESET);
            } else{
                printf(C_BLUE"Successfully made project at current path."SGR_RESET);
            }

        } else if(choice == 2){
            char projectName[64];
            char cracmd[100];
            char reactpkg[256];
            char pkgcmd[512];

            char choicets[5];

            printf(C_MAGENTA"Enter project name: "SGR_RESET);
            scanf("%s", projectName);
            int d;
            while ((d = getchar()) != '\n' && d != EOF);

            printf(C_MAGENTA"Do you want to use Typescript (y/n): "SGR_RESET);
            fgets(choicets, sizeof(choicets), stdin);
            choicets[strcspn(choicets, "\n")] = 0;

            if(strcmp(choicets, "y") == 0 || strcmp(choicets, "Y") == 0 || strcmp(choicets, "yes") == 0){
                printf(C_BLUE"Executing create-react-app with typescript: \n"SGR_RESET);
                sprintf(cracmd, "npx create-react-app %s --template typescript", projectName);
                system(cracmd);
            } else if(strcmp(choicets, "n") == 0 || strcmp(choicets, "N") == 0 || strcmp(choicets, "no") == 0){
                printf(C_CYAN"Executing create-react-app: \n"SGR_RESET);
                sprintf(cracmd, "npx create-react-app %s", projectName);
                system(cracmd);
            } else{
                printf("Unknown option... exiting");
                return 0;
            }

            printf(C_YELLOW"Enter packages to install(default = none): "SGR_RESET);
            fgets(reactpkg, sizeof(reactpkg), stdin);

            reactpkg[strcspn(reactpkg, "\n")] = 0;
            
            if(strcmp(reactpkg, "") != 0){
                sprintf(pkgcmd, "npm install %s", reactpkg);
                system(pkgcmd);

                printf(C_BLUE"Successfully made project at current path."SGR_RESET);
            }else{
                printf(C_BLUE"Successfully made project at current path."SGR_RESET);
            }

        } else{
            printf(C_RED"Unknown option, exiting..."SGR_RESET);
    }

    } else if(strcmp(preset_name, "vue") == 0){
            char tschoice[10];

            printf(C_GREEN"Executing npm create vite@latest for Vue...\n"SGR_RESET);

            printf(C_BR_CYAN"Do you want to use Typescript(y / n): "SGR_RESET);
            fgets(tschoice, sizeof(tschoice), stdin);
            tschoice[strcspn(tschoice, "\n")] = 0;
            
            if(strcmp(tschoice, "y") == 0 || strcmp(tschoice, "yes") == 0 || strcmp(tschoice, "Y") == 0){
                system("npm create vite@latest . -- --template vue-ts");
            } else if (strcmp(tschoice, "n") == 0 || strcmp(tschoice, "no") == 0 || strcmp(tschoice, "N") == 0) {
                system("npm create vite@latest --template vue");
            } else{
                printf(C_RED"Unknown option, exiting..."SGR_RESET);
                return 0;
            }

            char vitecmd[100];
            char vitepkg[256];
            char vitepkgcmd[512];

            printf(C_CYAN"Enter extra packages to install(default = none): "SGR_RESET);
            fgets(vitepkg, sizeof(vitepkg), stdin);

            vitepkg[strcspn(vitepkg, "\n")] = 0;

            if(strcmp(vitepkg, "") != 0){
                sprintf(vitepkgcmd, "npm install %s", vitepkg);
                system(vitepkgcmd);
                printf(C_BLUE"Successfully made project at current path."SGR_RESET);
            } else{
                printf(C_BLUE"Successfully made project at current path."SGR_RESET);
            }

    } else if (strcmp(preset_name, "c") == 0 || strcmp(preset_name, "clang") == 0){
        char cmakechoice[5];
        printf(C_MAGENTA"Making C preset...\n"SGR_RESET);

        printf(C_BR_BLUE"Would you like to use CMake (y/n): "SGR_RESET);
        fgets(cmakechoice, sizeof(cmakechoice), stdin); 
        cmakechoice[strcspn(cmakechoice, "\n")] = 0;

        if(strcmp(cmakechoice, "y") == 0 || strcmp(cmakechoice, "Y") == 0 || strcmp(cmakechoice, "yes") == 0){
            printf(C_YELLOW"Generating CMake project...\n"SGR_RESET);
            char projectname[64];
            char cmakelist[512];
            FILE *cmakeptr;
            cmakeptr = fopen("CMakeLists.txt", "w");

            printf(C_GREEN"Enter project name (default = myapp): "SGR_RESET);
            fgets(projectname, sizeof(projectname), stdin);
            projectname[strcspn(projectname, "\n")] = 0;

            if(strcmp(projectname, "") != 0){
                sprintf(cmakelist, "cmake_minimum_required(VERSION 3.10)\nproject(%s C)\n\nset(CMAKE_C_STANDARD 11)\n\nfile(GLOB SOURCES src/*.c)\nadd_executable(${PROJECT_NAME} ${SOURCES})\n", projectname);
            } else{
                sprintf(cmakelist, "cmake_minimum_required(VERSION 3.10)\nproject(myapp C)\n\nset(CMAKE_C_STANDARD 11)\n\nfile(GLOB SOURCES src/*.c)\nadd_executable(${PROJECT_NAME} ${SOURCES})\n");
            }

            fputs(cmakelist, cmakeptr);
            fclose(cmakeptr);

            printf(C_CYAN"Making Files and Folder structures..."SGR_RESET);
            system("mkdir src");
            FILE *mainptr = fopen("./src/main.c", "w");
            if (!mainptr){
                printf("Failed to make files, exiting...");
                return 2;
            }
            fprintf(mainptr,
                "#include <stdio.h>\n\n"
                "int main(void) {\n"
                "    printf(\"Hello, World!\\n\");\n"
                "    return 0;\n"
                "}\n"
            );
            fclose(mainptr);

            system("mkdir build && cd build && cmake .. && cmake --build .");

            printf(C_GREEN"\nBuild complete!\n"SGR_RESET);
            printf(C_BR_BLUE"To run the program:\n"SGR_RESET);
            printf(C_GRAY"cd build && ./your_executable_name\n"SGR_RESET);
            printf(C_CYAN"\nTo rebuild after changes:\n"SGR_RESET);
            printf(C_YELLOW"cd build && cmake --build .\n"SGR_RESET);
            printf(C_BR_CYAN"\nHappy coding!\n"SGR_RESET);
        } else if(strcmp(cmakechoice, "n") == 0 || strcmp(cmakechoice, "N") == 0 || strcmp(cmakechoice, "no") == 0) {
            printf(C_GREEN"Generating base C template...\n"SGR_RESET);
            
            char clangstr[] = "#include <stdio.h>\n\nint product(int x, int y){\n    return x*y;\n}\n\nint main () {\n    int a, b;\n    a = 5;\n    b = 6;\n\n    int multipliedResult = product(a, b);\n    printf(\"%d x %d = %d\", a, b, multipliedResult);\n    \n    return 2;\n}\n";

            FILE *clangptr = fopen("main.c", "w");
            fputs(clangstr, clangptr);
            fclose(clangptr);

            system("mkdir include");
            printf(C_MAGENTA"Making header file...\n"SGR_RESET);

            FILE *headerptr = fopen("./include/header.h", "w");
            fclose(headerptr);

            printf(C_BR_CYAN"Generating executables..."SGR_RESET);

            if (command_exists("clang")){
                system("clang main.c -o main");
            } else if(command_exists("gcc")){
                system("gcc main.c -o main");
            } else if (command_exists("gcc") && command_exists("clang")){
                system("clang main.c -o main");
            }
            
            printf(C_BLUE"\nFile generation done. Happy coding!\n"SGR_RESET);
        }
    } else if (strcmp(preset_name, "cpp") == 0 || strcmp(preset_name, "c++") == 0) {
        printf(C_CYAN"Generating C++ template...\n"SGR_RESET);

        char cppchoice[5];

        printf(C_BR_BLUE"Would you like to use CMake (y / n): "SGR_RESET);
        fgets(cppchoice, sizeof(cppchoice), stdin);
        cppchoice[strcspn(cppchoice, "\n")] = 0;

        if (strcmp(cppchoice, "y") == 0 || strcmp(cppchoice, "Y") == 0 || strcmp(cppchoice, "yes") == 0){
            system("mkdir src");
            FILE *mainptr = fopen("./src/main.cpp", "w");
            char projName[64];            

            printf("Enter project name (default = MyCppProject): ");
            fgets(projName, sizeof(projName), stdin);

            fprintf(mainptr, "#include <iostream>\n\nint main() {\n    std::cout << \"Hello, C++ world!\" << std::endl;\n    return 0;\n}\n");
            fclose(mainptr);

            FILE *cmakeptr = fopen("CMakeLists.txt", "w");
            if (cmakeptr) {
                char cmakelist[256];

                if (strcmp(projName, "") != 0){
                    sprintf(cmakelist, "cmake_minimum_required(VERSION 3.10)\n"
                        "project(MyCppProject CXX)\n\n"
                        "set(CMAKE_CXX_STANDARD 17)\n\n"
                        "add_executable(%s src/main.cpp)\n", projName);
                } else {
                    sprintf(cmakelist, "cmake_minimum_required(VERSION 3.10)\n"
                        "project(MyCppProject CXX)\n\n"
                        "set(CMAKE_CXX_STANDARD 17)\n\n"
                        "add_executable(MyCppProject src/main.cpp)\n");
                }

                fputs(cmakelist, cmakeptr);
                fclose(cmakeptr);
            }
            printf(C_GREEN"\nC++ project structure created.\n"SGR_RESET);
            printf(C_MAGENTA"Generating executables..."SGR_RESET);

            system("mkdir build && cd build && cmake .. && cmake --build .");
            printf(C_YELLOW"Generation Done!\n"SGR_RESET);
            if (strcmp(projName, "") != 0){
                printf(C_BR_CYAN"Project Generated!"SGR_RESET);
                printf(C_BLUE"Type cd build && ./%s to run the executable. Happy Coding!"SGR_RESET, projName);
            } else{
                printf(C_BR_CYAN"Project Generated!"SGR_RESET);
                printf(C_BLUE"Type cd build && ./MyCppProject to run the executable. Happy Coding!"SGR_RESET);
            }
        }
}
    
    else{
        printf(C_RED"Unknown parameter provided, exiting..."SGR_RESET);
    }

    return 1;
}