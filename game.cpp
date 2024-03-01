
#define WIN32
#include <iostream>
#include <random>
#include <time.h>
#include <conio.h>
#include <vector>
#include "std_lib_facilities.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/FL_Text_Display.H>
#include "Graph.h"
#include "ball.h"
#include "brick.h"
#include "board.h"
#include "mechanics.h"




int w_width = 640;
int w_height = 480;



int main() {
	srand(time(NULL));
	int score = 0;
	int lives = 3;

//Initialize Objects
	//The Window:
	Fl_Window *window = new Fl_Window(100, 100, w_width+20, w_height+20, "Bip-bop");
	//The Board/Paddle
	Board *board = new Board(260, 440);
	//The Bricks
	vector<Brick*> bricks;
		//total of 48 possible bricks, with differing integrities (0 also possible), distributed over 3 rows
	int n_bricks; //number used to determine when game has been won/all bricks have been broken
	for (int i=0; i<48; i++){
		bricks.push_back(new Brick(i%16*40, i/16*40, rand()%4));
		if (bricks[i]->broken()==false){
			n_bricks++;
		}
	}
	//The Ball
	Ball *ball = new Ball(320,240);
	//=============================

	//Setup up in-game information
	Fl_Text_Display *disp = new Fl_Text_Display(20, 460, 80, 480);
	Fl_Text_Buffer *tbuff = new Fl_Text_Buffer();
	Fl_Text_Buffer *sbuff = new Fl_Text_Buffer();
	tbuff->text("Score    0\nLives    3");
	sbuff->text("AAAAAAAAAA\nAAAAAAAAAA\n");
	disp->buffer(tbuff);
	//start up window
	window->show();
	//=============================

	//game loop
	while(Fl::wait()){
		//Check if ball bounces off of something
		BounceOffWall(ball);
		BounceOffBoard(ball, board);
			//iterate over bricks and check for collision with ball
		for(int i=0; i<bricks.size(); i++){
			if (bricks[i]->broken()){
				continue;
			}
			else if(BounceOffBrick(ball, bricks[i])){
				bricks[i]->hit();
				if(bricks[i]->broken()){				//if a brick breaks, a score point is granted
					score+=1;
				}
				break;
			}
		}
		if(score == n_bricks){  //Player has won
			break;
		}

		//Ball moves and check if dead
		ball->move();
		if(ball->getY()>w_height){
			lives--;
			ball->reset();
			if(lives <= 0){
				break;
			}
		}
		//Hard coded solution, will terminate when any button is pressed
		board->followBall(ball);

		//update scores and lives to window
		string new_text = "Score   "+to_string(score)+"\nLives    "+to_string(lives);
		tbuff->text(new_text.c_str());
		disp->buffer(tbuff);


		Sleep(1);
	}
	//=============================

	//End of Game
	cout <<"Final score: "<< score<<endl;
	return 0;

}


