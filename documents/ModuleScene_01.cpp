#include "Globals.h"
#include "Application.h"
#include "ModuleScene_01.h"
#include "ModuleWindow.h"


#include "parson/include/parson.h"

#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"

#include "glew/include/GL/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <vector>


#define GLVertexDD(idx) {float3& v = vertices[*idx - 1]; glVertex3f(v.x, v.y, v.z);}

class SolidSphere
{
protected:
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::vector<GLushort> indices;

public:
    SolidSphere(float radius, unsigned int rings, unsigned int sectors)
    {
        float const R = 1. / (float)(rings - 1);
        float const S = 1. / (float)(sectors - 1);
        int r, s;

        vertices.resize(rings * sectors * 3);
        normals.resize(rings * sectors * 3);
        texcoords.resize(rings * sectors * 2);
        std::vector<GLfloat>::iterator v = vertices.begin();
        std::vector<GLfloat>::iterator n = normals.begin();
        std::vector<GLfloat>::iterator t = texcoords.begin();
        for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
            float const y = sin(-M_PI_2 + M_PI * r * R);
            float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
            float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

            *t++ = s * S;
            *t++ = r * R;

            *v++ = x * radius;
            *v++ = y * radius;
            *v++ = z * radius;

            *n++ = x;
            *n++ = y;
            *n++ = z;
        }

        indices.resize(rings * sectors * 4);
        std::vector<GLushort>::iterator i = indices.begin();
        for (r = 0; r < rings; r++) for (s = 0; s < sectors; s++) {
            *i++ = r * sectors + s;
            *i++ = r * sectors + (s + 1);
            *i++ = (r + 1) * sectors + (s + 1);
            *i++ = (r + 1) * sectors + s;
        }
    }

    void draw(GLfloat x, GLfloat y, GLfloat z)
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(x, y, z);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
        glNormalPointer(GL_FLOAT, 0, &normals[0]);
        glTexCoordPointer(2, GL_FLOAT, 0, &texcoords[0]);
        glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
        glPopMatrix();
    }
};

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

    checkers_tex = App->texturer->LoadCheckerTex();
 
    glewInit();
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

    ret = UpdateGeometry();

    ret = UpdateEditor();
    
    //ImGui::Begin("Custom window",0, ImGuiWindowFlags_MenuBar);

     
     return ret;
}

