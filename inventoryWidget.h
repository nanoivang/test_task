#ifndef INVENTORYWIDGET_H
#define INVENTORYWIDGET_H

#include <QObject>
#include <QTableWidget>

class QSoundEffect;
class QSqlTableModel;
class Item;
class Inventory;
class InventoryItemDelegate;
class InventoryWidget : public QTableWidget
{
public:
    InventoryWidget(int rows, int columns, QWidget *parent = 0);
    ~InventoryWidget();
    void setInventory(Inventory *);
    void setItemList(QList<Item*>);
    Inventory * getInventory() { return mInventory; }
protected:
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);
private:
    void loadInventory();
    int mCells;
    QList<Item*> mItems;
    Inventory *mInventory = nullptr;
    InventoryItemDelegate *mDelegate = nullptr;
    QSoundEffect *mSoundEffect = nullptr;
    int cellSize = 64;
};

#endif // INVENTORYWIDGET_H
