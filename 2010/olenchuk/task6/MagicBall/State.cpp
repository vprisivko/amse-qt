//#include <QDomDocument>
//#include <QDomElement>


#include "State.h"
#include "Ball.h"
#include "Racket.h"

State :: State(Ball *ball, Racket *racket) {
	this->ball = ball;
	this->racket = racket;
}
//void State :: setState(Ball * ball, Racket * racket) {
	//this->racket->setCoordinates(racket->getCoordinates().x(), racket->getCoordinates().y());
	//this->ball->setWindowSize(ball->getWidth(), ball->getHeight());
//}
QDomElement State::serialize(QDomDocument * doc) {
	QDomElement stateElement = doc->createElement("State");
	doc->appendChild(stateElement);
	QDomElement lives = doc->createElement("Lives");
	lives.setAttribute("livesleft", this->ball->getLives());
	stateElement.appendChild(lives);
	QDomElement racket = doc->createElement("Racket");
	racket.setAttribute("x", this->racket->getCoordinates().x());
	racket.setAttribute("y", this->racket->getCoordinates().y());
	racket.setAttribute("racketWidth", this->racket->getRacketSize().width());
	stateElement.appendChild(racket);
	QDomElement windowSize = doc->createElement("Size");
	windowSize.setAttribute("width", this->racket->getWindowSize().width());
	windowSize.setAttribute("height", this->racket->getWindowSize().height());
	stateElement.appendChild(windowSize);
	return stateElement;
}
