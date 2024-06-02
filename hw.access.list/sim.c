#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fifo.h"
#include "nru.h"

#define MAX_ACCESS 50000

Access access_list[MAX_ACCESS];
int total_access = 0;

void read_access_list(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open access list file");
        exit(EXIT_FAILURE);
    }

    while (fscanf(file, "%d %c", &access_list[total_access].page_number, &access_list[total_access].operation) != EOF) {
        total_access++;
    }

    fclose(file);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <algorithm> <frame_count>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* algorithm = argv[1];
    int frame_count = atoi(argv[2]);

    read_access_list("access.list");

    if (strcmp(algorithm, "fifo") == 0) {
        simulate_fifo(access_list, total_access, frame_count);
    } else if (strcmp(algorithm, "nru") == 0) {
        simulate_nru(access_list, total_access, frame_count);
    } else {
        fprintf(stderr, "Unknown algorithm: %s\n", algorithm);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

