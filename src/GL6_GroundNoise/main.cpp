#include <iostream>
#include <glad/glad.h>
#include <stb_image.h>
#include <GLFW/glfw3.h>



#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "../include/Shader.h"
#include "../include/Texture.h"
#include "../include/Mesh.h"
#include "../include/Model.h"
#include "Ground.h"

GLFWwindow* window;
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 1024;

static const glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
static const glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
static const glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);

GLuint rendering_program;
GLuint VAO;
GLuint VBO;

Shader* shader      = nullptr;
Texture* texture    = nullptr;
Mesh* mesh          = nullptr;

glm::mat4 projMatrix = glm::perspectiveFov(glm::radians(60.0f), float(WINDOW_WIDTH), float(WINDOW_HEIGHT), 0.1f, 10.0f);;
glm::mat4 scaleMatrix = glm::mat4(1.0f);

bool toShow = false;

void window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    projMatrix = glm::perspectiveFov(glm::radians(60.0f), float(width), float(height), 0.1f, 10.0f);

    if (shader != nullptr)
    {
        shader->setUniformMatrix4fv("projMatrix", projMatrix);
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    float cameraSpeed = 0.5f;
	
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
        projMatrix = glm::translate(projMatrix, xAxis * -cameraSpeed);
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        projMatrix = glm::translate(projMatrix, xAxis * cameraSpeed);
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        projMatrix = glm::translate(projMatrix, zAxis * cameraSpeed);
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        projMatrix = glm::translate(projMatrix, zAxis * -cameraSpeed);
    if (key == GLFW_KEY_PAGE_UP && action == GLFW_PRESS)
        projMatrix = glm::translate(projMatrix, yAxis * cameraSpeed);
    if (key == GLFW_KEY_PAGE_DOWN && action == GLFW_PRESS)
        projMatrix = glm::translate(projMatrix, yAxis * -cameraSpeed);
        
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    // show mouse coordinate on the window
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        std::cout << "isPressed" << std::endl;
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        std::cout << "isReleased" << std::endl;
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

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Creating a ground !", nullptr, nullptr);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

	// Set events
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
	
    /* Initialize glad */
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


	
    /* Set the viewport */
    glClearColor(0.6784f, 0.8f, 1.0f, 1.0f);
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    // Camera
	projMatrix = glm::rotate(projMatrix, glm::radians(180.0f), zAxis);
    projMatrix = glm::translate(projMatrix, 2.0f * yAxis + zAxis * 2.0f);
    projMatrix = glm::rotate(projMatrix, glm::radians(-30.0f), xAxis);

	//projMatrix = glm::rotate(
    //    projMatrix, glm::radians(45.0f), xAxis);

	
    return true;
}

int nbGrid = 10;
float sizeGrid = 0.4f;

int initDatas()
{
    Ground g = Ground(nbGrid, nbGrid, sizeGrid,sizeGrid);
    mesh = g.createMesh();

    texture = new Texture();
    texture->load("datas/ground.jpg");
    texture->bind();
	
    shader = new Shader(
        "GL6_GroundNoise/shaders/vertexShader.vert",
        "GL6_GroundNoise/shaders/fragmentShader.frag");

    shader->apply();

    return true;
}

int deleteDatas()
{
    delete shader;
    delete mesh;
    delete texture;
	
    return true;
}

void render(float deltaTime)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 mvMatrix = glm::mat4(1.0f);
    
    mvMatrix = glm::translate(
        mvMatrix,
        -zAxis * 4.0f 
        + -xAxis * (nbGrid * sizeGrid)/2.0f);
	
    //mvMatrix = glm::rotate(
    //    mvMatrix,
    //    (float)deltaTime * glm::radians(90.0f),
    //    xAxis);
    
    mvMatrix *= scaleMatrix;
    
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