#include<stdio.h>
#include<conio.h>

int Score=0,stop=0;
int x=18,y=20;

int Ball(int index1,int index2,int position)
{
	static int topright=0,topleft=0,bottomleft=0,bottomright=1;

	if(index2==38)
	{
		topright==1?(topleft=1,bottomleft=0):
		(topleft=0,bottomleft=1);
		topleft=0,bottomright=0;
	}
	else if(index1==2)
	{
		topleft==1?(bottomleft=1,bottomright=0):
		(bottomleft=0,bottomright=1);
		topright=0,topleft=0;
	}
	else if(index2==3)
	{
		bottomleft==1?(topleft=0,bottomright=1):
		(topright=1,bottomright=0);
		topleft=0,bottomleft=0;
	}
	else if(index1==18 && (index2==position-1 || index2==position || index2==position+1))
	{
		bottomright==1?(topright=1,topleft=0):
		(topright=0,topleft=1);
		bottomleft=0,bottomright=0;
	}

	if(topright==1)
		x-=1,y+=1;
	else if(topleft==1)
		x-=1,y-=1;
	else if(bottomleft==1)
		x+=1,y-=1;
	else if(bottomright==1)
		x+=1,y+=1;

	if(index2==position && index1==18)
		Score+=5;

	return 0;
}

int Box(int position)
{
	int index1,index2;
	static int delay=0;
	textcolor(LIGHTRED);
		for(index1=1;index1<=20;index1++)  //top to bottom
		{
			for(index2=1;index2<=40;index2++) //left to right
			{
				if(index1==1||index1==20||index2==1||index2==2||index2==40||index2==39)
					if(stop==1)
						cprintf("%c",178); //color block-gchar
					else
						printf("%c",178);
				else
				{
					if((position>3 && position<38) && index1==19 && (index2==position-1||index2==position||index2==position+1))
					{
						printf("%c",223); //top block-gchar
					}
					else if((index1==x && index2==y) && delay==10) // ball delay
					{
						if(index1<19 && stop==0)
						{
							Ball(index1,index2,position);
							delay=0;
						}
						else
							stop=1;  //stop ball if out
					}
					else if((index1==x && index2==y) && index1<19)
						printf("0");
					else
						printf(" ");
				}
			}printf("\n");
		}
		delay++;

	return(stop);
}

int Info()
{
	gotoxy(1,7);
	printf("\n:..........BALL GAME..........:\n\nInstructions:\n");
	printf(" Press 'a' to move Left (<--)\n Press 'd' to move Right (-->)\n\n");
	printf("===============================\n");
	printf("Score will be Display at Bottom\n\n");
	printf("  Press Enter to Start Game\n\n");
	printf("\t     --x--");
	return 0;
}
int main()
{
	int Bar=20,j=0;
	char ch;
	while(1)
	{
		Bar=(rand()%1000)/20;
		if((Bar>3 && Bar<38))
		{
			y=Bar;
			break;
		}
	}
	clrscr();
	Info();
	getch();
	while(1)
	{
		if(stop==1)
		{
			if(j==5)
				break;
			j++;
		}
		if(!kbhit())
		{
			gotoxy(1,1);
			if(Bar==3)   // stay bar left end
				stop=Box(Bar+1);
			else if(Bar==38) //stay bar right end
				stop=Box(Bar-1);
			else
				stop=Box(Bar);
		}
		else
		{
			gotoxy(1,1);
			ch=getch();
			if((int)ch==97 && Bar>3)   //left 'a' & limite
				stop=Box(--Bar);
			else if((int)ch==100 && Bar<38) //right 'd' & limite
				stop=Box(++Bar);
			else if((int)ch==120) //exit 'x'
				break;
			else if((int)ch==99) //continue 'c'
			{
				Bar=20,x=18,y=20;
				stop=0;
			}
			else
				stop=Box(Bar);
		}
		printf("Press 'a' to move Left\t    Score=%d\n",Score);
		printf("Press 'd' to move Right\n\n");
		printf("Enter 'x' to Exit Game\n");
	}
	gotoxy(16,10);
	printf("GAME OVER");
	gotoxy(13,11);
	printf("Your Score: %d",Score);
	getch();

	return 0;
}