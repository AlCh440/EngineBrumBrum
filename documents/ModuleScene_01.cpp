#include "Globals.h"
#include "Application.h"
#include "ModuleScene_01.h"
#include "ModuleWindow.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

#include "glew/include/GL/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>


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
    
     testOpenGL();
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
            if (ImGui::MenuItem("Select All", "CTRL+A")) {}
            if (ImGui::MenuItem("Deselect All", "Shift+D")) {}
            if (ImGui::MenuItem("Select Children", "CTRL+C")) {}
            if (ImGui::MenuItem("Invert Selection", "CTRL+I")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Duplicate", "CTRL+D")) {}
            if (ImGui::MenuItem("Rename")) {}
            if (ImGui::MenuItem("Delete")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Play", "CTRL+P")) {}
            if (ImGui::MenuItem("Pause", "CTRL+Shift+P")) {}
            if (ImGui::MenuItem("Play", "CTRL+P")) {}

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
                ImGui::DragInt("Brightness", &i2, 1, 0, 100, "%d%%", ImGuiSliderFlags_AlwaysClamp);





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
           

            ImGui::Text("ABOUT THIS DEMO:");
            ImGui::BulletText("BrumBrum Engine");
            ImGui::BulletText("Best Motor ever not of a car");
           
            ImGui::Text("PROGRAMMER GUIDE:");
            
            ImGui::BulletText("Abochan & Juan Fernando (https://github.com/AlCh440/EngineBrumBrum)");
            ImGui::BulletText("We have the Mathegeolib, the glew, the JSON and the SDL");
            ImGui::BulletText("License");
            ImGui::Separator();

            ImGui::Text("USER GUIDE:");
            ImGui::ShowUserGuide();
        }

        ImGui::End();
    }


    return UPDATE_CONTINUE;
}

void ModuleScene_01::testOpenGL()
{
    //plane
    glLineWidth(1.0f);

    glBegin(GL_LINES);

    float d = 200.0f;

    for (float i = -d; i <= d; i += 1.0f)
    {
        glVertex3f(i, 0.0f, -d);
        glVertex3f(i, 0.0f, d);
        glVertex3f(-d, 0.0f, i);
        glVertex3f(d, 0.0f, i);
    }
    glEnd();


	
   
 

}

void ModuleScene_01::DrawCube01()
{
    //glTranslatef(1. + cum_val, 0., 1. + cum_val);
    glBegin(GL_TRIANGLES);

    glColor3f(1., 1., 0.);

    /// <summary>
    ///  8 Vertex
    /// x = -1 or 1, same for y, z
    /// Permutations
    /// 1 1 1 = 8
    /// 1 1 -1 = 4
    /// 1 -1 1 = 6
    /// -1 1 1 = 7
    /// -1 -1 1 = 5
    /// -1 1 -1 = 3
    /// -1 -1 -1 = 1
    /// 1 -1 -1 = 2
    /// </summary>

    // Remember Counterclockwise Order (Right Hand Rule)
    // glVertex3f(-1., -1., -1.);	// 1
    // glVertex3f(1., -1., -1.);	// 2
    // glVertex3f(-1., 1., -1.);	// 3
    // glVertex3f(1., 1., -1.);		// 4
    // glVertex3f(-1., -1., 1.);	// 5
    // glVertex3f(1., -1., 1.);		// 6
    // glVertex3f(-1., 1., 1.);		// 7
    // glVertex3f(1., 1., 1.);		// 8

    // Z = 1 / TriB
    glColor3f(1., 1., 0.);
    glVertex3f(-1., -1., 1.);	// 5
    glVertex3f(1., -1., 1.);	// 6
    glVertex3f(1., 1., 1.);		// 8

    // Z = 1 / TriT
    glVertex3f(-1., -1., 1.);	// 5
    glVertex3f(1., 1., 1.);		// 8
    glVertex3f(-1., 1., 1.);	// 7

    // *Backfaces have to be drawn in the inverse order you expect
    // You will look at them when you are rotated backwards
    // Z = -1 / TriB
    glColor3f(1., 0., 1.);
    glVertex3f(1., 1., -1.);	// 4
    glVertex3f(1., -1., -1.);	// 2
    glVertex3f(-1., -1., -1.);	// 1

    // Z = -1 / TriT
    glVertex3f(-1., -1., -1.);	// 1
    glVertex3f(-1., 1., -1.);	// 3
    glVertex3f(1., 1., -1.);	// 4

    // Top bottom and sides now...
    glColor3f(0., 1., 1.);
    // Top / TriR
    glVertex3f(1., 1., -1.);	// 4
    glVertex3f(-1., 1., -1.);	// 3
    glVertex3f(1., 1., 1.);		// 8

    // Top / TriL
    glVertex3f(-1., 1., -1.);	// 3
    glVertex3f(-1., 1., 1.);	// 7
    glVertex3f(1., 1., 1.);		// 8

    // Bottom / TriR
    glColor3f(1., 0., 0.);
    glVertex3f(1., -1., -1.);	// 2
    glVertex3f(1., -1., 1.);	// 6
    glVertex3f(-1., -1., -1.);	// 1

    // Bottom / TriL
    glVertex3f(-1., -1., -1.);	// 1
    glVertex3f(1., -1., 1.);	// 6
    glVertex3f(-1., -1., 1.);	// 5

    // SideL / TriT
    glColor3f(0., 1., 0.);
    glVertex3f(-1., -1., -1.);	// 1
    glVertex3f(-1., 1., 1.);	// 7
    glVertex3f(-1., 1., -1.);	// 3

    // SideL / TriB
    glVertex3f(-1., -1., -1.);	// 1
    glVertex3f(-1., -1., 1.);	// 5
    glVertex3f(-1., 1., 1.);	// 7

    // SideR / TriT
    glColor3f(0., 0., 1.);
    glVertex3f(1., -1., -1.);	// 2
    glVertex3f(1., 1., -1.);	// 4
    glVertex3f(1., 1., 1.);		// 8

    glVertex3f(1., -1., -1.);	// 2
    glVertex3f(1., 1., 1.);		// 8
    glVertex3f(1., -1., 1.);	// 6

    glEnd();

}

