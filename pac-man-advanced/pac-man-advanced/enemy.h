#pragma once
#include"tiempo-partida.h"
#include"mapa.h"
#include"utiles-consola.h"

#include <stdlib.h>
#include <time.h>

class Enemy
{
private:
	// Coordenadas de inicio, posicion y direccion
	COORD spawn;
	COORD position;
	COORD direction;
	// Dibujar el personaje con una X
	char character = 'X';
	// Al principio el tiempo que necesitamos para los powerup
	float powerup_countdown = 0;
	// Cuando se usa uno el tiempo que dura
	const float powerup_countdown_time = 15;
	// El color de los enemigos es rojo oscuro
	ConsoleUtils::COLOR	foreground = ConsoleUtils::COLOR::DARK_RED;
	ConsoleUtils::COLOR	background = ConsoleUtils::COLOR::BLACK;
	// El color de los powerup es cyan
	ConsoleUtils::COLOR	foreground_attack = ConsoleUtils::COLOR::DARK_RED;

	ConsoleUtils::COLOR	foreground_powerUp = ConsoleUtils::COLOR::CYAN;
	//Usa la funcion ramdondirection para moverse una posición aleatoriomente
	void RandomDirection();
public:
	// Enumeramos las funciones del enemigo
	enum ENEMY_STATE { ENEMY_NONE, ENEMY_KILLED, ENEMY_DEAD };
	Enemy();
	// Empieza en unas coordenadas
	Enemy(COORD _spawn);
	// Vamos pintando el mapa y borrando los powerup si los cojemos
	void Draw();
	void PowerUpPicked();
	ENEMY_STATE Update(Map* _map, COORD _player);
};

