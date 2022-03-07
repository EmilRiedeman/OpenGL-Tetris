#pragma once

#include "GL/glew.h"
#include <GLFW/glfw3.h>

namespace graphics {

class Display {
public:
    Display(int width, int height, const char *name, GLFWmonitor *monitor=nullptr);
    ~Display();

    [[nodiscard]] bool is_valid() const;
    [[nodiscard]] bool should_close() const;
    void swap_buffers();

private:
    GLFWwindow *const mWindow;
};

static GLFWwindow *gFirstWindow = nullptr;

}
