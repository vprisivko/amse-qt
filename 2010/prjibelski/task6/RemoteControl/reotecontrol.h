#ifndef REOTECONTROL_H
#define REOTECONTROL_H

#include <QtGui/QDialog>
#include <QLabel>
#include <QPushButton>
#include <QUdpSocket>
#include <QDomDocument>

struct RecievedState {
    int livesLeft;
    int windowWidth;
    int plateX;
    int plateW;

    static RecievedState createInstance ( QDomDocument * dom );

    bool canMoveRight() {
        return plateX + plateW < windowWidth;
    }

    bool canMoveLeft() {
        return plateX > 0;
    }
};

class RemoteControl : public QDialog
{
    Q_OBJECT;

public:
    RemoteControl( QWidget *parent = 0 );
    ~RemoteControl();

protected:
    void keyPressEvent( QKeyEvent * e );
    void focusKeyboard() {
        setFocusPolicy(Qt::StrongFocus);
        setFocus();
    }

public slots:
    void sendRightCommand();
    void sendLeftCommand();
    void sendRestartCommand();
    void stateRecieved();

private:
    QLabel * livesLeftLabel;
    QPushButton * restartButton;
    QPushButton * moveLeftButton;
    QPushButton * moveRightButton;

    int myPort;
    int toPort;
    QString ip;
    QUdpSocket * socket;
    QByteArray recievedData;

    RecievedState state;

    void createDialog();
    void loadSettings();
    void connectAll();
    void createSocket( int portNumber );
    void sendMoveCommand( QString direction );
    void stateUpdated();

};

#endif // REOTECONTROL_H
