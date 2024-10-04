#ifndef PURPLX
#define PURPLX

#include <stdio.h>
#include "glad/glad.h"
#include "glfw3.h"
#include <stdlib.h>
#include <string.h>

typedef __uint8_t P8Int;
typedef unsigned int PIndex;
typedef int PInt;
typedef float PFloat;
typedef unsigned int PUint;

typedef enum{
    STATIC,
    RIGID,
} PType;

typedef struct{
    PInt x;
    PInt y;
} PVector2i;

typedef struct{
    PFloat *positions;
    PIndex *indices;
    PUint vao;
    PUint buffer;
    PUint ibo;
    size_t position_length;
    size_t index_length;
} Mesh;

typedef struct{
    void (*update_func)(void);
    void (*ready_func)(void);
    void (*input_func)(GLFWwindow* window, int key, int scancode, int action, int mods);
    Mesh *meshes;
    PInt mesh_count;

} Purplx;

#include "Mesh.h"

Purplx *CreatePurplx();
PUint CreateShader(const char *vertex_shader, const char *fragment_shader);
P8Int Run(Purplx *purplx);

#endif /* PURPLX */