#include "ImageUI.h"
#include "ContainerUI.h"

ImageUI::ImageUI(ComponentImage* image)
{
	Cimage = image;
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

void ImageUI::DrawImageTexture()
{
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
	image_tex = new_img_tex;
}

ResourceTexture* ImageUI::GetMaterial()
{
	return image_texture;
}
