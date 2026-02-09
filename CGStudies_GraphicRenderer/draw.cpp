#include "draw.h"
#include <iostream>

void draw_rect(int x, int y, int width, int height, uint32_t color)
{
    for (int i = y; i < height; i++)
    {
        for (int j = x; j < width; j++)
        {
            color_buffer[(window_width * i) + j] = color;
        }
    }
}

void draw_grid(int grid_size, uint32_t color)
{
    for (int y = 0; y < window_height; y++)
    {
        for (int x = 0; x < window_width; x++)
        {
            if (x % grid_size == 0 || y % grid_size == 0)
                color_buffer[(window_width * y) + x] = color;
        }
    }
}

void draw_pixel(int x, int y, uint32_t color) 
{
    color_buffer[(window_width * y) + x] = color;
}
