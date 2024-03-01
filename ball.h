
#ifndef SRC_BALL_H_
#define SRC_BALL_H_

#include <FL/Fl.h>
#include <FL/Fl_Box.h>

class Ball: public Fl_Box{
private:
	int x;
	int y;
	int radius = 5;
	int direction;
	int direction_quad;
	int x0, y0;
	int ticks_since_bounce = -1;


public:
	Ball(int x, int y);
	void move();

	void setXY(int x, int y);
	void setDirection(int direction);
	void reset();

	int getX();
	int getY();
	int getDirection();
	int getRadius();
	int getDirectionQuad();
};

Ball::Ball(int x, int y): Fl_Box(x, y, 20, 20){
	this->box(FL_OFLAT_BOX);
	this->color(FL_RED);
	this->x = x;
	this->y = y;
	this->setDirection((rand() % 50 + 245)); //dir cannot be straight line
	this->show();
};

void Ball::move(){
	this->hide();
	direction = this->getDirection();
	float dy, dx;
	dy = abs(this-> y0 - this-> y);
	dx = abs(this-> x0 - this-> x);
	switch(this->direction_quad){
	//Quadrants 1 through 4:
	case 1:
		if (abs(tan(direction*(M_PI/180)))*dx <dy){
			this->x+=1;
		}
		else{
			this->y-=1;
		}
		break;

	case 2:
		if (abs(tan(direction*(M_PI/180)))*dx <dy){
			this->x-=1;
		}
		else{
			this->y-=1;
		}
		break;

	case 3:
		if (abs(tan(direction*(M_PI/180)))*dx <dy){
			this->x-=1;
		}
		else{
			this->y+=1;
		}
		break;

	case 4:
		if (abs(tan(direction*(M_PI/180)))*dx <dy){
			this->x +=1;
		}
		else{
			this->y+=1;
		}
		break;
	}
	this->position(this->x, this->y);
	this->show();
};


//===========================
//Setters
//===========================
void Ball::setXY(int x, int y){
	this-> x = x;
	this-> y = y;
}

void Ball::setDirection(int direction){
	//if direction vector is parallel to one of the axis:
	if(direction % 90 == 0){
		direction+=1;
	}
	if(direction>359){
		direction = (360-direction) + 1;
		this->direction = direction;
	}
	else if(direction<0){
		direction = 360 + direction;
		this->direction = direction;
	}
	this->direction = direction;
	this->direction_quad = int(ceil(direction/90)+ 1);
	this->x0 = this->x;
	this->y0 = this->y;
}

void Ball::reset(){
	this->setXY(320,240);
	this->setDirection((rand() % 50 + 245));

}




//===========================
//Getters
//===========================
int Ball::getX(){
	return this-> x;
}
int Ball::getY(){
	return this->y;
}
int Ball::getDirection(){
	return this->direction;
}
int Ball::getRadius(){
	return this->radius;
}
int Ball::getDirectionQuad(){
	return this->direction_quad;
}





#endif /* SRC_BALL_H_ */
