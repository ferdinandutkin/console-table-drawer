// lab4.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "TableDrawer.h"

typedef BOOL(WINAPI *SETCONSOLEFONT)(HANDLE, DWORD);
SETCONSOLEFONT SetConsoleFont;

const WORD colors[] =
{
	0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
	0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6, 0x7
};

namespace tabledraw {

	void customizeConsole(HANDLE& handle, WORD color) {
		HMODULE hmod = GetModuleHandleA("KERNEL32.DLL");
		SetConsoleFont = (SETCONSOLEFONT)GetProcAddress(hmod, "SetConsoleFont");
		
		if (!SetConsoleFont) {
			throw "ERROR";
		}

		SetConsoleFont(handle, 3);
		SetConsoleTextAttribute(handle, color);
	}

	void print(HANDLE& handle, COORD coord, WORD color, const char* primitive = " ") {
		customizeConsole(handle, color);
		SetConsoleCursorPosition(handle, coord);

		std::cout << primitive << std::endl;
	}

	void print(HANDLE& handle, COORD coord, const char* primitive = " ") {
		SetConsoleCursorPosition(handle, coord);

		std::cout << primitive << std::endl;
	}

	void printColumnRowData(HANDLE& handle, COORD coord, const char* fieldValue) {
		short fieldValueX = coord.X + LEFT_HORIZONTAL_PADDING;
		short fieldValueY = coord.Y;

		print(handle, { fieldValueX, fieldValueY }, colors[5], fieldValue);
	}

	void printColumnRow(HANDLE& handle, short x, short y, std::vector<const char*> fieldValues) {
		for (short j = 0; j < (short)fieldValues.size(); j++)
		{
			short cellX = COLUMN_COORD_X(x, j);

			print(handle, { cellX, y }, colors[3]);
			printColumnRowData(handle, { cellX + LEFT_HORIZONTAL_PADDING, y }, fieldValues[j]);
		}

		print(handle, { COLUMN_COORD_X(x, (short)fieldValues.size()), y }, colors[3]);
	}

	void printTable(HANDLE& handle, COORD coord, WORD color, std::vector<std::vector<const char*>> fields) {
		short rowCount = (short)fields.size();
		short columnCount = (short)fields[0].size();
		short tableWidth = columnCount * COLUMN_SIZE + 1;
		short x = coord.X;
		short y = coord.Y;

		print(handle, coord, color, LINE(tableWidth));

		for (short i = 0; i < rowCount; i++)
		{
			printColumnRow(handle, x, ROW_COORD_Y(y, i), fields[i]);
			print(handle, { x, ROW_LINE_COORD_Y(y, i) }, color, LINE(tableWidth));
		}

		print(handle, { coord.X, coord.Y + rowCount * 2 }, color, LINE(tableWidth));
	}
}
