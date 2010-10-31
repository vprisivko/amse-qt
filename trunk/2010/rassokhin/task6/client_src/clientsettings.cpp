#include "clientsettings.h"

#include <QString>
#include <QDebug>

void ClientSettings::saveSettings(QSettings *settings) const {
    qDebug("saving clientsettings");
    settings->setValue("server.address", getAddress());
    settings->setValue("server.port", getPort());
}

void ClientSettings::loadSettings(QSettings *settings) {
    qDebug("loading clientsettings");
    setAddress( settings->value("server.address", "localhost").toString());
    setPort( settings->value("server.port", 12000).toInt());
}
