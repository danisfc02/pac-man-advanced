#pragma once
#include "utiles-consola.h"
#include "mapa.h"
#include "Enemy.h"
#include <vector>

// Enumeramos los movimientos que nuestro persoanje va a hacer
enum USER_INPUTS { NONE, UP, DOWN, RIGHT, LEFT, QUIT };
class Player
{
private:
	// Coordenadas de aparición y dirección
	COORD spawn;
	COORD direction;
	// Se muestgra al personaje con una "O"
	char character = 'O';
	// Pintar el personaje en amarillo y el fondo en negro
	ConsoleUtils::COLOR foreground = ConsoleUtils::COLOR::YELLOW;
	ConsoleUtils::COLOR background = ConsoleUtils::COLOR::BLACK;

	// Puede cojer 25 powers up
	const int POWERUP_PICKED = 10;
public:
	// Posición del personaje
	COORD position;
	// Tenemos 3 vidas
	int vidas = 3;
	// Tenemos 0 puntos
	int points = 0;
	// Empieza en la coordenada de spawn y usa el Update y el Draw para mover a nuestro personaje
	Player(COORD _spawn);
	void Update(Map* _map, USER_INPUTS input, std::vector<Enemy>* enemies);
	void Draw();
};
