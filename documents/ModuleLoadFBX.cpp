#include "Globals.h"
#include "Application.h"
#include "ModuleLoadFBX.h"

#include "Assimp/assimp/cimport.h"
#include "Assimp/assimp/scene.h"
#include "Assimp/postprocess.h"

#pragma comment (lib, "Assimp/assimp/libx86/assimp-vc142-mt.lib")

                                                                                                                                        
ModuleLoadFBX::ModuleLoadFBX(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    uint id_index = 0; // index in VRAM
    uint num_index = 0;
    uint* index = nullptr;
    uint id_vertex = 0; // unique vertex in VRAM
    uint num_vertex = 0;
    float* vertex = nullptr;
}

ModuleLoadFBX::~ModuleLoadFBX()
{
}

// Load assets
bool ModuleLoadFBX::Start()
{
    LOG("Loading Intro assets");
    bool ret = true;

    struct aiLogStream stream;
    stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
    aiAttachLogStream(&stream);

    const char* filepath = ("GitHub\EngineBrumBrum\documents\Game\Assets\BakerHouse.bfx");
    LoadFile(filepath);
    return ret;
}

// Load assets
bool ModuleLoadFBX::CleanUp()
{

    aiDetachAllLogStreams();

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

void ModuleLoadFBX::LoadFile(const char* file_path)
{
    const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);



    if (scene != nullptr  && scene->HasMeshes())
    {
        // Use scene->mNumMeshes to iterate on scene->mMeshes array
        aiReleaseImport(scene);
    }
    else
    {
        const char* a = aiGetErrorString();
    }



}







