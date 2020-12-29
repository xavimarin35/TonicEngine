#ifndef _COMPONENT_IMAGE_H_
#define _COMPONENT_IMAGE_H_

#include "Component.h"

class ElementUI;
class ImageUI;

class ComponentImage : public Component
{
public:

	ComponentImage(GameObject* parent);
	~ComponentImage();

	bool Start();
	bool Update();
	bool CleanUp();
	void Draw();
	void DrawInspector();

private:

	ImageUI* image = nullptr;


};

#endif
