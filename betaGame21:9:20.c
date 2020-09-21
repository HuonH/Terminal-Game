//Game Code
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//variables and constants
char move;
int maxL = 20;
int maxH = 20;

//monster pos
int mH = 15;
int mL = 5;
//target pos
int tH = 15;
int tL = 17;
int counter = 0;
int score = 0;
//obstacles
struct point {
    int h;
    int l;
};

//initialize monster and player;

//functions
void display(int playerH, int playerL, int monsterH, int monsterL, int targetH, int targetL); //displays details
char getMove(void); // gets move from user
void actMove(int action, int height, int length); //computes new position for inputted move
int gameOver(int playerH,int playerL,int monsterH,int monsterL); //checks wether game over or not
void monsterMove(int mH, int mL, int pH, int pL); //moves monster
int checkObs(int height, int length); //checks if inputted point is occupied returns 1 if not occupied
void highscore(int score); //write highscore function, write to text file
int sees(int monsterH, int monsterL,int playerH,int playerL);
void scoring(int playerH, int playerL, int targetH, int targetL);
float bRand(float minlim, float maxlim, char subset); // "random" number generator
// potentially levels function?

int pH = 5;
int pL = 10;
int main(void)
{
  //instructions
  printf("Get the Treasure!\nDon't Get Eaten!\n");
  printf("Controls: \nn -> up\ns -> down\ne -> right\nw -> left\nX -> Quit\n");
    //implement do while looop for game true/false condition
    do {
      display(pH,pL,mH,mL,tH,tL);

      move = getMove();

      actMove(move,pH,pL);


      monsterMove(mH, mL, pH, pL);

      counter++;
      scoring(pH,pL,tH,tL);
    } while(gameOver(pH,pL,mH,mL));
    display(pH,pL,mH,mL,tH,tL);
}

void display(playerH,playerL,monsterH,monsterL,targetH,targetL)
{
  for(int h = 0; h <= maxH; h++)
  {
      for(int l = 0; l <= maxL; l++)
      {
          if(h == monsterH && l == monsterL)
          {
              printf("M"); //player location
          }
              else if(h == 0 || h == maxH)
              {
                  printf("_"); //top border
              }
              else if(l == 0 || l == maxL)
              {
                  printf("|"); //bottom border
              }
              else if(h == playerH && l == playerL)
              {
                  printf("O"); //target location
              }
              else if(h == targetH && l == targetL)
              {
                  printf("$");//monster location
              }
              else if(!(checkObs(h,l)))
              {
                  printf("#");//obstacles
              }
              else
              {
                  printf(" ");
              }
      }
      printf("\n");
  }

  printf("\n");
}

char getMove(void)
{
  //gets player move input
  do {
      scanf("%c",&move);//move = getchar( );
  } while(!(sizeof(move) == 1 && (move == 'n'|| move == 's'|| move == 'e'|| move == 'w' || move == 'X')));
  return move;
  printf("\n");
}

void actMove(action,height,length)
{
  int nextH = height;
  int nextL = length;
  //player actions
    if(action == 'n' && nextH != 1)
    {
        nextH--;// = pH - 1;
    }
    else if(action == 's' && nextH != maxH - 1)
    {
        nextH++;// = pH + 1;
    }
    else if(action == 'w' && nextL != 1)
    {
        nextL--;// = pL - 1;
    }
    else if(action == 'e' && nextL != maxL - 1)
    {
        nextL++;// = pL + 1;
    }

  //check next moves do not run into obstacles
  int cond = checkObs(nextH,nextL);
  if(cond == 1)
  {
      pH = nextH;
      pL = nextL;
  }
  else
  {
      pH = height;
      pL = length;
  }
}

int checkObs(int height, int length)
{

  struct point ob1,ob2,ob3,ob4,ob5,ob6,ob7,ob8;
  ob1.h = 6;
  ob1.l = 10;
  ob2.h = 5;
  ob2.l = 5;
  ob3.h = 10;
  ob3.l = 12;
  ob4.h = 15;
  ob4.l = 3;
  ob5.h = 18;
  ob5.l = 17;
  ob6.h = 15;
  ob6.l = 4;
  ob7.h = 15;
  ob7.l = 10;
  ob8.h = 17;
  ob8.l = 12;

  struct point obstacles[8] = {ob1,ob2,ob3,ob4,ob5,ob6,ob7,ob8}; //obstacle structure containing point obstacles

  int obLength = sizeof(obstacles)/sizeof(ob1);
  int cond = 1;
  for(int z = 0; z <= obLength; z++)
  {
      struct point curOb = obstacles[z];
      int obH = curOb.h;
      int obL = curOb.l;
      if(height == obH && length == obL)
      {
        cond = 0;
        return cond;
      }
  }
  return cond;
}

