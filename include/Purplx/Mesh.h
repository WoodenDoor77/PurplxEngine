#ifndef MESH
#define MESH

#include "Purplx.h"

Mesh *CreateMesh(Purplx *purplx, PFloat *verticies, size_t verticies_length, PIndex *indices, size_t indices_length, PType type);
void InsertMesh(Purplx *purplx, Mesh *mesh);

#endif /* MESH */