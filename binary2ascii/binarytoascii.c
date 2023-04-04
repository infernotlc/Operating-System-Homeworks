#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void usage() {
    printf("Usage: binarytoascii [-i input_file] [-o output_file] [-I input_fd] [-O output_fd]\n");
}

int main(int argc, char *argv[]) {
    // Default input/output file descriptors
    int input_fd = STDIN_FILENO;
    int output_fd = STDOUT_FILENO;
    // Default input/output file names
    char *input_file = NULL;
    char *output_file = NULL;
    // Parse command line arguments
    int opt;
    while ((opt = getopt(argc, argv, "i:o:I:O:")) != -1) {
        switch (opt) {
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'I':
                input_fd = atoi(optarg);
                break;
            case 'O':
                output_fd = atoi(optarg);
                break;
            default:
                usage();
                exit(EXIT_FAILURE);
        }
    }
    // Open input file if specified
    if (input_file != NULL) {
        input_fd = open(input_file, O_RDONLY);
        if (input_fd < 0) {
            perror("Error opening input file");
            exit(EXIT_FAILURE);
        }
    }
    // Open output file if specified
    if (output_file != NULL) {
        output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        if (output_fd < 0) {
            perror("Error opening output file");
            exit(EXIT_FAILURE);
        }
    }
    // Convert binary data to ASCII characters
    char byte;
    while (read(input_fd, &byte, sizeof(char)) == sizeof(char)) {
        dprintf(output_fd, "%d\n", (unsigned char) byte);
    }
    // Close input/output files if necessary
    if (input_file != NULL) {
        close(input_fd);
    }
    if (output_file != NULL) {
        close(output_fd);
    }
    return EXIT_SUCCESS;
}
