#include "settingsdialog.h"

#include <QtGui/QIntValidator>
#include <QtGui/QVBoxLayout>
#include <QtGui/QGridLayout>

SettingsDialog::SettingsDialog(ClientSettingsPtr settings, QWidget *parent)
        :QDialog(parent), settings(settings) {
    createObjects();
    connectObjects();
    reloadSettings();
}

void SettingsDialog::createObjects() {

    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    QGridLayout * settingsLayout = new QGridLayout();

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Save |
                                     QDialogButtonBox::Cancel,
                                     Qt::Horizontal, this);

    lPort = new QLabel(tr("Port"),this);
    lAddress = new QLabel(tr("Address"),this);

    leAddress = new QLineEdit(this);
    lePort = new QLineEdit(this);

    lePort->setValidator(new QIntValidator(1, 65535, this));

    mainLayout->addLayout(settingsLayout);
    mainLayout->addWidget(buttonBox);
    settingsLayout->addWidget(lAddress,0,0);
    settingsLayout->addWidget(lPort,1,0);
    settingsLayout->addWidget(leAddress,0,1);
    settingsLayout->addWidget(lePort,1,1);
}

void SettingsDialog::connectObjects() {
    connect(buttonBox, SIGNAL(accepted()), SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), SLOT(reject()));
}

void SettingsDialog::accept() {
    qDebug("SettingsDialog::accept()");
    settings->setAddress(leAddress->text());
    quint16 port = lePort->text().toInt();
    settings->setPort(port);
    this->close();
}

void SettingsDialog::cancel() {
    this->close();
}

void SettingsDialog::reloadSettings() {
    qDebug("SettingsDialog::reloadSettings()");
    leAddress->setText(settings->getAddress());
    lePort->setText(QString::number(settings->getPort()));
}
