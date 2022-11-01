#pragma once
#include "Globals.h"
#include <vector>

struct Vertex {
	float3 Pos;
	

};

class Mesh 
{
public:
	// mesh data
	std::vector<Vertex> vertices;
	std::vector<int> indices;

	int num_vertex = 0;
	int num_index = 0;
	void LoadMesh();
	void Draw();

	Mesh(std::vector<Vertex> vertices, std::vector<int> indices, int num_vertex, int num_index);
	~Mesh();

private:
	
	uint vertexId = 0;
	int indicesId = 0;

};