//
// std-pc.c - Исходник реализовывающий API платформозависящих функций стандартной библиотеки под ПК.
//


// Подключаем:
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../std.h"


// Выделить блок памяти:
void* platform_malloc(size_t size) {
    return malloc(size);
}


// Освободить блок памяти:
void platform_free(void* ptr) {
    free(ptr);
}


// Вывести простое сообщение:
void platform_print(const char* msg) {
    puts(msg);
}


// Вывести сообщение с форматированием:
void platform_printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}
