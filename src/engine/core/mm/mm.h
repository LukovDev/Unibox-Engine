//
// mm.c - Заголовочный файл исходника.
//

#pragma once


// Подключаем:
#include <engine/engine.h>


// Получить сколько всего используется памяти в байтах этим менеджером памяти:
size_t mm_get_used_size();

// Получить сколько всего используется памяти в килобайтах этим менеджером памяти:
float mm_get_used_size_kb();

// Получить сколько всего используется памяти в мегабайтах этим менеджером памяти:
float mm_get_used_size_mb();

// Получить сколько всего используется памяти в гигабайтах этим менеджером памяти:
float mm_get_used_size_gb();

// Получить размер блока в байтах:
size_t mm_get_block_size(void* ptr);

// Добавить байты к использованной памяти (атомарно):
void mm_used_size_add(size_t size);

// Вычесть байты из использованной памяти (атомарно):
void mm_used_size_sub(size_t size);

// Выделение памяти:
void* mm_alloc(size_t size);

// Выделение памяти с обнулением:
void* mm_calloc(size_t count, size_t size);

// Расширение блока памяти:
void* mm_realloc(void* ptr, size_t new_size);

// Освобождение памяти:
void mm_free(void* ptr);
