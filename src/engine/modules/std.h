//
// std.h - Заголовочный файл стандартной библиотеки под разные платформы.
//         Просто реализация базовых вещей для разных платформ.
//

#pragma once


// Выделить блок памяти:
void* platform_malloc(size_t size);

// Освободить блок памяти:
void platform_free(void* ptr);

// Вывести простое сообщение:
void platform_print(const char* msg);

// Вывести сообщение с форматированием:
void platform_printf(const char* fmt, ...);
