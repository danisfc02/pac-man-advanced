#pragma once
#include "mapa.h"
#include "player.h"
#include "tiempo-partida.h"
class ProgramInfo
{
public:
	// Para crear el mapa usar la función Map
	Map pacman_map = Map();
	// Los "ENEMY" se llaman enemigos
	std::vector<Enemy> enemigos;

	Player player = Player(pacman_map.spawn_player);
	USER_INPUTS input = USER_INPUTS::NONE;
	// Cuando empezamos la funcion run es verdadera y las funciones win y loose son falsas
	bool run = true;
	bool win = false;
	bool loose = false;
};

