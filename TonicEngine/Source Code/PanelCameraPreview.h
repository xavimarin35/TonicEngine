#ifndef __PANELCAMERAPREVIEW_H__
#define __PANELCAMERAPREVIEW_H__

#include "Application.h"
#include "PanelManager.h"
#include "TextureImporter.h"

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

};

#endif