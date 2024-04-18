#ifndef NCUSRS_IHM_H
#define NCUSRS_IHM_H

#ifdef _WIN32
#include <ncurses/ncurses.h>
#endif // windows

#ifdef linux
#include <ncurses.h>
#endif // linux

void prepareDraw();
void endDraw();
void draw(int, int);
void initIhm();
void disposeIhm();

void testIhm();
int getMaxX();
int getMaxY();
#endif // NCUSRS_IHM_H