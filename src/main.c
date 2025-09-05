//
// main.c - Основной файл программы.
//


// Подключаем:
#include <engine/engine.h>
#include <engine/core/graphics/window_sdl3.h>
#include <engine/core/mm/mm.h>


// Точка входа в программу:
#ifndef TESTING_MODE
int main(int argc, char *argv[]) {
    printf("%s\n", "Hello World!");

    AppConfig* config = AppConfig_create();
    config->title = "Window";
    config->icon = Image_load("data/icons/logo/unibox/Unibox-Full-W.png", IMG_RGBA);
    Application* app = WindowSDL3_create(config);
    printf("%s, memory used: %zu bytes (%g KB, %g MB)\n", config->title, mm_get_used_size(), mm_get_used_size_kb(), mm_get_used_size_mb());
    if (app->create(app)) {
        printf("Window created.\n");
    } else {
        printf("Window create error.\n");
    }

    // while (true) {}
    Application_destroy(&app);
    printf("memory used: %zu bytes (%g KB, %g MB)\n",
           mm_get_used_size(),
           mm_get_used_size_kb(),
           mm_get_used_size_mb());


    // Image* image = Image_load("data/icons/logo/unibox/Unibox-Full-W.png", IMG_RGBA);

    // SDL_Surface* icon = SDL_CreateSurfaceFrom(image->width, image->height, SDL_PIXELFORMAT_RGBA32, image->data, image->width*image->channels);

    // if (icon) {
    //     SDL_SetWindowIcon(window, icon);
    //     SDL_DestroySurface(icon);
    // }
    // Image_free(image);

    // int x, y;
    // SDL_GetWindowPosition(window, &x, &y);
    // printf("Window position: x = %d, y = %d\n", x, y);

    // bool app_run = true;
    // SDL_Event event;
    // while (app_run) {
    //     SDL_GetWindowSize(window, &winsize[0], &winsize[1]);
    //     while (SDL_PollEvent(&event)) {
    //         switch (event.type) {
    //         case SDL_EVENT_QUIT:
    //             app_run = 0;
    //             break;

    //         default:
    //             break;
    //         }
    //     }

    //     color[0] = 255;
    //     color[1] = 0;
    //     color[2] = 0;

    //     if (direction[0]) {
    //         rect.x += speed;
    //     } else {
    //         rect.x -= speed;
    //     }

    //     if (direction[1]) {
    //         rect.y += speed;
    //     } else {
    //         rect.y -= speed;
    //     }

    //     if (rect.x+rect.w >= winsize[0]) {
    //         direction[0] = false;
    //     } else if (rect.x <= 0) {
    //         direction[0] = true;
    //     }

    //     if (rect.y+rect.h >= winsize[1]) {
    //         direction[1] = false;
    //     } else if (rect.y <= 0) {
    //         direction[1] = true;
    //     }

    //     if (rect.x+rect.w > winsize[0]-1 || rect.x-1 < 0 || rect.y+rect.h > winsize[1]-1 || rect.y-1 < 0) {
    //         color[0] = 0;
    //         color[1] = 255;
    //         color[2] = 0;
    //     }

    //     SDL_SetRenderDrawColor(renderer, 10, 20, 30, 255);
    //     SDL_RenderClear(renderer);

    //     SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    //     SDL_RenderFillRect(renderer, &rect);
    //     SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], 255);
    //     SDL_RenderRect(renderer, &rect);

    //     SDL_RenderPresent(renderer);
    // }

    // SDL_DestroyWindow(window);
    // SDL_Quit();
    return 0;
}
#endif
