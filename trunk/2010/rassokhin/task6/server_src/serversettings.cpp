#include "serversettings.h"

#include <QString>

void ServerSettings::saveSettings(QSettings *settings) const {
    settings->setValue("server.address", getAddress());
    settings->setValue("server.port", getPort());
}

void ServerSettings::loadSettings(QSettings *settings) {
    setAddress( settings->value("server.address", "localhost").toString());
    setPort( settings->value("server.port", 13000).toInt());
}


