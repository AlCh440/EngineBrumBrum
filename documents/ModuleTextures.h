#pragma once
struct PhysBody3D;
struct PhysMotor3D;


class ModuleTextures : public Module
{
public:
	ModuleTextures(Application* app, bool start_enabled = true);
	~ModuleTextures();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	uint LoadCheckerTex();

};