update_status ModuleScene_01::menuDisplay()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {


            if (ImGui::MenuItem("New Scene", "CTRL+N")) {}
            if (ImGui::MenuItem("Open Scene", "CTRL+O")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Save", "CTRL+S")) {}
            if (ImGui::MenuItem("Save As", "CTRL+Shift+S")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("New Project")) {}
            if (ImGui::MenuItem("Open Project")) {}
            if (ImGui::MenuItem("Save Project")) {}

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

           
            
            ImGui::Image((GLuint*)checkers_tex, ImVec2(500, 500));

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Configuration"))
        {
            if (ImGui::BeginMenu("Window"))
            {
                ImGui::Checkbox("Full Screen", &fullscreen);
                {
                    App->window->SetFullscreen(fullscreen);
                }

                ImGui::Checkbox("Wireframe", &boolWireframe);

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

            

            // Vector3 fps_log;

            if (ImGui::BeginMenu("Application"))
            {
                char title[25];
                if (ImGui::BeginMenu("Frame Counter"))
                {
                    char title[25];

                    //sprintf_s(title, 25, "Frame rate %.1f", fps_log[fps_log.size() - 1]);

                    ImGui::EndMenu();
                }

                if (ImGui::BeginMenu("Hardware"))
                {
                    SDL_version linked;
                    SDL_GetVersion(&linked);

                    ImGui::Text("System: "); { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.4f, 0.0f, 1.0f), "%s", SDL_GetPlatform()); }
                    ImGui::Text("SDL Version: "); { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.4f, 0.0f, 1.0f), "%u.%u.%u", linked.major, linked.minor, linked.patch); }

                    ImGui::Separator();

                    ImGui::Text("CPU cores: "); { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.4f, 0.0f, 1.0f), "%d", SDL_GetCPUCount()); }
                    ImGui::Text("RAM: "); { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.0f, 1.4f, 0.0f, 1.0f), "%.2f GB", SDL_GetSystemRAM() / 1024.0f); }

                    ImGui::Text("Caps: ");
                    if (SDL_HasRDTSC() == SDL_bool::SDL_TRUE)
                    {
                        ImGui::SameLine();
                        ImGui::TextColored(ImVec4(1, 1, 0, 1), "RDTSC,");
                    }
                    if (SDL_HasMMX() == SDL_bool::SDL_TRUE)
                    {
                        ImGui::SameLine();
                        ImGui::TextColored(ImVec4(1, 1, 0, 1), "MMX,");
                    }
                    if (SDL_HasSSE() == SDL_bool::SDL_TRUE)
                    {
                        ImGui::SameLine();
                        ImGui::TextColored(ImVec4(1, 1, 0, 1), "SSE,");
                    }
                    if (SDL_HasSSE2() == SDL_bool::SDL_TRUE)
                    {
                        ImGui::SameLine();
                        ImGui::TextColored(ImVec4(1, 1, 0, 1), "SSE2,");
                    }
                    if (SDL_HasSSE3() == SDL_bool::SDL_TRUE)
                    {
                        ImGui::TextColored(ImVec4(1, 1, 0, 1), "SSE3,");
                    }
                    if (SDL_HasSSE41() == SDL_bool::SDL_TRUE)
                    {
                        ImGui::SameLine();
                        ImGui::TextColored(ImVec4(1, 1, 0, 1), "SSE41,");
                    }
                    if (SDL_HasSSE42() == SDL_bool::SDL_TRUE)
                    {
                        ImGui::SameLine();
                        ImGui::TextColored(ImVec4(1, 1, 0, 1), "SSE41,");
                    }
                    if (SDL_HasAVX() == SDL_bool::SDL_TRUE)
                    {
                        ImGui::SameLine();
                        ImGui::TextColored(ImVec4(1, 1, 0, 1), "AVX,");
                    }
                    if (SDL_HasAVX2() == SDL_bool::SDL_TRUE)
                    {
                        ImGui::SameLine();
                        ImGui::TextColored(ImVec4(1, 1, 0, 1), "AVX2");
                    }

                    ImGui::Separator();

                    const GLubyte* vendor = glGetString(GL_VENDOR);
                    const GLubyte* renderer = glGetString(GL_RENDERER);

                    ImGui::Text("GPU:");
                    ImGui::SameLine();
                    ImGui::TextColored(ImVec4(1, 1, 0, 1), "%s", vendor);

                    ImGui::Text("Brand:");
                    ImGui::SameLine();
                    ImGui::TextColored(ImVec4(1, 1, 0, 1), "%s", renderer);

                    GLint parameter = 0;
                    glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &parameter);
                    ImGui::Text("VRAM budget:");
                    ImGui::SameLine();
                    ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d Mb", parameter / 1024);
                    glGetIntegerv(GL_GPU_MEMORY_INFO_EVICTION_COUNT_NVX, &parameter);
                    ImGui::Text("VRAM usage:");
                    ImGui::SameLine();
                    ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d Mb", parameter / 1024);

                    glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &parameter);
                    ImGui::Text("VRAM available:");
                    ImGui::SameLine();
                    ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d Mb", parameter / 1024);

                    glGetIntegerv(GL_GPU_MEMORY_INFO_EVICTED_MEMORY_NVX, &parameter);
                    ImGui::Text("VRAM reserved:");
                    ImGui::SameLine();
                    ImGui::TextColored(ImVec4(1, 1, 0, 1), "%d Mb", parameter / 1024);

                   
                    
                    

                    ImGui::EndMenu();
                }


                ImGui::EndMenu();
            }




            if (ImGui::BeginMenu("Renderer"))
            {
                if (ImGui::Button("Depth Test")) 
                {
                    activateDepthTest = !activateDepthTest;
                }

                if (ImGui::Button("Cull Face"))
                {
                    activateCullFace = !activateCullFace;
                }

                if (ImGui::Button("Lightning"))
                {
                    activateLightning = !activateLightning;
                }

                if (ImGui::Button("Color Material"))
                {
                    activateColorMaterial = !activateColorMaterial;
                }

                if (ImGui::Button("Texture 2D"))
                {
                    activateTexture2D = !activateTexture2D;
                }


                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Input"))
            {



                ImGuiIO& io = ImGui::GetIO();
                if (ImGui::TreeNode("Mouse State"))
                {
                    if (ImGui::IsMousePosValid())
                        ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
                    else
                        ImGui::Text("Mouse pos: <INVALID>");
                    ImGui::Text("Mouse delta: (%g, %g)", io.MouseDelta.x, io.MouseDelta.y);

                    int count = IM_ARRAYSIZE(io.MouseDown);
                    ImGui::Text("Mouse down:");         for (int i = 0; i < count; i++) if (ImGui::IsMouseDown(i)) { ImGui::SameLine(); ImGui::Text("b%d (%.02f secs)", i, io.MouseDownDuration[i]); }
                    ImGui::Text("Mouse clicked:");      for (int i = 0; i < count; i++) if (ImGui::IsMouseClicked(i)) { ImGui::SameLine(); ImGui::Text("b%d (%d)", i, ImGui::GetMouseClickedCount(i)); }
                    ImGui::Text("Mouse released:");     for (int i = 0; i < count; i++) if (ImGui::IsMouseReleased(i)) { ImGui::SameLine(); ImGui::Text("b%d", i); }
                    ImGui::Text("Mouse wheel: %.1f", io.MouseWheel);
                    ImGui::Text("Pen Pressure: %.1f", io.PenPressure); // Note: currently unused
                    ImGui::TreePop();
                }





                ImGui::EndMenu();


            }



            if (ImGui::BeginMenu("Audio"))
            {
                static int i0 = 60;
                ImGui::InputInt("Volume", &i0);


                ImGui::EndMenu();
            }


            ImGui::EndMenu();

        }

        if (ImGui::BeginMenu("Objects"))
        {
            if (ImGui::Button("Cube"))
            {
                activateCube = !activateCube;

                ImGui::EndMenu();
            }

            if (ImGui::Button("Pyramid"))
            {
                activatePyramid = !activatePyramid;

                ImGui::EndMenu();
            }

            if (ImGui::Button("Cone"))
            {
                activateCone = !activateCone;

                ImGui::EndMenu();
            }

            if (ImGui::Button("Sphere"))
            {
                activateSphere = !activateSphere;

                ImGui::EndMenu();
            }

            ImGui::EndMenu();
        }



        ImGui::EndMainMenuBar();

    }


    if (activateAbout == true)
    {
        ImGui::Begin("About", 0, ImGuiWindowFlags_MenuBar);
        {


            ImGui::Text("Brenda 1:");
            ImGui::Text("The future of the engines");
            ImGui::Text("By Albert Chica & Fernando Almendro");
            ImGui::Text("Github: https://github.com/AlCh440/EngineBrumBrum ");
            ImGui::Separator();

            ImGui::Text("3D Party libraries used:");

            
            ImGui::BulletText("SDL");
            ImGui::BulletText("GLEW");
            ImGui::BulletText("MathGeoLib");
            ImGui::BulletText("ImGui");
            ImGui::BulletText("Parson");
            ImGui::BulletText("Assimp");
            ImGui::Separator();

            ImGui::Text("License:");
            ImGui::Text("MIT License");
            ImGui::Text("Copyright (c) 2022 AlCh440");
            
            ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy");
            ImGui::Text("of this software and associated documentation files(the Software), to deal");
            ImGui::Text("in the Software without restriction, including without limitation the rights");
            ImGui::Text("to use, copy, modify, merge, publish, distribute, sublicense, and /or sell");
            ImGui::Text("copies of the Software, and to permit persons to whom the Software is");
            ImGui::Text("furnished to do so, subject to the following conditions : ");
           
            ImGui::Text("The above copyright notice and this permission notice shall be included in all");
            ImGui::Text("copies or substantial portions of the Software.");
           
            ImGui::Text("THE SOFTWARE IS PROVIDED AS IS, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR");
            ImGui::Text("IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,");
            ImGui::Text("FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE");
            ImGui::Text("AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER");
            ImGui::Text("LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,");
            ImGui::Text("OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE");
            ImGui::Text("SOFTWARE.");

            ImGui::Separator();

            ImGui::Text("User's guide:");
            ImGui::ShowUserGuide();
        }

        ImGui::End();
    }
    
   

    if (activateDepthTest == true)
    {
        /*void mainn()
        {
            FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
        }*/
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_ALWAYS);

        

        /*out vec4 FragColor;

        float near = 0.1;
        float far = 100.0;

        float LinearizeDepth(float depth)
        {
            float z = depth * 2.0 - 1.0; // back to NDC 
            return (2.0 * near * far) / (far + near - z * (far - near));
        }

        void main()
        {
            float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
            FragColor = vec4(vec3(depth), 1.0);
        }*/
    }

    if (activateCullFace == true)
    {
        float vertices[] = {
            // clockwise
            vertices[0], // vertex 1
            vertices[1], // vertex 2
            vertices[2], // vertex 3
            // counter-clockwise
            vertices[0], // vertex 1
            vertices[2], // vertex 3
            vertices[1]  // vertex 2  
        };

        glEnable(GL_CULL_FACE);

        glCullFace(GL_BACK);
        glFrontFace(GL_CW);

    }

    if (activateLightning == true)
    {
        glEnable(GL_LIGHTING);
    }

    if (activateColorMaterial == true)
    {
        glEnable(GL_COLOR_MATERIAL);
    }

    if (activateTexture2D == true)
    {
        float texCoords[] = 
        {
        0.0f, 0.0f,  // lower-left corner  
        1.0f, 0.0f,  // lower-right corner
        0.5f, 1.0f   // top-center corner
        };

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

        float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);


        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        unsigned int texture;
        glGenTextures(1, &texture);

        glBindTexture(GL_TEXTURE_2D, texture);


        //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        float vertices[] = {
            // positions          // colors           // texture coords
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
        };

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindTexture(GL_TEXTURE_2D, texture);
       // glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
       
        glEnable(GL_TEXTURE_2D);


    

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

   //DrawCheckerCube();
}

