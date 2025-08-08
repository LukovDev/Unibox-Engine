//
// editor.c - Исходный файл редактора движка.
//


// Подключаем:
#include <core/include.h>
#include "editor.h"

#include <stdio.h>
#include <math.h>
// #include <stb_image.h>
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <cglm/cglm.h>
#include <core/files.h>


//
SDL_Window* create_window() {
    if (SDL_Init(SDL_INIT_VIDEO) == false) {
        printf("SDL Init Error: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window* window = SDL_CreateWindow("OpenGL Window", 960, 540, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) {
        printf("CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    // Минимальный и максимальный размер
    SDL_SetWindowMinimumSize(window, 100, 200);
    //SDL_SetWindowMaximumSize(window, 960, 540);

    int x, y;
    SDL_GetWindowPosition(window, &x, &y);
    printf("Window position: x = %d, y = %d\n", x, y);

    // int w, h, channels;
    // unsigned char* pixels = stbi_load("data/icons/icon.png", &w, &h, &channels, 4);

    // if (pixels) {
    //     SDL_Surface* icon = SDL_CreateSurfaceFrom(w, h, SDL_PIXELFORMAT_RGBA32, pixels, w*4);

    //     if (icon) {
    //         SDL_SetWindowIcon(window, icon);
    //         SDL_DestroySurface(icon);
    //     }

    //     stbi_image_free(pixels);
    // }

    return window;
}


//
void main_loop(SDL_Window* window, GLuint shader_program, GLuint VAO) {
    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT)
                running = 0;
        }

        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader_program);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);
    }
}


// Инициализация редактора движка:
int editor_init(int argc, char *argv[]) {
    const char* vertex_shader_src = fs_load_file("data/shaders/default.vert", "rb");
    const char* fragment_shader_src = fs_load_file("data/shaders/default.frag", "rb");

    std_printf("vertex_shader_src: %s\n", vertex_shader_src);
    std_printf("fragment_shader_src: %s\n", fragment_shader_src);

    SDL_Window* window = create_window();

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        printf("GL Context Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(0); // включаем VSync

    if (!gladLoadGL()) {
        fprintf(stderr, "gladLoadGL failed\n");
        return 1;
    }

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

    // === Шейдеры ===
    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_shader_src, NULL);
    glCompileShader(vertex);

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_shader_src, NULL);
    glCompileShader(fragment);

    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex);
    glAttachShader(shader_program, fragment);
    glLinkProgram(shader_program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    // === Вершины треугольника ===
    float vertices[] = {
         0.0f,  0.5f, 0.0f,  // верх
        -0.5f, -0.5f, 0.0f,  // левый
         0.5f, -0.5f, 0.0f   // правый
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Настройка VAO/VBO
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // layout(location = 0) → 3 float'а
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Главный цикл
    main_loop(window, shader_program, VAO);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shader_program);

    SDL_GL_DestroyContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
