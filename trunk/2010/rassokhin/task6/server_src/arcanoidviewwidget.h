#ifndef ARCANOIDVIEWWIDGET_H
#define ARCANOIDVIEWWIDGET_H

#include "arcanoidengine.h"
#include <QGraphicsView>
#include <QTimer>

class ArcanoidViewWidget : public QGraphicsView {
    Q_OBJECT;
public:

    ArcanoidViewWidget (ArcanoidEngine * engine, QWidget *parent = 0 );
    ~ArcanoidViewWidget();

private:
    virtual void resizeEvent( QResizeEvent *event );

    ArcanoidEngine * m_engine;
};

#endif // ARCANOIDVIEWWIDGET_H
