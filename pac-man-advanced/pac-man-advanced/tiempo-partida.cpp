#include "tiempo-partida.h"

TimeManager& TimeManager::getInstance()
{
	static TimeManager timeManager;
	return timeManager;
}
// Cada vez que pasa el tiempo nos lo va contando en milisegundos y lo va sumando al tiempo de juego
void TimeManager::NextFrame()
{
	frameCount++;
	auto elapsed = std::chrono::high_resolution_clock::now() - start;
	deltaTime = (float)std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count() / (float)1000;
	time += deltaTime;
	start = std::chrono::high_resolution_clock::now();
}