update_status ModuleScene_01::UpdateGeometry()
{
    update_status ret = UPDATE_CONTINUE;
    if (boolWireframe)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    

    testOpenGL();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    return ret;
}

update_status ModuleScene_01::UpdateEditor()
{
    update_status ret = UPDATE_CONTINUE;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(App->window->window);
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

    ret = menuDisplay();
    return ret;
}

void ModuleScene_01::DrawCheckerCube01()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, checkers_tex);
    
    //glTranslatef(1. + cum_val, 0., 1. + cum_val);
    glBegin(GL_TRIANGLES);

   

    
    // Z = 1 / TriB
    glTexCoord2f(0, 0);
    glVertex3f(-1., -1., 1.);	// 5
    glTexCoord2f(0, 1);
    glVertex3f(1., -1., 1.);	// 6
    glTexCoord2f(1, 1);
    glVertex3f(1., 1., 1.);	// 8

    // Z = 1 / TriT glTexCoord2f();
    glTexCoord2f(0, 0);
    glVertex3f(-1., -1., 1.);	// 5
    glTexCoord2f(1, 1);
    glVertex3f(1., 1., 1.);	// 8
    glTexCoord2f(1, 0);
    glVertex3f(-1., 1., 1.);	// 7
    
    //// *Backfaces have to be drawn in the inverse order you expect
    //// You will look at them when you are rotated backwards
    // Z = -1 / TriB
    glTexCoord2f(0, 1);
    glVertex3f(1., 1., -1.);	// 4
    glTexCoord2f(0, 0);
    glVertex3f(1., -1., -1.);	// 2
    glTexCoord2f(1, 0);
    glVertex3f(-1., -1., -1.);// 1
    
    // Z = -1 / TriT
    glTexCoord2f(1, 0);
    glVertex3f(-1., -1., -1.);// 1
    glTexCoord2f(1, 1);
    glVertex3f(-1., 1., -1.);	// 3
    glTexCoord2f(0, 1);
    glVertex3f(1., 1., -1.);	// 4
    
    // Top bottom and sides now...

    // Top / TriR
    glTexCoord2f(1, 1);
    glVertex3f(1., 1., -1.);	// 4
    glTexCoord2f(0, 1);
    glVertex3f(-1., 1., -1.);	// 3
    glTexCoord2f(1, 0);
    glVertex3f(1., 1., 1.);		// 8
    
    // Top / TriL
    glTexCoord2f(0, 1);
    glVertex3f(-1., 1., -1.);	// 3
    glTexCoord2f(0, 0);
    glVertex3f(-1., 1., 1.);	// 7
    glTexCoord2f(1, 0);
    glVertex3f(1., 1., 1.);		// 8
    
    // Bottom / TriR
    glTexCoord2f(1, 0);
    glVertex3f(1., -1., -1.);	// 2
    glTexCoord2f(1, 1);
    glVertex3f(1., -1., 1.);	// 6
    glTexCoord2f(0, 0);
    glVertex3f(-1., -1., -1.);	// 1
    
    // Bottom / TriL
    glTexCoord2f(0, 0);
    glVertex3f(-1., -1., -1.);	// 1
    glTexCoord2f(1, 1);
    glVertex3f(1., -1., 1.);	// 6
    glTexCoord2f(0, 1);
    glVertex3f(-1., -1., 1.);	// 5
    
    // SideL / TriT
    glTexCoord2f(0 , 0);
    glVertex3f(-1., -1., -1.);	// 1
    glTexCoord2f(1, 1);
    glVertex3f(-1., 1., 1.);	// 7
    glTexCoord2f(0, 1);
    glVertex3f(-1., 1., -1.);	// 3
    
    // SideL / TriB
    glTexCoord2f(0, 0);
    glVertex3f(-1., -1., -1.);	// 1
    glTexCoord2f(1, 0);
    glVertex3f(-1., -1., 1.);	// 5
    glTexCoord2f(1, 1);
    glVertex3f(-1., 1., 1.);	// 7
    
    // SideR / TriT
    glTexCoord2f(1, 0);
    glVertex3f(1., -1., -1.);	// 2
    glTexCoord2f(1, 1);
    glVertex3f(1., 1., -1.);	// 4
    glTexCoord2f(0, 1);
    glVertex3f(1., 1., 1.);		// 8
    
    glTexCoord2f(1, 0);
    glVertex3f(1., -1., -1.);	// 2
    glTexCoord2f(0, 1);
    glVertex3f(1., 1., 1.);		// 8
    glTexCoord2f(0, 0);
    glVertex3f(1., -1., 1.);	// 6

    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void ModuleScene_01::DrawCube02()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, checkers_tex);

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

    GLfloat x, y = 0;

    glBegin(GL_TRIANGLES);
    int col = -1;
    for (int i = 0; i < sizeof(indices) / sizeof(int); ++i) {
        if (i % 6 == 0) {
            ++col;
           
            switch (i)
            {
            case 0:
            {
                x = 0;
                y = 1;
            } break;
            case 1:
            {
                x = 1;
                y = 1;
            } break;
            case 2:
            {
                x = 0;
                y = 0;
            } break;
            default:
                x = 0;
                y = 0;
                break;
            }
        }

        float3& v = vertices[indices[i] - 1];
        glTexCoord2f(x, y);
        glVertex3f(v.x, v.y, v.z);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void ModuleScene_01::DrawCube03()
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

    

    glBegin(GL_TRIANGLES);
    int* idx = indices;

    // Front Face
    glColor3f(1., 1., 0.);
    GLVertexDD(idx); idx++; // 5
    GLVertexDD(idx); idx++; // 6
    GLVertexDD(idx); idx++; // 8

    GLVertexDD(idx); idx++; // 5
    GLVertexDD(idx); idx++; // 8
    GLVertexDD(idx); idx++; // 7

    // Back Fave
    glColor3f(1., 0., 1.);
    GLVertexDD(idx); idx++; // 4
    GLVertexDD(idx); idx++; // 2
    GLVertexDD(idx); idx++; // 1

    GLVertexDD(idx); idx++; // 1
    GLVertexDD(idx); idx++; // 3
    GLVertexDD(idx); idx++; // 4

    // Top Face
    glColor3f(0., 1., 1.);
    GLVertexDD(idx); idx++; // 4
    GLVertexDD(idx); idx++; // 3
    GLVertexDD(idx); idx++; // 8

    GLVertexDD(idx); idx++; // 3
    GLVertexDD(idx); idx++; // 7
    GLVertexDD(idx); idx++; // 8

    // Bottom Face
    glColor3f(1., 0., 0.);
    GLVertexDD(idx); idx++; // 2
    GLVertexDD(idx); idx++; // 6
    GLVertexDD(idx); idx++; // 1

    GLVertexDD(idx); idx++; // 1
    GLVertexDD(idx); idx++; // 6
    GLVertexDD(idx); idx++; // 5

    // SideL / TriT
    glColor3f(0., 1., 0.);
    GLVertexDD(idx); idx++; // 1
    GLVertexDD(idx); idx++; // 7
    GLVertexDD(idx); idx++; // 3

    GLVertexDD(idx); idx++; // 1
    GLVertexDD(idx); idx++; // 5
    GLVertexDD(idx); idx++; // 7

    // SideR / TriT
    glColor3f(0., 0., 1.);
    GLVertexDD(idx); idx++; // 2
    GLVertexDD(idx); idx++; // 4
    GLVertexDD(idx); idx++; // 8

    GLVertexDD(idx); idx++; // 2
    GLVertexDD(idx); idx++; // 8
    GLVertexDD(idx); idx++; // 6

    glEnd();

}

