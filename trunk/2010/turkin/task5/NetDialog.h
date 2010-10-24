#ifndef NETDIALOG_H
#define NETDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QUdpSocket>
#include <QDebug>
class NetDialog : public QDialog {
    Q_OBJECT;
    public:
        NetDialog(quint16 port, QWidget *parent = 0);
        ~NetDialog();

    private: // UI
        QListWidget* myListWidget;
        QLineEdit* myIPLineEdit;
        QLineEdit* myPortLineEdit;
        QLineEdit* myMessageLineEdit;
        QPushButton* mySendButton;
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
        void newChatMessage(const QString& message);

    signals:

    public slots:
        void sendSlot();
        void receiveSlot();

};

#endif // NETDIALOG_H
