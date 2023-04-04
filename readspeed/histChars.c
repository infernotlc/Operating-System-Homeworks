#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    int c, fd;
    char *data, *p;
    size_t length, i, count[256] = {0};
    struct stat st;
    int cache_size = BUFFER_SIZE;
    char *read_type = "read";

    while ((c = getopt(argc, argv, "t:b:")) != -1) {
        switch (c) {
            case 't':
                read_type = optarg;
                break;
            case 'b':
                cache_size = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-t read|mmap] [-b cache_size] file\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-t read|mmap] [-b cache_size] file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if (strcmp(read_type, "read") == 0) {
        char buffer[BUFFER_SIZE];
        ssize_t nread;

        fd = open(argv[optind], O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        while ((nread = read(fd, buffer, cache_size)) > 0) {
            for (i = 0; i < nread; i++) {
                count[(unsigned char)buffer[i]]++;
            }
        }

        if (nread == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (close(fd) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }
    } else if (strcmp(read_type, "mmap") == 0) {
        fd = open(argv[optind], O_RDONLY);
        if (fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        if (fstat(fd, &st) == -1) {
            perror("fstat");
            exit(EXIT_FAILURE);
        }

        length = st.st_size;
        data = mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0);
        if (data == MAP_FAILED) {
            perror("mmap");
            exit(EXIT_FAILURE);
        }

        for (p = data; p < data + length; p++) {
            count[(unsigned char)*p]++;
        }

        if (munmap(data, length) == -1) {
            perror("munmap");
            exit(EXIT_FAILURE);
        }

        if (close(fd) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Invalid read type: %s\n", read_type);
        exit(EXIT_FAILURE);
    }

    printf("ASCII character histogram:\n");
    for (i = 0; i < 256; i++) {
        if (count[i] > 0) {
            printf("%c: %lu\n", (char)i, count[i]);
        }
    }

    return 0;
}