void ModuleScene_01::DrawCubeArray()
{
    float3 vertices[] = {
        {-1, -1, 1}, { 1, -1, 1}, {-1, 1, 1},
        {1, -1, 1}, {1, 1, 1}, {-1, 1, 1},
        {1, -1, 1}, {1, -1, -1}, {1, 1, 1},
        {1, -1, -1}, {1, 1, -1}, {1, 1, 1},
        {-1, 1, -1}, {-1, 1, 1}, {1, 1, 1},
        {-1, 1, -1}, {1, 1, 1}, {1, 1, -1},
        {-1, -1, 1}, {-1, 1, 1}, {-1, 1, -1},
        {-1, -1, 1}, {-1, 1, -1}, {-1, -1, -1},
        {-1, -1, -1}, {1, -1, 1}, {-1, -1, 1},
        {-1, -1, -1}, {1, -1, -1}, {1, -1, 1},
        {-1, -1, -1}, {1, 1, -1}, {1, -1, -1},
        {-1, -1, -1}, {-1, 1, -1}, {1, 1, -1}
    };


    uint my_id = 0;
    glGenBuffers(1, (GLuint*)&(my_id));
    glBindBuffer(GL_ARRAY_BUFFER, my_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 36 * 3, vertices, GL_STATIC_DRAW);



    

    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, my_id);
    glVertexPointer(3, GL_FLOAT, 0, NULL);



    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDisableClientState(GL_VERTEX_ARRAY);


}

