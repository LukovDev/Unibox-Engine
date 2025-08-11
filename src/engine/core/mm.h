//
// mm.c - Заголовочный файл исходника, реализовывающий базовую работу универсального менеджера памяти.
//

#pragma once


// Размер кучи в байтах:
extern size_t mm_heap_size;

// Сколько памяти используется в байтах:
extern size_t mm_used_size;


// Структура типа блока памяти:
typedef struct {
    size_t size;
    void* ptr;
} MMBlock;
