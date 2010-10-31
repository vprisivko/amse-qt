#ifndef PUBLICSTATE_HPP
#define PUBLICSTATE_HPP

#include <QByteArray>

class PublicState {
public:
    PublicState() {};

    QByteArray serialize() const;
    static PublicState * deserialize(QByteArray rawData);
};

inline PublicState * PublicState::deserialize(QByteArray /*rawData*/) {
    return 0;
    // TODO: make xml here
}

inline QByteArray PublicState::serialize() const{
    QByteArray ret;
    // TODO: make xml here
    return ret;
}


#endif // PUBLICSTATE_HPP
