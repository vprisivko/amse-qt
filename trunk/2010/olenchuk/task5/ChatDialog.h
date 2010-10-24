#ifndef H_CHATDIALOG
#define H_CHATDIALOG

#include <QDialog>
//#include <QUdpSocket>

class QListWidget;
class QLineEdit;
class QPushButton;
class QUdpSocket;
//class QNetWorkAdressEntery;

class ChatDialog : public QDialog {
	
	Q_OBJECT

	public:
		ChatDialog(QWidget *parent = 0);

	public:
		bool initSocket(int port);
	
	private slots:
		void readMessage();
		void sendMessage();	

	private:
		int myPort;
		QUdpSocket *udpSocket;
		QListWidget *listWidget;
		QLineEdit *ipEdit;
		QLineEdit *portEdit;
		//QNetWorkAdressEntery *adress;
		QLineEdit *lineEdit;
		QPushButton *sendButton;

};


#endif
