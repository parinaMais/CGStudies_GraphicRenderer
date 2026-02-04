#include <iostream>
#include <SDL.h>

bool is_running = false;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

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
        800, // width
        600, // height
        SDL_WINDOW_BORDERLESS //flags
    );
    // checks if pointer is null
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
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) 
                is_running = false;
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

    std::cout << "this is for me to remember how to std::cout" << std::endl;
    return 0;
}