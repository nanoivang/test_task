#include "gamewindow.h"
#include "inventoryWidget.h"
#include "dbcontroller.h"
#include "itemwidget.h"
#include "item.h"

#include <QTableWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QPixmap>
#include <QImage>

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
    , mInventoryWidget(new InventoryWidget(3, 3, this))
    , mShowStartMenu(new QPushButton("Show Start Menu", this))
    , mMainLayout(new QGridLayout(this))
    , mItemWidget(new ItemWidget(this))
{
    connect(mShowStartMenu, &QPushButton::clicked, this, &GameWindow::startMenuRequested);
    connect(mShowStartMenu, &QPushButton::clicked, this, [this](){
       setDisabled(true);
    });
    mItemWidget->showItem(1);
    mInventoryWidget->setItemList(mItemWidget->getItemlist());

    mMainLayout->addWidget(mShowStartMenu, 0, 0, Qt::AlignLeft);
    mMainLayout->addWidget(mInventoryWidget, 0, 0, 2, 1, Qt::AlignLeft);
    mMainLayout->addWidget(mItemWidget, 1, 1, Qt::AlignVCenter);
    setDisabled(true);
}

void GameWindow::init() // Активация виджета GameWindow и загрузка инвентаря из inventory.db
{
    setEnabled(true);

    mInventoryWidget->setInventory(dbController::getInstance()->loadInventory());
    mInventoryWidget->setShowGrid(true);
}

GameWindow::~GameWindow()
{
    if (mInventoryWidget) {
        delete mInventoryWidget;
        mInventoryWidget = nullptr;
    }
}
