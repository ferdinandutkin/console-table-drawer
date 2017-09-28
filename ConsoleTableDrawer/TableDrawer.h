#pragma once

#define COLUMN_SIZE 12
#define DRAW_UNIT_WIDTH 1
#define COLUMN_COORD_X(x, n) x + n * COLUMN_SIZE
#define ROW_LINE_COORD_Y(y, n) y + n * 2
#define ROW_COORD_Y(y, n) ROW_LINE_COORD_Y(y, n) + 1
#define LEFT_HORIZONTAL_PADDING 1
#define LINE(x) std::string(x,' ').c_str()

namespace tabledraw {
	void printTable(HANDLE& handle, COORD coord, WORD color, std::vector<std::vector<const char*>> fields);
}