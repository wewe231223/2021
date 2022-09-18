#include "Component.h"


#define COM_MAINCHARACHER 1
#define COM_SUB 2
#define BACKGROUND 3
#define OTHERS 4

#define BitmapSize 192

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





Entity::Entity(int c1,Point* p1) {

	this->Position = p1;
	this->Code = c1;

}




void DCManager::Resister(std::vector<Entity*>* EV) {
	this->EntVec = EV;
}



#define BKRGB RGB(255,255,255)
//Paint(윈도우 핸들,표시할 메인DC,전역 인스턴스 포인터,화면 크기 연산한 RECT객체 포인터)
HDC DCManager::Paint(HWND hWnd,const HDC* mainDCPtr,const HINSTANCE* hInstPtr,RECT* rect) {
	this->EntVec->begin() = this->iter;

	this->CanvasDC = CreateCompatibleDC(*mainDCPtr);
	this->BufferDC = CreateCompatibleDC(*mainDCPtr);


	BufferBitmap = CreateCompatibleBitmap(*mainDCPtr,  (*rect).right, (*rect).bottom);
	SelectObject(this->BufferDC, BufferBitmap);
	FillRect(this->BufferDC, rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

	for (this->iter = this->EntVec->begin(); iter != this->EntVec->end();iter++) {
		
		this->EntityBitmap = LoadBitmap(*hInstPtr, MAKEINTRESOURCE((*iter)->Code));
		
		this->OldBitmap = (HBITMAP)SelectObject(this->CanvasDC, this->EntityBitmap);

		TransparentBlt(this->BufferDC, (*iter)->Position->x, (*iter)->Position->y, BitmapSize, BitmapSize,
					this->CanvasDC, 0, 0, BitmapSize, BitmapSize, BKRGB);
	
	}
	return this->BufferDC;
}









void DCManager::Free() {

	DeleteObject(SelectObject(this->BufferDC, this->BufferBitmap));
	DeleteObject(this->EntityBitmap);
	DeleteDC(this->BufferDC);
	DeleteDC(this->CanvasDC);

}

void KnightAnimation(Entity* K,bool* Reverse,int AniType){
	


	if (AniType == 1) {//idle situation

		if (!ChangeState(K, AniType)) {
			K->Code = Knight1;
		}

		switch (*Reverse) {

		case TRUE:
			if (K->Code == Knight1) {
				*Reverse = FALSE;
				K->Code++;
				break;
			}
			else {
				K->Code--;
				break;
			}
		case FALSE:
			if (K->Code == Knight4) {
				*Reverse = TRUE;
				K->Code--;
				break;
			}
			else {
				K->Code++;
				break;
			}
		}


	}
	else if (AniType == 2) { // Walk situation

		if (!ChangeState(K, AniType)) {
			K->Code = WalkKnight1;
		}
		
		
		if (K->Code == WalkKnight8) {
			K->Code = WalkKnight1;
		}
		else {
			K->Code++;
		}

	}

}

bool ChangeState(Entity* K, int aniT){

	switch (aniT){

	case 1:
		if (K->Code == Knight1 ||
			K->Code == Knight2 ||
			K->Code == Knight3 ||
			K->Code == Knight4 ) {
			return TRUE;
		}
		else {
			return FALSE;
		}

	case 2:
		if (K->Code == WalkKnight1 ||
			K->Code == WalkKnight2 || 
			K->Code == WalkKnight3 || 
			K->Code == WalkKnight4 || 
			K->Code == WalkKnight5 ||
			K->Code == WalkKnight6 ||
			K->Code == WalkKnight7 ||
			K->Code == WalkKnight8  ) {
			return TRUE;
		}
		else {
			return FALSE;
		}

	default:
		break;
	}



	return false;
}
