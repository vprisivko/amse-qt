#ifndef STATE_H
#define STATE_H

struct State{
  static const int NOTSTARTED = 0;
  static const int STARTED = 1;
  static const int GAMEOVER = 2;
  
  int statetype;
  int ballscount;
  int windowwidth;

  int ballx;
  int bally;
  
  int racketx;
  int rackethalfwidth;
  
  State();
};

#endif
