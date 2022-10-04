#include "Globals.h"
#include "Application.h"
#include "ModuleScene_01.h"
#include "ModuleWindow.h"

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
    update_status ret = UPDATE_CONTINUE;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->window->window);
    ImGui::NewFrame();
  
   
    //ImGui::Begin("Custom window",0, ImGuiWindowFlags_MenuBar);

    ImGui::ShowDemoWindow();

     ret = menuDisplay();

    

    

    //ImGui::End();

     return ret;
}

update_status ModuleScene_01::menuDisplay()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::Button("Close"))
            {
                return UPDATE_STOP;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::Button("About"))
            {
                activateAbout = !activateAbout;

            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Configuration"))
        {
            if (ImGui::BeginMenu("Window"))
            {
                ImGui::Checkbox("Full Screen", &fullscreen);
                {




                    if (fullscreen == true)
                    {
                        fullscreenno = true;
                        App->window->SetFullscreen(fullscreen);

                    }
                    if (fullscreen == false)
                    {
                        fullscreenno = false;
                        App->window->SetFullscreenNo(fullscreenno);
                    }
                }

                ImGui::Checkbox("Vsync", &vsync);
                {

                }

                if (ImGui::BeginMenu("Style"))
                {

                    ImGui::ShowStyleEditor();


                    ImGui::EndMenu();


                }

                static int i1 = 50, i2 = 42;
                ImGui::DragInt("drag int 0..100", &i2, 1, 0, 100, "%d%%", ImGuiSliderFlags_AlwaysClamp);





                ImGui::EndMenu();
            }

            if (ImGui::Button("Renderer"))
            {


            }
            if (ImGui::Button("Input"))
            {


            }
            if (ImGui::Button("Audio"))
            {


            }

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }


    if (activateAbout == true)
    {
        ImGui::Begin("About", 0, ImGuiWindowFlags_MenuBar);
        {
            ImGui::Text("BrumBrum");
            ImGui::Text("Best Motor ever not of a car");
            ImGui::Text("Abochan & Juan Fernando (https://github.com/AlCh440/EngineBrumBrum)");
            ImGui::Text("We have the Mathegeolib, the glew, the JSON and the SDL");
            ImGui::Text("License");
        }

        ImGui::End();
    }


    return UPDATE_CONTINUE;
}

void ModuleScene_01::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

