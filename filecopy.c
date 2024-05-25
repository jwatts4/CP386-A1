/*
 * 1. Open the input file for reading
 * 2. Create and open the output file for writing (overwrite if exists)
 * 3. Read from the input file and write to the output file
 * 4. Handle errors during file operations
 * 5. Close both files
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc <= 2) {
        printf("Insufficient parameters passed.\n");
        return 1;
    }

    // Retrieve parameters
    char* input_name = argv[1];
    char* output_name = argv[2];

    // No idea how long to make this, so this should be enough!
    const int LINE_LENGTH = 1024;

    // Open the input for reading
    FILE* input_file = fopen(input_name, "r");
    if (input_file == NULL) {
        perror("Error opening input file, here's why: ");
        return 1;
    }

    // Open the output file for writing and say goodbye to existing file
    FILE* output_file = fopen(output_name, "w");
    if (output_file == NULL) {
        perror("Error opening output file, here's why: ");
        fclose(input_file);
        return 1;
    }

    char buffer[LINE_LENGTH];  // Buffer to hold each line of the file
    while (fgets(buffer, LINE_LENGTH, input_file) != NULL) {
        if (fputs(buffer, output_file) == EOF) {
            perror("Error writing to output file, here's why: ");
            fclose(input_file);
            fclose(output_file);
            return 1;
        }
    }

    // Check for read errors
    if (ferror(input_file)) {
        perror("Error reading from input file, here's why: ");
    }

    // Close the files
    if (fclose(input_file) != 0) {
        perror("Error closing input file, here's why: ");
    }

    if (fclose(output_file) != 0) {
        perror("Error closing output file, here's why: ");
    }

    printf(
        "The contents of file '%s' have been successfully copied into '%s' "
        "file.\n",
        input_name, output_name);

    return 0;
}
