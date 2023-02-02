#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QObject>
#include <QLabel>
#include <QTableWidgetItem>

class QTableWidget;
class QTableWidgetItem;
class Item;
class InventoryItemDelegate;
class ItemWidget : public QTableWidget
{
    Q_OBJECT
public:
    ItemWidget(QWidget *parent = nullptr);
    ~ItemWidget();
    void showItem(int type);
    QList<Item*> getItemlist() { return mItems; }
    QTableWidgetItem *getWidgetItem();
protected:
    void updateGeometry();
private:
    void loadItems();
    QList<Item*> mItems;
    InventoryItemDelegate *mDelegate = nullptr;
    int cellSize = 64;
};

#endif // ITEMWIDGET_H
