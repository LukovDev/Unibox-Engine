//
// editor.c - Исходный файл редактора движка.
//


// Подключаем:
#include <core/include.h>
#include <core/utils/debug.h>
#include "editor.h"


// Инициализация редактора движка:
int editor_init(int argc, char *argv[]) {
    DebugLog_init();
    DebugLog_log("Hello world from %s\n", "Editor!");
    return 0;
}
