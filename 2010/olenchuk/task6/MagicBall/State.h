#ifndef STATE_H
#define STATE_H

#include <QDomDocument>
#include <QDomElement>

class Racket;
class Ball;

class State {

	public:
		State(Ball *ball, Racket *racket);

	public:
		//void setState(Ball * ball, Racket * racket);
		QDomElement serialize(QDomDocument * doc);
	
	private:
		Racket *racket;
		Ball *ball;
};


#endif
