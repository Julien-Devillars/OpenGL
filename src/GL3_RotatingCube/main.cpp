#include <iostream>
#include <glad/glad.h>-sizeCube
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include "../include/Shader.h"


GLFWwindow* window;
const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 1024;

static const GLfloat sizeCube = 0.20f;

static const GLfloat vertex_positions[] = {
    -sizeCube,-sizeCube,-sizeCube, // triangle 1 : begin
    -sizeCube,-sizeCube, sizeCube,
    -sizeCube, sizeCube, sizeCube, // triangle 1 : end
	
    sizeCube, sizeCube,-sizeCube, // triangle 2 : begin
    -sizeCube,-sizeCube,-sizeCube,
    -sizeCube, sizeCube,-sizeCube, // triangle 2 : end
	
    sizeCube,-sizeCube, sizeCube,
    -sizeCube,-sizeCube,-sizeCube,
    sizeCube,-sizeCube,-sizeCube,
	
    sizeCube, sizeCube,-sizeCube,
    sizeCube,-sizeCube,-sizeCube,
    -sizeCube,-sizeCube,-sizeCube,
	
    -sizeCube,-sizeCube,-sizeCube,
    -sizeCube, sizeCube, sizeCube,
    -sizeCube, sizeCube,-sizeCube,
	
    sizeCube,-sizeCube, sizeCube,
    -sizeCube,-sizeCube, sizeCube,
    -sizeCube,-sizeCube,-sizeCube,
	
    -sizeCube, sizeCube, sizeCube,
    -sizeCube,-sizeCube, sizeCube,
    sizeCube,-sizeCube, sizeCube,
	
    sizeCube, sizeCube, sizeCube,
    sizeCube,-sizeCube,-sizeCube,
    sizeCube, sizeCube,-sizeCube,
	
    sizeCube,-sizeCube,-sizeCube,
    sizeCube, sizeCube, sizeCube,
    sizeCube,-sizeCube, sizeCube,
	
    sizeCube, sizeCube, sizeCube,
    sizeCube, sizeCube,-sizeCube,
    -sizeCube, sizeCube,-sizeCube,
	
    sizeCube, sizeCube, sizeCube,
    -sizeCube, sizeCube,-sizeCube,
    -sizeCube, sizeCube, sizeCube,
	
    sizeCube, sizeCube, sizeCube,
    -sizeCube, sizeCube, sizeCube,
    sizeCube,-sizeCube, sizeCube
};

static const glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
static const glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
static const glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);

GLuint rendering_program;
GLuint VAO;
GLuint VBO;

Shader* shader = nullptr;

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

    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Draw a Rotating Cube !", nullptr, nullptr);

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

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 
        sizeof(vertex_positions), 
        vertex_positions, 
        GL_STATIC_DRAW);
	
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    shader = new Shader(
        "GL3_RotatingCube/shaders/vertexShader.vert",
        "GL3_RotatingCube/shaders/fragmentShader.frag");

    shader->apply();
    //shader->setUniformMatrix4fv("projMatrix", projMatrix);
	
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

	//static const GLfloat backgroundColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    //glClearBufferfv(GL_COLOR, 0, backgroundColor);
    //static const GLfloat one = 1.0f;
    //glClearBufferfv(GL_DEPTH, 0, &one);
	
    shader->apply();
    shader->setUniformMatrix4fv("projMatrix", projMatrix);

    const int maxN = 10;
    int N = std::min(maxN, static_cast<int>(deltaTime));

	for(int i = 0 ; i < N; ++i)
	{
        glm::mat4 mvMatrix = glm::mat4(1.0f);
        mvMatrix *= glm::translate(
            glm::mat4(1.0f),
            zAxis * -4.0f);
		
        mvMatrix *= glm::rotate(
            glm::mat4(1.0f),
            (float)deltaTime * glm::radians(45.0f),
            zAxis);
        
        mvMatrix *= glm::translate(
            glm::mat4(1.0f),
            xAxis * static_cast<float>(i * sizeCube * 2));
		
		
        shader->setUniform1f("colorValue", static_cast<float>(i * 0.5f));
        shader->setUniformMatrix4fv("mvMatrix", mvMatrix);

        glDrawArrays(GL_TRIANGLES, 0, 36);
	}
    
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