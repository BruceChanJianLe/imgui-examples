#include "imgui_handler.hpp"
#include <GLFW/glfw3.h>

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main (int argc, char *argv[])
{
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
    return 1;

  // GL 3.0 + GLSL 130
  const char* glsl_version = "#version 130";
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

  // Create window with graphics context
  GLFWwindow* window = glfwCreateWindow(1280, 720, "Dear ImGui GLFW+OpenGL3 Class example", nullptr, nullptr);
  if (window == nullptr)
    return 1;
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1); // Enable vsync

  gui_util::ImguiHandler handler(window, glsl_version);
  // GUI Loop
  handler.Init();
  while (handler.GuiOk())
  {
    // Start a new frame for gui
    handler.NewFrame();
    // Update gui content
    handler.Update();
    // Render gui
    handler.Render();
  }

  return 0;
}
