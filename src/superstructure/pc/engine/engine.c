//
// engine.c - Исходный файл надстройки движка.
//


// Подключаем:
#include <core/include.h>
#include <core/utils/debug.h>
#include "engine.h"


// Инициализация надстройки движка:
int engine_init(int argc, char *argv[]) {
    DebugLog_init();
    DebugLog_log("Hello world from %s\n", "Engine!");
    return 0;
}
