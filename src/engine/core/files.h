//
// files.h - Заголовочный файл исходника функций работы с файлами.
//

#pragma once


// Загрузить файл целиком в строку (выделяет память, нужно будет освободить):
char* fs_load_file(const char* filepath, const char* mode);

// Сохранить строку/данные в файл:
int fs_save_file(const char* filepath, const char* data, const char* mode);
