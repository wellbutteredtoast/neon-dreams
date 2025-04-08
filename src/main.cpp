#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (TTF_Init() != 0) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    

    SDL_Window* window = SDL_CreateWindow(
        "Neon Dreams",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    // Will only grab the latest error, either window or renderer
    if (!window || !renderer) {
        std::cerr << "SDL Init Error: " << SDL_GetError() << std::endl;
        if (!renderer) {
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 1;
        }
        if (!window) {
            SDL_Quit();
            return 1;
        }

        return 1;
    }

    // Default font rendering
    TTF_Font* font = TTF_OpenFont("assets/fonts/pixeled.ttf", 12);
    if (!font) {
        std::cerr << "Font Load Error: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    bool running = true;
    SDL_Event event;

    Uint32 lastTime = SDL_GetTicks();
    int frames = 0;
    float fps = 0.0f;

    // Game loop
    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        frames++;

        if (currentTime - lastTime >= 1000) {
            fps = frames * 1000.0f / (currentTime - lastTime);
            frames = 0;
            lastTime = currentTime;
        }

        // Event polling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
        SDL_RenderClear(renderer);

        // Render FPS text
        SDL_Color color = {255, 255, 255};
        std::string fpsText = "FPS: " + std::to_string(static_cast<int>(fps));
        SDL_Surface* surface = TTF_RenderText_Solid(font, fpsText.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        SDL_Rect dest;
        dest.x = 10;
        dest.y = 10;
        dest.w = surface->w;
        dest.h = surface->h;

        SDL_RenderCopy(renderer, texture, nullptr, &dest);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}