#include "itemwidget.h"
#include "item.h"
#include "inventoryitemdelegate.h"
#include "dbcontroller.h"

#include <QTableWidgetItem>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QHeaderView>

ItemWidget::ItemWidget(QWidget *parent)
    : QTableWidget(parent)
    , mDelegate(new InventoryItemDelegate(this))
{
    setRowCount(1);
    setColumnCount(1);

    setDragEnabled(true);

    mDelegate->drawCount(false);
    setItemDelegate(mDelegate);

    auto _vHeader = verticalHeader();
    auto _hHeader = horizontalHeader();

    _vHeader->setHidden(true);
    _vHeader->setSectionResizeMode(QHeaderView::Fixed);
    _vHeader->setDefaultSectionSize(cellSize);

    _hHeader->setHidden(true);
    _hHeader->setSectionResizeMode(QHeaderView::Fixed);
    _hHeader->setDefaultSectionSize(cellSize);

    setFixedSize((cellSize + 1) * rowCount(), (cellSize + 1) * columnCount());

    loadItems();
}

ItemWidget::~ItemWidget()
{
    qDeleteAll(mItems);
}

void ItemWidget::showItem(int type)
{
    for (auto item : mItems) {
        if (item->getType() == type) {
            auto _widgetItem = new QTableWidgetItem();
            _widgetItem->setData(Qt::UserRole + 1, item->getImagePath());
            setItem(0, 0, _widgetItem);
            break;
        }
    }
}

void ItemWidget::loadItems()
{
    mItems = dbController::getInstance()->getItems();
}

void ItemWidget::updateGeometry()
{
    if (mItems.size() <= rowCount() * columnCount()) {
        return;
    }
    setColumnCount(columnCount() + 1);
    setFixedWidth((cellSize + 1) * columnCount());
}
