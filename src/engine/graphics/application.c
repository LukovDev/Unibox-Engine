//
// application.c - Исходник реализовывающий абстрактный интерфейс для работы с окном.
//


// Подключаем:
#include <engine/core/mm/mm.h>
#include "application.h"


// Создать приложение:
Application* Application_create() {
    Application* app = mm_calloc(1, sizeof(Application));
    if (app == NULL) return NULL;
    app->config = NULL;  // На всякий случай явно указываем NULL.
    return app;
}


// Уничтожить приложение:
void Application_destroy(Application** app) {
    if (!app || !*app) return;
    if ((*app)->config != NULL) AppConfig_destroy(&(*app)->config);
    mm_free((*app));
    *app = NULL;
}


// Создать конфигурацию приложения (НЕ СОЗДАВАЙТЕ БОЛЬШЕ ОДНОГО И СЛЕДИТЕ ЗА УКАЗАТЕЛЯМИ ВНИМАТЕЛЬНО!):
AppConfig* AppConfig_create() {
    AppConfig* config = mm_calloc(1, sizeof(AppConfig));
    if (config == NULL) return NULL;

    // Заполняем поля (значениями по умолчанию):
    config->title = "Window";
    config->icon = NULL;
    config->size[0] = 960;
    config->size[1] = 540;
    config->position[0] = -1;
    config->position[1] = -1;
    config->vsync = true;
    config->fps = 60;
    config->visible = true;
    config->titlebar = true;
    config->resizable = true;
    config->fullscreen = false;
    config->min_size[0] = 0;
    config->min_size[1] = 0;
    config->max_size[0] = 0;
    config->max_size[1] = 0;

    return config;
}


// Уничтожить конфигурацию приложения (НЕ ИСПОЛЬЗУЙТЕ ЕСЛИ ПРИЛОЖЕНИЕ СОЗДАНО! МОГУТ БЫТЬ ПРОБЛЕМЫ С УКАЗАТЕЛЯМИ!):
void AppConfig_destroy(AppConfig** config) {
    if (!config || !*config) return;
    if ((*config)->icon != NULL) Image_destroy(&(*config)->icon);
    mm_free((*config));
    *config = NULL;
}
