#include "ElementUI.h"
#include <list>
#include "GameObject.h"
#include "CanvasUI.h"

ElementUI::ElementUI()
{
}

ElementUI::ElementUI(ELEMENT_UI_TYPE element_type)
{
	type = element_type;
	rendered = true;
}

ElementUI::~ElementUI()
{
}

bool ElementUI::Start()
{
	return true;
}

bool ElementUI::Update()
{
	return true;
}

bool ElementUI::CleanUp()
{
	return true;
}

bool ElementUI::Draw()
{
	return true;
}

ELEMENT_UI_TYPE ElementUI::GetType() const
{
	return type;
}

void ElementUI::SetType(const ELEMENT_UI_TYPE& new_type)
{
	type = new_type;
}

CanvasUI* ElementUI::GetCanvas() const
{
	return canvas;
}

void ElementUI::SetState(const ELEMENT_UI_STATE& new_state)
{
	state = new_state;
}

ELEMENT_UI_STATE ElementUI::GetState() const
{
	return state;
}

void ElementUI::SetSelected(const bool& new_selected)
{
	selected = new_selected;
}

bool ElementUI::GetSelected() const
{
	return selected;
}
