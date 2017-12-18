#include "KeyboardBuffer.hpp"

void Dacia::Key::OnAction(KeyAction act)
{
	switch (act)
	{
		case KeyAction::PRESS:
		{
			onKeyPressed->Action();
		}

		case KeyAction::RELEASE:
		{
			onKeyRelease->Action();
		}

		case KeyAction::HOLD:
		{
			onKeyHold->Action();
		}

		default: return;
	}
}
