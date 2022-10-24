#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"

#include "glew/include/GL/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

ModuleTextures::ModuleTextures(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleTextures::~ModuleTextures()
{
}

bool ModuleTextures::Start()
{
   

	return true;
}

update_status ModuleTextures::Update(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleTextures::CleanUp()
{
	return true;
}

uint ModuleTextures::LoadCheckerTex()
{
   
    constexpr int check01 = 16;
    constexpr int check02 = 16;

    GLubyte checkerImage[check01][check02][4];
    for (int i = 0; i < check01; i++) {
        for (int j = 0; j < check02; j++) {
            int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
            checkerImage[i][j][0] = (GLubyte)c;
            checkerImage[i][j][1] = (GLubyte)c;
            checkerImage[i][j][2] = (GLubyte)c;
            checkerImage[i][j][3] = (GLubyte)255;
        }
    }



    uint my_text = 0;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &my_text);
    glBindTexture(GL_TEXTURE_2D, my_text);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, check01, check02,
        0, GL_RGBA, GL_UNSIGNED_BYTE, checkerImage);

    return my_text;
}
