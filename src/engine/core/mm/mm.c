//
// mm.c - Исходник реализовывающий базовую работу менеджера памяти.
//
// Пока что просто обертка над обычным malloc, но позволяет отслеживать
// использование памяти, и получать размер блока памяти.
// Отслеживание памяти является атомарным, что подходит для многопоточности.
//


// Подключаем:
#include <engine/engine.h>
#include "mm.h"


// Сколько памяти используется в байтах:
static atomic_size_t mm_used_size = 0;


// Получить сколько всего используется памяти в байтах этим менеджером памяти:
size_t mm_get_used_size() {
    return mm_used_size;
}


// Получить сколько всего используется памяти в килобайтах этим менеджером памяти:
float mm_get_used_size_kb() {
    return mm_get_used_size() / 1024.0f;  // b -> kb.
}


// Получить сколько всего используется памяти в мегабайтах этим менеджером памяти:
float mm_get_used_size_mb() {
    return mm_get_used_size() / 1024.0f / 1024.0f;  // b -> kb -> mb.
}


// Получить сколько всего используется памяти в гигабайтах этим менеджером памяти:
float mm_get_used_size_gb() {
    return mm_get_used_size() / 1024.0f / 1024.0f / 1024.0f;  // b -> kb -> mb -> gb.
}


// Получить размер блока в байтах:
size_t mm_get_block_size(void* ptr) {
    if (!ptr) return 0;
    return *(size_t*)((char*)ptr - sizeof(size_t));
}


// Добавить байты к использованной памяти (атомарно):
void mm_used_size_add(size_t size) {
    atomic_fetch_add(&mm_used_size, size);
}


// Вычесть байты из использованной памяти (атомарно):
void mm_used_size_sub(size_t size) {
    atomic_fetch_sub(&mm_used_size, size);
}


// Выделение памяти:
void* mm_alloc(size_t size) {
    // Выделяем с запасом под данные размера блока:
    // [размер блока в size_t|сам блок] <- весь блок.
    // ptr = (void*)(raw_ptr + sizeof(size_t)) -> получить сам блок.
    // raw_ptr = (void*)(ptr - sizeof(size_t)) -> получить весь блок.
    char* raw_ptr = malloc(sizeof(size_t) + size);
    if (!raw_ptr) return NULL;
    *(size_t*)raw_ptr = size;  // Сохраняем размер.
    void* ptr = raw_ptr + sizeof(size_t);
    mm_used_size_add(mm_get_block_size(ptr));
    return ptr;
}


// Выделение памяти с обнулением:
void* mm_calloc(size_t count, size_t size) {
    char* raw_ptr = calloc(1, sizeof(size_t) + count * size);
    if (!raw_ptr) return NULL;
    *(size_t*)raw_ptr = count * size;  // Сохраняем размер.
    void* ptr = raw_ptr + sizeof(size_t);
    mm_used_size_add(mm_get_block_size(ptr));
    return ptr;
}


// Расширение блока памяти:
void* mm_realloc(void* ptr, size_t new_size) {
    if (!ptr) return mm_alloc(new_size);  // Если NULL -> обычный alloc.
    void* raw_ptr = (char*)ptr - sizeof(size_t);
    void* new_raw_ptr = realloc(raw_ptr, sizeof(size_t) + new_size);
    if (!new_raw_ptr) return NULL;
    mm_used_size_add(new_size - *(size_t*)new_raw_ptr);
    *(size_t*)new_raw_ptr = new_size;
    return (char*)new_raw_ptr + sizeof(size_t);
}


// Освобождение памяти:
void mm_free(void* ptr) {
    if (!ptr) return;
    mm_used_size_sub(mm_get_block_size(ptr));
    free((char*)ptr - sizeof(size_t));
}
