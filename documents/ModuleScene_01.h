#pragma once
#include "Module.h"

#include "Globals.h"


#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;
struct float3
{
	float x, y, z;
};
class ModuleScene_01 : public Module
{
public:
	ModuleScene_01(Application* app, bool start_enabled = true);
	~ModuleScene_01();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	update_status menuDisplay();
	void testOpenGL();

	update_status UpdateGeometry();
	update_status UpdateEditor();
	void DrawCube01();
	void DrawCube02();
	void DrawCube03();
	void DrawCubeArray();
	void DrawCubeIndices();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	bool myToolActive = true;
	bool myTryActive = true;
	bool closeButton = false;
	bool activateAbout = false;
	bool fullscreen = false;
	bool fullscreenno = false;
	bool vsync = false;
	bool boolWireframe = false;

};


