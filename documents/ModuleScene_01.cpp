#include "Globals.h"
#include "Application.h"
#include "ModuleScene_01.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


ModuleScene_01::ModuleScene_01(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleScene_01::~ModuleScene_01()
{}

// Load assets
bool ModuleScene_01::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

    IMGUI_CHECKVERSION();
    void* context = ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    
    // Setup Platform/Renderer bindings
    // window is the SDL_Window*
    // context is the SDL_GLContext

 
	return ret;
}

// Load assets
bool ModuleScene_01::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleScene_01::Update(float dt)
{
   
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->window->window);
    ImGui::NewFrame();
  

    ImGui::Begin("Custom window",0, ImGuiWindowFlags_MenuBar);

    ImGui::ShowDemoWindow();

    ImGui::BeginMainMenuBar();
    ImGui::Text("Main Menu");
    
    if (ImGui::Button(" Close", ImVec2(100, 20)))
    {
        return UPDATE_STOP;
    }

    ImGui::EndMainMenuBar();

    ImGui::BeginMenuBar();
    ImGui::Text("happy bar");
    ImGui::EndMenuBar();

    ImGui::End();

	return UPDATE_CONTINUE;
}

void ModuleScene_01::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

