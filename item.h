#ifndef ITEM_H
#define ITEM_H

#include <QWidget>
#include <QObject>
#include <QTableWidgetItem>

class Item : public QObject
{
    Q_OBJECT
public:
    Item(int type, QString name, QString imagePath);
    ~Item();
    int getType() { return mType; }
    QString getImagePath() { return mImagePath; }
private:
    int mType;
    QString mName;
    QString mImagePath;
};
#endif // ITEM_H
