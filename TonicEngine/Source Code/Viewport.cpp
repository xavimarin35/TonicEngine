#include "Viewport.h"

Viewport::Viewport()
{
}

Viewport::~Viewport()
{
}

bool Viewport::Start()
{
	return true;
}

bool Viewport::PreUpdate()
{
	return true;
}

bool Viewport::PostUpdate()
{
	return true;
}

bool Viewport::CleanUp()
{
	return true;
}

void Viewport::ChooseCamera(ComponentCamera* camera)
{
}

void Viewport::PrintTexture(uint tex)
{
}
