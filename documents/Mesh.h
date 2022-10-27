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

	void LoadMesh();
	void Draw();

	Mesh(std::vector<Vertex> vertices, std::vector<int> indices);
	~Mesh();

private:
	
	uint vertexId = 0;
	int indicesId = 0;

};