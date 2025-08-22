//
// application.h - Заголовочный файл исходника.
//

#pragma once


// Подключаем:
#include <engine/core/graphics/image.h>


// Объявление структур:
typedef struct Application Application;
typedef struct AppConfig AppConfig;

// Типовая структура приложения:
typedef struct Application {
    AppConfig* config;  // Конфигурация окна приложения.

    // Основные функции приложения (callbacks):
    void (*start)   (struct Application* self);            // Вызывается после создания окна.
    void (*update)  (struct Application* self, float dt);  // Вызывается каждый кадр (цикл окна).
    void (*render)  (struct Application* self, float dt);  // Вызывается каждый кадр (отрисовка окна).
    void (*resize)  (struct Application* self, int width, int height);  // Вызывается при изменении размера окна.
    void (*show)    (struct Application* self);            // Вызывается при разворачивании окна.
    void (*hide)    (struct Application* self);            // Вызывается при сворачивании окна.
    void (*destroy) (struct Application* self);            // Вызывается при закрытии окна.

    // -------------------------------- API окна: --------------------------------
    bool (*create) (struct Application* self);  // Вызовите для открытия приложения.
    bool (*close)  (struct Application* self);  // Вызовите для закрытия приложения.

    void        (*set_title) (struct Application* self, const char* title);  // Установить заголовок окна.
    const char* (*get_title) (struct Application* self);                     // Получить заголовок окна.

    void   (*set_icon) (struct Application* self, Image* image);             // Установить иконку окна.
    Image* (*get_icon) (struct Application* self);                           // Получить иконку окна.

    void (*set_size) (struct Application* self, int width, int height);      // Установить размер окна.
    void (*get_size) (struct Application* self, int* width, int* height);    // Получить размер окна.

    void (*set_width) (struct Application* self, int width);          // Установить ширину окна.
    int  (*get_width) (struct Application* self);                     // Получить ширину окна.

    void (*set_height) (struct Application* self, int height);        // Установить высоту окна.
    int  (*get_height) (struct Application* self);                    // Получить высоту окна.

    void (*get_center) (struct Application* self, int* x, int* y);    // Получить центр окна.

    void (*set_position) (struct Application* self, int x, int y);    // Установить позицию окна.
    void (*get_position) (struct Application* self, int* x, int* y);  // Получить позицию окна.

    void (*set_vsync) (struct Application* self, bool vsync);         // Установить вертикальную синхронизацию.
    bool (*get_vsync) (struct Application* self);                     // Получить вертикальную синхронизацию.

    void (*set_fps)        (struct Application* self, int fps);       // Установить фпс окна.
    int  (*get_target_fps) (struct Application* self);                // Получить установленный фпс окна.

    void (*set_visible) (struct Application* self, bool visible);     // Установить видимость окна.
    bool (*get_visible) (struct Application* self);                   // Получить видимость окна.

    void (*set_titlebar) (struct Application* self, bool titlebar);   // Установить видимость заголовка окна.
    bool (*get_titlebar) (struct Application* self);                  // Получить видимость заголовка окна.

    void (*set_resizable) (struct Application* self, bool resizable);    // Установить масштабируемость окна.
    bool (*get_resizable) (struct Application* self);                    // Получить масштабируемость окна.

    void (*set_fullscreen) (struct Application* self, bool fullscreen);  // Установить полноэкранный режим.
    bool (*get_fullscreen) (struct Application* self);                   // Получить полноэкранный режим.

    void (*set_min_size) (struct Application* self, int width, int height);    // Установить мин. размер окна.
    void (*get_min_size) (struct Application* self, int* width, int* height);  // Получить мин. размер окна.

    void (*set_max_size) (struct Application* self, int width, int height);    // Установить макс. размер окна.
    void (*get_max_size) (struct Application* self, int* width, int* height);  // Получить макс. размер окна.

    unsigned int (*get_window_display_id) (struct Application* self);  // Получить айди дисплея в котором это окно.

    bool (*get_display_size) (struct Application* self, unsigned int id, int* w, int* h);  // Получить размер дисплея.

    float (*get_current_fps) (struct Application* self);  // Получить текущий фпс.

    float (*get_dt) (struct Application* self);     // Получить дельту времени.

    double (*get_time) (struct Application* self);  // Получить время со старта окна.

    void (*display) (struct Application* self);     // Отрисовка содержимого окна.
} Application;

// Конфигурация окна приложения:
typedef struct AppConfig {
    const char* title;  // Заголовок окна.
    Image* icon;        // Иконка окна.
    int  size[2];       // Размер окна {width, height}.
    int  position[2];   // Позиция окна {x, y} или {-1, -1} для "по умолчанию".
    bool vsync;         // Вертикальная синхронизация.
    int  fps;           // Количество кадров в секунду.
    bool visible;       // Видимость окна (скрыт/виден).
    bool titlebar;      // Видимость заголовка окна.
    bool resizable;     // Масштабируемость окна.
    bool fullscreen;    // Полноэкранный режим.
    int  min_size[2];   // Минимальный размер окна {width, height}.
    int  max_size[2];   // Максимальный размер окна {width, height}.
} AppConfig;


// Создать конфигурацию приложения:
AppConfig* AppConfig_create();

// Удалить конфигурацию приложения:
void AppConfig_destroy(AppConfig* config);