void ModuleScene_01::DrawCubeIndices()
{
    float3 vertices[] = {
   {-1., -1., -1.}, {1., -1., -1.},
   {-1., 1., -1.}, {1., 1., -1.},
   {-1., -1., 1.}, {1., -1., 1.},
   {-1., 1., 1.}, {1., 1., 1.}

    };

    int indices[] = {
       4,5,6,	5,7,6,
       5,1,7,	1,3,7,
       0,4,2,	4,6,2,
       6,7,2,	7,3,2,
       1,0,3,	0,2,3,
       0,1,4,    1,5,4
    };

    uint my_id = 0;
    glGenBuffers(1, (GLuint*)&(my_id));
    glBindBuffer(GL_ARRAY_BUFFER, my_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * 3, vertices, GL_STATIC_DRAW);

    int my_indices = 0;
    glGenBuffers(1, (GLuint*)&(my_indices));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * 36, indices, GL_STATIC_DRAW);

    glRotatef(0.1f, 1.0f, 1.0f, 0.0f);

    glEnableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, my_id);
    glVertexPointer(3, GL_FLOAT, 0, NULL);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

    //glDrawArrays(GL_TRIANGLES, 0, 8);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void ModuleScene_01::DrawCheckerCube()
{

    float3 vertices[] = {
{-1., -1., -1.}, {1., -1., -1.},
{-1., 1., -1.}, {1., 1., -1.},
{-1., -1., 1.}, {1., -1., 1.},
{-1., 1., 1.}, {1., 1., 1.}

    };

    int indices[] = {
       4,5,6,	5,7,6,
       5,1,7,	1,3,7,
       0,4,2,	4,6,2,
       6,7,2,	7,3,2,
       1,0,3,	0,2,3,
       0,1,4,    1,5,4
    };

    //int uv[] = {
    //    0,0,0,1,1,1,0,0,1,1,1,0,0,1,0,0,1,0,1,0,1,1,0,1,1,1,0,1,1,0,0,1,0,0,1,0,1,0,1,1,0,0,0,0,1,1,0,1,0,0,1,1,0,1,0,0,1,0,1,1,1,0,1,1,0,1,1,0,0,1,0,0,
    //
    //};
   
    int uv[] = {
        0, 0, 0, 1, 1, 1,
    };
    
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    uint my_id = 0;
    glGenBuffers(1, (GLuint*)&(my_id));
    glBindBuffer(GL_ARRAY_BUFFER, my_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8 * 3, vertices, GL_STATIC_DRAW);

    //glBindBuffer(GL_ARRAY_BUFFER, my_id);
    

    int my_indices = 0;
    glGenBuffers(1, (GLuint*)&(my_indices));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * 36, indices, GL_STATIC_DRAW);
    
    
   //glVertexAttribPointer()
    glBindTexture(GL_TEXTURE_2D, checkers_tex);

    glVertexPointer(2, GL_INT, 0, NULL);
    uint my_uv = 0;
    glGenBuffers(1, (GLuint*)&(my_uv));
    
    glBindBuffer(GL_TEXTURE_BUFFER, my_uv);
    glBufferData(GL_TEXTURE_BUFFER, sizeof(uint) * 6, uv, GL_STATIC_DRAW);
    
    glVertexPointer(3, GL_FLOAT, 0, NULL);
    
    
    

    glEnableClientState(GL_VERTEX_ARRAY);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_indices);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, my_uv);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);

    //glDrawArrays(GL_TRIANGLES, 0, 8);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void ModuleScene_01::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
}

bool ModuleScene_01::Save()
{
    //json_object_set_boolean(json_object(data), "Fullscreen", fullscreen);
    //json_object_set_boolean(json_object(data), "Vsync", vsync);
    //json_object_set_boolean(json_object(data), "Wireframe", boolWireframe);

    return true;
}









	