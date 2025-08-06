/*
//
// debug.h - Заголовочный файл для отладки и логирования программы.
//

#pragma once


// Флаг о логировании программы:
extern bool DebugLog_enabled;

// Флаг о сохранении логов в файл:
extern bool DebugLog_save_in_file;

// Путь до директории в которой надо сохранять логи:
extern char DebugLog_path_to_save[1024];


// Инициализировать логирование (включив на винде поддержку ANSI-последовательность):
void DebugLog_init();

// Очень примитивное логирование сообщения:
void DebugLog_simple(char* message);

// Логирование сообщения:
void DebugLog_log(char* message, ...);

// Логирование предупреждения:
void DebugLog_warn(char* message, ...);

// Логирование ошибки:
void DebugLog_err(char* message, ...);

// Логирование фатальной ошибки:
void DebugLog_fatal(char* message, ...);
*/