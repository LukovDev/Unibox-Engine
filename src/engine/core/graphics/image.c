//
// image.c - Исходник для работы с картинками (изображениями в сыром виде).
//


// Подключаем:
#include <engine/core/mm/mm.h>
#include "stb_image.h"
#include "image.h"


// Загрузить картинку:
Image* Image_load(const char* filepath, int format) {
    Image* image = mm_alloc(sizeof(Image));
    if (image == NULL) return NULL;
    if (format == 0) format = IMG_RGBA;
    if (filepath == NULL) return NULL;
    image->data = stbi_load(filepath, &image->width, &image->height, &image->channels, format);
    if (image->data == NULL) {
        mm_free(image);
        return NULL;
    }
    mm_used_size_add(Image_get_size(image));
    return image;
}


// Освободить память картинки:
void Image_destroy(Image** image) {
    if (!image || !*image) return;
    if ((*image)->data != NULL) {
        stbi_image_free((*image)->data);
        mm_used_size_sub(Image_get_size(*image));
    }
    mm_free((*image));
    *image = NULL;
}


// Получить размер картинки в байтах:
size_t Image_get_size(Image* image) {
    if (!image) return 0;
    return image->width * image->height * image->channels;
}
