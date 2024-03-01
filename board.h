
#ifndef SRC_BOARD_H_
#define SRC_BOARD_H_
#include <FL/Fl.h>
#include <FL/Fl_Box.h>
#include "Ball.h"


class Board: public Fl_Box{
private:
	int x;
	int y;
	bool no_player = true;

public:
	Board(int x, int y);
	void move(int incr);
	void followBall(Ball* ball);
	int handle(int event);
	int getX();
	int getY();


};

Board::Board(int x, int y): Fl_Box(x, y, 120, 20){
	this->box(FL_FLAT_BOX);
	this->color(FL_BLACK);

	this->x = x;
	this->y = y;

	this->show();

};

void Board::move(int incr){
	this->hide();
	this->x += incr;
	this->position(this->x, this->y);
	this->show();
}

void Board::followBall(Ball* ball){
	if(no_player){
		int ballx = ball->getX();
		int dx = (ballx + 5) - (this->x + 60);

		//If dx is positive, move to right, otherwise move to left
		int incr = dx / abs(dx);
		this->move(incr);
	}
}

int Board::handle(int event){
    // returned int key codes
    int RKey = 100;
    int LKey = 97;
    switch(event)
    {
        //press down any key
        case 12:
        	this->no_player=false;
            if(Fl::event_key() == FL_Left || Fl::event_key() == LKey){
                //left
            	if(this->x > -90) this->move(-5);
                return 1;
            }
            else if(Fl::event_key() == FL_Right || Fl::event_key() == RKey){
                //right pressed
            	if (this->x< 610)this->move(5);
                return 1;
            }
         //no break
         default: return Fl_Widget::handle(event);
    }
}

//====================
//Getters
//====================

int Board::getX(){
	return this-> x;
}

int Board::getY(){
	return this-> y;
}

#endif /* SRC_BOARD_H_ */
