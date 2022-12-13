#ifndef __STATE_H__
#define __STATE_H__

typedef struct state
{
  void (*init)(void);
  void (*loop)(void);
} state;

extern state intro;
extern state game;
extern state gameover;

extern state *active;
extern state *next;

extern int victory;

#endif