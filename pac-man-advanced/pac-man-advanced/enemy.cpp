#include "Enemy.h"

// Función RamdonDirection
void Enemy::RandomDirection()
{
	// Conseguimos un efecto ramdon para elegir uno de los 4 casos para moverse en una direccion aleatoria
	direction = { 0,0 };
	int random = rand() % 4;
	switch (random)
	{
	case 0:
		direction.X = 1;
		break;
	case 1:
		direction.X = -1;
		break;
	case 2:
		direction.Y = 1;
		break;
	case 3:
		direction.Y = -1;
		break;
	}
}
Enemy::Enemy()
{
	// Usamos la funcion enemy para la reaparición de nuestro personaje
	spawn = { 0,0 };
	position = spawn;
	direction = { 0,0 };
}

Enemy::Enemy(COORD _spawn)
{
	// Usamos la funcion _spawn para que se genere en el mapa en sus coordenadas
	spawn = _spawn;
	position = _spawn;
	direction = { 0,0 };
}

void Enemy::Draw()
{
	// Dinujamos el enemigo en la posición y pintamos tanto el fondo como las paredes de los colores que ya seleccionamos anteriormente
	ConsoleUtils::Console_SetPos(position);
	ConsoleUtils::Console_SetColor(foreground, background);
	std::cout << character;
}
void Enemy::PowerUpPicked()
{
	// Cuando un enemigo coje un powerup mira el tiempo que llevamos de partida y lo suma al tiempo de countdown del powerup para saber cuanto dura
	powerup_countdown = TimeManager::getInstance().time + powerup_countdown_time;
}

Enemy::ENEMY_STATE Enemy::Update(Map* _map, COORD _player)
{
	RandomDirection();
	// Con esto pintamos en el mapa la nueva posicion usando el randomDirection que hicimos antes
	COORD newPosition = position;
	newPosition.X += direction.X;
	newPosition.Y += direction.Y;

	// Si la nueva posición es menor que 0 en X se pasa a la ultima posicion del ancho de la pantalla
	if (newPosition.X < 0)
	{
		newPosition.X = _map->Width - 1;
	}
	newPosition.X %= _map->Width;
	// Si la nueva posición es menor que 0 en Y se pasa a la ultima posicion del largo de la pantalla
	if (newPosition.Y < 0)
	{
		newPosition.Y = _map->Height - 1;
	}
	newPosition.Y %= _map->Height;
	// Si al moverse hay una pared la nueva posición sigue siendo la posición actual
	switch (_map->GetTile(newPosition.X, newPosition.Y))
	{
	case Map::MAP_TILES::PARED:
		newPosition = position;
		break;
	}
	position = newPosition;

	// Si no pasa nada el enemigo esta en NONE pero si el personaje le alcanza con un powerup para a estar DEAD y su posicion vuelve a estar KILLED en el spawn
	ENEMY_STATE state = ENEMY_STATE::ENEMY_NONE;
	if (position.X == _player.X && position.Y == _player.Y) {
		if (powerup_countdown <= TimeManager::getInstance().time) {
			state = ENEMY_STATE::ENEMY_DEAD;
		}
		else {
			position = spawn;
			state = ENEMY_STATE::ENEMY_KILLED;
		}
	}
	// Si el enemmigo tiene un powerup no pasa nada
	if (powerup_countdown <= TimeManager::getInstance().time) {
		foreground = foreground_attack;
	}
	else {
		foreground = foreground_powerUp;
	}
	return state;
}

