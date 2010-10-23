#ifndef UDPCHAT_H
#define UDPCHAT_H


#include <QWidget>
#include <QtNetwork/QUdpSocket>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>


class UdpChat : public QWidget
{
    Q_OBJECT
public:
    explicit UdpChat(QWidget *parent = 0);

private:
    QUdpSocket* socket;

    // gui stuff
    QScrollArea* msgScrollArea;
    QWidget* messageArea;
    QLineEdit* ipEdit;
    QLineEdit* portEdit;
    QTextEdit* messageTextEdit;
    QPushButton* sendButton;
    //

    // init routines
    void createWidgets();
    void placeItemsOnLayouts();
    void connectSigSlots();
    void bindSocket();
    //

    void newMessage( QByteArray& msg );

signals:


public slots:
    void sendMessage();
    void dataAtSocket();

};

#endif // UDPCHAT_H
