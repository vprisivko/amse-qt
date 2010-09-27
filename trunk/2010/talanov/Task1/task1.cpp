#include "task1.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>


task1::task1(QWidget *parent, Qt::WFlags flags)
    : QDialog(parent, flags)
{
  QLayout* mainLayout = new QVBoxLayout;
  QLayout* firstNameLayout = new QHBoxLayout;

  QLabel* nameLabel = new QLabel("Enter your name", this);
  QLineEdit* nameEdit = new QLineEdit("here", this);

  firstNameLayout->addWidget(nameLabel);
  firstNameLayout->addWidget(nameEdit);

  mainLayout->addItem(firstNameLayout);

  QLayout* lastNameLayout = new QHBoxLayout;

  QLabel* lastNameLabel = new QLabel("Enter your last name", this);
  QLineEdit* lastNameEdit = new QLineEdit("here", this);

  lastNameLayout->addWidget(lastNameLabel);
  lastNameLayout->addWidget(lastNameEdit);

  mainLayout->addItem(lastNameLayout);

  QPushButton* confirmButton = new QPushButton("Confirm", this);
  QObject::connect(confirmButton, SIGNAL(clicked()), this, SLOT(accept()));

  mainLayout->addWidget(confirmButton);

  setLayout(mainLayout);
  
}

task1::~task1()
{

}
