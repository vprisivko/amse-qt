#include "clientsettings.h"

#include <QString>

void ClientSettings::saveSettings(QSettings *settings) const {
    settings->setValue("server.address", getAddress());
    settings->setValue("server.port", getPort());
}

void ClientSettings::loadSettings(QSettings *settings) {
    setAddress( settings->value("server.address", "localhost").toString());
    setPort( settings->value("server.port", 12000).toInt());
}
