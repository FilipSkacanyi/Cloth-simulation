#pragma once

enum Action
{
	KEY_PRESSED,
	KEY_RELEASED,
	NONE
};

class Input
{
public:
	Input();
	~Input();

	void init();

	void keyDown(unsigned int key);
	void keyUp(unsigned int key);

	bool IsKeyDown(unsigned int key);

	Action getAction();
	void setAction(Action action);

private:
	bool m_keys[256];
	Action m_action = Action::NONE;
};

