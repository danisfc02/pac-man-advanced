#pragma once

#include "utiles-consola.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Map
{
public:
	// Enumeramos el mapa poniendo que tiene que dibujar según que haya en ese punto
	enum MAP_TILES { VACIO = ' ', PARED = '#', PUNTOS = '.', MEJORA = '*' };
	// El color de fondo que le damos al ,mapa
	std::map<MAP_TILES, ConsoleUtils::COLOR> backgrounds;
	// El color de los personajes del mapa
	std::map<MAP_TILES, ConsoleUtils::COLOR> foregrounds;
	// La anchura del mapa (Quitar porque el mapa se hara por archivo)
	int Width = 44;
	// La altura del mapa
	int Height = 19;
	// Size es igual a  Altura por Anchura
	int Size = Width * Height;
	// Los puntos que quedan en el mapa
	int points;
	// Las coordenadas de aparición de nuestro personaje
	COORD spawn_player;
	//	Las coordenadas de aparición de los enemigos
	COORD spawn_enemy;
private:
	MAP_TILES* storedmap;
	int inline GetPos(int _x, int _y);
public:

	Map();

	~Map();

	//Función draw
	void Draw();
	// Devuelve el mapa pintado con sus parametros de x y y
	MAP_TILES GetTile(int _x, int _y);

	void SetTile(int _x, int _y, MAP_TILES _tile);
};