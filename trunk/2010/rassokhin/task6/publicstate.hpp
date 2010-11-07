#ifndef PUBLICSTATE_HPP
#define PUBLICSTATE_HPP

#include <QByteArray>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>

class PublicState {
public:
    PublicState() {};

    bool leftAllowed;
    bool rightAllowed;
    bool playPauseAllowed;

    QByteArray serialize() const;
    static PublicState * deserialize(QByteArray rawData);
};

inline PublicState * PublicState::deserialize(QByteArray rawData) {
    QDomDocument doc;
    doc.setContent(rawData);
    QDomElement root = doc.documentElement();
    if(root.tagName() != "publicstate") return 0;
    PublicState * ps = new PublicState();
    ps->leftAllowed = root.attribute("leftAllowed", "0").toInt();
    ps->rightAllowed = root.attribute("rightAllowed", "0").toInt();
    ps->playPauseAllowed = root.attribute("playPauseAllowed", "0").toInt();

    return ps;
}

inline QByteArray PublicState::serialize() const{
    QDomDocument doc;
    QDomElement root = doc.createElement( "publicstate" );
    root.setAttribute("leftAllowed", (int)leftAllowed);
    root.setAttribute("rightAllowed", (int)rightAllowed);
    root.setAttribute("playPauseAllowed", (int)playPauseAllowed);
    doc.appendChild(root);
    return doc.toByteArray(-1);
}

#endif // PUBLICSTATE_HPP
