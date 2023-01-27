#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

void create_directory() {
    char dirName[128];
    printf("Enter the Directory name you want to create: ");
    scanf("%s", dirName);
    int status = mkdir(dirName, 0777);
    if(status == 0) {
        printf("Directory created successfully\n");
    } else {
        printf("Failed to create directory\n");
    }
}

void remove_directory() {
    char dirName[128];
    printf("Enter the Directory name you want to remove: ");
    scanf("%s", dirName);
    int status = rmdir(dirName);
    if(status == 0) {
        printf("Directory is removed Successfully\n");
    } else {
        printf("Failed to remove directory\n");
    }
}

void print_working_directory() {
    char *cwd = getcwd(NULL, 0);
    if(cwd != NULL) {
        printf("Current Working Directory is: %s\n", cwd);
        free(cwd);
    } else {
        printf("Failed to get current working directory\n");
    }
}

void change_directory_up() {
    char *cwd = getcwd(NULL, 0);
    printf("Working Directory Before Operation:%s\n", cwd);
    free(cwd);
    int status = chdir("..");
    if(status == 0) {
        printf("Directory Changed Successfully. \n");
        char *cwd = getcwd(NULL, 0);
        printf("Working Directory After Operation: %s\n", cwd);
        free(cwd);
    } else {
        printf("Failed to change directory\n");
    }
}

void read_directory_contents() {
    DIR *dirStream;
    struct dirent *entry;
    char *cwd = getcwd(NULL, 0);
    dirStream = opendir(cwd);

    if (dirStream == NULL) {
        printf("Error: Could not open directory %s\n", cwd);
        return;
    }

    while ((entry = readdir(dirStream)) != NULL) {
        if (entry->d_name != NULL) {
            printf("%s/\n", entry->d_name);
        } else {
            printf("Error pulling directory");
        }
    }
    free(cwd);
}

void close_directory() {
    DIR *dirStream = opendir(".");
    if (dirStream) {
        closedir(dirStream);
        printf("Directory Closed Successfully.\n");
    } else {
        printf("No open directory stream found.\n");
    }
}

int main() {
    char input = '0';
    while (input != 'q') {
        printf("Select the option(s) appropriately by entering the number: \n\
        Enter 1 for creating a directory\n\
        Enter 2 for removing directory\n\
        Enter 3 for printing working directory\n\
        Enter 4 for changing directory one level up\n\
        Enter 5 for reading the contents of directory\n\
        Enter 6 for closing the current directory\n\
        Enter q to exit the program\n");

        scanf(" %c", &input);
        switch(input) {
            case '1':
                create_directory();
            break;
            case '2':
                remove_directory();
            break;
            case '3':
                print_working_directory();
            break;
            case '4':
                change_directory_up();
            break;
            case '5':
                read_directory_contents();
            break;
            case '6':
                close_directory();
            break;
            case 'q':
                exit(0);
            break;
        }
}
}

