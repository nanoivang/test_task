#include "startwidget.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QPropertyAnimation>

StartWidget::StartWidget(QWidget *parent)
    : QWidget(parent)
    , mStartButton(new QPushButton("Start", this))
    , mCloseButton(new QPushButton("Close", this))
    , mLayout(new QHBoxLayout(this))
{
    mLayout->addWidget(mStartButton);
    mLayout->addWidget(mCloseButton);

    setMaximumHeight(mStartHeight);

    connect(mStartButton, &QPushButton::clicked, this, &StartWidget::onStartClicked);
    connect(mCloseButton, &QPushButton::clicked, this, &StartWidget::closeClicked);
}

StartWidget::~StartWidget()
{

}

void StartWidget::onStartClicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);
    animation->setStartValue(geometry());
    animation->setEndValue(QRect(x(), y(), width(), 0));
    mStartHeight = height();
    animation->start(QAbstractAnimation::DeleteWhenStopped);
    emit startClicked();
}

void StartWidget::startShowing()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(500);
    animation->setStartValue(geometry());
    animation->setEndValue(QRect(x(), y(), width(), mStartHeight));
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
