#include "PanelViewport.h"

PanelViewport::PanelViewport()
{
}

PanelViewport::~PanelViewport()
{
}

bool PanelViewport::Start()
{
	return true;
}

bool PanelViewport::PreUpdate()
{
	return true;
}

bool PanelViewport::PostUpdate()
{
	return true;
}

bool PanelViewport::CleanUp()
{
	return true;
}

void PanelViewport::ChooseCamera(ComponentCamera* camera)
{
}

void PanelViewport::PrintTexture(uint tex)
{
}
