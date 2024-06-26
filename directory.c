/*
 * 1. Create a directory (`mkdir`)
 * 2. Remove a directory (`rm -rf`)
 * 3. Get the current working directory (`pwd`)
 * 4. Changing to the parent directory (`..`)
 * 5. Reading the contents of the current directory (`ls`)
 * 6. Closing the opened directory (I can't think of a similar command)
 */

#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void create_directory() {
    char new_dir_name[50];  // would 50 characters be enough?
    int dir_created;        // 0 if created, -1 if mkdir fails
    mode_t mode = 0777;  // Grants full permissions for everyone, but should we?

    printf("Enter name of directory: ");
    scanf("%49s", new_dir_name);

    dir_created = mkdir(new_dir_name, mode);

    if (dir_created == 0) {
        printf("Directory created!! You're the best!\n\n");
    } else {
        // Error handling (dir_created == -1)
        // I could check the value of the errno global variable and print out
        // a more precise error message. However, this is probably good enough
        perror("Unable to create directory for you, here's why: ");
    }
}

void remove_directory() {
    char dir_to_remove[50];
    int dir_removed;

    printf("Enter the name of the directory to be removed: ");
    scanf("%49s", dir_to_remove);

    dir_removed =
        rmdir(dir_to_remove);  // This can only delete EMPTY directories

    if (dir_removed == 0) {
        printf("Directory removed!! You're the best!\n\n");
    } else {
        // failure
        perror("Unable to remove directory for you, here's why: ");
    }
}

void get_current_directory() {
    // Has to be a lot longer, since it holds the absolute path
    char current_directory_name[1000];

    // This will currently get and display the absolute path to the CWD.
    // Is this what we want? Or do we want just the name of the current node?
    if (getcwd(current_directory_name, sizeof(current_directory_name)) !=
        NULL) {
        printf("Current working directory: %s", current_directory_name);
    } else {
        // Error handling
        perror("Unable to retrieve current directory name for you, here why: ");
    }
}

void change_to_parent_directory() {
    if (chdir("..") == 0) {
        printf("Moved up to parent directory.\n");
    } else {
        // Error handling
        perror("Unable to move to parent directory, here's why: ");
    }
}

void read_directory() {
    DIR *dir; // pointer to a "directory stream"
    struct dirent *entry; // pointer to an "item" in the directory

    dir = opendir(".");
    if (dir == NULL) {
        perror("Unable to open directory for reading, here's why: ");
        return;
    }

    printf("Items in current directory:\n");
    entry = readdir(dir);
    while (entry != NULL) {
        printf("%s\n", entry->d_name);
        entry = readdir(dir);
    }

    if (closedir(dir) != 0) {
        perror("Unable to close the directory, here's why: ");
    }
}

void close_directory() {
    printf("Close directory (what does that even mean?)\n\n");
}

char display_menu() {
    char choice;
    printf("\n\nSelect the option(s) appropriately by selecting the number:\n");
    printf("1. Create a directory\n");
    printf("2. Remove a directory\n");
    printf("3. Print current working directory\n");
    printf("4. Change directory one level up\n");
    printf("5. Read the contents of the directory\n");
    printf("6. Close the current directory\n");
    printf("q. Exit the program\n");
    scanf(" %c", &choice);
    return choice;
}

int main() {
    while (1) {
        char choice = display_menu();
        switch (choice) {
            case '1':
                create_directory();
                break;
            case '2':
                remove_directory();
                break;
            case '3':
                get_current_directory();
                break;
            case '4':
                change_to_parent_directory();
                break;
            case '5':
                read_directory();
                break;
            case '6':
                close_directory();
                break;
            case 'q':
                exit(0);
                break;
            default:
                printf("Invalid choice, please try again!\n\n");
        }
    }

    return 0;
}
