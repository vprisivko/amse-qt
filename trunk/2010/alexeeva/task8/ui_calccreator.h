/********************************************************************************
** Form generated from reading UI file 'calccreator.ui'
**
** Created: Sun Nov 28 00:50:05 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALCCREATOR_H
#define UI_CALCCREATOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalcCreatorClass
{
public:
    QAction *m_open;
    QAction *m_save;
    QAction *m_revert;
    QAction *m_openCalcWidget;
    QWidget *centralwidget;
    QTextEdit *m_edit;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QDockWidget *m_dockWgt;
    QWidget *dockWidgetContents;
    QToolBar *toolBar;

    void setupUi(QMainWindow *CalcCreatorClass)
    {
        if (CalcCreatorClass->objectName().isEmpty())
            CalcCreatorClass->setObjectName(QString::fromUtf8("CalcCreatorClass"));
        CalcCreatorClass->resize(800, 600);
        m_open = new QAction(CalcCreatorClass);
        m_open->setObjectName(QString::fromUtf8("m_open"));
        m_save = new QAction(CalcCreatorClass);
        m_save->setObjectName(QString::fromUtf8("m_save"));
        m_revert = new QAction(CalcCreatorClass);
        m_revert->setObjectName(QString::fromUtf8("m_revert"));
        m_openCalcWidget = new QAction(CalcCreatorClass);
        m_openCalcWidget->setObjectName(QString::fromUtf8("m_openCalcWidget"));
        m_openCalcWidget->setCheckable(true);
        centralwidget = new QWidget(CalcCreatorClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        m_edit = new QTextEdit(centralwidget);
        m_edit->setObjectName(QString::fromUtf8("m_edit"));
        m_edit->setGeometry(QRect(0, 0, 811, 531));
        CalcCreatorClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CalcCreatorClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        CalcCreatorClass->setMenuBar(menubar);
        statusbar = new QStatusBar(CalcCreatorClass);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        CalcCreatorClass->setStatusBar(statusbar);
        m_dockWgt = new QDockWidget(CalcCreatorClass);
        m_dockWgt->setObjectName(QString::fromUtf8("m_dockWgt"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        m_dockWgt->setWidget(dockWidgetContents);
        CalcCreatorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(2), m_dockWgt);
        toolBar = new QToolBar(CalcCreatorClass);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        CalcCreatorClass->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(m_open);
        menuFile->addAction(m_save);
        menuFile->addAction(m_revert);
        toolBar->addAction(m_open);
        toolBar->addAction(m_save);
        toolBar->addAction(m_revert);
        toolBar->addAction(m_openCalcWidget);

        retranslateUi(CalcCreatorClass);
        QObject::connect(m_openCalcWidget, SIGNAL(triggered(bool)), m_dockWgt, SLOT(setVisible(bool)));

        QMetaObject::connectSlotsByName(CalcCreatorClass);
    } // setupUi

    void retranslateUi(QMainWindow *CalcCreatorClass)
    {
        CalcCreatorClass->setWindowTitle(QApplication::translate("CalcCreatorClass", "MainWindow", 0, QApplication::UnicodeUTF8));
        m_open->setText(QApplication::translate("CalcCreatorClass", "Open", 0, QApplication::UnicodeUTF8));
        m_open->setShortcut(QApplication::translate("CalcCreatorClass", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        m_save->setText(QApplication::translate("CalcCreatorClass", "Save", 0, QApplication::UnicodeUTF8));
        m_save->setShortcut(QApplication::translate("CalcCreatorClass", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        m_revert->setText(QApplication::translate("CalcCreatorClass", "Revert", 0, QApplication::UnicodeUTF8));
        m_revert->setShortcut(QApplication::translate("CalcCreatorClass", "Ctrl+R", 0, QApplication::UnicodeUTF8));
        m_openCalcWidget->setText(QApplication::translate("CalcCreatorClass", "Open calculator panel", 0, QApplication::UnicodeUTF8));
        m_openCalcWidget->setShortcut(QApplication::translate("CalcCreatorClass", "O", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("CalcCreatorClass", "File", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("CalcCreatorClass", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CalcCreatorClass: public Ui_CalcCreatorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALCCREATOR_H
