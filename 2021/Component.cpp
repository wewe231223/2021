#include "Component.h"


#define COM_MAINCHARACHER 1
#define COM_SUB 2
#define BACKGROUND 3
#define OTHERS 4

//Point - �� ��ü�� ���� ���翬���� �����ε��� ������ ����
Point::Point() {
	this->x = 0;
	this->y = 0;
}


//Point ����� (x,y) �� �������� �����Ұ� 
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
	HDC DisplayDC, MemoryDC, ContainerDC, OldDC;//ȭ������� ���� DC, ��Ʈ���� �׷��� DC, ��Ʈ���� �ű� DC,��Ʈ��DC������ �õ�DC
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
		//tode : returnDC�� ���;ȿ� �ִ� ��� ��Ʈ���� ����ġ�� �׸��� 
		//       DC�� ������ ���������ν������� ������۸� �� �� 

	}





	return returnDC;
}