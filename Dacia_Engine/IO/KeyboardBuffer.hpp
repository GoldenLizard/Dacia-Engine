#pragma once

#include <Utilities\Common.hpp>
#include <Utilities\EngineUtilities.hpp>

namespace Dacia
{
	enum class KeyAction : byte
	{
		PRESS	= 1 << 0, 
		HOLD	= 1 << 1, 
		RELEASE = 1 << 2
	};

	struct Key
	{
		explicit inline Key(uint8 id, 
			std::initializer_list<std::pair<KeyAction,Skeletons::Command>>);

		void OnAction(KeyAction);

		std::unique_ptr<Skeletons::Command> onKeyPressed;
		std::unique_ptr<Skeletons::Command> onKeyHold;
		std::unique_ptr<Skeletons::Command> onKeyRelease;

		uint8 id;
	};

	class KeyboardBuffer
	{
		public:

			KeyboardBuffer();
			void TriggerKey(byte keyID);

		private:

			std::array<Key, 0xff> m_keys;
	};

}
