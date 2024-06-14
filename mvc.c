#include <stdio.h>
#include <stdlib.h>

// Function to display usage information
void show_usage(const char *program_name) {
    printf("Usage: %s <source_file> <destination_file>\n", program_name);
}

// Function to copy the contents of the source file to the destination file
int copy_file(const char *source_file, const char *destination_file) {
    FILE *src = fopen(source_file, "rb");
    if (src == NULL) {
        perror("Error opening source file");
        return -1;
    }

    FILE *dest = fopen(destination_file, "wb");
    if (dest == NULL) {
        perror("Error opening destination file");
        fclose(src);
        return -1;
    }

    char buffer[4096];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        if (fwrite(buffer, 1, bytes, dest) != bytes) {
            perror("Error writing to destination file");
            fclose(src);
            fclose(dest);
            return -1;
        }
    }

    fclose(src);
    fclose(dest);

    return 0;
}

// Function to delete the source file
int delete_file(const char *filename) {
    if (remove(filename) != 0) {
        perror("Error deleting source file");
        return -1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 3) {
        show_usage(argv[0]);
        return EXIT_FAILURE;
    }

    // Get the source and destination file paths from the arguments
    const char *source_file = argv[1];
    const char *destination_file = argv[2];

    // Copy the source file to the destination
    if (copy_file(source_file, destination_file) != 0) {
        return EXIT_FAILURE;
    }

    // Delete the source file
    if (delete_file(source_file) != 0) {
        return EXIT_FAILURE;
    }

    // Successful move
    return EXIT_SUCCESS;
}




