#pragma once
#include "Texture.h"
#include <vector>
#include "Globals.h"


class Material
{
public:
	
	Material(std::vector<Texture>& texture);
	~Material();
	

	std::vector<Texture> textures;

	float3 ambient;
	float3 diffuse;
	float3 specular;
	float shininess;
};