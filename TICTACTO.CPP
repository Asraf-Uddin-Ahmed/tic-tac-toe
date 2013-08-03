#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>


int PlayerCount=0;

int UserRow=0,UserColumn=0;	//recent played location

int GameBoard[3][3]={
		      -1,-1,-1,
		      -1,-1,-1,
		      -1,-1,-1
		    };
/*
matrix value of player 1 is 0
matrix value of player 2 is 1
*/

#include"mouse1.cpp"



/*
print board
*/
int board()
{
	setfillstyle(1,0);
	bar(0,0,640,480);

	setfillstyle(1,7);
	bar(150,80,160,400);
	bar(260,80,270,400);
	bar(50,180,370,190);
	bar(50,290,370,300);
	//rectangle(50,80,370,400);
return 0;
}



/*
print O
*/
int O(int x,int y)
{
	setcolor(15);
	setfillstyle(1,15);
	fillellipse(x,y,40,40);
	setfillstyle(1,0);
	fillellipse(x,y,20,20);
return 0;
}



/*
print X
*/
int X(int i,int j)
{
	setcolor(15);
	line(i-30,j-40,i+30,j+20);
	line(i-30,j-20,i+30,j+40);
	line(i-30,j-40,i-30,j-20);
	line(i+30,j+20,i+30,j+40);
	line(i-30,j+20,i+30,j-40);
	line(i-30,j+40,i+30,j-20);
	line(i-30,j+20,i-30,j+40);
	line(i+30,j-40,i+30,j-20);

	setfillstyle(1,15);
	floodfill(i+2,j+2,15);
	floodfill(i-25,j-25,15);
	floodfill(i+25,j-25,15);
	floodfill(i-25,j+25,15);
	floodfill(i+25,j+25,15);
return 0;
}



/*
print new game message
refresh the matrix to give new board
*/
int new_game()
{
char ch;
int i,j;
	outtextxy(530,250,"New Game (enter/esc)?");
	ch=getch();
	if(ch==13)
	{
		hide_mouse();
		board();
		for(i=0;i<3;i++)
			for(j=0;j<3;j++)
				GameBoard[i][j]=-1;
		show_mouse();
	}
	else  exit(1);
return 0;
}



/*
determine winner
print winner message
*/
int winner()
{
int i,j,New=0;
	setcolor(1);
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	settextstyle(1,0,1);
/*PLAYER 1*/
	    //diagonally                                                                                                                       //column wise							                                                                                                                              //row wise
	if( (GameBoard[0][0]==0&&GameBoard[1][1]==0&&GameBoard[2][2]==0) || (GameBoard[0][2]==0&&GameBoard[1][1]==0&&GameBoard[2][0]==0)  || (GameBoard[0][0]==0&&GameBoard[1][0]==0&&GameBoard[2][0]==0) || (GameBoard[0][1]==0&&GameBoard[1][1]==0&&GameBoard[2][1]==0) || (GameBoard[0][2]==0&&GameBoard[1][2]==0&&GameBoard[2][2]==0) || (GameBoard[0][0]==0&&GameBoard[0][1]==0&&GameBoard[0][2]==0) || (GameBoard[1][0]==0&&GameBoard[1][1]==0&&GameBoard[1][2]==0) || (GameBoard[2][0]==0&&GameBoard[2][1]==0&&GameBoard[2][2]==0) )
	{
		outtextxy(530,230,"USER win...");
		return 1;
	}

/*PLAYER 2*/
		 //diagonally                                                                                                                     //column wise                                                                                                                                                                                   //row wise
	else if( (GameBoard[0][0]==1&&GameBoard[1][1]==1&&GameBoard[2][2]==1) || (GameBoard[0][2]==1&&GameBoard[1][1]==1&&GameBoard[2][0]==1)  || (GameBoard[0][0]==1&&GameBoard[1][0]==1&&GameBoard[2][0]==1) || (GameBoard[0][1]==1&&GameBoard[1][1]==1&&GameBoard[2][1]==1) || (GameBoard[0][2]==1&&GameBoard[1][2]==1&&GameBoard[2][2]==1) || (GameBoard[0][0]==1&&GameBoard[0][1]==1&&GameBoard[0][2]==1) || (GameBoard[1][0]==1&&GameBoard[1][1]==1&&GameBoard[1][2]==1) || (GameBoard[2][0]==1&&GameBoard[2][1]==1&&GameBoard[2][2]==1) )
	{
		outtextxy(530,230,"PC win...");
		return 2;
	}

//Draw
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			if(GameBoard[i][j]==-1)
				New++;
//no empty space
	if(New==0)
	{
		outtextxy(530,230,"Draw...");
		return 3;
	}

return 0;
}



