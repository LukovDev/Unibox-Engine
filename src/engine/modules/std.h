//
// std.h - Заголовочный файл стандартной библиотеки под разные платформы.
//

#pragma once


// Подключаем:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>


// Выделить блок памяти:
void* std_malloc(size_t size);

// Выделить блок памяти с нулевыми значениями:
void* std_calloc(size_t count, size_t size);

// Выделить блок памяти:
void* std_realloc(void* ptr, size_t new_size);

// Освободить блок памяти:
void std_free(void* ptr);

// Вывести сообщение с форматированием:
void std_printf(const char* fmt, ...);


// Структура для представления файла:
typedef struct stdFile stdFile;

// Открыть файл:
stdFile* std_fopen(const char* path, const char* mode);

// Закрыть файл:
void std_fclose(stdFile* file);

// Запись форматированная:
int std_fprintf(stdFile* file, const char* fmt, ...);

// Чтение форматированное:
int std_fscanf(stdFile* file, const char* fmt, ...);

// Прочитать блок:
size_t std_fread(void* ptr, size_t size, size_t count, stdFile* file);

// Записать блок:
size_t std_fwrite(const void* ptr, size_t size, size_t count, stdFile* file);

// Прочитать символ:
int std_fgetc(stdFile* file);

// Записать символ:
int std_fputc(int c, stdFile* file);

// Прочитать строку:
char* std_fgets(char* str, int num, stdFile* file);

// Записать строку:
int std_fputs(const char* str, stdFile* file);

// Сдвинуть указатель:
int std_fseek(stdFile* file, long offset, int origin);

// Узнать позицию указателя:
long std_ftell(stdFile* file);

// Перемотать к началу:
void std_rewind(stdFile* file);

// Удалить файл:
int std_remove(const char* filename);

// Переименовать файл:
int std_rename(const char* old_name, const char* new_name);

// Проверить конец файла:
int std_feof(stdFile* file);

// Проверить ошибку чтения:
int std_ferror(stdFile* file);

// Очистить ошибку чтения:
void std_clearerr(stdFile* file);

// Сбросить из буфера в файл (синхронизация):
int std_fflush(stdFile* file);
