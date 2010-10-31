#include "clientcontrolswidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../command.hpp"
#include "../publicstate.hpp"

ClientControlsWidget::ClientControlsWidget(QWidget *parent) : QWidget(parent) {
    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    QHBoxLayout * cursorButtinsLayout = new QHBoxLayout();

    playPauseButton = new QPushButton("Play/Pause", this);
    leftButton = new QPushButton("<<", this);
    rightButton = new QPushButton(">>", this);

    cursorButtinsLayout->addWidget(leftButton);
    cursorButtinsLayout->addWidget(rightButton);
    mainLayout->addWidget(playPauseButton);
    mainLayout->addLayout(cursorButtinsLayout);

    leftButton->setMinimumHeight(50);
    rightButton->setMinimumHeight(50);
    leftButton->setDisabled(true);
    rightButton->setDisabled(true);
    //playPauseButton->setDisabled(true);

    connect(leftButton,SIGNAL(clicked()),SLOT(leftClick()));
    connect(rightButton,SIGNAL(clicked()),SLOT(rightClick()));
    connect(playPauseButton,SIGNAL(clicked()),SLOT(playPauseClick()));
}

void ClientControlsWidget::leftClick(){
    static Command cmd(Command::MOVE_LEFT);
    QByteArray msg;
    msg.append(cmd.serialize());
    emit sendingDataToServer(msg);
}

void ClientControlsWidget::rightClick() {
    static Command cmd(Command::MOVE_RIGHT);
    QByteArray msg;
    msg.append(cmd.serialize());
    emit sendingDataToServer(msg);
}

void ClientControlsWidget::playPauseClick() {
    static Command cmd(Command::PLAYPAUSE);
    QByteArray msg;
    msg.append(cmd.serialize());
    emit sendingDataToServer(msg);
}

void ClientControlsWidget::tryToResolveMessage(QByteArray message) {
    PublicState * ps = PublicState::deserialize(message);
    if(ps == 0) return;
    applyState(PublicState(*ps));
}

void ClientControlsWidget::applyState(const PublicState &/*ps*/) {
    ///if (ps.isActive())

    // TODO обработка состояний
}


