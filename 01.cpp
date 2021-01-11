#include <cstdlib>
#include <iostream>
#include <ctime>
#include <Windows.h>

#define MAX_WIDTH 50
#define MAX_WIDTH_SCREEN 50
#define MAX_HEIGHT 50
#define MAX_HEIGHT_SCREEN 55

using namespace std;
class Position {
	int x;
	int y;
public:
	Position() {
		x = 0;
		y = 0;
	}
	Position(int a, int b) {
		x = a;
		y = b;
	}
	// setter
	void setX(int mx) {
		this->x = mx;
	}
	void setY(int my) {
		this->y = my;
	}
	void setBoth(int mx, int my) {
		this->x = mx;
		this->y = my;
	}
	// getter
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
};
class Status {
	// base Status
	unsigned int hitPoint;
	unsigned int level;
	unsigned int atk;
	unsigned int def;
	int curHp;

public:
	Status() {
		this -> hitPoint = 10;
		this->level = 1;
		this->atk = 1;
		this->def = 1;
	}
	void levelup(int amount = 1) {
		this->level += amount;
		respec();
	}
	void respec() {
		// level에 따라
		hitPoint = level * 10;
		atk = 1 + (level - 1) * 3;
		def = 1 + (level - 1) * 3;
		curHp = hitPoint;
	}
	void heal(int amount) {
		curHp += amount;
	}

};
class Entity {
	Status myStat;
	Position myPos;
	char shape;
public:
	void setShape(char a) {
		shape = a;
	}
	void changePosition(int mx, int my) {
		myPos.setBoth(mx, my);
	}
	void moveDir(int direction) {	// NSEW: 0123
		switch (direction) {
		case 0:
			// North
			changePosition(myPos.getX(), myPos.getY() + 1);
			break;
		case 1:
			changePosition(myPos.getX(), myPos.getY() - 1);
			break;
		case 2:
			changePosition(myPos.getX() + 1, myPos.getY());
			break;
		case 3:
			changePosition(myPos.getX() - 1, myPos.getY());
			break;
		default:
			//ERROR
			break;
		}
	}
};
class Player :public Entity{
	int gold;
	int score;
	int exp;
	Player() {
		setShape('@');
	}
};
class Game {
	// 게임의 메인 화면, 입력등을 받고 그에 맞는 행동을 하고, 스크린을 출력하고, 맵을 출력함. 
	char screen[MAX_HEIGHT_SCREEN][MAX_WIDTH_SCREEN];		// 얘는 출력 화면
	char entireMap[MAX_HEIGHT][MAX_WIDTH];	// 얘는 전체 맵
	Player me;
	WindowsMech mech;
public:
	Game();
	void gameStart() {
		startOperation();
		while (true) {

		}
	}
	void startOperation() {
		// 메인화면 출력.	-> 이건 나중에.
		// Room 구성. 
		configureRooms();
	}
	void configureRooms() {

	}
	void getKeyInput(char key) {
		switch (key) {
		case 'w':
			me.moveDir(0);
			break;
		case 's': 
			me.moveDir(1);
			break;
		case 'd':
			me.moveDir(2);
			break;
		case 'a':
			me.moveDir(3);
			break;
//		case 'z':

		}
	}
	void configureScreen() {
		for (int i = 0; i < MAX_HEIGHT_SCREEN; i++) {
			for (int j = 0; j < MAX_WIDTH_SCREEN; j++) {
				if (i < MAX_HEIGHT && j < MAX_WIDTH) {
					screen[i][j] = entireMap[i][j];
					continue;
				}
				else if (i == MAX_HEIGHT + 1)
					screen[i][j] = '='; 
			}
		}
	}
};
class Room {
	int width;
	int height;
	char map[30][30];
	Position roomPoint;
public:
	Room() {
		width = 0;
		height = 0;
		roomPoint.setBoth(0, 0);
	}
	Room(int w, int h) {
		width = w;
		height = h;
		createMap();
	}
	void createMap() {
		// width와 height을 이용해 map 구성.
		// 경계		
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++) {
				if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
					map[i][j] = '%';
					continue;
				}
				int item = rand()%100;
				if (item < 15)
					map[i][j] = 'B';
				else if (item < 30)
					map[i][j] = 'O';
				else
					map[i][j] = ' ';
			}
		return;
	}
	void checkSpace(char scr[MAX_HEIGHT][MAX_WIDTH]) {

		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++) {
				scr[roomPoint.getY() + i][roomPoint.getX() + j] = map[i][j];
			}
	}
	void fillScreen(char scr[MAX_HEIGHT][MAX_WIDTH]) {
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
				scr[roomPoint.getY() + i][roomPoint.getX() + j] = map[i][j];
	}
};
class WindowsMech {
	// 출력
	// 커서이동
	// 더블버퍼링

};
int main() {
	srand((unsigned int)time(NULL));
	Game thisGame;

}
// 고대신 60 라스타칸 60 얼왕기 120