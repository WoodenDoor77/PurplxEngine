#include "Purplx.h"

const char* vertex_shader_source = "#version 330 core\n"
                           "layout (location = 0) in vec4 position;\n"
                           "void main() {\n"
                           "gl_Position = position;\n"
                           "}\n";

const char* fragment_shader_source = "#version 330 core\n"
                           "layout (location = 0) out vec4 color;\n"
                           "void main() {\n"
                           "color = vec4(1.0, 0.0, 0.0, 1.0);\n"
                           "}\n";

void error_callback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
}

void window_resized(GLFWwindow *window, int width, int height){
    glViewport(0, 0, width, height);
}

PUint CompileShader(const char *source, PUint type){
    PUint id = glCreateShader(type);
    glShaderSource(id, 1, &source, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char*)malloc(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        
        printf("%s\n", message);

        glDeleteShader(id);

        return 0;
    }

    return id;
}

PUint CreateShader(const char *vertex_shader, const char *fragment_shader){
    PUint program = glCreateProgram();
    PUint vs = CompileShader(vertex_shader, GL_VERTEX_SHADER);
    PUint fs = CompileShader(fragment_shader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

Purplx *CreatePurplx(){
    Purplx *purplx = (Purplx*)malloc(sizeof(Purplx));
    purplx->meshes = (Mesh*)malloc(sizeof(Purplx));
    return purplx;
}

P8Int Run(Purplx *purplx){
    PVector2i window_size = {640, 640};

    glfwSetErrorCallback(error_callback);

    if (!glfwInit()){
        glfwTerminate();
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(window_size.x, window_size.y, "Torgan", NULL, NULL);

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("error: could not load glad");
        glfwTerminate();
        return -1;
    }
    glViewport(0, 0, window_size.x, window_size.y);
    glfwSetFramebufferSizeCallback(window, window_resized);

    glfwSetKeyCallback(window, purplx->input_func);

    PUint shader = CreateShader(vertex_shader_source, fragment_shader_source);
    glUseProgram(shader);

    purplx->ready_func();

    while (!glfwWindowShouldClose(window)){
        purplx->update_func();

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0; i < purplx->mesh_count; i++){
            glBindBuffer(GL_ARRAY_BUFFER, purplx->meshes[i].buffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, purplx->meshes[i].ibo);

            glBindVertexArray(purplx->meshes[i].vao);
            glDrawElements(GL_TRIANGLES, purplx->meshes[i].index_length, GL_UNSIGNED_INT, NULL);
        }

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

