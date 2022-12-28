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
