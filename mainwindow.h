#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class StartWidget;
class GameWindow;
class QVBoxLayout;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    StartWidget *mStartWidget = nullptr;
    GameWindow *mGameWindow = nullptr;
    QWidget *mMainWidget = nullptr;
    QVBoxLayout *mMainWidgetLayout = nullptr;
};
#endif // MAINWINDOW_H
