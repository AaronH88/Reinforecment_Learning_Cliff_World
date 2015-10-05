#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "cliffWorld.c"

#define North 0
#define South 1
#define East  2
#define West  3

struct boardPos cliffWorld[4][12];

#define n (4*12)
#define m  4
double lookUpTable[n][m];

struct player {
  int x;
  int y;
};

struct availableMoves {
  int N;
  int S;
  int E;
  int W;
};

struct availableMoves getAvailMoves(int x, int y) {
  int xPos = x;
  int yPos =  y;
  struct availableMoves avail = {.N = 1, .S = 1, .E = 1, .W = 1};

  if (xPos <= 0)
    avail.N = 0;
  if (xPos >= 3)
    avail.S = 0;
  if (yPos <= 0)
    avail.W = 0;
  if (yPos >= 11)
    avail.E = 0;

  return avail;
}

int chooseAction (struct player p, double epsilon) {
  int action, i, count = 0;
  double q[4] = {0};
  double maxQ;
  // find the q values in cliffWorld look up table
  for(i = 0; i < 4 ; i++) {
    q[i] = cliffWorld[p.x][p.y].action_Q_Value[i];
  } 

  double ran = (rand() % 10);
  //explore :)
  if(ran < (epsilon * 10)) {
    action = (rand() % 4);
  } else{
  //find the max q value available
    maxQ = q[0];
    action = 0;
    for(i = 1; i < 4; i++) {
      if(q[i] > maxQ) { 
	maxQ = q[i];
	action = i;
      }
    }// for
    //check to see if their is more than one max value
    for(i = 0; i < 4; i++){
      if(q[i] == maxQ) { 
	count++;
      }
    }// for
    //if you have more than one max value you must randomly choose between the maxes
    if(count > 1){
      int r = rand() % count;
      int random = 0;
      for(i = 0; i < 4; i++) {
	if(q[i] == maxQ){
	  if(r == random){
	    action = i;
	  }// if
	  random++;
	}// if
      }// for
    }// if
  }// else
  return action;
}


//display the grid world and show the action values

void printMap() {
  int i , j;
  double no = 0.0, so = 0.0, ea = 0.0, we = 0.0;
  printf("\n\n\n\n\n\n\n\n");
  for(i = 0; i < 4; i++){
    for(j = 0; j < 12; j++){

      no = cliffWorld[i][j].action_Q_Value[0];
      so = cliffWorld[i][j].action_Q_Value[1];
      ea = cliffWorld[i][j].action_Q_Value[2];
      we = cliffWorld[i][j].action_Q_Value[3];
      printf("n: %lf | s: %lf | e: %lf | w: %lf || " , no, so, ea, we);

    }
    printf("\n\n");
  }

}

double calReward(struct player p ) { 
  double reward = -0.1;
  reward += cliffWorldMap[p.x][p.y];
  return reward;
}


int main(int argc, char **argv)
{
  srand(time(NULL));
  int i = 0, j = 0, k = 0;
  double epsilon = 0.9; 
  double alpha = 0.1; 
  double gamma = 0.9;

  // setting up the lookUp table
  for(i = 0; i < n; i++ ) {
    for(j = 0; j < m; j++) {
      lookUpTable[i][j] = 0.0;
      //printf("%d ", lookUpTable[i][j]);
    }
    // printf("\n");
  }

  //setting up the grid world

  for(i = 0; i < 4; i++ ) {
    for(j = 0; j < 12; j++) {
      struct boardPos x;
      x.xPos = i;
      x.yPos = j;
      x.stateValue = cliffWorldMap[i][j];
      for(k = 0; k < 4; k++)
	x.action_Q_Value[k] = 0;
      cliffWorld[i][j] = x;
    }
  }

  int win = 0, loss = 0;

 for(i = 0; i < 100000; i++){
   struct player play = {.x = 3, .y = 0};
   int noOfMoves = 0;
   double this_Q, max_Q, new_Q;
   
   while((play.x != 3 || play.y != 11) &&
	 (play.x != 3 || play.y != 10) &&
	 (play.x != 3 || play.y != 9)  &&
	 (play.x != 3 || play.y != 8)  &&
	 (play.x != 3 || play.y != 7)  &&
	 (play.x != 3 || play.y != 6)  &&
	 (play.x != 3 || play.y != 5)  &&
	 (play.x != 3 || play.y != 4)  &&
	 (play.x != 3 || play.y != 3)  &&
	 (play.x != 3 || play.y != 2)  &&
	 (play.x != 3 || play.y != 1) ){

     int old_X = play.x;
     int old_Y = play.y;
          
     int action = chooseAction(play, epsilon); 

     //get the q value of this state before you move
     this_Q = cliffWorld[play.x][play.y].action_Q_Value[action];
     struct availableMoves avail = getAvailMoves(play.x, play.y);

   
     if(action == North && avail.N == 1){
       play.x -= 1;
     }
     if(action == South && avail.S == 1){
       play.x += 1;
     }
     if(action == East && avail.E == 1){
       play.y += 1;
     }
     if(action == West && avail.W == 1){
       play.y -= 1;
     }
     noOfMoves++;

     //printf("action: %d\n", action);
     //printf("play.x: %d\tplay.y: %d\n",play.x , play.y);
     int newState = (play.x * play.y);
     double reward = calReward(play);
     //reward += cliffWorldMap[play.x][play.y];

     //find the max q value available
     max_Q = cliffWorld[play.x][play.y].action_Q_Value[0];
     int j;
     for(j = 1; j < 4; j++) {
       if(cliffWorld[play.x][play.y].action_Q_Value[j] > max_Q) { 
	 max_Q = cliffWorld[play.x][play.y].action_Q_Value[j];
       }
     }

     // Calculate new value for Q
     new_Q = this_Q + alpha * (reward + gamma * max_Q - this_Q);
     // set the new Q value
     cliffWorld[old_X][old_Y].action_Q_Value[action] = new_Q;

   }// while
   
   if(play.x == 3 && play.y == 11)
     win++;
   else
     loss++;
   printf("Number of moves: %d\twins: %d\tlosses: %d\n" , noOfMoves, win, loss);
   if((i % 100) == 0) {
      printMap();
   } 
   // slowly lower exploration
   if((i+1) % 1000) {
     epsilon -= 0.01;
   }

 }// for
 
 return 0;
}
