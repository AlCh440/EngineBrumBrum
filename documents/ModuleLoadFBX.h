#pragma once
struct PhysBody3D;
struct PhysMotor3D;


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
	
	void LoadFile(const char* file_path);


};


