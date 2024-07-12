#include <stdbool.h>
#include <stdint.h>
#include "src/include/SDL2/SDL.h"
#include "src/include/SDL2/SDL_events.h"
#include "src/include/SDL2/SDL_render.h"
#include "src/include/SDL2/SDL_video.h"
#include "src/include/linkedList.h"

#define WIDTH 320 
#define HEIGHT 200


int main(int argc, char *argv[]){

    bool quit = false;
    bool leftMouseButtonDown = false;
    SDL_Event event;

    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    bool drawing = false;

    linkedList *lines = newList();

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Line Drawing",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640 * 2, 480 * 2, 0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_RenderSetLogicalSize(renderer, WIDTH, HEIGHT);

    while (!quit) {

        SDL_WaitEvent(&event);


        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        x1 = event.motion.x;
                        y1 = event.motion.y;
                        x2 = event.motion.x;
                        y2 = event.motion.y;
                        drawing = true;
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        drawing = false;
                        Line line = {x1, y1, x2, y2};
                        addFirstNode(lines, line);
                        break;
                }
                break;
            case SDL_MOUSEMOTION:
                if (drawing) {
                    x2 = event.motion.x;
                    y2 = event.motion.y;
                }
                break;
        }

        SDL_SetRenderDrawColor(renderer, 242,  242,  242, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        if (drawing)
            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

        node *cursor = lines->head;
        for (int i = 0; i < lines->len; i++) {
            Line line = cursor->value;
            SDL_RenderDrawLine(renderer, line.x1, line.y1, line.x2, line.y2);
            cursor = cursor->next;
        }


        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
