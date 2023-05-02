#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#if defined(DEBUG_OPENGL_TEST)

std::vector<float> vertices = {
    -0.5, -0.5,
     0.5, -0.5,
     0.0,  0.5
};

typedef struct renderbuf {
    uint32_t vertexArrayObject;
    uint32_t vertexBufferObject;
} renderbuf;

typedef struct Shader {
    uint32_t id;
} Shader;

std::string LoadFile(std::string path) {

    std::ifstream shaderFile;
    shaderFile.open(path);
    std::stringstream stream;
    stream << shaderFile.rdbuf();
    shaderFile.close();
    std::string str = stream.str();
    return str;
}

Shader LoadShader(std::string shaderPath) {
    Shader shader{};
    shader.id = glCreateProgram();

    std::string vertexShaderPath = shaderPath+"/vMain.glsl",
                fragmentShaderPath = shaderPath+"/fMain.glsl";
    
    const char* vSource = LoadFile(vertexShaderPath).c_str();
    const char* fSource = LoadFile(fragmentShaderPath).c_str();

    uint32_t vertex = glCreateShader(GL_VERTEX_SHADER),
             fragment = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertex, 1, &vSource, NULL);
    glShaderSource(fragment, 1, &fSource, NULL);
    glCompileShader(vertex);
    glCompileShader(fragment);

    glAttachShader(shader.id, vertex);
    glAttachShader(shader.id, fragment);
    glLinkProgram(shader.id);
    return shader;
};

renderbuf CreateRenderBuffer() {

    renderbuf buf = renderbuf();
    glGenVertexArrays(1, &buf.vertexArrayObject);
    glGenBuffers(1, &buf.vertexBufferObject);

    return buf;
}
GLFWwindow* window;

void Initialize() {

    if (!glfwInit()) glfwTerminate();

#if defined(__APPLE__)
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    window = glfwCreateWindow(1300, 900, "OpenGL API", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (!glewInit()) std::cout << "Hello2\n";
    
    renderbuf buf = CreateRenderBuffer();
    Shader shader = LoadShader("shaders/gl");

    glBindVertexArray(buf.vertexArrayObject);

    glBindBuffer(GL_VERTEX_ARRAY, buf.vertexBufferObject);
    glBufferData(GL_VERTEX_ARRAY, sizeof(vertices) * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
    glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0, 0.0, 0.0, 1.0);

        glBindVertexArray(buf.vertexArrayObject);
        glUseProgram(shader.id);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

#endif