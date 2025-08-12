//
// main.c - Основной файл программы для ПК.
//


// Подключаем:
#include <core/include.h>
#include "editor/editor.h"
#include "game/game.h"
#include "tests/tests.h"


// Точка входа в программу:
int main(int argc, char *argv[]) {
    int result = 0;

    #ifdef EDITOR_MODE
        result = editor_init(argc, argv);
    #elif GAME_MODE
        result = game_init(argc, argv);
    #elif TESTS_MODE
        result = tests_init(argc, argv);
    #else
        #error "BUILD MODE IS NOT SUPPORTED."
    #endif

    return result;
}
