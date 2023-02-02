#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "gamewindow.h"
#include "startwidget.h"

#include <QWidget>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mMainWidget(new QWidget(this))
{
    ui->setupUi(this);

    mMainWidgetLayout = new QVBoxLayout(mMainWidget);

    mGameWindow = new GameWindow(mMainWidget);
    mStartWidget = new StartWidget(mMainWidget);

    mMainWidgetLayout->addWidget(mStartWidget);
    mMainWidgetLayout->addWidget(mGameWindow);


    connect(mGameWindow, &GameWindow::startMenuRequested, mStartWidget, &StartWidget::startShowing);
    connect(mStartWidget, &StartWidget::startClicked, mGameWindow, &GameWindow::init);
    connect(mStartWidget, &StartWidget::closeClicked, this, &MainWindow::close);
    setCentralWidget(mMainWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

