//
// tests.c - Исходник, реализовывающий тесты движка.
//


// Подключаем:
#include <core/include.h>
#include <python311/Python.h>
#include "tests.h"


// Проверка теста:
void check_test(char* name, int result) {
    if (result == 0) {
        std_printf("[OK] %s\n", name);
    } else {
        std_printf("[FAIL] %s\n", name);
    }
}


// Тест работы питона:
int test_python() {
    int result = 0;
    Py_Initialize();
    PyRun_SimpleString("print('Hello from Python!')");
    Py_Finalize();
    check_test("test_python()", result);
    return result;
}


// Инициализация теста:
int tests_init(int argc, char *argv[]) {
    int result = 0;
    result = test_python();

    if (result != 0) {
        std_printf("Tests failed!\n");
    } else {
        std_printf("Tests passed!\n");
    }
    return result;
}
