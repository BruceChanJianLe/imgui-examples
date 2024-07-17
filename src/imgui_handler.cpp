#include "imgui_handler.hpp"
#include <GLFW/glfw3.h>

namespace gui_util
{
  ImguiHandler::ImguiHandler(GLFWwindow* window, const char* glsl_version)
  : window_{window}
  , glsl_version_{nullptr}
  , init_gui_{false}
  , show_another_window_{false}
  , clear_color_{0.45f, 0.55f, 0.60f, 1.00f}
  {
    glfwMakeContextCurrent(window_);
    glfwSwapInterval(1); // Enable vsync
  }

  ImguiHandler::~ImguiHandler()
  {
    Shutdown();
  }

  void ImguiHandler::Init()
  {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window_, true);
    ImGui_ImplOpenGL3_Init(glsl_version_);

    io_ = ImGui::GetIO();

    init_gui_ = true;
  }

  void ImguiHandler::NewFrame()
  {
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
    glfwPollEvents();

    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
  }

  void ImguiHandler::Update()
  {
    if (init_gui_)
    {
      static float f = 0.0f;
      static int counter = 0;

      ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

      ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
      ImGui::Checkbox("Another Window", &show_another_window_);

      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
      ImGui::ColorEdit3("clear color", (float*)&clear_color_); // Edit 3 floats representing a color

      if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
      {
        counter++;
      }
      ImGui::SameLine();
      ImGui::Text("counter = %d", counter);

      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io_.Framerate, io_.Framerate);
      ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window_)
    {
      ImGui::Begin("Another Window", &show_another_window_);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
      ImGui::Text("Hello from another window!");
      if (ImGui::Button("Close Me"))
      {
        show_another_window_ = false;
      }
      ImGui::End();
    }
  }

    void ImguiHandler::Render()
    {
      // Rendering
      ImGui::Render();
      glClear(GL_COLOR_BUFFER_BIT);
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      glfwSwapBuffers(window_);
    }

    void ImguiHandler::Shutdown()
    {
      // Cleanup
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();
      ImGui::DestroyContext();

      glfwDestroyWindow(window_);
      glfwTerminate();
    }
} // gui_util
