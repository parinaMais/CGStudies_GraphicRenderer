#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL.h>
#include <vector>

extern SDL_Window* window;
extern SDL_Renderer* renderer;
// uint32_t is a FIXED SIZE type. This is to guarantee that every color will have 32 bits (8 per channel, RGBA)
extern std::vector<uint32_t>color_buffer;
extern SDL_Texture* color_buffer_texture;

extern int window_width;
extern int window_height;

bool initialize_window(void);
void render_color_buffer();
void clear_color_buffer(uint32_t color);
void destroy_window();

#endif
