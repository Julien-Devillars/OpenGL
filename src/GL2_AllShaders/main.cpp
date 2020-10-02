#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define  GLM_FORCE_RADIANS

#include <glm/glm.hpp>

#include "../include/Shader.h"

GLFWwindow* window;
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 1024;



GLuint rendering_program;
GLuint vertex_array_object;

Shader* shader = nullptr;


int initWindow()
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Draw a Tesselate triangle !", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

	
    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Initialize glad */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
	
    /* Set the viewport */
    //glClearColor(0.6784f, 0.8f, 1.0f, 1.0f);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glPointSize(5.0);
	
    glEnable(GL_DEPTH_TEST);

    glPatchParameteri(GL_PATCH_VERTICES, 3); // Set the number of tesselation vertices patches to the value
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	
    return true;
}


int initDatas()
{
    shader = new Shader(
        "GL2_AllShaders/shaders/vertexShader.vert",
        "GL2_AllShaders/shaders/fragmentShader.frag",
        "GL2_AllShaders/shaders/geometryShader.geom",
        "GL2_AllShaders/shaders/tesselationControlShader.tcs",
        "GL2_AllShaders/shaders/tesselationEvaluationShader.tes");
	
    shader->apply();

    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);
	
    return true;
}

int deleteDatas()
{
    delete shader;
	
    return true;
}

void render(float time)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
    shader->apply();
	
    glDrawArrays(GL_PATCHES, 0, 3); // Draw patchs
}

void update()
{
    float startTime = static_cast<float>(glfwGetTime());
    float newTime  = 0.0f;
    float deltaTime = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Update game time value */
        newTime  = static_cast<float>(glfwGetTime());
        deltaTime = newTime - startTime;

        /* Render here */
        render(deltaTime);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

int main(void)
{
    if (!initWindow())
        return -1;

    if (!initDatas())
        return -1;
	
    update();

	glfwTerminate();
	
    if (!deleteDatas())
        return -1;
	
    return 0;
}