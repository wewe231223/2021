#include "Component.h"


#define COM_MAINCHARACHER 1
#define COM_SUB 2
#define BACKGROUND 3
#define OTHERS 4

//Point - 점 객체에 대한 복사연산자 오버로딩과 생성자 선언
Point::Point() {
	this->x = 0;
	this->y = 0;
}


//Point 선언시 (x,y) 의 형식으로 지정할것 
Point::Point(int a, int b) {
	this->x = a;
	this->y = b;
}


Point& Point::operator=(const Point& other) {

	int tempx = other.x;
	int tempy = other.y;

	memcpy(&(this->x), &tempx, sizeof(int));
	memcpy(&(this->y), &tempy, sizeof(int));


	return *this;
}
/*
	HDC DisplayDC, MemoryDC, ContainerDC, OldDC;//화면출력할 메인 DC, 비트맵을 그려둘 DC, 비트맵을 옮길 DC,비트맵DC선택할 올드DC
	PAINTSTRUCT* ps;
	HBITMAP ExpressBitmap, OldBitmap;
	RECT rect;
*/



Entity::Entity(int c1, int pr1,Point* p1) {

	this->Position = p1;
	this->Code = c1;
	this->Priority = pr1;
	
}


bool Entity::operator< (const Entity& other) {
	return this->Priority < other.Priority;
}


bool Entity::operator> (const Entity& other) {
	return this->Priority > other.Priority;
}




DCManager::DCManager(std::vector<Entity*>* EV) {
	this->EntVec = EV;
}

HDC DCManager::Paint(HWND hWnd) {
	HDC returnDC;
	this->EntVec->begin() = this->iter;

	while (iter != this->EntVec->end()) {
		//tode : returnDC에 벡터안에 있는 모든 비트맵을 제위치에 그리고 
		//       DC를 리턴후 윈도우프로시져에서 더블버퍼링 할 것 

	}





	return returnDC;
}