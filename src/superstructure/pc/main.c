//
// main.c - Основной файл программы для ПК.
//


// Подключаем:
#include <core/include.h>
#include "engine/engine.h"
#include "editor/editor.h"


// Точка входа в программу:
int main(int argc, char *argv[]) {
    int result = 0;

    #ifdef EDITOR_MODE
        result = editor_init(argc, argv);
    #elif ENGINE_MODE
        result = engine_init(argc, argv);
    #else
        #error "BUILD MODE IS NOT SUPPORTED."
    #endif

    return result;
}
