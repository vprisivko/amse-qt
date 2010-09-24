#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>

QLayout * getInputForm(QWidget * parent, QString label) {
    QLayout * ret = new QHBoxLayout();
    ret->addWidget(new QLabel(label,parent));
    ret->addWidget(new QLineEdit(parent));
    return ret;
}

int main (int argc, char ** argv) {
    QApplication app(argc, argv);
    QDialog * dial = new QDialog();
    QVBoxLayout * mainlayout = new QVBoxLayout(dial);
    mainlayout->addLayout(getInputForm(dial,"firstname"));
    mainlayout->addLayout(getInputForm(dial,"lastname"));
    mainlayout->addLayout(getInputForm(dial,"phone"));
    mainlayout->addLayout(getInputForm(dial,"email"));
    mainlayout->addWidget(new QPushButton("send to db",dial));
    dial->setLayout(mainlayout);
    dial->show();
    return app.exec();
}
