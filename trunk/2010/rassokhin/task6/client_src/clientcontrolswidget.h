#ifndef CLIENTCONTROLSWIDGET_H
#define CLIENTCONTROLSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QByteArray>
#include "../publicstate.hpp"

class ClientControlsWidget : public QWidget {
    Q_OBJECT;
public:
    ClientControlsWidget(QWidget * parent = 0);

signals:
    void sendingDataToServer(QByteArray message);

public slots:
    void tryToResolveMessage(QByteArray message);

private slots:
    void leftClick();
    void rightClick();
    void playPauseClick();

private:
    QPushButton * leftButton;
    QPushButton * rightButton;
    QPushButton * playPauseButton;

    void applyState(const PublicState & ps);

};

#endif // CLIENTCONTROLSWIDGET_H
