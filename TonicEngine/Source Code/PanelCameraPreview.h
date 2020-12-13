#ifndef __PANELCAMERAPREVIEW_H__
#define __PANELCAMERAPREVIEW_H__

#include "Application.h"
#include "PanelManager.h"
#include "TextureImporter.h"
#include "Viewport.h"

class PanelCameraPreview : public PanelManager
{
public:
	PanelCameraPreview();
	~PanelCameraPreview();

	bool Start();
	bool Draw();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	Viewport* viewport_tex = nullptr;
	ImVec2 current_size = { 1024, 720 };
	ImVec2 new_size;

};

#endif