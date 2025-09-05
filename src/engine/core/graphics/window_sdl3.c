//
// window_sdl3.c - Исходник, содержащий реализацию интерфейса для работы с окном на основе SDL3.
//


// Подключаем:
#include <engine/engine.h>
#include <engine/core/mm/mm.h>
#include "window_sdl3.h"


// Локальные переменные окна:
static WindowSDL3_Vars* AppVars;


// Создать окно:
Application* WindowSDL3_create(AppConfig* config) {
    Application* app = Application_create();
    if (app == NULL) return NULL;

    // Создаём локальные переменные окна:
    AppVars = mm_calloc(1, sizeof(WindowSDL3_Vars));

    // Задаём значения полей:
    app->config = config;

    app->create = WindowSDL3_Impl_create;
    app->close = NULL;

    app->set_title = NULL;
    app->get_title = NULL;

    app->set_icon = NULL;
    app->get_icon = NULL;

    app->set_size = NULL;
    app->get_size = NULL;

    app->set_width = NULL;
    app->get_width = NULL;

    app->set_height = NULL;
    app->get_height = NULL;

    app->get_center = NULL;

    app->set_position = NULL;
    app->get_position = NULL;

    app->set_vsync = NULL;
    app->get_vsync = NULL;

    app->set_fps = NULL;
    app->get_target_fps = NULL;

    app->set_visible = NULL;
    app->get_visible = NULL;

    app->set_titlebar = NULL;
    app->get_titlebar = NULL;

    app->set_resizable = NULL;
    app->get_resizable = NULL;

    app->set_fullscreen = NULL;
    app->get_fullscreen = NULL;

    app->set_min_size = NULL;
    app->get_min_size = NULL;

    app->set_max_size = NULL;
    app->get_max_size = NULL;

    app->get_window_display_id = NULL;
    app->get_display_size = NULL;
    app->get_current_fps = NULL;
    app->get_dt = NULL;
    app->get_time = NULL;
    app->display = NULL;

    return app;
}


// Реализация интерфейса:


// TODO: Добавить Renderer* renderer структуру.
bool WindowSDL3_Impl_create(Application* self) {
    AppConfig* cfg = self->config;

    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        printf("SDL Init Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_WindowFlags flags = SDL_WINDOW_HIDDEN;
    SDL_Window* window = SDL_CreateWindow(cfg->title, cfg->size[0], cfg->size[1], flags);
    if (!window) {
        printf("CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    AppVars->window = window;

    // Настройка окна:

    SDL_SetWindowMinimumSize(window, cfg->min_size[0], cfg->min_size[1]);
    SDL_SetWindowMaximumSize(window, cfg->max_size[0], cfg->max_size[1]);

    SDL_ShowWindow(window);
    return true;  // true - успех, false - ошибка.
}
