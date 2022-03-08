#include "Display.hpp"

using graphics::Display;

Display::Display(int width, int height, const char *name, GLFWmonitor *monitor):
        mWindow(glfwCreateWindow(width, height, name, monitor, graphics::gFirstWindow)) {
    if (!is_valid()) return;
    glfwMakeContextCurrent(mWindow);
    if (!graphics::gFirstWindow) {
        graphics::gFirstWindow = mWindow;
        glewInit();
    }
}

Display::~Display() {
    glfwDestroyWindow(mWindow);
}

bool graphics::Display::is_valid() const {
    return mWindow;
}

bool graphics::Display::should_close() const {
    return glfwWindowShouldClose(mWindow);
}

void graphics::Display::swap_buffers() {
    glfwSwapBuffers(mWindow);
}
