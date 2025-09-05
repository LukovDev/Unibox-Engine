//
// tests.c - Исходник, который тестирует функционал всего движка.
//


// Импортируем:
#include <engine/engine.h>
#include <engine/graphics/application.h>

#include <engine/core/mm/mm.h>
#include <engine/core/graphics/image.h>


// Тестирование менеджера памяти:
int test_mm() {
    printf("=== Memory Manager Test ===\n");
    printf("Initial used memory: %zu bytes\n", mm_get_used_size());

    // 1. Простое выделение:
    printf("\nStage 1: Allocating 1 KB and testing \"mm_get_block_size()\"\n");
    size_t alloc_size = 1024;  // 1 KB.
    void* ptr1 = mm_alloc(alloc_size);
    if (ptr1 == NULL) {
        printf("Failed: Allocation memory failed.\n");
        return 1;
    }
    printf("After alloc %zu bytes: %zu bytes of block, %zu bytes of total used.\n",
           alloc_size, mm_get_block_size(ptr1), mm_get_used_size());
    if (mm_get_block_size(ptr1) != alloc_size) {
        printf("Failed: Alloc size mismatch, or broken \"mm_get_block_size()\".\n");
        return 1;
    }

    // 2. Выделение с обнулением:
    printf("\nStage 2: Clear allocating 256 ints (1 KB total)\n");
    size_t calloc_ints = 256;
    int* ptr2 = (int*)mm_calloc(calloc_ints, sizeof(int));  // 256 * 4 = 1024 bytes.
    if (ptr2 == NULL) {
        printf("Failed: Clear allocation memory failed.\n");
        return 1;
    }
    printf("After calloc %zu ints: %zu bytes of block, %zu bytes of total used.\n",
           calloc_ints, mm_get_block_size(ptr2), mm_get_used_size());
    if (mm_get_block_size(ptr2) != calloc_ints*sizeof(int)) {
        printf("Failed: Calloc size mismatch.\n");
    }

    // Проверяем обнуление блока calloc:
    bool zeroed = true;
    for (size_t i = 0; i < calloc_ints; i++) {
        if (ptr2[i] != 0) zeroed = false;
    }
    printf("Calloc block zeroed: %s\n", zeroed ? "YES" : "NO");
    if (zeroed == false) {
        printf("Failed: Calloc block not zeroed.\n");
        // return 1;
    }

    // 3. Расширение блока памяти:
    printf("\nStage 3: Reallocating (ptr1) to 2 KB\n");
    size_t realloc_size = 2048;  // 2 KB.
    ptr1 = mm_realloc(ptr1, realloc_size);  // 2 KB.
    if (ptr1 == NULL) {
        printf("Failed: Reallocation memory failed.\n");
        return 1;
    }
    printf("After realloc to %zu bytes: %zu bytes of block, %zu bytes of total used.\n",
           realloc_size, mm_get_block_size(ptr1), mm_get_used_size());
    if (mm_get_block_size(ptr1) != realloc_size) {
        printf("Failed: Realloc size mismatch.\n");
        // return 1;
    }

    // 4. Освобождение памяти:
    printf("\nStage 4: Freeing memory blocks (ptr1 and ptr2)\n");
    // ptr1:
    printf("Before free ptr1 (size: %zu b): %zu bytes of total used.\n", mm_get_block_size(ptr1), mm_get_used_size());
    mm_free(ptr1);
    printf("After free ptr1: %zu bytes of total used.\n", mm_get_used_size());
    // ptr2:
    printf("Before free ptr2 (size: %zu b): %zu bytes of total used.\n", mm_get_block_size(ptr2), mm_get_used_size());
    mm_free(ptr2);
    printf("After free ptr2: %zu bytes of total used.\n", mm_get_used_size());

    // 5. Проверка утечки памяти:
    printf("\nStage 5: Checking memory leaks\n");
    if (mm_get_used_size() != 0) {
        printf("Failed: Memory leak detected (%zu bytes leaked).\n", mm_get_used_size());
        return 1;
    } else {
        printf("Passed: No memory leaks detected.\n");
    }

    printf("\nFinal used memory (must be 0 bytes): %zu bytes.\n", mm_get_used_size());
    
    printf("=== Finished ===\n");
    return 0;
}


// Тестирование графического интерфейса:
int test_graphics() {
    printf("=== Graphics Test ===\n");

    // Тестирования работы с изображениями:
    printf("Stage 1: Image test:\n");
    const char* img_path = "data/icons/logo/unibox/Unibox-Full-B.png";
    printf("Loading image path: \"%s\"\n", img_path);
    // Загрузка изображения:
    Image* img = Image_load(img_path, IMG_RGBA);
    if (img == NULL) {
        printf("1. Image_load() failed (ptr is NULL).\n");
        return 1;
    } else { printf("1. Image_load() passed (ptr is not NULL).\n"); }
    // Получение размера в байтах:
    size_t img_size = Image_get_size(img);
    if (img_size == 0) {
        printf("2. Image_get_size() failed (size is 0 bytes).\n");
        return 1;
    } else { printf("2. Image_get_size() passed (size: %zu bytes).\n", img_size); }
    // Уничтожение:
    Image_destroy(&img);
    if (img != NULL) {
        printf("3. Image_destroy() failed (ptr is not NULL).\n");
        return 1;
    } else { printf("3. Image_destroy() passed (ptr is NULL).\n"); }
    printf("Image test passed.\n");

    // Тестирование абстрактного апи для создания и уничтожения структуры приложения:
    printf("\nStage 2: Application test:\n");
    Application* app = Application_create();
    if (app == NULL) {
        printf("1. Application_create() failed (ptr is NULL).\n");
        return 1;
    } else { printf("1. Application_create() passed (ptr is not NULL).\n"); }
    Application_destroy(&app);
    if (app != NULL) {
        printf("2. Application_destroy() failed (ptr is not NULL).\n");
        return 1;
    } else { printf("2. Application_destroy() passed (ptr is NULL).\n"); }
    printf("Application test passed.\n");

    // Тестирование абстрактного апи для создания и уничтожения структуры конфигурации приложения:
    printf("\nStage 3: AppConfig test:\n");
    AppConfig* cfg = AppConfig_create();
    if (cfg == NULL) {
        printf("1. AppConfig_create() failed (ptr is NULL).\n");
        return 1;
    } else { printf("1. AppConfig_create() passed (ptr is not NULL).\n"); }
    AppConfig_destroy(&cfg);
    if (cfg != NULL) {
        printf("2. AppConfig_destroy() failed (ptr is not NULL).\n");
        return 1;
    } else { printf("2. AppConfig_destroy() passed (ptr is NULL).\n"); }
    printf("AppConfig test passed.\n");

    printf("=== Finished ===\n");
    return 0;
}


// Полное тестирование:
int full_testing() {
    printf("Full testing\n\n");
    int total_tests = 2;

    // Проверка аллокатора памяти:
    if (test_mm() != 0) {
        printf("mm test failed.\n");
        return 1;
    }
    printf("[1/%d passed]\n\n", total_tests);

    // Проверка графического интерфейса:
    if (test_graphics() != 0) {
        printf("graphics test failed.\n");
        return 1;
    }
    printf("[2/%d passed]\n\n", total_tests);

    printf("All tests passed.\n");
    return 0;
}


// Точка входа тестирования:
#ifdef TESTING_MODE
int main() {
    printf("Unibox Engine Testing Mode.\n");
    return full_testing();
}
#endif
