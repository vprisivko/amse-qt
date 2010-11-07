#include "arcanoidviewwidget.h"
#include <QPalette>
#include <QTimer>
#include <QSize>
#include <QResizeEvent>

ArcanoidViewWidget::ArcanoidViewWidget(ArcanoidEngine *engine, QWidget *parent) :
        QGraphicsView(engine,parent), m_engine(engine) {
    connect(m_engine, SIGNAL(changed(QList<QRectF>)), this, SLOT(update()));
    resize(640, 480);
}

ArcanoidViewWidget::~ArcanoidViewWidget() {}

void ArcanoidViewWidget::resizeEvent(QResizeEvent *ev) {
    QPalette palette;
    palette.setBrush(backgroundRole(),QBrush(QColor("black")));
    setPalette(palette);
    setAutoFillBackground(true);

    QSize boardSize = ev->size();
    m_engine->resize(boardSize);
    update();
}

