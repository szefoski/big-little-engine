#include "program_shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include "shape.h"
#include "texture.h"
#include "textureMVP.h"
#include "texturesBank.h"

#include <array>
#include <filesystem>
#include <iostream>
#include <vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

int init(GLFWwindow *&window)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if defined __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //enable blending
    glEnable(GL_BLEND);// you enable blending function
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //enable z-buffer
    glEnable(GL_DEPTH_TEST);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return 0;
}

void render(GLFWwindow* window)
{
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std::cout << glm::to_string(trans) << std::endl;

    lbe::Shape shape;
    shape.Prepare();
    //auto vertexColorUniform = glGetUniformLocation(program, "ourColor");

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    lbe::TextureMVP texture;
    texture.Prepare();
    auto textureShelfId = lbe::texturesBank::LoadTexture("res/container.jpg");
    auto textureDebugImageId = lbe::texturesBank::LoadTexture("res/debug_image.png");

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.4f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //texture.Draw();
        //shape.Draw();
        texture.Draw(textureDebugImageId);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}


int main()
{
    GLFWwindow* window;
    init(window);
    render(window);

    glfwTerminate();
    return 0;
}