void monsterMove(monsterH, monsterL, playerH, playerL)
{
    //random movement every 5 moves
    int step;
    int move = 0;
    int seen = sees(monsterH,monsterL,playerH,playerL);

    float hGap2 = pow((monsterH - playerH),2);
    float lGap2 = pow((monsterL - playerL),2);
    float distance = pow((lGap2 + hGap2),0.5); //getting distance between m and p

    if(distance < 2) //ansolute difference less than 2 eaten
    {
        monsterH = playerH;
        monsterL = playerL;
    }
    else if(seen == 1)//same H, Monster moves in L
    {
        printf("~spotted~\n");
        if(abs(monsterL - playerL) < 4)
        {
            monsterL = playerL;
        }
        else
        {
            if(playerL < monsterL)
            {
                step = -1;
            }
            else if(playerL > monsterL)
            {
                step = 1;
            }
            do {
              if(playerL == monsterL)
              {
                  printf("Eaten\n");
                  return;//gameover
              }
              else
              {
                  monsterL = monsterL + step;
                  move++;
              }
            } while(move <= 4);
        }
    }
    else if(seen == 2)//same L, monster moves in H
    {
        printf("~spotted~\n");
        if(abs(monsterH - playerH) < 4)
        {
            monsterH = playerH;
        }
        else
        {
            if(playerH < monsterH)
            {
                step = -1;
            }
            else if(playerH > monsterH)
            {
                step = 1;
            }
            do {
              if(playerH == monsterH)
              {
                  printf("Eaten\n");
                  return;//gameover
              }
              else
              {
                  monsterH = monsterH + step;
                  move++;
              }
            } while(move < 4);
        }
    }
    else if(counter % 3 == 0)
    {
      do {//assigns random position to monster every 3 turns;
        monsterH = bRand(1,maxH - 1,'N');
        monsterL = bRand(1,maxL - 1,'N');
      } while(!checkObs(monsterH,monsterL));
    }
    //if player on same row or column, monster moves 4 spaces in direction
    //check if obstacle blocking vision

    mH = monsterH;
    mL = monsterL;

}

int sees(int monsterH, int monsterL, int playerH, int playerL) //returns 0 if not spotted, 1 if same H (need to move in L), 2 if same L (need to move in H)
{
  int curMH = monsterH;
  int curML = monsterL;
  int seesYou = 0;

  if(monsterH == playerH)
  {
      do {
        if(playerH == monsterH && playerL == monsterL)
        {
            seesYou = 1;
            return seesYou;
        }
        monsterL++;
      } while(checkObs(monsterH,monsterL) && monsterL < maxH - 1);

      monsterL = curML;

      do {
        if(playerH == monsterH && playerL == monsterL)
        {
            seesYou = 1;
            return seesYou;
        }
        monsterL--;
      } while(checkObs(monsterH,monsterL) && monsterL > 1);
  }

  else if(monsterL == playerL)
  {
      do {
        if(playerH == monsterH && playerL == monsterL)
        {
            seesYou = 2;
            return seesYou;
        }
        monsterH++;
      } while(checkObs(monsterH,monsterL) && monsterH < maxL - 1);

      monsterH = curMH;

      do {
        if(playerH == monsterH && playerL == monsterL)
        {
            seesYou = 2;
            return seesYou;
        }
        monsterH--;
      } while(checkObs(monsterH,monsterL) && monsterH > 1);
  }
  else
  {
      seesYou = 0;
      return seesYou;
  }
  monsterH = curMH;
  monsterL = curML;
  return seesYou;
}

int gameOver(playerH, playerL, monsterH, monsterL)
{
    if(move == 'X')
    {
      return 0;
    }
    else if(monsterH == playerH && monsterL == playerL)
    {
        printf("You made a tasty snack!\nGame Over!\n");
        return 0;
    }
    else
    {
      return 1;
    }
}
void scoring(int playerH, int playerL, int targetH, int targetL)
{
  if(playerH == targetH && playerL == targetL)
  {
    score++;
    printf("Score: %i\n",score);

    do { //assigns new random position to target, that isnt on an obstacle
      targetH = bRand(1,maxH - 1,'N');
      targetL = bRand(1,maxL - 1,'N');
    } while(!checkObs(targetH,targetL));

    tH = targetH;
    tL = targetL;
  }

}

float bRand(float minlim, float maxlim, char subset) //returns pseudo random number between min and max of the inputted subset
{
    //needs stdio.h & stdlib.h
    //subsets: N -> Natural numbers (positive whole incl 0) Z -> Integers (positive and negative whole numbers) Q -> Rational (can be represented as a fraction)
    float factor = 10;
    float randNum;
    float num;
    int sign = 1;

    if(rand() % 2 == 0)
    {
        sign = -1; //gets sign if subset can be negative
    }

    do {
      randNum = rand();
    } while(randNum == 0);

    if(randNum < minlim)
    {
        do {
          randNum = randNum * factor;
        } while(randNum < minlim);
    }
    else if(randNum > maxlim)
    {
        do {
          randNum = randNum / factor;
        } while(randNum > maxlim);
    }

    if(subset == 'N')
    {
        num = (int) randNum;
    }
    else if(subset == 'Z')
    {
        num = sign * randNum;
    }
    else if(subset == 'Q')
    {
        num = sign * randNum;
    }
    else
    {
        return 0;//error
    }
    return num;
}
