#ifndef __C_MESH_H__
#define __C_MESH_H__

#include "Component.h"
#include "glmath.h"

class GameObject;



class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject* gameObject, bool active);
	virtual ~ComponentMesh();

	void Draw();
	void DrawFaceNormals(GameObject* comp);
	void DrawVertexNormals(Component* comp);

public:

	bool showFaceNormals = false;
	
	/*meshData data;*/

};

#endif
