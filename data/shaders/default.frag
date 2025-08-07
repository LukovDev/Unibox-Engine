//
// default.frag - Шейдер фрагмента по умолчанию.
//

#version 330 core

// Координаты текстуры и выходной цвет:
in vec2 v_texcoord;
out vec4 FragColor;

// Основная функция:
void main() {
    FragColor = vec4(1, 0, 1, 1);
}
