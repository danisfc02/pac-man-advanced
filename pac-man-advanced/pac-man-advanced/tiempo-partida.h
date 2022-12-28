#pragma once
#include <chrono>
class TimeManager
{
	// Cuando empieza el contador del tiempo de juego y como se va actualizando
	std::chrono::high_resolution_clock::time_point start
		= std::chrono::high_resolution_clock::now();
public:

	// Cada vez que pasa el tiempo se va actualizando
	unsigned int frameCount;
	float time;
	float deltaTime;

	static TimeManager& getInstance();

	void NextFrame();
};
