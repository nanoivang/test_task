#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QObject>
#include <QWidget>

class QPushButton;
class QHBoxLayout;
class StartWidget : public QWidget
{
    Q_OBJECT

public:
    StartWidget(QWidget *parent = nullptr);
    ~StartWidget();
signals:
    void startClicked();
    void closeClicked();
public slots:
    void startShowing();
private slots:
    void onStartClicked();
private:
    QPushButton *mStartButton = nullptr;
    QPushButton *mCloseButton = nullptr;
    QHBoxLayout *mLayout = nullptr;
    int mStartHeight = 100;
};

#endif //STARTWIDGET_H
