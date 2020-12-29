#ifndef _UI_ELEMENT_H_
#define _UI_ELEMENT_H_

class CanvasUI;

enum ELEMENT_UI_TYPE
{
	NONE_TYPE = 0,
	CANVAS,
	BUTTON,
	IMAGE, 
	LABEL, 
	TEXT
};

enum ELEMENT_UI_STATE
{
	NONE_STATE = 0,
	PRESSED, // Mouse has pressed the button
	CLICKED, // Mouse is hovering WITH MOUSE BUTTON CLICKED
	HOVERED // Mouse is hovering WITHOUT MOUSE BUTTON CLICKED
};

class ElementUI
{
public:
	ElementUI();
	ElementUI(ELEMENT_UI_TYPE type);
	~ElementUI();

	virtual bool Start();
	virtual bool Update();
	virtual bool CleanUp();
	virtual bool Draw();

	CanvasUI* GetCanvas() const;

	ELEMENT_UI_TYPE GetType() const;
	void SetType(const ELEMENT_UI_TYPE& new_type);

	ELEMENT_UI_STATE GetState() const;
	void SetState(const ELEMENT_UI_STATE& new_state);
	
	bool GetSelected() const;
	void SetSelected(const bool& new_selected);

private:

	bool selected = false;
	bool rendered = true;	

	ELEMENT_UI_TYPE type = ELEMENT_UI_TYPE::NONE_TYPE;
	ELEMENT_UI_STATE state = ELEMENT_UI_STATE::NONE_STATE;
	
	CanvasUI* canvas = nullptr;

};

#endif
