#include "inventory.h"

Inventory::Inventory()
{
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            auto cell = new InventoryCell();
            cell->row = i;
            cell->column = j;
            cell->type = -1;
            cell->count = 0;
            mCells.append(cell);
        }
    }
}

Inventory::~Inventory()
{
    qDeleteAll(mCells);
}

void Inventory::addItem(int row, int column, int type, int count)
{
    int toAdd = count == -1 ? 0 : count;
    auto cell = mCells[row * 3 + column];
    cell->type = type;
    cell->count += toAdd;
    if (toAdd > 0) {
        emit itemCountChanged(row, column, type, cell->count);
    }
}

void Inventory::removeItem(int row, int column, int type, int count)
{
    auto cell = mCells[row * 3 + column];
    cell->count -= count;
    if (cell->count <= 0) {
        cell->type = -1;
        cell->count = 0;
    }
    emit itemCountChanged(row, column, cell->type, cell->count);
}
