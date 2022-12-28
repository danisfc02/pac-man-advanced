#include "mapa.h"

Map::Map()
{
	// Aqui generamos el archivo de texto para cargar el mapa
	std::string filePath;
	std::cout << "Escribe mapa de archivo:" << std::endl;
	std::cin >> filePath;
	std::ifstream file(filePath);
	std::string line;
	std::vector<std::string> lines;
	while (std::getline(file, line))
	{
		lines.push_back(line);
	}
	// Si no ponemos ninguno estos son los valores del mapa por defecto
	file.close();
	Width = 0;
	Height = 0;
	Size = 0;
	std::vector<std::string> Map_Load;

	for (size_t i = 0; i < lines.size(); i++)
	{
		if (i == 0)
		{
			std::string WidthNum;
			std::string HeightNum;
			int commaCount = 0;
			for (size_t j = 0; j < lines[i].size(); j++)
			{
				if (lines[i][j] == ',')
				{
					commaCount++;
				}
				else
				{
					if (commaCount == 0)
					{
						WidthNum += lines[i][j];
					}
					else
					{
						HeightNum += lines[i][j];
					}
				}
			}
			Width = std::stoi(WidthNum);
			Height = std::stoi(HeightNum);
			Size = Width * Height;
		}
		else
		{
			Map_Load.push_back(lines[i]);
		}
	}
	// Ponemos el tamaño, largo y ancho de el mapa
	std::cout << "Map: " << Size << std::endl;
	std::cout << "  Width: " << Width << std::endl;
	std::cout << "  Height: " << Height << std::endl;
	// Aquí cargamos el mapa
	for (size_t i = 0; i < Map_Load.size(); i++)
	{
		std::cout << Map_Load[i] << std::endl;
	}
	storedmap = new MAP_TILES[Size];
	points = 0;
	int x = 0;
	int y = 0;
	char tile = ' ';
	for (size_t i = 0; i < Size; i++)
	{
		// En las posiciones donde haya enemigos, puntos o player se ponen un empty
		x = i % Width;
		y = i / Width;
		tile = Map_Load[y][x];
		switch (tile)
		{
		case MAP_TILES::PUNTOS:
			points++;
			storedmap[i] = (MAP_TILES)tile;
			break;
		case 'P':
			spawn_player.X = x;
			spawn_player.Y = y;
			storedmap[i] = MAP_TILES::VACIO;
			break;
		case 'E':
			spawn_enemy.X = x;
			spawn_enemy.Y = y;
			storedmap[i] = MAP_TILES::VACIO;
			break;
		default:
			storedmap[i] = (MAP_TILES)tile;
			break;
		}
	}
	foregrounds[MAP_TILES::VACIO] = ConsoleUtils::COLOR::BLACK;
	foregrounds[MAP_TILES::PARED] = ConsoleUtils::COLOR::DARK_BLUE;
	foregrounds[MAP_TILES::PUNTOS] = ConsoleUtils::COLOR::DARK_YELLOW;
	foregrounds[MAP_TILES::MEJORA] = ConsoleUtils::COLOR::DARK_YELLOW;
	backgrounds[MAP_TILES::VACIO] = ConsoleUtils::COLOR::BLACK;
	backgrounds[MAP_TILES::PARED] = ConsoleUtils::COLOR::DARK_BLUE;
	backgrounds[MAP_TILES::PUNTOS] = ConsoleUtils::COLOR::BLACK;
	backgrounds[MAP_TILES::MEJORA] = ConsoleUtils::COLOR::BLACK;
}
// Al usar un mapa por archivo se borren los ajustes de antes
Map::~Map()
{
	delete[] storedmap;
}

void Map::Draw()
// Dibujamos el mapa
{
	for (size_t i = 0; i < Size; i++)
	{
		if (i % Width == 0 && i > 0)
		{
			ConsoleUtils::Console_SetColor();
			std::cout << ' ' << std::endl;
		}
		MAP_TILES tile = storedmap[i];
		ConsoleUtils::Console_SetColor(foregrounds[tile], backgrounds[tile]);
		std::cout << (char)tile;
	}
	ConsoleUtils::Console_SetColor();
}

int inline Map::GetPos(int _x, int _y)
{
	int pos = _y * Width + _x;
	if (Size <= pos)
		return Size - 1;
	return pos;
}

Map::MAP_TILES Map::GetTile(int _x, int _y)
{
	int pos = GetPos(_x, _y);
	return storedmap[pos];
}

void Map::SetTile(int _x, int _y, MAP_TILES _tile)
{
	int pos = GetPos(_x, _y);
	storedmap[pos] = _tile;
}