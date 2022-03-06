add_subdirectory(glfw)
add_subdirectory(glew)

set(LIBS glfw libglew_static PARENT_SCOPE)