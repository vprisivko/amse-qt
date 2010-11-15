#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <QDialog>
#include <QSettings>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QUdpSocket>
#include <QDebug>
#include <QTextEdit>
#include <QXmlDefaultHandler>
#include <QDomDocument>
#include <QDomElement>

class ControlDialog : public QDialog {
    Q_OBJECT;

    public:
        ControlDialog(quint16 port, QWidget *parent = 0);

    private:
        QLineEdit* myIPLineEdit;
        QLineEdit* myPortLineEdit;
        QPushButton* myLeftButton;
        QPushButton* myRightButton;
        QPushButton* myStartButton;

    private:
        QUdpSocket* mySocket;

    private:
        void setWidgets();
        void setValidators();
        void initSocket(quint16 port);
        void createConnects();

    private:
        struct State {
            bool started;
            int ballX, ballY;
            int windowHeight, windowWidth;
            int racketWidth, racketX;
         };

        class StateXmlHandler: public QXmlDefaultHandler {
            public:
                StateXmlHandler(State* state);
                bool startElement(const QString &, const QString &, const QString &, const QXmlAttributes &);
            private:
                State* myState;

        };

        void processState(const ControlDialog::State& state);
        void sendCommand(QString cmd);

    public slots:
        void leftButtonPressed();
        void rightButtonPressed();
        void directionButtonReleased();
        void startButtonPressed();
        void receiveSlot();
};

#endif
