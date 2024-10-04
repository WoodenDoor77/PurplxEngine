#include "Purplx.h"

Mesh *CreateMesh(Purplx *purplx, PFloat *verticies, size_t verticies_length, PIndex *indices, size_t indices_length, PType type){
    GLenum gl_type;

    if (type == STATIC){
        gl_type = GL_STATIC_DRAW;
    }
    else{
        gl_type = GL_DYNAMIC_DRAW;
    }

    int dimensions = 2;
    verticies_length /= sizeof(PFloat);
    indices_length /= sizeof(PIndex);

    Mesh *mesh = (Mesh*)malloc(sizeof(Mesh));

    mesh->position_length = verticies_length / 2;
    mesh->positions = (PFloat*)malloc(sizeof(PFloat) * verticies_length);
    memcpy(mesh->positions, verticies, sizeof(PFloat) * verticies_length);

    mesh->index_length = indices_length;
    mesh->indices = (PIndex*)malloc(sizeof(PIndex) * indices_length);
    memcpy(mesh->indices, indices, sizeof(PIndex) * indices_length);

    PUint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    mesh->vao = vao;

    PUint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, verticies_length * sizeof(PFloat), mesh->positions, gl_type);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, sizeof(PFloat) * dimensions, 0);
    mesh->buffer = buffer;

    PUint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_length * sizeof(PIndex), mesh->indices, gl_type);
    mesh->ibo = ibo;

    InsertMesh(purplx, mesh);

    return mesh;
}

void InsertMesh(Purplx *purplx, Mesh *mesh) {
    purplx->meshes = realloc(purplx->meshes, purplx->mesh_count + 1 * sizeof(Mesh));

    purplx->meshes[purplx->mesh_count] = *mesh;
    purplx->mesh_count += 1;
}