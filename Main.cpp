#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define ENGINE_WINDOW_WIDTH 1920
#define ENGINE_WINDOW_HEIGHT 1080

//vert shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//frag shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{
    //initialize glfw and give it window hints
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat verticies[] =
    {
        -0.5, -0.5 * float(sqrt(3)) / 3, 0.0f,
        0.5, -0.5 * float(sqrt(3)) / 3, 0.0f,
        0.0, 0.5 * float(sqrt(3)) * 2 / 3, 0.0f
    };

    //create window and check to make sure that it worked
    GLFWwindow* window = glfwCreateWindow(ENGINE_WINDOW_WIDTH, ENGINE_WINDOW_HEIGHT, "LambdaEngine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "GLFW failed to work\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    //load opengl
    gladLoadGL();

    glViewport(0, 0, ENGINE_WINDOW_WIDTH, ENGINE_WINDOW_HEIGHT);

    //create and compile vert and frag shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //create shader program
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    //delete shaders (not needed anymore)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    //create vertex array and vertex buffer
    GLuint VAO, VBO;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //set background color
    glClearColor(0.7f, 0.13f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    //main loop
    while (!glfwWindowShouldClose(window))
    {
        //clear screen
        glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //tell opengl which shader program to use
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    //test
    std::cout << "hello world\n";
    
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}