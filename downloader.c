#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include string.h for strlen

#define MAX_URL_LENGTH 256

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <download_path>\n", argv[0]);
        return 1;
    }

    // Open the file
    FILE *file;
    file = fopen("pages.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    char download_path[256];
    snprintf(download_path, sizeof(download_path), "%s/", argv[1]);

    // Read URLs line by line and download them using curl
    char url[MAX_URL_LENGTH];
    while (fgets(url, sizeof(url), file)) {
        // Remove newline character if present
        if (url[strlen(url) - 1] == '\n')
            url[strlen(url) - 1] = '\0';

        // Construct the curl command
        char command[512];
        snprintf(command, sizeof(command), "curl -o \"%s/%s\" \"%s\"", download_path, strrchr(url, '/') + 1, url);

        // Execute the curl command
        int status = system(command);
        if (status != 0) {
            fprintf(stderr, "Error downloading URL: %s\n", url);
        }
    }

    // Close the file
    fclose(file);

    return 0;
}
