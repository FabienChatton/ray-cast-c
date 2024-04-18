#include <stdio.h>
#include <setjmp.h>
#include <math.h>
#include <stdlib.h>

#include "gameCtrl.h"
#include "ncusrsIhm.h"

jmp_buf bufJmp;
double playerX;
double playerY;
double playerAngle;

int boardLenghtX;
int boardLenghtY;

char* board;

char getMapInfo(int x, int y)
{
	if (x <= 0) return '1';
	if (x > boardLenghtX) return '1';
	if (y <= 0) return '1';
	if (y > boardLenghtY) return '1';
	return board[y * boardLenghtX + x];
}

void movePlayerUp()
{
	double angleR = playerAngle * (M_PI / 180.0);	
	double xToAdd = cos(angleR) * 0.1;
	double yToAdd = sin(angleR) * -0.1;
	if (getMapInfo(playerX + xToAdd, playerY + yToAdd) == '0')
	{
		playerX += xToAdd;
		playerY += yToAdd;
	}
}

void movePlayerDown()
{
	double angleR = playerAngle * (M_PI / 180.0);	
	double xToAdd = cos(angleR) * -0.1;
	double yToAdd = sin(angleR) * 0.1;
	if (getMapInfo(playerX + xToAdd, playerY + yToAdd) == '0')
	{
		playerX += xToAdd;
		playerY += yToAdd;
	}
}

FILE* openMapFile()
{
	return fopen("map.txt", "r");
}

void testGame()
{
	initIhm();
	FILE* mapFile = openMapFile();
	if (mapFile == NULL)
	{
		printf("creating default map file\n");
		FILE* newMapFile = fopen("map.txt", "w");
		fprintf(newMapFile, "10 10\n1111111111\n1000000001\n1000000001\n1000000001\n1000100001\n1000000001\n1000000001\n1000000001\n1000000001\n1111111111\n");
		fclose(newMapFile);
		mapFile = openMapFile();
		if (mapFile == NULL)
		{
			fprintf(stderr, "inpossible to open map file\n");
			longjmp(bufJmp, 1);
			return;
		}
	}
	else
	{
		printf("open map file success\n");
	}
	fscanf(mapFile, "%d %d", &boardLenghtX, &boardLenghtY);
	board = malloc(boardLenghtX * boardLenghtY * sizeof(char));
	if (board == NULL)
	{
		fprintf(stderr, "inpossible malloc board\n");
		longjmp(bufJmp, 1);
		return;
	}
	
	char lastChar = '\0';
	lastChar = fgetc(mapFile); // ignore new line
	if (lastChar == '\r')
	{
		lastChar = fgetc(mapFile); // ignore new line
	}
	for (int i = 0; i < boardLenghtX; i++) {
		for (int j = 0; j < boardLenghtY; j++) {
			lastChar = fgetc(mapFile);
			
			board[i * boardLenghtX + j] = lastChar;
		}
		lastChar = fgetc(mapFile); // ignore new line
		if (lastChar == '\r')
		{
			lastChar = fgetc(mapFile); // ignore new line
		}
	}
	
	playerX = 2;
	playerY = 2;
	playerAngle = 0;
	
	fclose(mapFile);
	int ch;
	
	
	do
	{
		switch(ch)
			{
			case KEY_LEFT:
				playerAngle -= 5;
				break;
			case KEY_RIGHT:
				playerAngle += 5;
				break;
			case KEY_UP:
				movePlayerUp();
				break;
			case KEY_DOWN:
				movePlayerDown();
				break;	
		}
		
		prepareDraw();
		int maxX = getMaxX();
		
		int x = playerAngle - maxX / 2;
		int xLimite = playerAngle + maxX / 2;
		
		for (int i = x, f = 0; i < xLimite && f < maxX; i++, f++) {
			double dst = getDst2(i);
			draw(f, dst);
		}
		endDraw();
	} while((ch = getch()) != KEY_F(1));
	
	disposeGame();
}

void disposeGame()
{
	free(board);
}

float getDst2(int angleDegre)
{
	int limite = 100000;
	int i = 0;
	double pressision = 0.1;

	double axr = angleDegre * (M_PI / 180.0);
	
	double xToAdd = cos(axr) * pressision;
	double yToAdd = sin(axr) * pressision;
	
	/*
	printf("ay %d\n", ay);
	printf("ax %d\n", ax);
	printf("axr %f\n", axr);
	printf("ayr %f\n", ayr);
	printf("xToAdd %f\n", xToAdd);
	printf("yToAdd %f\n", yToAdd);
	*/
	
	
	double x = playerX;
	double y = playerY;
	double len = 0;
	
	char mapInfo = '0';
	while (mapInfo == '0' && i++ < limite) {
		len += pressision;
		x += xToAdd;
		y -= yToAdd;
		/*
		printf("x %f\n", x);
		printf("y %f\n", y);
		*/
		mapInfo = getMapInfo(x, y);
	}
	
	/*
	printf("x %f %d\n", x, (int) x);
	printf("y %f %d\n", y, (int) y);
	printf("len %f\n", len);
	*/
	return len;
}

double getPlayerX()
{
	return playerX;
}

double getPlayerY()
{
	return playerY;
}

double getPlayerAngle()
{
	return playerAngle;
}


