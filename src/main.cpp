#include <iostream>

#include "GL/glew.h"
#include <GLFW/glfw3.h>

#include "graphics/Display.hpp"

static void Run() {
    graphics::Display display(640, 480, "Hello World");
    if (!display.is_valid()) return;
    std::cout << "Using version " << glGetString(GL_VERSION) << '\n';
    graphics::Display::enable_vertical_sync(true);
    while (!display.should_close()) {
        graphics::Display::clear();
        display.swap_buffers();
        glfwPollEvents();
    }
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize glfw\n";
        return -1;
    }
    Run();
    glfwTerminate();
    return 0;
}