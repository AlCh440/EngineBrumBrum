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

    const char* filepath = ("Assets/BakerHouse.fbx");
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
    meshes.front().Draw();

    return UPDATE_CONTINUE;
}



void ModuleLoadFBX::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

bool ModuleLoadFBX::Save()
{

    return true;
}

void ModuleLoadFBX::LoadNode(aiNode* nextNode, const aiScene* scene)
{
    for (int i = 0; i < nextNode->mNumMeshes; i++)
    {
        aiMesh* aux = scene->mMeshes[nextNode->mMeshes[i]];
        meshes.push_back(LoadMesh(aux, scene));
    }

    for (unsigned int i = 0; i < nextNode->mNumChildren; i++)
    {
        LoadNode(nextNode->mChildren[i], scene);
    }
}

Mesh ModuleLoadFBX::LoadMesh(aiMesh* mesh, const aiScene* scene)
{

    //temporary varaibles to store the mesh data
    std::vector<Vertex> vertices;
    std::vector<int> indices;
 

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        float3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Pos = vector;


        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }



    return Mesh(vertices, indices);
}

void ModuleLoadFBX::LoadFile(const char* file_path)
{
    const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);



    if (scene != nullptr  && scene->HasMeshes())
    {
        // Use scene->mNumMeshes to iterate on scene->mMeshes array
        LoadNode(scene->mRootNode, scene);
        aiReleaseImport(scene);
    }
    else
    {
        const char* a = aiGetErrorString();
    }



}







