#pragma once
#include "Module.h"

#include "Globals.h"


#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleScene_01 : public Module
{
public:
	ModuleScene_01(Application* app, bool start_enabled = true);
	~ModuleScene_01();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	bool myToolActive = true;
};
