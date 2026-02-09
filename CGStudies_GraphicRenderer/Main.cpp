#include <iostream>
#include <SDL.h>
#include <vector>

bool is_running = false;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* color_buffer_texture = NULL;

int window_width = 256;
int window_height = 256;

// uint32_t is a FIXED SIZE type. This is to guarantee that every color will have 32 bits (8 per channel, RGBA)
std::vector<uint32_t>color_buffer(sizeof(uint32_t) * window_width * window_height);

bool initialize_window(void) 
{
    // we must indicate what OperatingSystem hardware to initialize, graphics, keyboard, mouse... 
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
    {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }

    // SDL_CreateWindow takes 6 parameters: 
    window = SDL_CreateWindow(
        NULL, // a title
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, // position X and position Y (origin of the window at top-left), 
        window_width, // width
        window_height, // height
        SDL_WINDOW_BORDERLESS //flags
    );
    if (!window) 
    {
        fprintf(stderr, "Error creating SDL window.\n");
        return false;
    }

    // Create a SDL renderer
                         // this index referes to which monitor, -1 is the first one found
    renderer = SDL_CreateRenderer(window, -1, 0); // and 0 means no flags
    if (!renderer)
    {
        fprintf(stderr, "Error creating SDL renderer.\n");
        return false;
    }

    return true;
}

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

void render_color_buffer() 
{
    SDL_UpdateTexture(
        color_buffer_texture,
        NULL,
        color_buffer.data(),
        (int)(window_width * sizeof(uint32_t)) // size of pixels in a single row
    );

    SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color) 
{
    for (int y = 0; y < window_height; y++)
    {
        for (int x = 0; x < window_width; x++) 
        {
            uint8_t r = 0 + x;
            uint8_t g = 0 + y;
            uint8_t b = 0;
            uint8_t a = 1.0;

            // bitshifting to combine the colors back
            // remember: every section is 8bits, so shifting in multiples of 8
            color = (a << 24) | (r << 16) | (g << 8) | b;

            // window_width * y means we are selecting our row index
            // + x means that, once we're in the right row, we offset (1 unit at a time) to find the right column).
            color_buffer[(window_width * y) + x] = color;
        }
    }
}

void render() 
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    render_color_buffer();
    clear_color_buffer(0XFFFFFF00);

    SDL_RenderPresent(renderer);
}

void clean_up() 
{
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
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

    clean_up();

    std::cout << "this is for me to remember how to std::cout" << std::endl;
    return 0;
}