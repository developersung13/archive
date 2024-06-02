#ifndef ACCESS_H
#define ACCESS_H

typedef struct {
    int page_number;
    char operation; // 'R' for read, 'W' for write
} Access;

#endif // ACCESS_H

