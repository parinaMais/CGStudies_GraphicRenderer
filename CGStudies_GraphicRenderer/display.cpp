#include "display.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
// uint32_t is a FIXED SIZE type. This is to guarantee that every color will have 32 bits (8 per channel, RGBA)
std::vector<uint32_t>color_buffer(sizeof(uint32_t)* window_width* window_height);
SDL_Texture* color_buffer_texture = NULL;

int window_width = 256;
int window_height = 256;

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
            // window_width * y means we are selecting our row index
            // + x means that, once we're in the right row, we offset (1 unit at a time) to find the right column).
            color_buffer[(window_width * y) + x] = color;
        }
    }
}

void destroy_window()
{
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}
