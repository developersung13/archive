#include "nru.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int page;
    int reference;
    int modify;
    int time;
} Page;

void simulate_nru(Access access_list[], int total_access, int frame_count) {
    Page *frames = (Page *)malloc(frame_count * sizeof(Page));
    int hits = 0, faults = 0, read_count = 0, write_count = 0;
    int current_time = 0;

    for (int i = 0; i < frame_count; i++) {
        frames[i].page = -1;
        frames[i].reference = 0;
        frames[i].modify = 0;
        frames[i].time = 0;
    }

    for (int i = 0; i < total_access; i++) {
        int page = access_list[i].page_number;
        char operation = access_list[i].operation;
        current_time++;

        int hit = 0;
        for (int j = 0; j < frame_count; j++) {
            if (frames[j].page == page) {
                frames[j].reference = 1;
                if (operation == 'W') {
                    frames[j].modify = 1;
                }
                frames[j].time = current_time;
                hit = 1;
                hits++;
                break;
            }
        }

        if (!hit) {
            int replace_index = -1;
            int min_class = 4;
            for (int j = 0; j < frame_count; j++) {
                int class = frames[j].reference * 2 + frames[j].modify;
                if (class < min_class) {
                    min_class = class;
                    replace_index = j;
                } else if (class == min_class && frames[j].time < frames[replace_index].time) {
                    replace_index = j;
                }
            }

            frames[replace_index].page = page;
            frames[replace_index].reference = 1;
            frames[replace_index].modify = (operation == 'W') ? 1 : 0;
            frames[replace_index].time = current_time;
            faults++;
        }

        if (operation == 'R') {
            read_count++;
        } else if (operation == 'W') {
            write_count++;
        }
    }

    free(frames);

    printf("Total number of access: %d\n", total_access);
    printf("Total number of read: %d\n", read_count);
    printf("Total number of write: %d\n", write_count);
    printf("Number of page hits: %d\n", hits);
    printf("Number of page faults: %d\n", faults);
    printf("Page fault rate: %d/%d = %.2f%%\n", faults, total_access, (double)faults / total_access * 100);
}

