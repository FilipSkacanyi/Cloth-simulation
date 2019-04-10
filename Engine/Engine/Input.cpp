#include "Input.h"



Input::Input()
{
}


Input::~Input()
{
}

void Input::init()
{
	for (int i = 0; i < 256; i++)
	{
		m_keys[i] = false;
	}
}

void Input::keyDown(unsigned int key)
{
	m_keys[key] = true;
}

void Input::keyUp(unsigned int key)
{
	m_keys[key] = false;
}

bool Input::IsKeyDown(unsigned int key)
{
	return m_keys[key];
}

Action Input::getAction()
{
	return m_action;
}

void Input::setAction(Action action)
{
	m_action = action;
}
