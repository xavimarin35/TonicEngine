#include "ImageUI.h"

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
	return true;
}

void ImageUI::DrawImageTexture()
{
}
