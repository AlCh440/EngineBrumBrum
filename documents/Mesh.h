#pragma once
#include "Globals.h"
#include <vector>

struct Vertex {
	float3 Pos;
	float3 Normal;

};

class Mesh 
{
public:
	// mesh data
	std::vector<Vertex>       vertices;
	std::vector<int> indices;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	~Mesh();

private:
	

};