#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_directory(const char *path) {
    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        // Error handling: path does not exist or cannot be accessed
        return -1;
    }
    return S_ISDIR(path_stat.st_mode);
}

int is_path_unset() {
    char *path = getenv("PATH");
    return (path == NULL || strlen(path) == 0);
}

void handle_command(const char *command) {
    if (is_path_unset()) {
        // Check if the command is a directory
        int dir_check = is_directory(command);
        if (dir_check == 1) {
            printf("%s is a directory\n", command);
        } else if (dir_check == 0) {
            printf("%s is not a directory\n", command);
        } else {
            printf("Error: Unable to access %s\n", command);
        }
    } else {
        // Handle the command normally (e.g., search in PATH directories)
        printf("Executing command: %s\n", command);
        // Add your command execution logic here
    }
}

int main() {
    char command[256];

    while (1) {
        printf("minishell> ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;
        }

        // Remove newline character from command
        command[strcspn(command, "\n")] = '\0';

        if (strlen(command) == 0) {
            continue; // empty command, prompt again
        }

        handle_command(command);
    }

    return 0;
}

