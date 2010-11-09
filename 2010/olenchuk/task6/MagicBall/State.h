#ifndef STATE_H
#define STATE_H

#include <QDomDocument>
#include <QDomElement>

class MagicBall;

class State {

	public:
		State(MagicBall *magicBall);

	public:
		QDomElement serialize(QDomDocument * doc);
		void updateState();
		void restartState();
		int getLives();
		int getSpeed();

	private:
		void updateShapeBall();
		
		
	private:
		MagicBall *magicBall;
		int lives;
		int speed;
		int x;
		int y;
		bool  isPresenceStrainBall;
};


#endif
