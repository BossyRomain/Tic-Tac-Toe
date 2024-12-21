#include "board/board.hpp"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

#define EMPTY_CELL 0

Board::Board() {
    m_rows = 3;
    m_cols = 3;

    m_tiles = new int*[m_rows];
    for(int r = 0; r < m_rows; r++) {
        m_tiles[r] = new int[m_cols];

        for(int c = 0; c < m_cols; c++) {
            m_tiles[r][c] = EMPTY_CELL;
        }
    }
}

Board::~Board() {
    deleteTiles();
}

int Board::getRows() const {
    return m_rows;
}

int Board::getCols() const {
    return m_cols;
}

int Board::getTile(Vector2i pos) const {
    return coordsIn(pos) ? m_tiles[pos.y][pos.x] : -1;
}

void Board::setRows(int rows) {
    if(rows > 0) {
        updateTiles(rows, m_cols);
    }
}

void Board::setCols(int cols) {
    if(cols > 0) {
        updateTiles(m_rows, cols);
    }
}

void Board::setTile(Vector2i pos, int value) {
    if(coordsIn(pos)) {
        m_tiles[pos.y][pos.x] = value;
    }
}

void Board::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_rows"), &Board::getRows);
    ClassDB::bind_method(D_METHOD("set_rows", "rows"), &Board::setRows);

    ClassDB::bind_method(D_METHOD("get_cols"), &Board::getCols);
    ClassDB::bind_method(D_METHOD("set_cols", "cols"), &Board::setCols);

    ClassDB::bind_method(D_METHOD("get_tile"), &Board::getTile);
    ClassDB::bind_method(D_METHOD("set_tile", "pos", "val"), &Board::setTile);

    ADD_PROPERTY(PropertyInfo(Variant::INT, "rows"), "set_rows", "get_rows");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "cols"), "set_cols", "get_cols");
}

bool Board::coordsIn(Vector2i pos) const {
    return pos.x >= 0 && pos.x < m_cols && pos.y >= 0 && pos.y < m_cols;
}

void Board::deleteTiles() {
    for(int r = 0; r < m_rows; r++) {
        delete m_tiles[r];
    }
    delete m_tiles;
}

void Board::updateTiles(int newRows, int newCols) {
    int** newTiles = new int*[newRows];

    for(int r = 0; r < newRows; r++) {
        newTiles[r] = new int[newCols];

        for(int c = 0; c < newCols; c++) {
            if(r >= m_rows || c >= m_cols) {
                newTiles[r][c] = EMPTY_CELL;
            } else {
                newTiles[r][c] = m_tiles[r][c];
            }
        }
    }

    deleteTiles();
    m_tiles = newTiles;
    m_rows = newRows;
    m_cols = newCols;
}