#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "clientsettings.h"

class SettingsDialog : public QDialog {
    Q_OBJECT;
public:
    SettingsDialog(ClientSettingsPtr settings, QWidget * parent = 0);

private slots:
    void accept();
    void cancel();

public slots:
    void reloadSettings();

private:
    QLabel * lPort;
    QLabel * lAddress;
    QLineEdit * lePort;
    QLineEdit * leAddress;
    QDialogButtonBox * buttonBox;
    ClientSettingsPtr settings;

    void createObjects();
    void connectObjects();
};

#endif // SETTINGSDIALOG_H
