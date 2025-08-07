//
// std-pc.c - Исходник реализовывающий API платформозависящих функций стандартной библиотеки под ПК.
//            Просто реализует некоторые функции, которые могут быть зависимыми от платформы.
//


// Подключаем:
#include <stdio.h>
#include "../std.h"


// Структура для представления файла:
struct stdFile {
    FILE* ptr;
};


// Выделить блок памяти:
void* std_malloc(size_t size) {
    return malloc(size);
}


// Выделить блок памяти с нулевыми значениями:
void* std_calloc(size_t count, size_t size) {
    return calloc(count, size);
}


// Выделить блок памяти:
void* std_realloc(void* ptr, size_t new_size) {
    return realloc(ptr, new_size);
}


// Освободить блок памяти:
void std_free(void* ptr) {
    free(ptr);
}


// Вывести сообщение с форматированием:
void std_printf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    fflush(stdout);
}


// Открыть файл:
stdFile* std_fopen(const char* path, const char* mode) {
    stdFile* file = (stdFile*)std_malloc(sizeof(stdFile));
    if (!file) return NULL;
    file->ptr = fopen(path, mode);
    if (!file->ptr) {
        std_free(file);
        return NULL;
    }
    return file;
}


// Закрыть файл:
void std_fclose(stdFile* file) {
    if (!file) return;
    fclose(file->ptr);
    std_free(file);
}


// Запись форматированная:
int std_fprintf(stdFile* file, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int res = vfprintf(file->ptr, fmt, args);
    va_end(args);
    return res;
}


// Чтение форматированное:
int std_fscanf(stdFile* file, const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int res = vfscanf(file->ptr, fmt, args);
    va_end(args);
    return res;
}


// Прочитать блок:
size_t std_fread(void* ptr, size_t size, size_t count, stdFile* file) {
    return fread(ptr, size, count, file->ptr);
}


// Записать блок:
size_t std_fwrite(const void* ptr, size_t size, size_t count, stdFile* file) {
    return fwrite(ptr, size, count, file->ptr);
}


// Прочитать символ:
int std_fgetc(stdFile* file) {
    return fgetc(file->ptr);
}


// Записать символ:
int std_fputc(int c, stdFile* file) {
    return fputc(c, file->ptr);
}


// Прочитать строку:
char* std_fgets(char* str, int num, stdFile* file) {
    return fgets(str, num, file->ptr);
}


// Записать строку:
int std_fputs(const char* str, stdFile* file) {
    return fputs(str, file->ptr);
}


// Сдвинуть указатель:
int std_fseek(stdFile* file, long offset, int origin) {
    return fseek(file->ptr, offset, origin);
}


// Узнать позицию указателя:
long std_ftell(stdFile* file) {
    return ftell(file->ptr);
}


// Перемотать к началу:
void std_rewind(stdFile* file) {
    rewind(file->ptr);
}


// Удалить файл:
int std_remove(const char* filename) {
    return remove(filename);
}


// Переименовать файл:
int std_rename(const char* old_name, const char* new_name) {
    return rename(old_name, new_name);
}


// Проверить конец файла:
int std_feof(stdFile* file) {
    return feof(file->ptr);
}


// Проверить ошибку чтения:
int std_ferror(stdFile* file) {
    return ferror(file->ptr);
}


// Очистить ошибку чтения:
void std_clearerr(stdFile* file) {
    clearerr(file->ptr);
}


// Сбросить из буфера в файл (синхронизация):
int std_fflush(stdFile* file) {
    return fflush(file->ptr);
}
