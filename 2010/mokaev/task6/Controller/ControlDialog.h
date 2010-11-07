#ifndef _CONTROL_DIALOG_H_
#define _CONTROL_DIALOG_H_

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QKeyEvent>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QHostAddress>
#include <QtXml/QXmlDefaultHandler>

const int BALLS_IN_RESERVE = 3;
const int DIALOG_WIDTH = 460;
const int DIALOG_HEIGHT = 160;

class ControlDialog : public QDialog{
    Q_OBJECT;

    public:
        ControlDialog( QHostAddress& ip, int port, QWidget* parent = NULL );
    public slots:
        void start();
        void left();
        void right();
        void setIpAndPort();
        void readDatagrams();

    private:
        void createWidgets();
        void addWidgets();
        void createSocket();
        void setConnection();
        void parseData( const QByteArray& data );
        void keyPressEvent( QKeyEvent* );

    private:
        class XmlHandler: public QXmlDefaultHandler {
            public:
                bool startElement( const QString&, const QString&, const QString& name, const QXmlAttributes& attrs );
                int gameBegins;
                int gameOver;
        };

        friend class ControlDialog :: XmlHandler;
    private:
        QLabel* ipLabel;
        QLabel* portLabel;
        QLabel* infoLabel;

        QLineEdit* ipTextBox;
        QLineEdit* portTextBox;

        QPushButton* leftButton;
        QPushButton* rightButton;
        QPushButton* goButton;
        QPushButton* connectButton;
    private:
        QUdpSocket* udpSocket;
        QHostAddress myAddress;
        QHostAddress hostAddress;
    private:
        int myPort;
        int arcanoidPort;
        int ballsInReserve;
};

#endif
