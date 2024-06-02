#include "fifo.h"
#include <stdio.h>
#include <stdlib.h>

void simulate_fifo(Access access_list[], int total_access, int frame_count) {
    int *frames = (int *)malloc(frame_count * sizeof(int));
    int *used = (int *)calloc(frame_count, sizeof(int));
    int hits = 0, faults = 0, read_count = 0, write_count = 0;
    int next_replace = 0;

    for (int i = 0; i < frame_count; i++) {
        frames[i] = -1;
    }

    for (int i = 0; i < total_access; i++) {
        int page = access_list[i].page_number;
        char operation = access_list[i].operation;

        int hit = 0;
        for (int j = 0; j < frame_count; j++) {
            if (frames[j] == page) {
                hit = 1;
                hits++;
                break;
            }
        }

        if (!hit) {
            frames[next_replace] = page;
            next_replace = (next_replace + 1) % frame_count;
            faults++;
        }

        if (operation == 'R') {
            read_count++;
        } else if (operation == 'W') {
            write_count++;
        }
    }

    free(frames);
    free(used);

    printf("Total number of access: %d\n", total_access);
    printf("Total number of read: %d\n", read_count);
    printf("Total number of write: %d\n", write_count);
    printf("Number of page hits: %d\n", hits);
    printf("Number of page faults: %d\n", faults);
    printf("Page fault rate: %d/%d = %.2f%%\n", faults, total_access, (double)faults / total_access * 100);
}

