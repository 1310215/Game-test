#include <iostream>
#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

#define COURSE_WIDTH   (16)
#define COURSE_HEIGHT  (16)

#define SCREEN_WIDTH   (16)
#define SCREEN_HEIGHT  (16)

#define UPDATE_FPS      (60)
#define UPDATE_INTERVAL (1000/UPDATE_FPS)

#define DRAW_FPS        (10)
#define DRAW_INTERVAL   (1000/DRAW_FPS)

typedef struct {
	float x, y;
}VEC2;
typedef struct {
	VEC2 position;
	VEC2 velocity;
}PLAYER;

char course[COURSE_HEIGHT][COURSE_WIDTH] = {
	"               ",
	"               ",
	"               ",
	"               ",
	"               ",
	"               ",
	"               ",
	"               ",
	"               ",
	"               ",
	"               ",
	"               ",
	"               ",
	"               ",
	"bbbbbbbbbbbbbbb",
	"bbbbbbbbbbbbbbb",
};

char screen[SCREEN_HEIGHT][SCREEN_WIDTH];

char aa[256][2 + 1];

PLAYER player;

bool keyPressed[256];

void DrawScreen() {
	for (int y = 0; y < SCREEN_HEIGHT; y++)
		for (int x = 0; x < SCREEN_WIDTH; x++)
			screen[y][x] = course[y][x];
	{
		int x = roundf(player.position.x);
		int y = roundf(player.position.y);

		if( x>=0 && x < SCREEN_WIDTH
		&& y>=0 && y < SCREEN_HEIGHT)
			screen[y][x] = '@';
	}
	
system("cls");
	for (int y = 0; y < SCREEN_HEIGHT; y++) {
		for (int x = 0; x < SCREEN_WIDTH; x++)
			printf("%s",aa[screen[y][x]]);
		printf("\n");
	}
}

void Init() {
	player.position = {4,13};

	memset(keyPressed,0,sizeof keyPressed);
	DrawScreen();
}

int main(){
	sprintf_s(aa['b'], "■");
	sprintf_s(aa[' '], "　");
	sprintf_s(aa[0],"✕");
	sprintf_s(aa['@'], "★");

	Init();

	clock_t lastUpdateClock = clock();
	clock_t lastDrawClock = clock();
	while (1) {
		clock_t nowClock = clock();
		if(nowClock >= lastUpdateClock + UPDATE_INTERVAL) {
			lastUpdateClock = nowClock;

			float acceleration = 0.005f;
			if(keyPressed['d']) player.velocity.x+=acceleration;
            if(keyPressed['a']) player.velocity.x-=acceleration;

			player.velocity.x *= 0.95f;

			player.position.x += player.velocity.x;
			player.position.y += player.velocity.y;

		}

		if(nowClock >= lastDrawClock + DRAW_INTERVAL) {
			lastDrawClock = nowClock;

			DrawScreen();
		}

		if(_kbhit()) {
			switch(_getch()) {
				case 'a':
					if(keyPressed['d'])
						keyPressed['d'] = false;
					else
						keyPressed['a'] = true;
					break;

				case 'd':
					if(keyPressed['a'])
						keyPressed['a'] = false;
					else
						keyPressed['d'] = true;
					break;
					//追加コード
				default:
					keyPressed['a'] = false;
					keyPressed['d'] = false;
					player.velocity.x = 0;
					break;
			}
		}
	}
}


