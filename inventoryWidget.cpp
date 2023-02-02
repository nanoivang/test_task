#include "inventoryWidget.h"
#include "inventory.h"
#include "dbcontroller.h"
#include "inventoryitemdelegate.h"
#include "item.h"

#include <QHeaderView>
#include <QMouseEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QSoundEffect>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlTableModel>


InventoryWidget::InventoryWidget(int rows, int columns, QWidget *parent)
    : QTableWidget(parent)
    , mDelegate(new InventoryItemDelegate(this))
    , mSoundEffect(new QSoundEffect(this))
{
    setRowCount(rows);
    setColumnCount(columns);
    setFixedHeight((cellSize + 1) * rows);
    setFixedWidth((cellSize + 1) * columns);
    setAcceptDrops(true);
    setDragEnabled(true);
    setItemDelegate(mDelegate);
    setSelectionMode(QAbstractItemView::SingleSelection);

    auto _vHeader = verticalHeader();
    auto _hHeader = horizontalHeader();

    _vHeader->setHidden(true);
    _vHeader->setSectionResizeMode(QHeaderView::Fixed);
    _vHeader->setDefaultSectionSize(cellSize);

    _hHeader->setHidden(true);
    _hHeader->setSectionResizeMode(QHeaderView::Fixed);
    _hHeader->setDefaultSectionSize(cellSize);

    mSoundEffect->setSource(QUrl("qrc:/sound/bite_sound"));
    mSoundEffect->setVolume(0.9);
    mSoundEffect->setLoopCount(0);
}

InventoryWidget::~InventoryWidget()
{

}

void InventoryWidget::setInventory(Inventory *inv)
{
    mInventory = inv;
    connect(mInventory, &Inventory::itemCountChanged, this, [this](int row, int col, int type, int count){
        dbController::getInstance()->writeInventoryChanges(row, col, type, count);
    });
    loadInventory();
}

void InventoryWidget::setItemList(QList<Item*> items)
{
    mItems = items;
}

void InventoryWidget::loadInventory()
{
    Item* ptr = nullptr;
    for (auto cell : mInventory->getCells()) {
        if (cell->type != -1 && cell->count > 0) {
            for (auto _item : mItems) {
                if (_item->getType() == cell->type) {
                    ptr = _item;
                    break;
                }
            }
            if (ptr == nullptr) {
                return;
            }
            auto _widgetItem = new QTableWidgetItem();
            _widgetItem->setData(Qt::UserRole + 1, ptr->getImagePath());
            _widgetItem->setData(Qt::UserRole + 2, cell->count);
            setItem(cell->row, cell->column, _widgetItem);
        }
    }
}

void InventoryWidget::dropEvent(QDropEvent *event) // D'n'D функционал
{
    QByteArray encoded = event->mimeData()->data("application/x-qabstractitemmodeldatalist"); // Зашифрованные данные из QTableWidgetItem
    QDataStream stream(&encoded, QIODevice::ReadOnly);

    int row, col;
    QMap<int,  QVariant> roleDataMap;
    stream >> row >> col >> roleDataMap; // row - строка, col - столбец, roleDataMap - данные в Qt::UserRole+1/Qt::DecorationRole/Qt::DisplayRole и тд

    int destRow = rowAt(event->position().y());
    int destCol = columnAt(event->position().x());

    if (event->source() == this) { // если перетащили из самого инвентаря
        if (destRow == row && destCol == col)
            return;
        if (auto sourceItem = takeItem(row, col)) {
            if (auto destItem = item(destRow, destCol)) { // если есть предмет на курсоре, то прибавляем кол-во перетаскиваемых предметов к предмету на курсоре.
                int oldCount = destItem->data(Qt::UserRole + 2).toInt();
                destItem->setData(Qt::UserRole + 2, oldCount + sourceItem->data(Qt::UserRole + 2).toInt());
            }
            else {
                setItem(destRow, destCol, sourceItem); // если нет предмета на курсоре, то мы просто переносим QTableWidgetItem на destRow/destCol
            }
            mInventory->removeItem(row, col, 1, sourceItem->data(Qt::UserRole + 2).toInt());
            mInventory->addItem(destRow, destCol, 1, sourceItem->data(Qt::UserRole + 2).toInt());
        }
    }
    else { // если перетащили из itemWidget
        if (auto oldItem = item(destRow, destCol)) { // если есть предмет на курсоре, то прибавляем кол-во перетаскиваемых предметов к предмету на курсоре.
            int count = oldItem->data(Qt::UserRole + 2).toInt();
            count++;
            oldItem->setData(Qt::UserRole + 2,  count);
            mInventory->addItem(destRow, destCol, 1, 1);
        }
        else {
            QTableWidgetItem *item = new QTableWidgetItem(); // если на курсоре нет предмета (таргет ивента дроп) то создаем новый предмет
            item->setData(Qt::UserRole + 1, roleDataMap[Qt::UserRole + 1]);
            item->setData(Qt::UserRole + 2, 1);
            setItem(destRow, destCol, item);
            mInventory->addItem(destRow, destCol, 1, 1);
        }
    }
    event->acceptProposedAction();
}

void InventoryWidget::mousePressEvent(QMouseEvent *event) // Вопроизведение звука и удаление яблока при правом клике.
{
    if (event->button() == Qt::RightButton) {
        int destRow = rowAt(event->position().y());
        int destCol = columnAt(event->position().x());

        if (auto clickedItem = item(destRow, destCol)) {
            int count = clickedItem->data(Qt::UserRole + 2).toInt();
            count--;
            if (count == 0) {
                delete clickedItem;
                clickedItem = nullptr;
            }
            else {
                clickedItem->setData(Qt::UserRole + 2, count);
            }
            mInventory->removeItem(destRow, destCol, 1, 1);
            if (mSoundEffect->isLoaded()) {
                mSoundEffect->play();
            }
        }
    }
    else {
        QTableWidget::mousePressEvent(event); // если клик был другим, то обрабатывается стандартно.
    }

}