/*
read matrix to print O & X
*/
int read_matrix()
{
int r,c,x,y;
	hide_mouse();
	for(r=0;r<3;r++)
		for(c=0;c<3;c++)
			if(GameBoard[r][c]==0)
			{
			//convert array location to pixel point
				y=(r+1)*110+20;
				x=(c+1)*110-10;
				O(x,y);
			}
			else if(GameBoard[r][c]==1)
			{
			//convert array location to pixel point
				y=(r+1)*110+20;
				x=(c+1)*110-10;
				X(x,y);
			}
	show_mouse();
return 0;
}



/*
play PC
*/
int PC_move()
{
int i=0,j=0;
int x=0,o=0;	//for searching O or X has or not

/*ATTACK to win*/
//row wise
	for(i=0;i<3;i++)
	//3rd position empty
		if(GameBoard[i][0]==1 && GameBoard[i][1]==1 && GameBoard[i][2]==-1)
		{
			GameBoard[i][2]=1;
			return 1;
		}
	//1st position empty
		else if(GameBoard[i][2]==1 && GameBoard[i][1]==1 && GameBoard[i][0]==-1)
		{
			GameBoard[i][0]=1;
			return 1;
		}
	//2nd position empty
		else if(GameBoard[i][0]==1 && GameBoard[i][2]==1 && GameBoard[i][1]==-1)
		{
			GameBoard[i][1]=1;
			return 1;
		}

//column wise
	for(i=0;i<3;i++)
	//3rd position empty
		if(GameBoard[0][i]==1 && GameBoard[1][i]==1 && GameBoard[2][i]==-1)
		{
			GameBoard[2][i]=1;
			return 1;
		}
	//1st position empty
		else if(GameBoard[2][i]==1 && GameBoard[1][i]==1 && GameBoard[0][i]==-1)
		{
			GameBoard[0][i]=1;
			return 1;
		}
	//2nd position empty
		else if(GameBoard[0][i]==1 && GameBoard[2][i]==1 && GameBoard[1][i]==-1)
		{
			GameBoard[1][i]=1;
			return 1;
		}

//diagonally
	if(GameBoard[1][1]==1)
	//1,1 & 2,2
		if(GameBoard[2][2]==1 && GameBoard[0][0]==-1)
		{
			GameBoard[0][0]=1;
			return 1;
		}
	//1,1 & 2,0
		else if(GameBoard[2][0]==1 && GameBoard[0][2]==-1)
		{
			GameBoard[0][2]=1;
			return 1;
		}
	//1,1 & 0,2
		else if(GameBoard[0][2]==1 && GameBoard[2][0]==-1)
		{
			GameBoard[2][0]=1;
			return 1;
		}
	//1,1 & 0,0
		else if(GameBoard[0][0]==1 && GameBoard[2][2]==-1)
		{
			GameBoard[2][2]=1;
			return 1;
		}


/*DEFEND to lose*/
//row wise
	for(i=0;i<3;i++)
	//3rd position empty
		if(GameBoard[i][0]==0 && GameBoard[i][1]==0 && GameBoard[i][2]==-1)
		{
			GameBoard[i][2]=1;
			return 1;
		}
	//1st position empty
		else if(GameBoard[i][2]==0 && GameBoard[i][1]==0 && GameBoard[i][0]==-1)
		{
			GameBoard[i][0]=1;
			return 1;
		}
	//2nd position empty
		else if(GameBoard[i][0]==0 && GameBoard[i][2]==0 && GameBoard[i][1]==-1)
		{
			GameBoard[i][1]=1;
			return 1;
		}

//column wise
	for(i=0;i<3;i++)
	//3rd position empty
		if(GameBoard[0][i]==0 && GameBoard[1][i]==0 && GameBoard[2][i]==-1)
		{
			GameBoard[2][i]=1;
			return 1;
		}
	//1st position empty
		else if(GameBoard[2][i]==0 && GameBoard[1][i]==0 && GameBoard[0][i]==-1)
		{
			GameBoard[0][i]=1;
			return 1;
		}
	//2nd position empty
		else if(GameBoard[0][i]==0 && GameBoard[2][i]==0 && GameBoard[1][i]==-1)
		{
			GameBoard[1][i]=1;
			return 1;
		}

//diagonally
	//1,1 & 2,2
	if(GameBoard[1][1]==0 && GameBoard[2][2]==0 && GameBoard[0][2]==-1)
	{
			GameBoard[0][2]=1;
			return 1;
	}
	//1,1 & 2,0
	else if(GameBoard[1][1]==0 && GameBoard[2][0]==0 && GameBoard[0][2]==-1)
	{
			GameBoard[0][2]=1;
			return 1;
	}
	//1,1 & 0,2
	else if(GameBoard[1][1]==0 && GameBoard[0][2]==0 && GameBoard[2][0]==-1)
	{
			GameBoard[2][0]=1;
			return 1;
	}



//1st turn
	if(GameBoard[1][1]==-1)
	{
		GameBoard[1][1]=1;
		return 1;
	}
	else if(GameBoard[1][1]==0 && GameBoard[0][0]==-1 )
	{
		GameBoard[0][0]=1;
		return 1;
	}

//Trick for defend & attack

//making proceedure to occupied mid row,if no user position
	for(i=0;i<3;i++)
		if(GameBoard[1][i]==0)
			break;
	if(i==3&&GameBoard[1][0]==-1)
	{
		GameBoard[1][0]=1;
		return 1;
	}

//making proceedure to occupied mid column,if no user position
	for(i=0;i<3;i++)
		if(GameBoard[i][1]==0)
			break;
	if(i==3&&GameBoard[0][1]==-1)
	{
		GameBoard[0][1]=1;
		return 1;
	}

//search for defend tricks & making proceedure to win
	//1 row has user & hasn't pc
	for(i=0,o=0,x=0;i<3;i++)
		if(GameBoard[0][i]==0)
			o++;
		else if(GameBoard[0][i]==1)
			x++;
	if(o>0 && x==0 && GameBoard[0][2]==-1)
	{
		GameBoard[0][2]=1;
		return 1;
	}
	//3 row has user & hasn't pc
	for(i=0,o=0,x=0;i<3;i++)
		if(GameBoard[2][i]==0)
			o++;
		else if(GameBoard[2][i]==1)
			x++;
	if(o>0 && x==0  && GameBoard[2][2]==-1)
	{
		GameBoard[2][2]=1;
		return 1;
	}

	//1 column has user & hasn't pc
	for(i=0,o=0,x=0;i<3;i++)
		if(GameBoard[i][0]==0)
			o++;
		else if(GameBoard[i][0]==1)
			x++;

	if(o>0 && x==0  && GameBoard[2][0]==-1)
	{
		GameBoard[2][0]=1;
		return 1;
	}
	//3 column has user & hasn't pc
	for(i=0,o=0,x=0;i<3;i++)
		if(GameBoard[i][2]==0)
			o++;
		else if(GameBoard[i][2]==1)
			x++;
	if(o>0 && x==0  && GameBoard[2][2]==-1)
	{
		GameBoard[2][2]=1;
		return 1;
	}

//play side of user played position **not used
	if(UserColumn-1>=0 && GameBoard [UserRow] [UserColumn-1]==-1)
	{        //printf("-");
		 GameBoard [UserRow] [UserColumn-1]=1;
		 return 0;
	}
	else if(UserColumn+1<3 && GameBoard [UserRow] [UserColumn+1]==-1)
	{        //printf("+");
		 GameBoard [UserRow] [UserColumn+1]=1;
		 return 0;
	}

//turn but has nothing to do.just play empty space
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			if(GameBoard[i][j]==-1)
			{
				GameBoard[i][j]=1;
				return 1;
			}


return 0;
}



