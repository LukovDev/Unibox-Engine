//
// image.c - Исходник для работы с картинками (изображениями в сыром виде).
//


// Подключаем:
#include "image.h"
#include "stb_image.h"


// Функция загрузки картинки:
Image* Image_load(const char* filepath, int format) {
    Image* image = malloc(sizeof(Image));
    if (image == NULL) return NULL;
    image->data = stbi_load(filepath, &image->width, &image->height, &image->channels, format);
    if (image->data == NULL) {
        free(image);
        return NULL;
    }
    return image;
}


// Функция освобождения памяти картинки:
void Image_free(Image* image) {
    if (image == NULL) return;
    stbi_image_free(image->data);
    free(image);
}
