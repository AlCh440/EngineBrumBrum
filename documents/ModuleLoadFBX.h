#pragma once
#include "Mesh.h"

struct PhysBody3D;
struct PhysMotor3D;
struct aiNode;
struct aiScene;
struct aiMesh;

class ModuleLoadFBX : public Module
{
public:
	ModuleLoadFBX(Application* app, bool start_enabled = true);
	~ModuleLoadFBX();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();


	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	bool Save() override;

	void LoadNode(aiNode* nextNode, const aiScene* scene);
	void LoadFile(const char* file_path);
	Mesh LoadMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Mesh> meshes;
};


