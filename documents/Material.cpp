#include "Material.h"



Material::Material(std::vector<Texture>& texture)
{
	textures = texture;
}

Material::~Material()
{
}
