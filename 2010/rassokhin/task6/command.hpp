#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <QByteArray>

class Command {
public:
    Command(int type = NONE);
    QByteArray serialize() const;
    static Command * deserialize(QByteArray rawData);

    int getType() const {return type;}
    enum Type {
        NONE = 0x0,
        MOVE_LEFT = 0x1,
        MOVE_RIGHT = 0x2,
        PLAYPAUSE = 0x4,
        CONNECT = 0x8,
        DISCONNECT = 0x10,
        ACCEPTCONNECTION = 0x20,
    };

    int type;
};

#include <QXmlSimpleReader>
#include <QXmlInputSource>
#include <QXmlDefaultHandler>
#include <QXmlAttributes>

inline Command::Command(int tp):type(tp) {}

class CommandXmlHandler : public QXmlDefaultHandler {
public:
    CommandXmlHandler():QXmlDefaultHandler(), commandtype(Command::NONE) {}
    inline bool startElement ( const QString &, const QString & localName, const QString &, const QXmlAttributes & atts ) {
        if(localName != "command") return false;
        if(atts.count() == 0) return false;
        int ind = atts.index("type");
        if(ind == -1) return false;
        commandtype = QString(atts.value(ind)).toInt();
        return true;
    }
    inline bool endElement ( const QString &, const QString &, const QString &) {return true;}
    inline bool characters ( const QString & ) {return true;}
    inline Command * getCommand() const { return new Command(commandtype); }
private:
    int commandtype;
};

inline QByteArray Command::serialize() const {
    QByteArray ret;
    ret.append("<command type=\""+QString::number(type)+"\" />"); // its fast =)
    return ret;
}

inline Command * Command::deserialize(QByteArray rawData) {
    QXmlSimpleReader xmlReader;
    QXmlInputSource source;
    source.setData(rawData);
    CommandXmlHandler handler;
    xmlReader.setContentHandler(&handler);
    xmlReader.parse(&source);
    return handler.getCommand();
}

#endif // COMMAND_HPP
