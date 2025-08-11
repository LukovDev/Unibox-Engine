//
// mm.c - Исходник реализовывающий базовую работу универсального менеджера памяти.
//


// Подключаем:
#include <core/include.h>
#include "mm.h"


// Размер кучи в байтах:
size_t mm_heap_size = 0;

// Сколько памяти используется в байтах:
size_t mm_used_size = 0;


// Функция для создания типа блока памяти:
MMBlock* mm_create_block(size_t size, void* ptr) {
    MMBlock* block = std_malloc(sizeof(MMBlock));
    if (!block) return NULL;
    block->size = size;
    block->ptr = ptr;
    return block;
}


// Функция для запроса выделения памяти:
MMBlock* mm_alloc(size_t size) {
    void* ptr = std_malloc(size);
    if (!ptr) return NULL;
    MMBlock* b = mm_create_block(size, ptr);
    if (!b) {
        std_free(ptr);
        return NULL;
    }
    mm_used_size += b->size;
    return b;
}


// Функция для запроса выделения памяти с очисткой:
MMBlock* mm_calloc(size_t count, size_t size) {
    void* ptr = std_calloc(count, size);
    if (!ptr) return NULL;
    MMBlock* b = mm_create_block(size*count, ptr);
    if (!b) {
        std_free(ptr);
        return NULL;
    }
    mm_used_size += b->size;
    return b;
}


// Функция для запроса расширения блока памяти:
MMBlock* mm_realloc(MMBlock* block, size_t new_size) {
    if (!block) return NULL;
    void* ptr = std_realloc(block->ptr, new_size);
    if (!ptr) return NULL;
    mm_used_size += (new_size - block->size);
    block->size = new_size;
    block->ptr = ptr;
    return block;
}


// Функция для запроса очистки блока памяти:
void mm_free(MMBlock* block) {
    if (!block) return;
    mm_used_size -= block->size;
    std_free(block->ptr);
    std_free(block);
}
