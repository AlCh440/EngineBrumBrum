#include "Mesh.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

#include "glew/include/GL/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <vector>



void Mesh::LoadMesh()
{
    
    glGenBuffers(1, (GLuint*)&(vertexId));
    glBindBuffer(GL_ARRAY_BUFFER, vertexId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size() * 3, &vertices.front(), GL_STATIC_DRAW);

   
    glGenBuffers(1, (GLuint*)&(indicesId));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices.front(), GL_STATIC_DRAW);
}

void Mesh::Draw()
{
   

    

    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, vertexId);
    glVertexPointer(3, GL_FLOAT, 0, NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesId);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

    //glDrawArrays(GL_TRIANGLES, 0, 8);
    glDisableClientState(GL_VERTEX_ARRAY);
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<int> indices)
{
    this->vertices = vertices;
    this->indices = indices;

    LoadMesh();
}

Mesh::~Mesh()
{
}
