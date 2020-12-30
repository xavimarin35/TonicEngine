#include "ComponentImage.h"
#include "ImageUI.h"

ComponentImage::ComponentImage(GameObject* parent) : Component(COMPONENT_TYPE::IMAGE_UI, parent)
{
	type = COMPONENT_TYPE::IMAGE_UI;
	object = parent;

	image = new ImageUI(this);
}

ComponentImage::~ComponentImage()
{
}

bool ComponentImage::Start()
{
	return true;
}

bool ComponentImage::Update()
{
	return true;
}

bool ComponentImage::CleanUp()
{
	return true;
}

void ComponentImage::Draw()
{
}

void ComponentImage::DrawInspector()
{
}
