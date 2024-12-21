#ifndef BOARD_HPP
#define BOARD_HPP

#include <godot_cpp/core/object.hpp>

namespace godot {

class Board: public Object {
	GDCLASS(Board, Object)

public:

	Board();

	~Board();

	int getRows() const;

	int getCols() const;

	int getTile(Vector2i pos) const;

	void setRows(int rows);

	void setCols(int cols);

	void setTile(Vector2i pos, int value);

protected:

	static void _bind_methods();

private:

	bool coordsIn(Vector2i pos) const;

	void deleteTiles();

	void updateTiles(int newRows, int newCols);

	int m_rows;

	int m_cols;

	int** m_tiles;
};

}

#endif