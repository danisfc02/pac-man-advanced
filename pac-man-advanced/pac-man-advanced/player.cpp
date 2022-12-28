#include "Player.h"
// Coordenadas de spawn del personaje
Player::Player(COORD _spawn)
{
    spawn = _spawn;
    position = _spawn;
    direction = { 0,0 };
}

void Player::Update(Map* _map, USER_INPUTS input, std::vector<Enemy>* enemies)
{
    COORD newPosition = position;
    // Movimiento del persoanje
    switch (input)
    {
    case UP:
        newPosition.Y--;
        break;
    case DOWN:
        newPosition.Y++;
        break;
    case RIGHT:
        newPosition.X++;
        break;
    case LEFT:
        newPosition.X--;
        break;
    }
    // Si pasa de los extremos mandar al otro
    if (newPosition.X < 0)
    {
        newPosition.X = _map->Width - 1;
    }
    newPosition.X %= _map->Width;
    if (newPosition.Y < 0)
    {
        newPosition.Y = _map->Height - 1;
    }
    newPosition.Y %= _map->Height;

    switch (_map->GetTile(newPosition.X, newPosition.Y))
    {
        // Si hay una pared no se mueve
    case Map::MAP_TILES::PARED:
        newPosition.Y = position.Y;
        newPosition.X = position.X;
        break;
        // Si coje un punto remplaza su posicion
    case Map::MAP_TILES::PUNTOS:
        _map->points--;
        points++;
        _map->SetTile(newPosition.X, newPosition.Y, Map::MAP_TILES::VACIO);
        break;
        // Si cojes el powerup los enemigos pasan a ser matables y te pones en la posicon del powerup
    case Map::MAP_TILES::MEJORA:
        points += POWERUP_PICKED;
        for (size_t i = 0; i < enemies->size(); i++)
        {
            enemies->at(i).PowerUpPicked();
        }
        _map->SetTile(newPosition.X, newPosition.Y, Map::MAP_TILES::VACIO);
        break;
    }

    position = newPosition;
}

void Player::Draw()
// Vamos dibujando el mapa
{
    ConsoleUtils::Console_SetPos(position);
    ConsoleUtils::Console_SetColor(foreground, background);
    std::cout << character;
}
