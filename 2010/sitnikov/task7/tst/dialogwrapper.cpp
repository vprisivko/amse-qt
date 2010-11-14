#include "dialogwrapper.h"


DialogWrapper::DialogWrapper(QWidget *parent /* = 0 */) : Dialog(parent) { }

void DialogWrapper::timerEvent(QTimerEvent *t)
{
	emit timerEventSignal();
	Dialog::timerEvent(t);
}
