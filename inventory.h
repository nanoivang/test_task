#ifndef INVENTORY_H
#define INVENTORY_H

#include <QObject>
#include <QTableWidget>

class QSoundEffect;
class QSqlTableModel;
class InventoryItemDelegate;

struct InventoryCell {
    int row;
    int column;
    int type;
    int count;
};

class Inventory : public QObject
{
    Q_OBJECT
public:
    Inventory();
    ~Inventory();

    void addItem(int row, int column, int type, int count);
    void removeItem(int row, int column, int type, int count);
    QList<InventoryCell*> getCells() { return mCells; }
signals:
    void itemCountChanged(int row, int column, int type, int count);
private:
    int rowCount = 3;
    int columnCount = 3;
    QList<InventoryCell *> mCells;

};

#endif // INVENTORY_H
