#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>

namespace ConsoleUtils
{
	// Enumeramos los colores usados en el jeugo
	enum COLOR { BLACK, DARK_BLUE, DARK_GREEN, DARK_CYAN, DARK_RED, DARK_MAGENTA, DARK_YELLOW, LIGHT_GREY, DARK_GREY, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE };

	// Ponemos que el color de la consola y del fondo sea negro y del mapa blanco
	inline void Console_SetColor(COLOR _foreground = COLOR::WHITE, COLOR _background = COLOR::BLACK)
	{
		HANDLE colorencargado = GetStdHandle(STD_OUTPUT_HANDLE);
		WORD colores = (_background << 4) | _foreground;
		SetConsoleTextAttribute(colorencargado, colores);
	}
	// Ponemos el cursor de la pantalla en un punto especifico
	inline void Console_SetPos(COORD _pos)
	{
		HANDLE colorencargado = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(colorencargado, _pos);
	}
	// Ponemos la coordenada en x y y
	inline void Console_SetPos(int _x, int _y)
	{
		COORD pos = { _x,_y };
		Console_SetPos(pos);
	}
	// MArcamos la coordenada en la que empieza a crearnos el mapa y los colores en los que lo dibuja
	inline void Console_ClearCharacter(COORD _topleft = { 0,0 }, char _character = ' ', COLOR _foreground = COLOR::WHITE, COLOR _background = COLOR::BLACK)
	{
		WORD color = (_background << 4) | _foreground;
		CONSOLE_SCREEN_BUFFER_INFO pantalla;
		DWORD written;
		HANDLE colorencargado = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(colorencargado, &pantalla);
		FillConsoleOutputCharacterA(colorencargado, _character, pantalla.dwSize.X * pantalla.dwSize.Y, _topleft, &written);
		FillConsoleOutputAttribute(colorencargado, color, pantalla.dwSize.X * pantalla.dwSize.Y, _topleft, &written);
		Console_SetPos(_topleft);
	}
	inline bool KeyPressed(int _key)
	{
		return GetKeyState(_key) & 0x8000;
	}

	inline bool KeyPressed(char _key)
	{
		return GetKeyState(_key) & 0x8000;
	}

	inline bool KeyToggled(int _key)
	{
		return GetKeyState(_key) & 1;
	}

	inline bool KeyToggled(char _key)
	{
		return GetKeyState(_key) & 1;
	}
};