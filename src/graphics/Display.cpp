#include "Display.hpp"

using graphics::Display;

Display::Display(int width, int height, const char *name, GLFWmonitor *monitor):
        mWindow(glfwCreateWindow(width, height, name, monitor, nullptr)) {
    if (!is_valid()) return;
    bind();
    glewInit();
}

Display::~Display() {
    glfwDestroyWindow(mWindow);
}

void Display::bind() const {
    glfwMakeContextCurrent(mWindow);
}

bool Display::is_valid() const {
    return mWindow;
}

bool Display::should_close() const {
    return glfwWindowShouldClose(mWindow);
}

void Display::swap_buffers() {
    glfwSwapBuffers(mWindow);
}

void Display::enable_vertical_sync(bool v) {
    glfwSwapInterval(v);
}

void graphics::Display::clear(int mask) {
    glClear(mask);
}
