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
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * num_vertex * 3, &vertices.front(), GL_DYNAMIC_DRAW);
    
   
    glGenBuffers(1, (GLuint*)&(indicesId));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * num_index, &indices.front(), GL_DYNAMIC_DRAW);
}

void Mesh::Draw()
{

	
    
    glEnableClientState(GL_VERTEX_ARRAY);
    // glBindBuffer(GL_ARRAY_BUFFER, vertexId);
    glVertexPointer(3, GL_FLOAT, 0, &vertices);
    
    glBindVertexArray(vertexId);
    glDrawElements(GL_TRIANGLES, num_index, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
    
 glDisableClientState(GL_VERTEX_ARRAY);
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<int> indices, int num_vertex, int num_index)
{
    this->vertices = vertices;
    this->indices = indices;
    this->num_vertex = num_vertex;
    this->num_index = num_index;

    LoadMesh();
}

Mesh::~Mesh()
{
}