/********************************** MAIN *********************************************/

main()
{
int d=0,m;
int i,j,r,c;
char ch;


initgraph(&d,&m,"c:\\tc\\bgi");


board();

load_driver();
show_mouse();


while(1)
{
	mouse_position();

	if( (button&1)==1 )
	{
		for(i=50;i<=270;i+=110)
			for(j=80;j<=300;j+=110)
				if(x>=i&&x<=i+100 && y>=j&&y<=j+100)
				{
				/*determine mid point*/
					x=i+50;
					y=j+50;

				/*determine array element & location*/
					UserRow=r=(y/100)-1;
					UserColumn=c=(x/100)-1;

					if(GameBoard[r][c]==-1)
					{
						GameBoard[r][c]=PlayerCount%2;

					/*turn to next player*/
						PlayerCount++;
					}
				}

		read_matrix();

		/*
		//MATRIX print
		for(i=0;i<3;i++)
		{
			 for(int j=0;j<3;j++)
				printf("%2d ",GameBoard[i][j]);
			 printf("\n");
		}
		  */
		//printf("%d %d ",x,y);
		delay(200);
	}

//calling winner() function
	else if( winner()>0 ) new_game();


	else if(PlayerCount%2==1)
	{
		PC_move();
		PlayerCount++;
		read_matrix();
	}

	else if( kbhit() )
		if( (ch=getch()) =='n') new_game();
		else if(ch==27) exit(1);

}


//getch();
//return 0;
}