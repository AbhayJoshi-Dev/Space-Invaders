#include"Game.h"

//std::unique_ptr<AssetManager> m_assetManager = std::make_unique<AssetManager>();

int main(int argc, char* args[])
{
	Game game;
	game.GameLoop();

	return 0;
}