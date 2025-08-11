//
// files.c - Исходник, реализовывающий базовые функции работы с файлами.
//


// Подключаем:
#include <core/include.h>
#include "files.h"


// Загрузить файл целиком в строку (выделяет память, нужно будет освободить):
char* fs_load_file(const char* filepath, const char* mode) {
    stdFile* f = std_fopen(filepath, mode);
    if (!f) return NULL;

    // Переместить курсор в конец, чтобы узнать размер:
    std_fseek(f, 0, SEEK_END);
    long filesize = std_ftell(f);
    std_rewind(f);

    if (filesize < 0) {
        std_fclose(f);
        return NULL;
    }

    // Выделяем память (+1 для нулевого терминатора):
    char* buffer = (char*)std_malloc(filesize + 1);
    if (!buffer) {
        std_fclose(f);
        return NULL;
    }

    size_t read_size = std_fread(buffer, 1, filesize, f);
    std_fclose(f);

    if (read_size != (size_t)filesize) {
        std_free(buffer);
        return NULL;
    }

    buffer[filesize] = '\0';  // Нуль-терминатор для удобства.

    return buffer; // Используйте std_free() для освобождения памяти.
}


// Сохранить строку/данные в файл:
int fs_save_file(const char* filepath, const char* data, const char* mode) {
    stdFile* f = std_fopen(filepath, mode);
    if (!f) return false;

    size_t len = strlen(data);
    size_t written = std_fwrite(data, 1, len, f);

    std_fflush(f);
    std_fclose(f);

    return written == len;
}
