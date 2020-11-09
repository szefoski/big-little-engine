// clang-format off
#include <glad/gl.h>
#include <GLFW/glfw3.h>
// clang-format on
#include <array>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>
#include <lbe/ogl_object_3d.h>
#include <lbe/ogl_shape.h>
#include <lbe/ogl_texture.h>
#include <lbe/ogl_texture_mvp.h>
#include <lbe/ogl_textures_bank.h>
#include <spdlog/spdlog.h>
#include <filesystem>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

int init(GLFWwindow*& window) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
  if (window == NULL) {
    spdlog::critical("Failed to create GLFW window!");
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);  // vsync

  int version = gladLoadGL(glfwGetProcAddress);
  if (version == 0) {
    spdlog::critical("Failed to initialize GLAD!");
    return -1;
  }
  spdlog::info("Loaded OpenGL {}.{}", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  ImGui::StyleColorsDark();
  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init("#version 130");

  // enable blending
  glEnable(GL_BLEND);  // you enable blending function
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // enable z-buffer
  glEnable(GL_DEPTH_TEST);

  int nr_attributes;
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nr_attributes);
  spdlog::info("Maximum nr of vertex attributes supported: {}", nr_attributes);

  glViewport(0, 0, 800, 600);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  return 0;
}

void render(GLFWwindow* window) {
  glm::vec4 vertices(1.0f, 0.0f, 0.0f, 1.0f);
  glm::mat4 transform_matrix = glm::mat4(1.0f);
  transform_matrix = glm::translate(transform_matrix, glm::vec3(1.0f, 1.0f, 0.0f));
  vertices = transform_matrix * vertices;
  spdlog::info("{}", glm::to_string(transform_matrix)); 

  lbe::OglShape shape;
  shape.Prepare();
  // auto vertexColorUniform = glGetUniformLocation(program, "ourColor");

  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  lbe::OglTextureMVP texture;
  texture.Prepare();

  lbe::OglObject3d object_3d;
  object_3d.Init();

  auto textureShelfId =
      lbe::OglTexturesBank::LoadTexture("res/graphic/container.jpg");
  auto textureDebugImageId =
      lbe::OglTexturesBank::LoadTexture("res/graphic/debug_image.png");

  bool show_demo_window = true;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static float some_value = 0.0f;
    static int button_press_counter = 0;
    ImGui::Begin("Hello, world!");
    ImGui::Text("This is some useful text.");  // Display some text (you can use
                                               // a format strings too)
    ImGui::Checkbox(
        "Demo Window",
        &show_demo_window);  // Edit bools storing our window open/close state
    // ImGui::Checkbox("Another Window", &show_another_window);

    ImGui::SliderFloat("float", &some_value, 0.0f,
                       1.0f);  // Edit 1 float using a slider from 0.0f to 1.0f
    ImGui::ColorEdit3(
        "clear color",
        (float*)&clear_color);  // Edit 3 floats representing a color

    if (ImGui::Button("Button"))  // Buttons return true when clicked (most
                                  // widgets return true when edited/activated)
      button_press_counter++;
    ImGui::SameLine();
    ImGui::Text("counter = %d", button_press_counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();

    ImGui::Render();

    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // texture.Draw();
    // shape.Draw();
    // texture.Draw(textureShelfId);
    object_3d.Draw(textureDebugImageId, 0.0f, 0.0f, -3.0f, -50.0f);
    object_3d.Draw(textureDebugImageId, 3.0f, 0.0f, 0.0f, 0.0f);
    object_3d.Draw(textureDebugImageId, -3.0f, -2.0f, 0.0f, 10.0f);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

int main() {
  spdlog::info("Welcome to spdlog!");
  spdlog::error("Some error message with arg: {}", 1);

  spdlog::warn("Easy padding in numbers like {:08d}", 12);
  spdlog::critical(
      "Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
  spdlog::info("Support for floats {:03.2f}", 1.23456);
  spdlog::info("Positional args are {1} {0}..", "too", "supported");
  spdlog::info("{:>30}", "right aligned");

  GLFWwindow* window;
  init(window);
  render(window);

  glfwTerminate();
  return 0;
}