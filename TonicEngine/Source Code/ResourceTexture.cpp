#include "ResourceTexture.h"
#include "TextureImporter.h"

bool ResourceTexture::LoadInMemory()
{
	return App->tex_imp->LoadTextureFromLibrary(this);
}

void ResourceTexture::ReleaseMemory()
{
}
