#include "State.h"
#include "MagicBall.h"
#include "Ball.h"
#include "Racket.h"

State :: State(MagicBall *magicBall) {
	isPresenceStrainBall = false;
	this->magicBall = magicBall;
	lives = 0;
	speed = 1;
	qsrand(time(0));
	x = 0;
	y = 0;
	x = qrand() % 4;
	y = qrand() % 4;
	
	if (x > 1) {
		x = 1;
	} else {
		x = -1;
	}
	if (y < 1) {
		y = 1;
	} else {
		y = -1;
	}
}
void State :: updateState() {
	isPresenceStrainBall = false;
	if (magicBall->ball->getCenter().x() - magicBall->ball->getDefRad() <= magicBall->rect().x()) {
		isPresenceStrainBall = true;
		if (magicBall->ball->getRadius().x() <= magicBall->ball->getDefRad()/4) {
			x = -x;
		}
		if ((magicBall->ball->getRadius().x() + x) <= magicBall->ball->getDefRad()) {
			magicBall->ball->setRadiusX(magicBall->ball->getRadius().x() + x);
		}
	}
	if (magicBall->ball->getCenter().y() - magicBall->ball->getDefRad() <= magicBall->rect().y()) {
		isPresenceStrainBall = true;
		if (magicBall->ball->getRadius().y() <= magicBall->ball->getDefRad()/4) {
			y = -y;
		}
		if ((magicBall->ball->getRadius().y() + y) <= magicBall->ball->getDefRad()) {
			magicBall->ball->setRadiusY(magicBall->ball->getRadius().y() + y);
		}
	}
	if (magicBall->ball->getCenter().x() + magicBall->ball->getDefRad() >= magicBall->width()) {
		isPresenceStrainBall = true;
		if (magicBall->ball->getRadius().x() <= magicBall->ball->getDefRad()/4) {
			x = -x;
		}
		if ((magicBall->ball->getRadius().x() - x) <= magicBall->ball->getDefRad()) {
			magicBall->ball->setRadiusX(magicBall->ball->getRadius().x() - x);
		}
	}
	//Ракетка в деле...
	if (magicBall->ball->getCenter().y() + magicBall->ball->getDefRad() >= magicBall->racket->getCoordinates().y()) {
		if ((magicBall->ball->getCenter().x() + magicBall->ball->getDefRad() >= magicBall->racket->getCoordinates().x()) && 
			(magicBall->ball->getCenter().x() - magicBall->ball->getDefRad() <= 
				magicBall->racket->getCoordinates().x() + magicBall->racket->getRacketSize().width())) {

			isPresenceStrainBall = true;
			if (magicBall->ball->getRadius().y() <= magicBall->ball->getDefRad()/4) {
				y = -y;
			}
			if ((magicBall->ball->getRadius().y() - y) <= magicBall->ball->getDefRad()) {
				magicBall->ball->setRadiusY(magicBall->ball->getRadius().y() - y);
			}
		}


		if ((magicBall->ball->getCenter().x() + magicBall->ball->getDefRad() >= magicBall->racket->getCoordinates().x()) && 
			(magicBall->ball->getCenter().x() < magicBall->racket->getCoordinates().x()) && (x > 0)) {
			
			if (magicBall->ball->getRadius().y() <= magicBall->ball->getDefRad()/4) {
				x = -x;
				magicBall->acceleration();
			}
			//if ((magicBall->ball->getRadius().x() - x) <= magicBall->ball->getDefRad()) {
				//magicBall->ball->setRadiusX(magicBall->ball->getRadius().x() - x);
			//}
		}
		if ((magicBall->ball->getCenter().x() - magicBall->ball->getDefRad() <= 
			magicBall->racket->getCoordinates().x() + magicBall->racket->getRacketSize().width()) && 
				(magicBall->ball->getCenter().x() > magicBall->racket->getCoordinates().x() + magicBall->racket->getRacketSize().width()) 
					&& (x < 0)) {
			
			if (magicBall->ball->getRadius().y() <= magicBall->ball->getDefRad()/4) {
				x = -x;
				magicBall->acceleration();
			}
			//if ((magicBall->ball->getRadius().x() + x) <= magicBall->ball->getDefRad()) {
				//magicBall->ball->setRadiusX(magicBall->ball->getRadius().x() + x);
			//}
		}
	}
	
	if (magicBall->ball->getCenter().y() + magicBall->ball->getRadius().y() >= magicBall->height()) {
		magicBall->ball->setRadiusX(magicBall->ball->getDefRad());
		magicBall->ball->setRadiusY(magicBall->ball->getDefRad());
		magicBall->timeControl();
		if (lives > 0) {
			lives = lives - 1;
		}
		return;
	}
	updateShapeBall(); //Необходимо если ракетка выскочила из под шарика, обратимость процесса деформации..
	magicBall->ball->setCenterX(magicBall->ball->getCenter().x() + x);
	magicBall->ball->setCenterY(magicBall->ball->getCenter().y() + y);
}
void State :: restartState() {
	loss();
	lives = 3;
	magicBall->stopAllTimers();
	magicBall->startTimerPaint();
}
void State :: loss() {
	magicBall->ball->setCenterX(magicBall->racket->getCoordinates().x() + magicBall->racket->getRacketSize().width()/2);
	magicBall->ball->setCenterY(magicBall->racket->getCoordinates().y() - magicBall->ball->getDefRad());
}
int State :: getLives() {
	return lives;
}
int State :: getSpeed() {
	return speed;
}
void State :: updateShapeBall() {
	if (!isPresenceStrainBall) {
		magicBall->ball->setRadiusX(magicBall->ball->getDefRad());
		magicBall->ball->setRadiusY(magicBall->ball->getDefRad());	
	}
}
QDomElement State::serialize(QDomDocument * doc) {
	QDomElement stateElement = doc->createElement("State");
	doc->appendChild(stateElement);
	QDomElement lives = doc->createElement("Lives");
	lives.setAttribute("livesleft", this->lives);
	stateElement.appendChild(lives);
	QDomElement racket = doc->createElement("Racket");
	racket.setAttribute("x", this->magicBall->racket->getCoordinates().x());
	racket.setAttribute("y", this->magicBall->racket->getCoordinates().y());
	racket.setAttribute("racketWidth", this->magicBall->racket->getRacketSize().width());
	stateElement.appendChild(racket);
	QDomElement windowSize = doc->createElement("Size");
	windowSize.setAttribute("width", this->magicBall->racket->getWindowSize().width());
	windowSize.setAttribute("height", this->magicBall->racket->getWindowSize().height());
	stateElement.appendChild(windowSize);
	return stateElement;
}
