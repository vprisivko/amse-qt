#ifndef CONTROL_DIALOG_H
#define CONTROL_DIALOG_H

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
        ~ControlDialog();

    private: // UI
        QLineEdit* myIPLineEdit;
        QLineEdit* myPortLineEdit;
        QPushButton* myLeftButton;
        QPushButton* myRightButton;
        QPushButton* myStartButton;

    private:
        QSettings* mySettings;
        QUdpSocket* mySocket;

    private:
        void setupUI();
        void setValidators();
        void loadSettings();
        void saveSettings();
        void initSocket(quint16 port);
        void createConnects();

    private: //network state
        
        struct State {
            bool started;
            int ballX, ballY;
            int windowHeight, windowWidth;
            int padWidth, padX;
         };

        class StateXmlHandler: public QXmlDefaultHandler {
            public:
                StateXmlHandler(State* state);
                bool startElement(const QString &, const QString &, const QString &, const QXmlAttributes &);
            private:
                State* myState;

        };

        void processState(const ControlDialog::State& state);
        void sendCommand(QString command);

        
    signals:

    public slots:
        void leftButtonPressed();
        void rightButtonPressed();
        void directionButtonReleased();
        void startButtonPressed();
        void receiveSlot();
  

    

};

#endif // NETDIALOG_H
