//
// application.c - Исходник реализовывающий абстрактный интерфейс для работы с окном.
//


// Подключаем:
#include "application.h"
#include <engine/core/graphics/image.h>


// Создать конфигурацию приложения:
AppConfig* AppConfig_create() {
    AppConfig* config = malloc(sizeof(AppConfig));
    if (config == NULL) return NULL;

    // Заполняем поля:
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


// Удалить конфигурацию приложения:
void AppConfig_destroy(AppConfig* config) {
    if (config == NULL) return;
    if (config->icon != NULL) Image_free(config->icon);
    free(config);
}
