#pragma once

namespace Dacia
{
	namespace Skeletons
	{
		struct Noncopyable
		{
			Noncopyable()									= default;
			Noncopyable(Noncopyable const &)				= delete;
			Noncopyable & operator=(Noncopyable const &)	= delete;
		};

		struct Immovable
		{
				Immovable()									= default;
				Immovable(Immovable &&)						= delete;
				Immovable & operator =(Immovable &&)		= delete;
		};

		struct Unique
		{
				Unique()									= default;
				Unique(const Unique &)						= delete;
				Unique(Unique &&)							= delete;
				Unique & operator=(Unique const &)			= delete;
				Unique & operator=(Unique &&)				= delete;
		};

		struct Command
		{
			void virtual Action() = 0;
			void inline operator()()
			{
				this->Action();
			}
		};

		struct Iterator
		{

		};

		struct Observer
		{
			void virtual Update() = 0;
			void virtual Notify() = 0;
		};
	}
}