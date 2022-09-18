#pragma once
#include "2021.h"

class Point {
public:

	int x;
	int y;


	Point();
	Point(int, int);
	~Point() {};

	Point& operator=(const Point&);


};



class Shape {

public:
	Point Center;

	Shape() {};
	~Shape() {};


	virtual void draw() = 0;
	virtual void move(Point) = 0;

};

class Entity {

public:
	int Code;
	Point* Position;



	Entity() {}
	~Entity() {}

	Entity(int,Point*);


};

class DCManager {
private:
	//엔티티 출력 관련 벡터 
	std::vector<Entity*>* EntVec;
	std::vector<Entity*>::iterator iter;
	
	//더블버퍼링 관련 변수
	PAINTSTRUCT ps;
	
	HDC BufferDC, CanvasDC;
	HBITMAP BufferBitmap, EntityBitmap, OldBitmap;


public:
	
	~DCManager() {}

	void Resister(std::vector<Entity*>*);
	HDC Paint(HWND,const HDC*,const HINSTANCE*,RECT*);
	void Free();
};


void KnightAnimation(Entity* , bool* , int );
bool ChangeState(Entity*, int);
