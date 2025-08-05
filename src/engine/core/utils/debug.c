//
// debug.c - Создаёт код для отладки и логирования программы.
//


// Подключаем:
#include <time.h>
#include <stdio.h>
#include <core/include.h>
#include "printcolors.h"
#include "debug.h"

#ifdef _WIN32
    #include <windows.h>
#endif


// Переменные:

// Флаг о логировании программы:
bool DebugLog_enabled = true;

// Флаг о сохранении логов в файл:
bool DebugLog_save_in_file = false;

// Путь до директории в которой надо сохранять логи:
char DebugLog_path_to_save[1024] = "data/logs/";


// Получить текущее время в формате "HH:MM:SS":
static char* DebugTime_stamp() {
    static char buffer[9];  // HH:MM:SS\0.
    time_t now = time(NULL);
    struct tm tm_info;
    #if defined(_WIN32)
        localtime_s(&tm_info, &now);
    #else
        localtime_r(&now, &tm_info);
    #endif
    strftime(buffer, sizeof(buffer), "%H:%M:%S", &tm_info);
    return buffer;
}


// Получить текущую дату в формате "DD.MM.YY":
static char* DebugTime_date() {
    static char buffer[9];  // DD.MM.YY\0.
    time_t now = time(NULL);
    struct tm tm_info;
    #if defined(_WIN32)
        localtime_s(&tm_info, &now);
    #else
        localtime_r(&now, &tm_info);
    #endif
    strftime(buffer, sizeof(buffer), "%d.%m.%y", &tm_info);
    return buffer;
}


// Сохранить вывод сообщения:
static void DebugLog_save_log(char* path, char* message) {
    if (!DebugLog_save_in_file || !path || !message) return;

    const char* date = DebugTime_date();
    if (!date) return;

    // Размер: path + '/' + '[' + date + ']' + ".log" + '\0':
    size_t len = strlen(path) + 1 + 1 + strlen(date) + 1 + 4 + 1;
    char* fullpath = platform_malloc(len);
    if (!fullpath) return;

    // Формируем путь к файлу:
    snprintf(fullpath, len, "%s/[%s].log", path, date);

    // Открываем файл в режиме дозаписи:
    FILE* file = fopen(fullpath, "a");
    if (!file) {
        platform_free(fullpath);
        return;
    }

    fprintf(file, "%s\n", message);

    fclose(file);
    platform_free(fullpath);
}


// Логирование:
static void _DebugLog(char* level, char* level_color, char* color, char* message, va_list args) {
    if (!DebugLog_enabled) return;

    char* timestamp = DebugTime_stamp();

    // Форматируем сообщение в буфер
    int len = vsnprintf(NULL, 0, message, args);
    if (len <= 0) return;

    char* msg = platform_malloc(len + 1);
    if (!msg) return;

    vsnprintf(msg, len + 1, message, args);

    // Печать с цветами:
    platform_printf(
        "%s[%s%s%s] [%s%s%s]: %s%s%s\n",
        PCLR_FG_WHITE, PCLR_FG_BRIGHT_YELLOW, timestamp, PCLR_FG_WHITE,
        level_color, level, PCLR_FG_WHITE, color, msg, PCLR_RESET
    );

    // Сохраняем лог без цветов:
    int full_len = len + 64;
    char* line = platform_malloc(full_len);
    if (line) {
        snprintf(line, full_len, "[%s] [%s]: %s", timestamp, level, msg);
        DebugLog_save_log(DebugLog_path_to_save, line);
        platform_free(line);
    }

    platform_free(msg);
}


// Инициализировать логирование (включив на винде поддержку ANSI-последовательность):
void DebugLog_init() {
    if (!DebugLog_enabled) return;
    #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE) return;

        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode)) return;

        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, dwMode);
    #endif
}


// Очень примитивное логирование сообщения:
void DebugLog_simple(char* message) {
    if (!DebugLog_enabled) return;
    platform_printf("[%s] [%s]: %s\n", DebugTime_stamp(), "SIMPLE LOG", message);
    DebugLog_save_log(DebugLog_path_to_save, message);
}


// Логирование сообщения:
void DebugLog_log(char* message, ...) {
    if (!DebugLog_enabled) return;
    va_list args;
    va_start(args, message);
    _DebugLog("LOG", PCLR_FG_GREEN, PCLR_FG_WHITE, message, args);
    va_end(args);
}


// Логирование предупреждения:
void DebugLog_warn(char* message, ...) {
    if (!DebugLog_enabled) return;
    va_list args;
    va_start(args, message);
    _DebugLog("WARN", PCLR_FG_YELLOW, PCLR_FG_WHITE, message, args);
    va_end(args);
}


// Логирование ошибки:
void DebugLog_err(char* message, ...) {
    if (!DebugLog_enabled) return;
    va_list args;
    va_start(args, message);
    _DebugLog("ERROR", PCLR_FG_RED, PCLR_FG_WHITE, message, args);
    va_end(args);
}


// Логирование фатальной ошибки:
void DebugLog_fatal(char* message, ...) {
    if (!DebugLog_enabled) return;
    va_list args;
    va_start(args, message);
    _DebugLog("FATAL", PCLR_FG_BRIGHT_RED, PCLR_FG_BRIGHT_RED, message, args);
    va_end(args);
}
