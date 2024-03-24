#pragma once
class Game
{
public:
	std::string savePath;
	bool paused;
	void Update(double dt);
	void Render();
	void TogglePaused();
	Game();
	~Game();
};