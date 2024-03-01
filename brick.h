
#ifndef SRC_BRICK_H_
#define SRC_BRICK_H_

#include <FL/Fl.h>
#include <FL/Fl_Box.h>

class Brick: public Fl_Box{
private:
	int x;
	int y;
	int integrity;
	bool isBroken = false;

public:
	Brick(int x, int y, int integrity);
	int getX();
	int getY();
	void setColor();
	void hit();
	void crumble();
	bool broken();


};

Brick::Brick(int x, int y, int integrity): Fl_Box(x, y, 40, 40){
	this->box(FL_FLAT_BOX);
	this->x = x;
	this->y = y;
	this->integrity=integrity;
	this->setColor();
	if (integrity==0){
		this->crumble();
	}
	this->show();

};

void Brick::setColor(){
	integrity = this->integrity;
	if (integrity==3){
		this->color(FL_BLUE);
	}
	else if (integrity==2){
		this->color(FL_GREEN);
	}
	else if (integrity==1){
		this->color(FL_WHITE);
	}
	else if (integrity<=0){
		this->color(FL_GRAY);
	}
}

void Brick::hit(){
	this->integrity-=1;
	this->setColor();
	if (integrity<=0){
		this->crumble();
	}
}
void Brick::crumble(){
	this->isBroken=true;
}

bool Brick::broken(){
	return this->isBroken;
}
//=================
//Getters
//=================

int Brick::getX(){
	return this->x;
}

int Brick::getY(){
	return this->y;
}


#endif /* SRC_BRICK_H_ */
