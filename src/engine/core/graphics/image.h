//
// image.h - Заголовочный файл для работы с картинками (изображениями в сыром виде).
//

#pragma once


// Подключаем:
#include <engine/engine.h>


// Размеры каналов в байтах:
#define IMG_R    1
#define IMG_RA   2
#define IMG_RGB  3
#define IMG_RGBA 4

// Типовая структура картинки:
typedef struct {
    int width;
    int height;
    int channels;
    uchar* data;
} Image;


// Загрузить картинку:
Image* Image_load(const char* filepath, int format);

// Освободить память картинки:
void Image_destroy(Image** image);

// Получить размер картинки в байтах:
size_t Image_get_size(Image* image);
