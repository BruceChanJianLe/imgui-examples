#pragma once
// Imgui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
// glfw3
#include <GLFW/glfw3.h>
// STL
#include <iostream>

namespace gui_util
{
  class ImguiHandler
  {
  public:
    ImguiHandler(GLFWwindow* window, const char* glsl_version);
    virtual ~ImguiHandler();

        /**
     * \brief initialize gui, call before using
     */
    void Init();

    /**
     * \brief Must be called before Update()
     */
    void NewFrame();

    /**
     * \brief Implement your own update loop
     * \attention must be called in a loop
     */
    virtual void Update();

    /**
     * \brief Render your gui, must be called after Update()
     */
    void Render();

    /**
     * \brief Render your gui, must be called after Update()
     */
    bool GuiOk() const { return init_gui_ && !glfwWindowShouldClose(window_); }

  private:
    /**
     * \brief This will be automatically called in destructor
     */
    void Shutdown();

    bool init_gui_;
    bool show_another_window_;
    ImVec4 clear_color_;
    ImGuiIO io_;

    const char* glsl_version_;
    GLFWwindow* window_;

  private:
    ;
  };
} // gui_util
