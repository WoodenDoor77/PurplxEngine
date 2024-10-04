#include <stdio.h>
#include "glad/glad.h"
#include "glfw3.h"
#include <stdlib.h>
#include "Purplx.h"

Purplx *purplx;

void update(){

}

void ready(){
    PFloat positions[] = {
        -0.5f, -0.5,
        0.0f, 0.5f,
        0.5f, -0.5f,
    };

    //Mesh *thing = CreateMesh(purplx, positions, sizeof(positions));

    PFloat positions2[] = {
        0.0f, 0.0f,
        0.5f, 0.0f,
        0.5f, 0.5f,

        0.0f, 0.5f,
    };

    PIndex indices[] = {
        0, 1, 2,
        2, 3, 0,
    };

    Mesh *thing2 = CreateMesh(purplx, positions2, sizeof(positions2), indices, sizeof(indices), STATIC);
}

void input(GLFWwindow* window, int key, int scancode, int action, int mods){

}

int main(){
    purplx = CreatePurplx();
    purplx->input_func = input;
    purplx->ready_func = ready;
    purplx->update_func = update;

    P8Int error = Run(purplx);

    if (error != 0){
        printf("error: %d\n", error);
        return -1;
    }
    printf("DONE\n");

    return 0;
}