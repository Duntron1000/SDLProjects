#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_events.h"
#include "src/include/SDL2/SDL_render.h"
#include "src/include/SDL2/SDL_video.h"

#define WIDTH 640
#define HEIGHT 480

int main(int argc, char *argv[]){

    bool quit = false;
    bool leftMouseButtonDown = false;
    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Pixel Drawing",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, 0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_Texture * texture = SDL_CreateTexture(renderer,
            SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);

    uint32_t *pixels;
    pixels = (uint32_t*)malloc(WIDTH * HEIGHT * sizeof(uint32_t));

    if (pixels == NULL) {
        printf("Error allocating pixels");
        return -1;
    }
    
    /* make the pixels all white */
    memset(pixels, 255, WIDTH * HEIGHT * sizeof(Uint32));

    while (!quit) {
        /* send the pixle array to update the texture */
        SDL_UpdateTexture(texture, NULL, pixels, WIDTH * sizeof(uint32_t));

        SDL_WaitEvent(&event);

        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                    leftMouseButtonDown = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                    leftMouseButtonDown = true;
            case SDL_MOUSEMOTION:
                if (leftMouseButtonDown) {
                    int mousex = event.motion.x;
                    int mousey = event.motion.y;

                    pixels[mousey * WIDTH + mousex] = 0;
                }
                break;
        }



        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }

    free(pixels);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
