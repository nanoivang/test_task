#ifndef INVENTORYITEMDELEGATE_H
#define INVENTORYITEMDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>

class InventoryItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    InventoryItemDelegate(QObject *parent = nullptr);
    ~InventoryItemDelegate();
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void drawCount(bool draw);
private:
    bool mDrawCount = true;

};

#endif // INVENTORYITEMDELEGATE_H
