
#ifndef SRC_MECHANICS_H_
#define SRC_MECHANICS_H_

#include <iostream>
#include <random>
#include <time.h>
#include <conio.h>
#include "std_lib_facilities.h"
#include "board.h"
#include "ball.h"
#include "brick.h"


bool BounceOffWall(Ball* ball){
	int x,y,x_graph,y_graph,direction,radius;
	x_graph = ball->getX();
	y_graph = ball->getY();
	direction = ball->getDirection();
	radius = ball->getRadius();
	x = x_graph+5;
	y = y_graph+5;



	//Bounce off vertical wall
	if(x - radius <= 0 or x + radius  >= 640){
		//Bounce up
		if(direction<180){
				ball->setDirection(90+(90 - direction));
			}
		//Bounce down
		else if(direction>180){
			ball->setDirection(270+(270 - direction));
		}
		if(x - radius <= 0){
			ball->setXY(x_graph+1, y_graph);
		}
		else{
			ball->setXY(x_graph-1, y_graph);
		}
		return true;
	}
	//Bounce off horizontal wall
	else if(y - radius <= 0){
		//Bounce left
		if(direction>90){
			ball->setDirection(180+(180 - direction));
		}
		//Bounce right
		else if(direction<90){
			ball->setDirection(- direction);
		}
		ball->setXY(x_graph, y_graph+1);
		return true;
	}
	else{
		return false;
	}
}

bool BounceOffBoard(Ball* ball, Board* board){
	int x,y,x_graph,y_graph,direction,radius, boardx, boardy,width,height;
	x_graph = ball->getX();
	y_graph = ball->getY();
	direction = ball->getDirection();
	radius = ball->getRadius();
	boardx = board->getX();
	boardy = board->getY();
	x = x_graph + 5;
	y = y_graph + 5;
	width = 120;
	height = 20;

	//if ball collides with board
	if(y + radius >= boardy - height/2 && x <= boardx + width && x >= boardx){
		//ball collides with left side of board
		if(x <= boardx + width/10 * 2){
			//Bounce left
			if(direction<270){
				ball->setDirection(direction-30);
			}
			//Bounce right
			else if(direction>270){
				ball->setDirection(direction-240);
			}
		}
		//ball collides with right side of board
		else if(x >= boardx + width/10 * 8){
			//Bounce left
			if(direction<270){
				//ball->setDirection(180+(180 - direction)-30);
				ball->setDirection(direction-30);
			}
			//Bounce right
			else if(direction>270){
				//ball->setDirection(180+(180 - direction)+30);
				ball->setDirection(direction-240);
			}
		}
		//else ball collides with middle of board
		else{
			//Bounce left
			if(direction<270){
				ball->setDirection(180+(180 - direction));
			}
			//Bounce right
			else if(direction>270){
				ball->setDirection(180+(180 - direction));
			}
		}
		return true;
		ball->setXY(x_graph, y_graph-1);
	}
	else{
		return false;
	}
}



void HorizontalBounceLower(Ball* ball){
	int direction = ball->getDirection();
	//Bounce left
	if(direction>90){
		ball->setDirection(180+(180 - direction));
	}
	//Bounce right
	else if(direction<90){
		ball->setDirection( -direction);
	}
	ball->setXY(ball->getX(), ball->getY()+1);
}

void HorizontalBounceUpper(Ball* ball){
	int direction = ball->getDirection();
	//Bounce left
	if(direction<270){
		ball->setDirection(180 + (270 - direction));
	}
	//Bounce right
	else if(direction>270){
		ball->setDirection(abs(direction - 270));

	ball->setXY(ball->getX(), ball->getY()-1);
	}
}

void VerticalBounceLeft(Ball* ball){
	int direction = ball->getDirection();
	//Bounce up
	if(direction<180){
		ball->setDirection(90+(90 - direction));
	}
	//Bounce down
	else if(direction>180){
		ball->setDirection(270+(270 - direction));
	}
	ball->setXY(ball->getX()-1, ball->getY());
}

void VerticalBounceRight(Ball* ball){
	int direction = ball->getDirection();
	//Bounce up
	if(direction<180){
		ball->setDirection(90+(90 - direction));
	}
	//Bounce down
	else if(direction>180){
		ball->setDirection(270+(270 - direction));
	}
	ball->setXY(ball->getX()+1, ball->getY());
}



bool BounceOffBrick(Ball* ball, Brick* brick){
	int x,y,x_graph,y_graph,radius, brickx, bricky,width;
	x_graph = ball->getX();
	y_graph = ball->getY();
	radius = ball->getRadius();
	brickx = brick->getX();
	bricky = brick->getY();
	x = x_graph + 5;
	y = y_graph + 5;
	width = 40;

	//if ball collides with brick on a horizontal side
	if(x >= brickx && x <= brickx + width && (y + radius == bricky || y - radius == bricky + width)){
		//ball collides with lower horizontal side
		if(y - radius <= bricky + width){
			HorizontalBounceLower(ball);
		}
		//ball collides with upper horizontal side
		else if(y + radius >= bricky){
			HorizontalBounceUpper(ball);
		}
		return true;
	}
	//if ball collides with brick on a vertical side
	else if((x + radius == brickx || x - radius == brickx + width) && y >= bricky && y<= bricky + width){
		//ball collides with left vertical side
		if(x + radius == brickx){
			VerticalBounceLeft(ball);
		}
		//ball collides with right vertical side
		else if(x - radius == brickx + width){
			VerticalBounceRight(ball);
		}
		return true;
	}
	else{
		return false;
	}
}
#endif /* SRC_MECHANICS_H_ */
