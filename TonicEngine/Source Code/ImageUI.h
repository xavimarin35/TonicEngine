#ifndef _IMAGE_UI_H_
#define _IMAGE_UI_H_

#include "ElementUI.h"
#include "ModuleUserInterface.h"

class ComponentImage;
class ResourceTexture;
class ContainerUI;

class ImageUI : public ElementUI
{
public:
	ImageUI(ComponentImage* image);
	~ImageUI();

	bool Start();
	bool Update();
	bool CleanUp();
	bool Draw();

	void DrawImageTexture();

	ContainerUI* GetContainer();
	void ResizeImage(float2 size);
	void CreateContainerImage();

	void SetImageID(int new_img_id);
	int GetImageID();
	void SetTextureToImageUI(ResourceTexture* new_img_tex);
	ResourceTexture* GetMaterial();

	ComponentImage* Cimage = nullptr;
	
private:

	ContainerUI* container_image = nullptr;
	ResourceTexture* image_texture = nullptr;
	int img_id = 0;

};

#endif
