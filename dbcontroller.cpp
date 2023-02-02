#include "dbcontroller.h"
#include "item.h"
#include "inventory.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlRecord>

dbController* dbController::instancePtr = nullptr;

dbController::dbController()
{

}

dbController::~dbController()
{

}

dbController *dbController::getInstance()
{
    if (instancePtr == nullptr) {
        instancePtr = new dbController();
        instancePtr->init();
    }
    return instancePtr;
}

void dbController::writeInventoryChanges(int row, int col, int type, int count) // Запись изменений в бд
{
    int id = row * 3 + col;
    QString query = QString("UPDATE Inventory SET Count=%1, ItemType=%2 WHERE Id=%3;").arg
            (QString::number(count), QString::number(type), QString::number(id));
    qDebug() << "query:" << query;
    qDebug() << "Writing to inventory table: " << mQuery->exec(query);
}

Inventory* dbController::loadInventory() // Загружаем данные из инвентаря
{
    if (mConnected) {
        if (mQuery->exec("SELECT * from Inventory")) {
            auto result = new Inventory();
            while(mQuery->next()) {
                QSqlRecord record = mQuery->record();
                int row = record.value("Row").toInt();
                int col = record.value("Column").toInt();
                int ItemType = record.value("ItemType").toInt();
                int count = record.value("Count").toInt();
                result->addItem(row, col, ItemType, count);
            }
            return result;
        }
    }
    return nullptr;
}

QList<Item*> dbController::getItems() // Достаем предметы из БД
{
    QList<Item*> items;
    if (mConnected) {
        mQuery->exec("SELECT * from Items");
        while (mQuery->next()) {
            QSqlRecord record = mQuery->record();
            int type = record.value("ItemType").toInt();
            QString name = record.value("Name").toString();
            QString imagePath = record.value("Image").toString();
            items.append(new Item(type, name, imagePath));
        }
    }
    return items;
}

void dbController::init() // Иницализация локальной базы данных
{
    mModel = new QSqlTableModel();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./database.db");
    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
        mConnected = false;
    }
    else {
        qDebug() << "Database: connection ok";
        mConnected = true;
    }

    mQuery = new QSqlQuery();
    if (!db.tables().contains(QLatin1String("Items"))) {
        qDebug() << mQuery->exec("CREATE TABLE Items"
                           "(Id INTEGER PRIMARY KEY,"
                           "Name TEXT NOT NULL,"
                           "ItemType INTEGER,"
                           "Image TEXT NOT NULL)");
        qDebug() << "Insert Item:" << mQuery->exec("INSERT INTO Items (Id, Name, ItemType, Image) VALUES (1, 'Apple', 1, ':/images/items/apple')");
    }

    if (!db.tables().contains(QLatin1String("Inventory"))) {
        qDebug() << "Create Inventory Table: "<< mQuery->exec("CREATE TABLE Inventory"
                           "(Id INTEGER PRIMARY KEY,"
                           "Row INTEGER,"
                           "Column INTEGER,"
                           "ItemType INTEGER,"
                           "Count INTEGER)");
        qDebug() << "Insert Inventory Item:" << mQuery->exec("INSERT INTO Inventory (Id, Row, Column, ItemType, Count) VALUES "
                                                             "(0, 0, 0, -1, 0),"
                                                             "(1, 0, 1, -1, 0),"
                                                             "(2, 0, 2, -1, 0),"
                                                             "(3, 1, 0, -1, 0),"
                                                             "(4, 1, 1, -1, 0),"
                                                             "(5, 1, 2, -1, 0),"
                                                             "(6, 2, 0, -1, 0),"
                                                             "(7, 2, 1, -1, 0),"
                                                             "(8, 2, 2, -1, 0)");
    }

    mModel->setTable("Inventory");
}
