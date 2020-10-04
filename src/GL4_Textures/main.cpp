#include <iostream>
#include <glad/glad.h>
#include <stb_image.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include "../include/Shader.h"
#include "../include/Texture.h"
#include "../include/Mesh.h"
#include "../include/Model.h"

GLFWwindow* window;
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 1024;

static const GLfloat sizeVertex = 0.75f;

static const std::vector<Vertex> vertices =
{
    {   glm::vec3(0.5f , 0.5f, 0.5f),
    	glm::vec3(0.0f, 0.0f, 0.0f),
    	glm::vec2(1.0f, 0.0f)
    },
    {   glm::vec3(-0.5f , 0.5f, 0.5f),
    	glm::vec3(0.0f, 0.0f, 0.0f),
    	glm::vec2(0.0f, 0.0f)
    },
    {   glm::vec3(-0.5f , -0.5f, 0.5f),
    	glm::vec3(0.0f, 0.0f, 0.0f),
    	glm::vec2(0.0f, 1.0f)
    },
    {   glm::vec3(0.5f , 0.5f, 0.5f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f)
    },
    {   glm::vec3(-0.5f , -0.5f, 0.5f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec2(0.0f, 1.0f)
    },
    {   glm::vec3(0.5f , -0.5f, 0.5f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec2(1.0f, 1.0f)
    }
};
static const std::vector<unsigned int> indices = {0, 1, 2, 3, 4, 5};

static const glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
static const glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
static const glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);

GLuint rendering_program;
GLuint VAO;
GLuint VBO;

Shader* shader      = nullptr;
Texture* texture    = nullptr;
Model* mesh          = nullptr;

glm::mat4 projMatrix = glm::perspectiveFov(glm::radians(60.0f), float(WINDOW_WIDTH), float(WINDOW_HEIGHT), 0.1f, 10.0f);;


void window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    projMatrix = glm::perspectiveFov(glm::radians(60.0f), float(width), float(height), 0.1f, 10.0f);

    if (shader != nullptr)
    {
        shader->setUniformMatrix4fv("projMatrix", projMatrix);
    }
}

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

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Add some Textures !", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, window_size_callback);

    /* Initialize glad */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /* Set the viewport */
    glClearColor(0.6784f, 0.8f, 1.0f, 1.0f);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glEnable(GL_DEPTH_TEST);

    return true;
}


int initDatas()
{

    mesh = new Model("GL4_Textures/res/cube.obj");

	texture = new Texture();
    texture->load("GL4_Textures/res/wall.jpg");
    texture->bind();
	
    shader = new Shader(
        "GL4_Textures/shaders/vertexShader.vert",
        "GL4_Textures/shaders/fragmentShader.frag");

    shader->apply();

    return true;
}

int deleteDatas()
{
    delete shader;

    return true;
}

void render(float deltaTime)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glm::mat4 mvMatrix = glm::mat4(1.0f);
    mvMatrix *= glm::translate(
        glm::mat4(1.0f),
        zAxis * -4.0f);
	
    mvMatrix *= glm::rotate(
        glm::mat4(1.0f),
        (float)deltaTime * glm::radians(90.0f),
        xAxis + yAxis * deltaTime);
	
    shader->setUniformMatrix4fv("mvMatrix", mvMatrix);
    shader->setUniformMatrix4fv("projMatrix", projMatrix);

    shader->apply();
    texture->bind();
    mesh->Draw();
}

void update()
{
    float startTime = static_cast<float>(glfwGetTime());
    float newTime = 0.0f;
    float deltaTime = 0.0f;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Update game time value */
        newTime = static_cast<float>(glfwGetTime());
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