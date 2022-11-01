#pragma once
#include "Globals.h"
#include <vector>
#include "GameObject.h"

struct Vertex {
	float3 Pos;
	

};

class Mesh 
{
public:
	// mesh data
	std::vector<Vertex> vertices;
	std::vector<int> indices;
	std::vector<float2> uv_coords;

	int num_vertex = 0;
	int num_index = 0;
	void LoadMesh();
	void Draw();
	uint num_vertices = 0;

	uint textureID = 0;
	
	GameObject* myGameObject = nullptr;

	Mesh(std::vector<Vertex> vertices, std::vector<int> indices, std::vector<float2> uv, int num_vertex, int num_index);
	~Mesh();
	
	void DeleteMesh(Mesh* m);

private:
	
	uint vertexId = 0;
	int indicesId = 0;


	//vector<Mesh*> meshes;

	uint uvId = 0;

};