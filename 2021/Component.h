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
private:
	int Priority;
public:
	int Code;
	Point* Position;



	Entity() {}
	~Entity() {}

	Entity(int,int ,Point*);

	bool operator< (const Entity& other);
	bool operator> (const Entity& other);
};




class DCManager {
private:
	std::vector<Entity*>* EntVec;
	std::vector<Entity*>::iterator iter;


public:
	DCManager(std::vector<Entity*>* EV);
	~DCManager() {}

	HDC Paint(HWND);


};