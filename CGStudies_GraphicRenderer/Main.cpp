#include <iostream>
#include "display.h"
#include "draw.h"

bool is_running = false;

void setup() 
{
    color_buffer_texture = SDL_CreateTexture(
        renderer, // the assigned SDL renderer
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING, // this is so we can update it several times per frame
        window_width,
        window_height
    );
}

void process_input() 
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
        // this is triggered when we click the X button of the window
        case SDL_QUIT:
            is_running = false;
            //clean_up();
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) 
            {
                is_running = false;
                //clean_up();
            }
            break;
    }
}

void update() 
{

}

void render() 
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    draw_grid(10, 0xFFFFFF00);
    draw_rect(20, 35, 120, 200, 0xFFFFFFFF);
    draw_pixel(window_width / 2, window_height / 2, 0xFFFF0000);

    render_color_buffer();
    clear_color_buffer(0XFF000000);

    SDL_RenderPresent(renderer);
}

// these parameters are needed in order for SDL to run, otherwise I get the LNK2019 error
int main(int argc, char*args[]) {
    is_running = initialize_window();
    
    setup();

    while (is_running)
    {
        process_input();
        update();
        render();
    }

    destroy_window();

    // TODO: fazer isso virar um fps
    //std::clog << "\rScanlines remaining: " << (window_height - y) << ' ' << std::flush;

    std::cout << "this is for me to remember how to std::cout" << std::endl;
    return 0;
}