#include "ncusrsIhm.h"
#include "gameCtrl.h"

int row, col;
void initIhm()
{
	
	initscr();			/* Start curses mode 		*/
	raw();				/* Line buffering disabled	*/
	keypad(stdscr, TRUE);		/* We get F1, F2 etc..		*/
	noecho();			/* Don't echo() while we do getch */
	
	
}

void draw(int col, int distance)
{
	#ifdef _WIN32
	attron(A_DIM);
	#endif // windows
	
	for (int i = distance; i < row - distance; i++) {
		#ifdef _WIN32
		mvprintw(i, col, " ");
		#endif // windows
		
		#ifdef linux
		mvprintw(i, col, "#");
		#endif // linux
		
	}
	#ifdef _WIN32
	attroff(A_DIM);
	#endif // windows
}

void disposeIhm()
{
	endwin();			/* End curses mode		  */
}

void setMaxXY()
{
	getmaxyx(stdscr,row,col);
}

int getMaxX()
{
	setMaxXY();
	return col;
}

int getMaxY()
{
	setMaxXY();
	return row;
}

void prepareDraw()
{
	clear();
	setMaxXY();
}

void endDraw()
{
	mvprintw(0, 0, "press f1 to quite, x: %f, y: %f, a: %f", getPlayerX(), getPlayerY(), getPlayerAngle());
	refresh();
}