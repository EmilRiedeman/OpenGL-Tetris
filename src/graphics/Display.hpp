#pragma once

#include "GL/glew.h"
#include <GLFW/glfw3.h>

namespace graphics {

class Display {
public:
    Display(int width, int height, const char *name, GLFWmonitor *monitor=nullptr);
    ~Display();

    void bind() const;
    [[nodiscard]] bool is_valid() const;
    [[nodiscard]] bool should_close() const;
    void swap_buffers();
    static void enable_vertical_sync(bool v);
    static void clear(int mask=GL_COLOR_BUFFER_BIT);

private:
    GLFWwindow *const mWindow;
};

}
