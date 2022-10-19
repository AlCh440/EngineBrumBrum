#include "Globals.h"
#include "Application.h"
#include "ModuleLoadFBX.h"

//#include "Assimp/assimp/cimport.h"
//#include "Assimp/assimp/scene.h"
//#include "Assimp/postprocess.h"

#pragma comment (lib, "Assimp/assimp/libx86/assimp-vc142-mt.lib")

                                                                                                                                        
ModuleLoadFBX::ModuleLoadFBX(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleLoadFBX::~ModuleLoadFBX()
{
}

// Load assets
bool ModuleLoadFBX::Start()
{
    LOG("Loading Intro assets");
    bool ret = true;


    return ret;
}

// Load assets
bool ModuleLoadFBX::CleanUp()
{
    LOG("Unloading Intro scene");

    return true;
}

// Update
update_status ModuleLoadFBX::Update(float dt)
{
   

    return UPDATE_CONTINUE;
}



void ModuleLoadFBX::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

bool ModuleLoadFBX::Save()
{

    return true;
}









