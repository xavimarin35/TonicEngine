#ifndef _IMAGE_UI_H_
#define _IMAGE_UI_H_

#include "ElementUI.h"

class ComponentImage;
class ResourceTexture;

class ImageUI : public ElementUI
{
public:
	ImageUI(ComponentImage* image);
	~ImageUI();

	bool Start();
	bool Update();
	bool CleanUp();
	bool Draw();

	ComponentImage* Cimage = nullptr;
	ResourceTexture* image_tex = nullptr;

private:


};

#endif
