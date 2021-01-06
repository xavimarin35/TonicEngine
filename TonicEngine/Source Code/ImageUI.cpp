#include "ImageUI.h"
#include "ContainerUI.h"
#include "glew/include/GL/glew.h"
#include "ModuleGUI.h"
#include "ModuleResources.h"

ImageUI::ImageUI(ComponentImage* image)
{
	CreateContainerImage();
	Cimage = image;

	image_texture = (ResourceTexture*)App->resources->Get(App->resources->GetNewFile("Assets/Others/test.png"));
	image_texture->LoadInMemory();
}

ImageUI::~ImageUI()
{
}

bool ImageUI::Start()
{
	return true;
}

bool ImageUI::Update()
{
	return true;
}

bool ImageUI::CleanUp()
{
	return true;
}

bool ImageUI::Draw()
{
	DrawImageTexture();

	return true;
}

void ImageUI::DrawImageTexture() // THERE'S AN ERROR IN glDrawElements() THAT I CAN'T FIX OMG
{
	App->ui->UseUIRenderSettings();

	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, container_image->GetContainerMesh()->data.id_vertex);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	if (image_texture != nullptr)
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, container_image->GetContainerMesh()->data.id_tex_coords);

		glBindTexture(GL_TEXTURE_2D, image_texture->tex.id);

		glTexCoordPointer(3, GL_FLOAT, 0, NULL);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, container_image->GetContainerMesh()->data.id_index);
	glDrawElements(GL_TRIANGLES, container_image->GetContainerMesh()->data.num_index, GL_UNSIGNED_INT, NULL); 

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (image_texture)
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glDisableClientState(GL_VERTEX_ARRAY);
}

ContainerUI* ImageUI::GetContainer()
{
	return container_image;
}

void ImageUI::ResizeImage(float2 size)
{
	
}

void ImageUI::CreateContainerImage()
{
	container_image = new ContainerUI();
}

void ImageUI::SetImageID(int new_img_id)
{
	img_id = new_img_id;
}

int ImageUI::GetImageID()
{
	return img_id;
}

void ImageUI::SetTextureToImageUI(ResourceTexture* new_img_tex)
{
	image_texture = new_img_tex;
}

ResourceTexture* ImageUI::GetTexture()
{
	return image_texture;
}
