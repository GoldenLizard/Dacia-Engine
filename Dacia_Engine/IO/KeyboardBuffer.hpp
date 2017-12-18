#pragma once

#include <Utilities\Common.hpp>
#include <Utilities\EngineUtilities.hpp>

namespace Dacia
{
	enum class KeyAction : byte
	{
		PRESS, HOLD, RELEASE
	};

	struct Key
	{
		explicit Key(uint8 id);

		void OnAction(KeyAction);

		std::unique_ptr<Skeletons::Command> onKeyPressed;
		std::unique_ptr<Skeletons::Command> onKeyHold;
		std::unique_ptr<Skeletons::Command> onKeyRelease;

		uint8 id;
		bool  isHolded;
	};

	class KeyboardBuffer
	{
		public:

		private:

			std::array<Key, 0xff> m_keys;
	};

}
