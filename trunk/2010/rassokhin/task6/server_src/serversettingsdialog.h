#ifndef SERVERSETTINGSDIALOG_H
#define SERVERSETTINGSDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "serversettings.h"

class ServerSettingsDialog : public QDialog {
    Q_OBJECT;
public:
    ServerSettingsDialog(ServerSettingsPtr settings, QWidget * parent = 0);

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
    ServerSettingsPtr settings;

    void createObjects();
    void connectObjects();
};

#endif // SERVERSETTINGSDIALOG_H
