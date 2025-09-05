//
// window_sdl3.h - Заголовочный файл исходника.
//

#pragma once


// Подключаем:
#include <engine/graphics/application.h>
#include <SDL3/SDL.h>


// Типовая структура переменных окна:
typedef struct {
    SDL_Window* window;
} WindowSDL3_Vars;


// Создать окно:
Application* WindowSDL3_create(AppConfig* config);


// Реализация интерфейса:


bool WindowSDL3_Impl_create(Application* self);

