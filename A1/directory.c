#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

void create_directory(char *dir_name) {
    int status = mkdir(dir_name, 0755);
    if(status == 0) {
        printf("Directory created successfully\n");
    } else {
        printf("Failed to create directory\n");
    }
}

void remove_directory(char *dir_name) {
    int status = rmdir(dir_name);
    if(status == 0) {
        printf("Directory is removed successfully\n");
    } else {
        printf("Failed to remove directory\n");
    }
}

void print_working_directory() {
    char *cwd = getcwd(NULL, 0);
    if(cwd != NULL) {
        printf("Current working directory: %s\n", cwd);
        free(cwd);
    } else {
        printf("Failed to get current working directory\n");
    }
}

void change_directory_up() {
    
    printf("Working Directory Before Operation: %s\n", cwd);
    int status = chdir("..");
    if(status == 0) {
        printf("Changed directory to one level up\n");
    } else {
        printf("Failed to change directory\n");
    }
}

void read_directory_contents(char *dir_name) {
    DIR *dir = opendir(dir_name);
    if(dir) {
        struct dirent *entry
