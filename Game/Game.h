#pragma once

namespace Game {
	class Game
	{
	public:
		Game();
		~Game();
		void Tick();
	protected:
		int tick = 0;
	};
}

