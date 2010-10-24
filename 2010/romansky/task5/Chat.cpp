#include "Chat.h"

Chat::Chat(QWidget* parent, int port = 10000):QDialog(parent){ 
  mydefaultaddress="127.0.0.1";
  myip.setAddress(mydefaultaddress);
  myport = port;
  mysocket = new QUdpSocket();
  myportset = mysocket->bind(myip,myport);
  

  if (myportset){
    QVBoxLayout* mainlayout = new QVBoxLayout();
    QHBoxLayout* iplayout = new QHBoxLayout();
    QHBoxLayout* textlayout = new QHBoxLayout();

    mylistview = new QListView();


    mysendbutton = new QPushButton("Send");
    mysetbutton = new QPushButton("Set");

    myipedit = new QLineEdit();
    myipedit->setText(mydefaultaddress);
    myportedit = new QLineEdit();
    mytext  = new QLineEdit();

    mymodel = new QStringListModel();
    mylistview->setModel(mymodel);
  
    mysendportset = false;

    iplayout->addWidget(new QLabel("IP  "));
    iplayout->addWidget(myipedit);
    iplayout->addWidget(new QLabel("  port  "));
    iplayout->addWidget(myportedit);
    iplayout->addWidget(mysetbutton);

    textlayout->addWidget(mytext);
    textlayout->addWidget(mysendbutton);


    mainlayout->addWidget(mylistview);
    mainlayout->addItem(iplayout);
    mainlayout->addItem(textlayout);

    setLayout(mainlayout);

    setWindowTitle(QString::number(myport));

    connect(mysetbutton, SIGNAL(clicked()), this, SLOT(Set()));
    connect(mysendbutton, SIGNAL(clicked()), this, SLOT(Send()));
    connect(mysocket, SIGNAL(readyRead()), this, SLOT (Read()));
  } else {
    QVBoxLayout* mainlayout = new QVBoxLayout();
    QLabel* messagelabel = new QLabel("Invalid port   " + QString::number(port));
    mainlayout->addWidget(messagelabel);
    setLayout(mainlayout);
  }
}

bool Chat::isportset(){
  return myportset;
}

bool Chat::issendportset(){
  return mysendportset;
}

void Chat::Set(){
  QMessageBox* messagebox = new QMessageBox();
  if (!(mysendip.setAddress(myipedit->text()))){
    messagebox->setText("Invalid IP");
    messagebox->show();
    return;
  }
  mysendport = myportedit->text().toInt();
  mysendportset = true;
}

void Chat::Send(){
  QMessageBox* messagebox = new QMessageBox();
  QByteArray datagram;
  if(! (issendportset())){
    messagebox->setText("Set adress of receiver");
    messagebox->show();
  } else {
    datagram = mytext->text().toAscii();
    mysocket->writeDatagram(datagram,mysendip,mysendport);
    mymodel->insertRows(mymodel->rowCount(), 1);
    mymodel->setData(mymodel->index(mymodel->rowCount()-1),"me:   "+QString(datagram));
    mylistview->scrollToBottom();
    mytext->setText("");
  }
}

void Chat::Read(){
  QByteArray datagram;
  QHostAddress sender;
  quint16 senderPort;
  while(mysocket->hasPendingDatagrams()){
    datagram.resize(mysocket->pendingDatagramSize());
    mysocket->readDatagram(datagram.data(), datagram.size(),&sender, &senderPort);
    mymodel->insertRows(mymodel->rowCount(), 1);
    mymodel->setData(mymodel->index(mymodel->rowCount()-1),myip.toString()+"/"+QString::number(myport)+":   "+QString(datagram));
    mylistview->scrollToBottom();
  }
}