void ModuleScene_01::DrawCube02()
{
    float3 vertices[] = {
   {-1., -1., -1.}, {1., -1., -1.},
   {-1., 1., -1.}, {1., 1., -1.},
   {-1., -1., 1.}, {1., -1., 1.},
   {-1., 1., 1.}, {1., 1., 1.}

    };
    int indices[] = {
        5,6,8,	5,8,7,
        4,2,1,	1,3,4,
        4,3,8,	3,7,8,
        2,6,1,	1,6,5,
        1,7,3,	1,5,7,
        2,4,8,	2,8,6
    };

    float3 colors[] = {
    {1., 1., 0.}, {1., 0., 1.}, {0., 1., 1.},
    {1., 0., 0.}, {0., 1., 0.}, {0., 0., 1.}
    };

    glBegin(GL_TRIANGLES);
    int col = -1;
    for (int i = 0; i < sizeof(indices) / sizeof(int); ++i) {
        if (i % 6 == 0) {
            ++col;
            glColor3f(colors[col].x, colors[col].y, colors[col].z);
        }
        float3& v = vertices[indices[i] - 1];
        glVertex3f(v.x, v.y, v.z);
    }
    glEnd();
}

void ModuleScene_01::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}








//void DDCube_BadIndices()
//{
//	glBegin(GL_TRIANGLES);
//	int* idx = indices;
//
//	// Front Face
//	glColor3f(1., 1., 0.);
//	GLVertexDD(idx); idx++; // 5
//	GLVertexDD(idx); idx++; // 6
//	GLVertexDD(idx); idx++; // 8
//
//	GLVertexDD(idx); idx++; // 5
//	GLVertexDD(idx); idx++; // 8
//	GLVertexDD(idx); idx++; // 7
//
//	// Back Fave
//	glColor3f(1., 0., 1.);
//	GLVertexDD(idx); idx++; // 4
//	GLVertexDD(idx); idx++; // 2
//	GLVertexDD(idx); idx++; // 1
//
//	GLVertexDD(idx); idx++; // 1
//	GLVertexDD(idx); idx++; // 3
//	GLVertexDD(idx); idx++; // 4
//
//	// Top Face
//	glColor3f(0., 1., 1.);
//	GLVertexDD(idx); idx++; // 4
//	GLVertexDD(idx); idx++; // 3
//	GLVertexDD(idx); idx++; // 8
//
//	GLVertexDD(idx); idx++; // 3
//	GLVertexDD(idx); idx++; // 7
//	GLVertexDD(idx); idx++; // 8
//
//	// Bottom Face
//	glColor3f(1., 0., 0.);
//	GLVertexDD(idx); idx++; // 2
//	GLVertexDD(idx); idx++; // 6
//	GLVertexDD(idx); idx++; // 1
//
//	GLVertexDD(idx); idx++; // 1
//	GLVertexDD(idx); idx++; // 6
//	GLVertexDD(idx); idx++; // 5
//
//	// SideL / TriT
//	glColor3f(0., 1., 0.);
//	GLVertexDD(idx); idx++; // 1
//	GLVertexDD(idx); idx++; // 7
//	GLVertexDD(idx); idx++; // 3
//
//	GLVertexDD(idx); idx++; // 1
//	GLVertexDD(idx); idx++; // 5
//	GLVertexDD(idx); idx++; // 7
//
//	// SideR / TriT
//	glColor3f(0., 0., 1.);
//	GLVertexDD(idx); idx++; // 2
//	GLVertexDD(idx); idx++; // 4
//	GLVertexDD(idx); idx++; // 8
//
//	GLVertexDD(idx); idx++; // 2
//	GLVertexDD(idx); idx++; // 8
//	GLVertexDD(idx); idx++; // 6
//
//	glEnd();
//}