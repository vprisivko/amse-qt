// =====================================================================================
// 
//       Filename:  dialog.h
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  29.09.2010 22:08:09
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Dmitriy Serdyuk (), serdyuk.dmitriy@gmail.com
//        Company:  
// 
// =====================================================================================

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QTimerEvent>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QLineEdit>
#include <QBoxLayout>

class Dialog : public QDialog {
    Q_OBJECT;
private:
    int myTimer1;
    int myTimer2;

    int myTimer1Id;
    int myTimer2Id;

    QLabel *myLabel1;
    QLabel *myLabel2;

    QComboBox *myComboBox;

    QLineEdit *mySetLineEdit;

    QPushButton *mySetButton;
    QPushButton *myStopButton;

    QVBoxLayout *myMainLayout;
    QHBoxLayout *mySetLayout;

public:
    Dialog(QWidget *p = 0);

    void timerEvent(QTimerEvent *e);

private slots:
    void onSetPressed();
    void onStopPressed();
};

#endif   // ----- #ifndef DIALOG_H -----

