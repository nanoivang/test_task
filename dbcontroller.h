#ifndef DBCONTROLLER_H
#define DBCONTROLLER_H

#include <QObject>
#include <QSqlDatabase>

class QSqlTableModel;
class QSqlDatabase;
class QSqlQuery;
class Inventory;
class Item;

class dbController : QObject
{
    Q_OBJECT
protected:
    dbController();
    ~dbController();
    static dbController *instancePtr;
    dbController(dbController &other) = delete;
    void operator=(const dbController &) = delete;
public:
    static dbController *getInstance();
    void init();
    bool isConnected() { return mConnected; }
    Inventory* loadInventory();
    QList<Item*> getItems();
    QSqlTableModel *model() { return mModel; }
    void writeInventoryChanges(int, int, int, int);
private:
    bool mConnected = false;
    QSqlTableModel *mModel = nullptr;
    QSqlDatabase db;
    QSqlQuery *mQuery = nullptr;
};

#endif // DBCONTROLLER_H
