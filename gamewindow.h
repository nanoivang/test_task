#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QObject>
#include <QWidget>

class Item;
class QPushButton;
class QGridLayout;
class QTableWidget;
class ItemWidget;
class InventoryWidget;

class GameWindow : public QWidget
{
    Q_OBJECT
public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
public slots:
    void init();
signals:
    void startMenuRequested();
private:
    InventoryWidget *mInventoryWidget = nullptr;
    ItemWidget *mItemWidget = nullptr;
    Item *mAppleItem = nullptr;
    QPushButton *mShowStartMenu = nullptr;
    QGridLayout *mMainLayout = nullptr;
};

#endif // GAMEWINDOW_H
