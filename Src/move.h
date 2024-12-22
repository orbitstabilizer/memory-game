#ifndef MOVE_H
#define MOVE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t button;
    uint8_t time;
    bool fail;
} MOVE;

#endif