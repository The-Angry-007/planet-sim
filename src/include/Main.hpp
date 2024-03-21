#pragma once
#include "include/Gui.hpp"
#include "include/Path.hpp"
#include "include/Planet.hpp"
#include "include/inputHandler.hpp"
class Planet;
class Path;
extern sf::RenderWindow* window;
//the constant that determines the strength of gravity
extern float G;
extern float scale;
extern int planetId;
extern sf::Vector2f offset;
extern float universalDensity;
extern InputHandler inp;
extern std::vector<Planet*> planets;
extern sf::Clock* timer;
extern Gui gui;

void SolvePlanetCollisions(std::vector<Planet*>& planets, bool joinpaths, std::vector<int>* indices = new std::vector<int>());
std::vector<Path*> getPosesInFuture(int stepsPerSec, float numSecs, std::vector<Planet*> planets, Planet* extraPlanet = nullptr);
