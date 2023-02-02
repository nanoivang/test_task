#include "inventoryitemdelegate.h"
#include "item.h"

#include <QPainter>

InventoryItemDelegate::InventoryItemDelegate(QObject * parent)
    : QStyledItemDelegate(parent)
{

}

InventoryItemDelegate::~InventoryItemDelegate()
{

}

void InventoryItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const //отрисовка QImage(ImagePath) в QTableWidget
{
    QStyledItemDelegate::paint(painter, option, QModelIndex());

    QImage image = QImage(index.data(Qt::UserRole + 1).toString());
    if (!image.isNull()) {
        painter->drawImage(option.rect, image);
    }
    int count = index.data(Qt::UserRole + 2).value<int>();
    if (count > 0 && mDrawCount) {
        QPoint p = QPoint(option.rect.x() + option.rect.width() - 10, option.rect.y() + option.rect.height() - 5);
        painter->drawText(p, QString::number(count));
    }
}

void InventoryItemDelegate::drawCount(bool draw)
{
    mDrawCount = draw;
}
