#ifndef DRAW_H
#define DRAW_H

#include "display.h"

void draw_rect(int x, int y, int width, int height, uint32_t color);

void draw_grid(int grid_size, uint32_t color);

void draw_pixel(int x, int y, uint32_t color);

#endif