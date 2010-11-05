#include "Test.h"
Test::Test():QObject(){
  mytimedialog = new TimeDialog();
  mytimer = new QTimer(this);
  periodended = false;
  mynumberofperiods = 0;
  mytimeafterperiod = 0;
  QObject::connect(mytimer, SIGNAL(timeout()), this ,SLOT(endperiod()));
}
Test::Test(TimeDialog* timedialog):QObject(){
  mytimedialog = timedialog;
  mytimer = new QTimer(this);
  periodended = false;
  mynumberofperiods = 0;
  mytimeafterperiod = 0;
  QObject::connect(mytimer, SIGNAL(timeout()), this ,SLOT(endperiod()));
}

void Test::firstbegintime(){
  mynumberofperiods = 0;
  mytimeafterperiod = 0;
  mybegintime = mytimedialog->getfirsttime();
  QCOMPARE(0,mybegintime);
}

void Test::firsttestSet(){
  QPushButton* setbutton;
  QLineEdit* setlineedit;
  setbutton = mytimedialog->getsetbutton();
  QSignalSpy setspy(mytimedialog, SIGNAL(setSignal()));
  setlineedit = mytimedialog->getsetlineedit();
  QTest::keyPress(setlineedit,Qt::Key_1);
  QTest::mouseClick(setbutton,Qt::LeftButton);
  mytimer->start(1);
  QCOMPARE(1,setspy.count());
}


void Test::firsttestStop(){
  QPushButton* stopbutton;
  stopbutton = mytimedialog->getstopbutton();
  QTest::qWait(1000);
  QSignalSpy stopspy(mytimedialog, SIGNAL(stopSignal()));
  QTest::mouseClick(stopbutton,Qt::LeftButton);
  QCOMPARE(1,stopspy.count());
}
void Test::firstendtime(){
  mytimeafterperiod = mytimedialog->getfirsttime();
  QCOMPARE(mybegintime,mytimeafterperiod - mynumberofperiods);
  mytimer->stop();
}

void Test::secondbegintime(){
  mynumberofperiods = 0;
  mytimeafterperiod = 0;
  mybegintime = mytimedialog->getsecondtime();
  QCOMPARE(0,mybegintime);
}

void Test::secondtestSet(){
  QPushButton* setbutton;
  QComboBox* timerbox;
  QLineEdit* setlineedit;
  setbutton = mytimedialog->getsetbutton();
  timerbox = mytimedialog->getbox();
  QTestEventList* eventlist = new QTestEventList();
  QSignalSpy boxspy(timerbox,SIGNAL(currentIndexChanged(int)));
  eventlist->addMouseClick(Qt::LeftButton);
  eventlist->addMouseClick(Qt::LeftButton);
  //eventlist->addMouseClick(Qt::LeftButton,0,timerbox->pos());
  //eventlist->addMouseClick(Qt::LeftButton,0,QPoint(timerbox->pos().x(),timerbox->pos().y()-5));
  //eventlist->simulate(mytimedialog);
  timerbox->setCurrentIndex(1);
  //QTest::mouseClick(timerbox,Qt::LeftButton);
  //QTest::mouseClick(timerbox,Qt::LeftButton,0,QPoint(timerbox->pos().x()+10,timerbox->pos().y()+15),10);
  QCOMPARE(1,boxspy.count());
  QSignalSpy setspy(mytimedialog, SIGNAL(setSignal()));
  setlineedit = mytimedialog->getsetlineedit();
  QTest::mouseClick(setbutton,Qt::LeftButton,0,timerbox->pos(),10);
  mytimer->start(1);
  QCOMPARE(1,setspy.count());
}


void Test::secondtestStop(){
  QPushButton* stopbutton;
  stopbutton = mytimedialog->getstopbutton();
  QTest::qWait(1000);
  QSignalSpy stopspy(mytimedialog, SIGNAL(stopSignal()));
  QTest::mouseClick(stopbutton,Qt::LeftButton);
  QCOMPARE(1,stopspy.count());
}
void Test::secondendtime(){
  mytimeafterperiod = mytimedialog->getsecondtime();
  QCOMPARE(mybegintime,mytimeafterperiod - mynumberofperiods);
  mytimer->stop();
}

void Test::endperiod(){
  mynumberofperiods++;
}
