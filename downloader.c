#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define MAX_URL_LENGTH 256

int main() {
    FILE *file;
    char url[MAX_URL_LENGTH];
    
    // Open the file
    file = fopen("pages.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }
    
    // Read URLs line by line and download them using curl
    while (fgets(url, sizeof(url), file)) {
        // Remove newline character if present
        if (url[strlen(url) - 1] == '\n')
            url[strlen(url) - 1] = '\0';
        
        // Construct the curl command
        char command[512];
        snprintf(command, sizeof(command), "curl -O \"%s\"", url);
        
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
