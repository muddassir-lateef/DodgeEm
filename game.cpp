//============================================================================
// Name        		    : game.cpp
// Starter code provided by : Hassan Mustafa
// Made by      	    : Muddassir Lateef
// Copyright   		    : (c) Reserved
// Description 		    : Basic 2D game of Dodge 'Em...
//============================================================================
/*

Name	:  Muddassir Lateef
Section	: CS-B
Roll No	: 19I-0505

*/
#ifndef DODGE_CPP_
#define DODGE_CPP_
#include<fstream>
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;
	//menu related 
	int pmenucntr=1;
	bool pmselected=false;
	bool menu=true;
	bool pmenu=true;
	bool scorescreen=false;
	bool sentryscreen=false;
//
	bool hlpscreen=false;
	char hsname[7]={};
	int hscntr=0;
// secret menu 
	bool smenu=false;
	int smlcntr=0;
	int smrcntr=0;
	int smenucntr=1;
	bool smselected=false;
// password
	bool passmenu=true;
	bool correctpass=true;
	int pin=0;
	int pincntr=0;
//car cheats
	bool invincible=false;
//player status
	int g_score=0;
	int lives=3;
	int level=1;
// game status
	bool g_crash=false;	
	bool gameover=	false;
	bool start=false;

//game parameters

	float arena[40][6];

//extra counters
	int lChangecntr=0;
	int flashescntr=0;
	int axiscounter=90;
//food
	int food[84][95];

//effects
	bool lvlscreen=false;
	bool lchange=false;
//movement checks
	int startmv =-1;
	bool spressed=false;
	
//player variables
	bool pCarHorz=false;
	int g_pspeed=4;
	int g_pxMov=-g_pspeed ;	
	int g_pyMov=0;	
	int inixpc=380;
	int iniypc=30;
	float g_xpc=inixpc;
	float g_ypc=iniypc;
	int g_dirPc=0;  // direction of player car(0=car not moving ,1=left,2=up,3=right,4=down)
	int loopp=4;
//opponent variables
	int inixoc=520;
	int iniyoc=30;
	float g_xoc=inixoc;
	float g_yoc=iniyoc;
	bool oCarHorz=false;
	int g_ospeed=4;
	int g_oxMov=g_ospeed ;	
	int g_oyMov=0;	
	int g_dirOc=0;  // direction of player car(0=car not moving ,1=left,2=up,3=right,4=down)
	int loopo=4;
//opponent2 variables
	int inixo2c=520;
	int iniyo2c=680;
	float g_xo2c=inixo2c;
	float g_yo2c=iniyo2c;
	bool o2CarHorz=false;
	int g_o2speed=4;
	int g_o2xMov=-g_ospeed ;	
	int g_o2yMov=0;	
	int g_dirO2c=0;  // direction of player car(0=car not moving ,1=left,2=up,3=right,4=down)
	int loopo2=4;
//car parameters
	int g_carwx=60;
	int g_carhx=50;
	int g_carwy=41;
	int g_carhy=72;

///////////////////////////////////

bool Write(string SData) //writing data
{	
	ofstream out;
	out.open ("hs.txt");
	if(out)
	{
		out<<SData<<endl;
		out.close();
		return true;
	}
	return false;
}
string Read()        //reading data
{
	ifstream in ("hs.txt");
	if(in)
	{
		char buffer[100];
		string SData="";
		in.getline(buffer,99);
	do{
		SData+=(string)buffer;
		in.getline(buffer,99);
	}while(in);
	return SData;

	}
}
string Reada(int x) //reading data in parts
{
	string temp;
	temp=Read();
	int ic=0;
	int cntr=1;
	int previ=0;
	for(int i=0; i<100,cntr<=x ;i++)
	{
		previ=ic;
		if(temp[i]=='/')
		{
			cntr++;
			ic=i;
		}		
	}
	previ++;
	char tempa[20];

	int s=ic-previ;

	for(int i=previ,k=0; k<s;i++,k++)
	{
		tempa[k]=temp[i];
	}
	if(ic-previ<4)
	{
	for(int i=s;i<4-s;i++)
	{
		tempa[i]=' ';

	}
	}
	return tempa;
}
int Str2Num(string s)   //converting string into numbers 
{
	int dig[4];
	int num=0;
	for(int i=0 ;i<4 ;i++)
	{
	dig[i]=int(s[i])-48;
	}
	for(int i=0;i<4;i++)
	{
		num+=(dig[i]*pow(10,3-i));
	}
	return num;
}
string Str2Name(string s)	// getting a string of name from parts of data
{
	char temp[17];
	for(int i=0;i<17;i++)
	{
		temp[i]=s[i];	
	}
	return temp;
}
string Str2Score(string s) //getting a string of numbers from parts of data
{
	char temp[4];
	for(int i=18,j=0;i<22;j++,i++)
	{
		temp[j]=s[i];	
	}
	return temp;


}
string score2str(int score)  //converting int score into string score
{
	char tema[4];
	if(score>=9999)
	{
		tema[0]='9';
		tema[1]='9';
		tema[2]='9';
		tema[3]='9';		
	}
	else
	{
		string tem;
		tem=Num2Str(score);
		if(score<1000 && score>99)
		{
			tema[0]='0';
			tema[1]=tem[0];
			tema[2]=tem[1];
			tema[3]=tem[2];		
		}
		else if(score<100 && score>9)
		{
			tema[0]='0';
			tema[1]='0';
			tema[2]=tem[0];
			tema[3]=tem[1];		
		}
		else if(score<10 && score>-1)
		{
			tema[0]='0';
			tema[1]='0';
			tema[2]='0';
			tema[3]=tem[1];		
		}
	}
	
	return tema;
}

string scoreslist(int sort[5],string num[5],string n[5]) //compiling the whole data
{
		char numa[4][4], na[4][17];
	for(int i=0 ;i<4 ;i++)
	{
		for(int j=0;j<4;j++)
		{
		numa[i][j]=num[sort[i]][j];


		}
		for(int j=0;j<17;j++)
		{
		na[i][j]=n[sort[i]][j];
		}
	}
	char tem[4][23];
	for(int i=0 ;i<4;i++)
	{
		for(int j=0;j<17;j++)
		{
			tem[i][j]=na[i][j];

		}
		tem[i][17]=':';
		for(int j=0;j<4;j++)
		{
			tem[i][j+18]=numa[i][j];
		}
		tem[i][22]='/';	
	}
	char tem1[24],tem2[24],tem3[24],tem4[24];
	for(int i=0 ;i<23 ;i++)
	{
		tem1[i]=tem[0][i];
	}
	tem1[23]='\0';
	for(int i=0 ;i<23 ;i++)
	{
		tem2[i]=tem[1][i];
	}
	tem2[23]='\0';
	for(int i=0 ;i<23 ;i++)
	{
		tem3[i]=tem[2][i];
	}
	tem3[23]='\0';
	for(int i=0 ;i<23 ;i++)
	{
		tem4[i]=tem[3][i];
	}
	tem4[23]='\0';

	string tema=tem1;
	string temb=tem2;
	string temc=tem3;
	string temd=tem4;

	string finalList;
	finalList="*/"+tema+temb+temc+temd;

	return finalList;
}

/////////////////////////////////

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

}


/*
 * Main Canvas drawing function.
 * */
//Board *b;
void GameDisplay()/**/{

if(menu==true)
{
	if(pmenu==true) //pause menu is selected
	{
		if(pmselected==false) //if any menu option is not selected
		{
		glClearColor(1, 1,1, 0); // Red==Green==Blue==1 --> White Colour
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors
		DrawStringa( 100,760 , "To select an option,navigate there with arrow keys and press spacebar.", colors[BLACK]);

		if(pmenucntr==1)
		{
		DrawStringa( 375,680 , "1) Start New Game.", colors[RED]);
		DrawStringa( 350,680 , ">                                      <", colors[RED]);
		}
		else
		{
		DrawStringa( 375,680 , "1) Start New Game.", colors[BLACK]);
		}
		if(pmenucntr==2)
		{
		DrawStringa( 375,610 , "2) High Scores.", colors[RED]);
		DrawStringa( 350,610 , ">                                      <", colors[RED]);
		}
		else
		{
		DrawStringa( 375,610 , "2) High Scores.", colors[BLACK]);
		}
		if(pmenucntr==3)
		{
		DrawStringa( 375,540 , "3) Help", colors[RED]);
		DrawStringa( 350,540 , ">                                      <", colors[RED]);
		}
		else
		{
		DrawStringa( 375,540 , "3) Help", colors[BLACK]);
		}
		if(pmenucntr==4)
		{
		DrawStringa( 375,470 , "4) Exit", colors[RED]);
		DrawStringa( 350,470 , ">                                      <", colors[RED]);
		}
		else
		{
		DrawStringa( 375,470 , "4) Exit", colors[BLACK]);
		}
		if(pmenucntr==5)
		{
		if(g_score!=0)
		{
		DrawStringa( 375,400 , "5) Continue", colors[RED]);
		DrawStringa( 350,400 , ">                                      <", colors[RED]);
		}
		else
		{
		DrawStringa( 375,400 , "5) Continue", colors[GRAY]);
		DrawStringa( 350,400 , ">                                      <", colors[GRAY]);
		}
		}
		else
		{
		DrawStringa( 375,400 , "5) Continue", colors[BLACK]);
		}
		
//		DrawStringa( 100,200 , "To resume the game,either select Continue in options or press P again.", colors[BLACK]);

		}
		else // if any pause menu option is selected
		{
			if(pmenucntr==1) //start new game
			{
				pmenu=false;
				menu=false;
				g_xpc=inixpc;
				g_ypc=iniypc;
				g_xoc=inixoc;
				g_yoc=iniyoc;
				g_oxMov=g_ospeed;
				g_oyMov=0;
				g_pxMov=-g_ospeed;
				g_pyMov=0;
				loopp=4;
				loopo=4;
				g_xo2c=inixo2c;
				g_yo2c=iniyo2c;
				g_o2xMov=-g_o2speed;
				g_o2yMov=0;
				o2CarHorz=false;
				loopo2=4;		
				oCarHorz=false;
				pCarHorz=false;
				start=false;
				level=1;
				g_score=0;
			}
			if(pmenucntr==2) //high score
			{
				pmenu=false;
				scorescreen=true;
				pmselected=false;
			}
			if(pmenucntr==3) //help
			{
			hlpscreen=true;
			pmenu=false;
			pmselected=false;

			}
			if(pmenucntr==4) //exit
			{
				exit(1);
			}
			if(pmenucntr==5 && g_score>0 ) //continue
			{
				pmenu=false;
				menu=false;
			}
			pmselected=false;
		}
	}
	if(scorescreen==true) //high scores
	{
			glClearColor(1, 1,1, 0); // Red==Green==Blue==1 --> White Colour
			glClear (GL_COLOR_BUFFER_BIT); //Update the colors

			string n[5];
			string num[5];
			string tem[4];
			DrawStringa( 375,700 , "HIGH SCORES", colors[BLUE]);
			DrawStringa( 375,698 , "_____________", colors[BLUE]);
			DrawStringa( 250,300 , "Press 'q' or 'Q' to go back to main menu.", colors[BLACK]);



			for(int i=0 ;i<4 ;i++)
			{
				tem[i]=Reada(i+2);
			}	
			for(int i=0 ;i<4 ;i++)
			{
				n[i]=Str2Name(tem[i]);
			}
			DrawStringa( 320,610 ,n[0], colors[GOLD]);
			DrawStringa( 320,560 ,n[1], colors[INDIGO]);
			DrawStringa( 320,510 ,n[2], colors[BLUE]);
			DrawStringa( 320,460 ,n[3], colors[RED]);
	
			for(int i=0 ;i<4 ;i++)
			{
				num[i]=Str2Score(tem[i]);
			}
			DrawStringa( 490,610 ,num[0], colors[GOLD]);
			DrawStringa( 490,560 ,num[1], colors[INDIGO]);
			DrawStringa( 490,510 ,num[2], colors[BLUE]);
			DrawStringa( 490,460 ,num[3], colors[RED]);

////////////////////////////////////////////////////////////////////////
	}
	if(hlpscreen==true) //help screen
	{
		glClearColor(1, 1,1, 0); // Red==Green==Blue==1 --> White Colour
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors
////////////////////////////////////////////////////////////
DrawStringa(445,770,"Help",colors[BLACK]);
DrawStringa(445,768,"____",colors[BLACK]);
DrawStringa(80,700,">> The main objective of this game is to collect all food without losing all lives.",colors[BLACK]);
DrawStringa(80,660,">> There are four levels in this game with varying difficulty which you need to complete.",colors[BLACK]);
DrawStringa(80,620,">> You can change the lanes of your car using arrow keys at gaps.",colors[BLACK]);
DrawStringa(80,580,">> You can boost your car by holding space bar.",colors[BLACK]);
DrawStringa(80,540,">> You will lose a life when an opponent touches you.",colors[BLACK]);
DrawStringa(80,500,">> You can toogle the pause menu at anytime by pressing 'P' or 'p'.",colors[BLACK]);
DrawStringa(80,460,">>Level 1:",colors[RED]);
DrawStringa(80,420,"The opponent car is in inactive mode (can only change top and bottom lanes).",colors[BLACK]);
DrawStringa(80,380,">>Level 2:",colors[RED]);
DrawStringa(80,340,"The opponent car is in active mode (can chnage all lanes).",colors[BLACK]);
DrawStringa(80,300,">>Level 3:",colors[RED]);
DrawStringa(80,260,"The opponent car has double speed.",colors[BLACK]);
DrawStringa(80,220,">>Level 4:",colors[RED]);
DrawStringa(80,180,"Two opponent cars chase you.",colors[BLACK]);
DrawStringa(375,70,"Press 'q' or 'Q' to go back.",colors[BLUE]);

/////////////////////////////////////////////////////////////////


	}
	if(smenu==true) //secret menu is selected
	{
		if(passmenu==false)
		{
			if(smselected==false)
			{
			glClearColor(0, 0,0, 0); // Red==Green==Blue==1 --> White Colour
			glClear (GL_COLOR_BUFFER_BIT); //Update the colors
			DrawStringa( 70, 460, "Lives:", colors[GOLDEN_ROD]);    
			string livesInSt=Num2Str(lives);	
			DrawStringa( 140, 460, livesInSt, colors[AQUA_MARINE]);
		
			DrawStringa( 70, 420, "Level:", colors[GOLDEN_ROD]);    
			string levelInSt=Num2Str(level);	
			DrawStringa( 140, 420, levelInSt, colors[AQUA_MARINE]);
			if(level!=3)
			{
			DrawStringa( 70, 380, "Opponent Speed :", colors[GOLDEN_ROD]);    
			}
			else
			{
			DrawStringa( 70, 380, "Opponent Speed : 2*", colors[GOLDEN_ROD]);    
			}
			string SpeedOInSt=Num2Str(g_ospeed);	
			DrawStringa( 280, 380, SpeedOInSt, colors[AQUA_MARINE]);
			DrawStringa( 70, 340, "Player Speed       :", colors[GOLDEN_ROD]);    
			string SpeedPInSt=Num2Str(g_pspeed);	
			DrawStringa( 280, 340, SpeedPInSt, colors[AQUA_MARINE]);
	
			DrawStringa( 70, 300, "Invincibility         :", colors[GOLDEN_ROD]);    
			if(invincible==true)
			{	
			DrawStringa( 280, 300, "Yes", colors[AQUA_MARINE]);
			}
			else
			{	
			DrawStringa( 280, 300, "No", colors[AQUA_MARINE]);
			}
	
	
			DrawStringa( 100,760 , "To select an option,navigate there with arrow keys and press spacebar.", colors[WHITE]);
	
			if(smenucntr==1)
			{
			DrawStringa( 375,680 , "1) Reduce Opponent speed ", colors[RED]);
			DrawStringa( 350,680 , ">                                               <", colors[RED]);
			}
			else
			{
			DrawStringa( 375,680 , "1) Reduce Opponent speed ", colors[WHITE]);
			}
			if(smenucntr==2)
			{
			DrawStringa( 375,610 , "2) Skip a level", colors[RED]);
			DrawStringa( 350,610 , ">                                               <", colors[RED]);
			}
			else
			{
			DrawStringa( 375,610 , "2) Skip a level", colors[WHITE]);
			}
			if(smenucntr==3)
			{
			DrawStringa( 375,540 , "3) Invinciblity", colors[RED]);
			DrawStringa( 350,540 , ">                                               <", colors[RED]);
			}
			else
			{
			DrawStringa( 375,540 , "3) Invinciblity", colors[WHITE]);
			}
			if(smenucntr==4)
			{
			DrawStringa( 375,470 , "4) Lives", colors[RED]);
			DrawStringa( 350,470 , ">                                               <", colors[RED]);
			}
			else
			{
			DrawStringa( 375,470 , "4) Lives", colors[WHITE]);
			}
			if(smenucntr==5)
			{
			DrawStringa( 375,400 , "5) Exit", colors[RED]);
			DrawStringa( 350,400 , ">                                               <", colors[RED]);
			}
			else
			{
			DrawStringa( 375,400 , "5) Exit", colors[WHITE]);
			}
	
			}
			else
			{
				if(smenucntr==1) //start new game
				{
					if(g_ospeed-1 >0)
					g_ospeed-=1;
					if(g_o2speed-1 >0)
					g_o2speed-=1;	
				}
				if(smenucntr==2)
				{
					level++;
					if(level>4)
					{
						level=1;
					}
				start=false;
				g_xpc=inixpc;
				g_ypc=iniypc;
				g_xoc=inixoc;
				g_yoc=iniyoc;
				g_oxMov=g_ospeed;
				g_oyMov=0;
				g_pxMov=-g_pspeed;
				g_pyMov=0;
				loopp=4;
				loopo=4;
				g_xo2c=inixo2c;
				g_yo2c=iniyo2c;
				g_o2xMov=-g_o2speed;
				g_o2yMov=0;
				o2CarHorz=false;
				loopo2=4;		
				oCarHorz=false;
				pCarHorz=false;
				}
				if(smenucntr==3)
				{
					if(invincible==true)
					{
					invincible=false;
					}
					else
					{
					invincible=true;
					}
					
				}
				if(smenucntr==4)
				{
					lives++;
				}
				if(smenucntr==5 )
				{
					correctpass=true;
					smenu=false;
					pmenu=true;
					passmenu=true;
				}
				smselected=false;
			}
		}
		else  //Authentication of pin for secret menu
		{
			glClearColor(0, 0,0, 0 ); // Red==Green==Blue==1 --> White Colour
			glClear (GL_COLOR_BUFFER_BIT); //Update the colors
			DrawStringa( 330,700 , "[  Press 'q' or 'Q' to go back.  ]", colors[WHITE]);
	
			DrawStringa( 330,415 , "Enter the 4-digit pin:", colors[WHITE]);
			if(pincntr==1)
			{
			DrawStringa( 575,415 , "*", colors[WHITE]);
			}
			if(pincntr==2)
			{
			DrawStringa( 575,415 , "* *", colors[WHITE]);
			}
			if(pincntr==3)
			{
			DrawStringa( 575,415 , "* * *", colors[WHITE]);
			}
			if(pincntr==4)
			{
			DrawStringa( 575,415 , "* * * *", colors[WHITE]);
			}
			DrawStringa( 575,415 , "_ _ _ _", colors[WHITE]);
			if(correctpass==false)
			{
			DrawStringa( 400,375 , "Wrong Pin! Try again.", colors[RED]);
			}
			if(pincntr==4)
			{
				if(pin==1234)
				{
					passmenu=false;
					pincntr=0;
					pin=0;
				}
				else
				{
					pin=0;
					pincntr=0;
					correctpass=false;
				}
			}
		}
	}	
}
else
{	
	if(gameover==true) //if game has ended
	{
		g_xpc=inixpc;
		g_ypc=iniypc;
		g_xoc=inixoc;
		g_yoc=iniyoc;
		g_oxMov=g_ospeed;
		g_oyMov=0;
		g_pxMov=-g_ospeed;
		g_pyMov=0;
		loopp=4;
		loopo=4;
		g_xo2c=inixo2c;
		g_yo2c=iniyo2c;
		g_o2xMov=-g_o2speed;
		g_o2yMov=0;
		o2CarHorz=false;
		loopo2=4;		
		oCarHorz=false;
		pCarHorz=false;
		start=false;
		level=1;
		if(sentryscreen==false)
		{
		glClearColor(1, 1,1, 0 ); // Red==Green==Blue==1 --> White Colour
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors

			if(lives<2) //player lost
			{	
			DrawStringa( 375,415 , "You Lost.Better Luck Next time.", colors[RED]);
			}
			if(level>4) //player won
			{
			DrawStringa( 375,415 , "Congratulations.You Won the game.", colors[RED]);
			}
			if(lives>1)
			DrawStringa( 375,415 , "Congratulations.You Won the game.", colors[RED]);
			DrawStringa( 250,215 , "Press fullstop(.) to go to next screen.", colors[RED]);

		}
		else // Name entry for high scores
		{
		glClearColor(0, 0,0, 0 ); // Red==Green==Blue==1 --> White Colour
		glClear (GL_COLOR_BUFFER_BIT); //Update the colors

			int sort[5]={};
			int s[5];
			string n[5];
			string num[5];
			string tem[4];
			DrawStringa( 50, 780, "Score :", colors[GOLDEN_ROD]);    
			string ScoreInSt=Num2Str(g_score);	
			DrawStringa( 120, 780, ScoreInSt, colors[AQUA_MARINE]);
			for(int i=0 ;i<4 ;i++)
			{
				tem[i]=Reada(i+2);
			}	
			for(int i=0 ;i<4 ;i++)
			{
				n[i]=Str2Name(tem[i]);
			}
	
			for(int i=0 ;i<4 ;i++)
			{
				num[i]=Str2Score(tem[i]);
			}
	
			for(int i=0 ;i<4 ;i++)
			{
			s[i]=Str2Num(num[i]);
			}	
			s[4]=g_score;
		
			DrawStringa( 275,500 , "Enter your name: ", colors[GOLD]);
			char name[17];
			DrawStringa( 475,500 , "______", colors[SILVER]);			
			for(int i=0;i<16;i++)
			{
				name[i]=' ';
			}
			name[16]='\0';
			for(int i=0;i<hscntr;i++)
			{
				name[i]=hsname[i];
			}
			DrawStringa( 475,500 , name, colors[BLUE]);

			int i;
			for( i=0;name[i]!='\0';i++)
			{}

			for(int k=i ;k<17 ;k++)
			{
				name[k]=' ';
			}
	
			if(hscntr==6)
			{
				n[4]=name;
				num[4]=score2str(s[4]);
				if(s[4]>s[0])
				{
					sort[0]=4;
					sort[1]=0;
					sort[2]=1;
					sort[3]=2;
					sort[4]=3;
				}
				else if(s[4]>s[1])
				{
					sort[0]=0;
					sort[1]=4;
					sort[2]=1;
					sort[3]=2;
				}
				else if(s[4]>s[2])
				{
					sort[0]=0;
					sort[1]=1;
					sort[2]=4;
					sort[3]=2;
				}
				else if(s[4]>s[3])
				{
					sort[0]=0;
					sort[1]=1;
					sort[2]=2;
					sort[3]=4;
				}
				string sl=scoreslist(sort,num,n);
				Write(sl);
				hscntr++;
				g_score=0;
			}
			if(hscntr>6)
			{
				DrawStringa( 475,200 , "Press any key to see high scores.", colors[WHITE]);
			}
		}
	}
	else{	

	if(lvlscreen==true) //level change happens
	{
		if(flashescntr%2==0) //to create a flashing screen if player level ups
		{
			for(int j=0 ;j<10;j++)
			{
				glClearColor(1, 1,1, 1 );
			}
		}
		else
		{
			for(int j=0 ;j<10;j++)
			{
				glClearColor(0, 0,0, 1 );
			}
		}
		cout<<"\a"<<endl; //for beep or bell sound
		flashescntr++;
		if(flashescntr>60) //end of flashy screen
		{
			flashescntr=0;
			lvlscreen=false;
			start=false;
			g_xpc=inixpc;
			g_ypc=iniypc;
			g_xoc=inixoc;
			g_yoc=iniyoc;
			g_oxMov=g_ospeed;
			g_oyMov=0;
			g_pxMov=-g_ospeed;
			g_pyMov=0;
			loopp=4;
			loopo=4;
			g_xo2c=inixo2c;
			g_yo2c=iniyo2c;
			g_o2xMov=-g_o2speed;
			g_o2yMov=0;
			o2CarHorz=false;
			loopo2=4;		
			oCarHorz=false;
			pCarHorz=false;
		}
	}
	else
	{
			glClearColor(0, 0,0, 1 );
	}
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

////////////////////////////////////////////////////////


//Some important indicators

	DrawStringa( 50, 815, "Food:", colors[TOMATO]);
	DrawStringa( 50, 780, "Score :", colors[GOLDEN_ROD]);    
	string ScoreInSt=Num2Str(g_score);	
	DrawStringa( 120, 780, ScoreInSt, colors[AQUA_MARINE]);
	DrawStringa( 350, 780, "Level:", colors[GOLDEN_ROD]);    
	string levelInSt=Num2Str(level);	
	DrawStringa( 420, 780, levelInSt, colors[AQUA_MARINE]);
	DrawStringa( 470, 780, "Lives:", colors[GOLDEN_ROD]);    
	string livesInSt=Num2Str(lives);	
	DrawStringa( 540, 780, livesInSt, colors[AQUA_MARINE]);


/////////////////////////////////////////////////////////

//PLAYER CAR

	int tempx=g_pxMov;
	int tempy=g_pyMov;
		
	if(lvlscreen==true)
	{
		g_o2xMov=0;
		g_o2yMov=0;
		g_oxMov=0;
		g_oyMov=0;
		g_pxMov=0;
		g_pyMov=0;		
	}
if(start==true)
{
	if(g_pxMov>0)
	{
		g_dirPc=3;			//right
		pCarHorz=false;
	}
	if(g_pxMov<0)
	{
		g_dirPc=1;		//left
		pCarHorz=false;
	}
	if(g_pyMov>0)
	{
		g_dirPc=2;			//up
		pCarHorz=true;
	}
	if(g_pyMov<0)
	{
		g_dirPc=4;			//down
		pCarHorz=true;
	}

	if(pCarHorz==false &&  spressed==true )
	{
		g_pxMov*=5;
	}
	if(pCarHorz==true &&  spressed==true )
	{
		g_pyMov*=5;
	}
	g_xpc+=g_pxMov;
	g_ypc+=g_pyMov;
}

	// drawing the players car
	float width = 15; 
	float height = 10;
	float* color = colors[BLUE]; 
	float radius = 5;
	float widtha=9;
	float heighta=16;
	float defb=3;
	float defc=10;
	float defd=12;
	if(pCarHorz==false)
	{
	DrawRoundRect(g_xpc,g_ypc,width,height,color,radius); // bottom left tyre
	DrawRoundRect(g_xpc+width*3,g_ypc,width,height,color,radius); // bottom right tyre
	DrawRoundRect(g_xpc+width*3,g_ypc+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(g_xpc,g_ypc+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(g_xpc, g_ypc+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(g_xpc+width, g_ypc+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(g_xpc+width*3, g_ypc+height*2, width, height, color, radius/2); // body right rect
	}
	else
	{
	float tem=1;
	DrawRoundRect(g_xpc,g_ypc+tem,widtha-1,heighta+1,color,radius); // bottom left tyre
	DrawRoundRect(g_xpc+widtha*3+2*defb,g_ypc+tem,widtha-1,heighta+1,color,radius); // bottom right tyre
	DrawRoundRect(g_xpc+widtha*3+2*defb,g_ypc+heighta*4-defc+tem,widtha-1,heighta+1,color,radius); // top right tyre
	DrawRoundRect(g_xpc,g_ypc+heighta*4-defc+tem,widtha-1,heighta+1,color,radius); // top left tyre
	DrawRoundRect(g_xpc+(widtha*3+2*defb)/2, g_ypc+heighta*3+defb-1+tem, widtha, heighta+defb+1, color, radius/2+1);//body to
	DrawRoundRect(g_xpc+widtha-1, g_ypc+heighta+tem, widtha*2+defd/2+1, heighta*3-defd+1, color, radius/2+1); // body center
	DrawRoundRect(g_xpc+(widtha*3+2*defb)/2, g_ypc+tem, widtha, heighta+defb, color, radius/2+1); // body bottom rect
	}

///////////////////////////////////////////////////////////////////////////////////////////////////

//FOOD

	//food is assigned to the required locations in array
	int fsizey=84;
	int fsizex=95;
	if(start==false) //game has not started;
	{	for(int x=1 ; x<=5;x++)
		{
			for(int j=0 ;j<95 ;j++)
			{
				for(int i=0 ;i<84 ;i++ )
				{
					//i=y-axis ,j=x-axis
					if( i>=6 && i<=75 && (j==6+9*(x-1) || j==85-9*(x-1)) )
					{
					food[fsizey-i][j]=6;
					i+=8;	          //6 symbolizees that food is present
					}
				}
			}
		}
	}

	//drawing the food			
	for(int i=0 ;i<84;i++)
	{
		for(int j=0 ;j<95;j++)
		{
			if(food[i][j]==6)
			{
				DrawSquare(  (j+1)*10, (fsizey-(i+1))*10 ,20,colors[YELLOW]); 
			}
		}

	}
	
	//eating food
	if(start==true)
	{
	for(int i=0 ;i<84;i++)
	{
	for(int j=0 ;j<95;j++)
	{

	if(g_dirPc==1 && g_xpc>=(j+1)*10 && g_xpc<=(j+1)*10+20 && g_ypc+g_carhx>=(fsizey-(i+1))*10 && g_ypc<=(fsizey-(i+1))*10+20 )
	{
		if(food[i][j]==6 )
		{
			food[i][j]=0;
			g_score++;
		cout<<"\a"<<endl; //for beep or bell sound
		}
	}

	if(g_dirPc==2 && g_xpc+g_carwy>=(j+1)*10 && g_xpc<=(j+1)*10+20 && g_ypc+g_carhy>=(fsizey-(i+1))*10 && g_ypc<=(fsizey-(i+1))*10+20 )
	{
		if(food[i][j]==6)
		{
			food[i][j]=0;
			g_score++;
		cout<<"\a"<<endl; //for beep or bell sound
		}
	}

	if(g_dirPc==3 && g_xpc+g_carwx>=(j+1)*10 && g_xpc<=(j+1)*10+20 && g_ypc+g_carhx>=(fsizey-(i+1))*10 && g_ypc<=(fsizey-(i+1))*10+20 )
	{
		if(food[i][j]==6)
		{
			food[i][j]=0;
			g_score++;
		cout<<"\a"<<endl; //for beep or bell sound
		}
	}
	if(g_dirPc==4 && g_xpc+g_carwy>=(j+1)*10 && g_xpc<=(j+1)*10+20 && g_ypc+g_carhx>=(fsizey-(i+1))*10 && g_ypc<=(fsizey-(i+1))*10+20 )
	{
		if(food[i][j]==6)
		{
			food[i][j]=0;
			g_score++;
		cout<<"\a"<<endl; //for beep or bell sound
		}
	}
	}
	}
	}

	//counting food and drawing food bar
	int foodcounter=0;
	int x=130,y=822;
	for(int i=0 ;i<84;i++)
	{
	for(int j=0 ;j<95;j++)
	{
		if(food[i][j]==6)
		{
			foodcounter++;
			DrawCircle(x,y,5,colors[RED]);	//drawing food bar		
			x+=8;
		}
	}
	}
	if(foodcounter==0)
	{
		if(lvlscreen==false)
		{
		level++;
		}
		lvlscreen=true;
	}
///////////////////////////////////////////////////////////////////////////////////////////////////	


//OPPONENT CAR

if(start==true)
{
	if(g_oxMov>0)
	{
		g_dirOc=3;			//right
		oCarHorz=false;
	}
	if(g_oxMov<0)
	{
		g_dirOc=1;		//left
		oCarHorz=false;
	}
	if(g_oyMov>0)
	{
		g_dirOc=2;			//up
		oCarHorz=true;
	}
	if(g_oyMov<0)
	{
		g_dirOc=4;			//down
		oCarHorz=true;
	}
	if(oCarHorz==false &&  level==3 )
	{
		
		g_xoc+=(g_oxMov*2);
	}
	if(oCarHorz==true &&  level==3 )
	{
		
		g_yoc+=(g_oyMov*2);
	}
	if(level!=3)
	{	
	g_yoc+=g_oyMov;
	g_xoc+=g_oxMov;
	}
	if(lchange==true)
	{	
	lChangecntr++;
	}	
/// neeed changes according to level ///
	if(lChangecntr>50)
	{
		lchange=false;
		lChangecntr=0;
	}
///////////////////////////////////////////////////////

}
	//drawing the car
	float* coloro = colors[GREEN]; 
	if(oCarHorz==false)
	{

	DrawRoundRect(g_xoc,g_yoc,width,height,coloro,radius); // bottom left tyre
	DrawRoundRect(g_xoc+width*3,g_yoc,width,height,coloro,radius); // bottom right tyre
	DrawRoundRect(g_xoc+width*3,g_yoc+height*4,width,height,coloro,radius); // top right tyre
	DrawRoundRect(g_xoc,g_yoc+height*4,width,height,coloro,radius); // top left tyre
	DrawRoundRect(g_xoc, g_yoc+height*2, width, height, coloro, radius/2); // body left rect
	DrawRoundRect(g_xoc+width, g_yoc+height, width*2, height*3, coloro, radius/2); // body center rect
	DrawRoundRect(g_xoc+width*3, g_yoc+height*2, width, height, coloro, radius/2); // body right rect

	}
	else
	{
	float tem=1;
	DrawRoundRect(g_xoc,g_yoc,widtha-1,heighta+1,coloro,radius); // bottom left tyre
	DrawRoundRect(g_xoc+widtha*3+2*defb,g_yoc,widtha-1,heighta+1,coloro,radius); // bottom right tyre
	DrawRoundRect(g_xoc+widtha*3+2*defb,g_yoc+heighta*4-defc,widtha-1,heighta+1,coloro,radius); // top right tyre
	DrawRoundRect(g_xoc,g_yoc+heighta*4-defc,widtha-1,heighta+1,coloro,radius); // top left tyre
	DrawRoundRect(g_xoc+(widtha*3+2*defb)/2, g_yoc+heighta*3+defb-1, widtha, heighta+defb+1, coloro, radius/2+1);//body top rec
	DrawRoundRect(g_xoc+widtha-1, g_yoc+heighta, widtha*2+defd/2+1, heighta*3-defd+1, coloro, radius/2+1); // body center rect
	DrawRoundRect(g_xoc+(widtha*3+2*defb)/2, g_yoc, widtha, heighta+defb, coloro, radius/2+1); // body bottom rect

	}

/////////////////////////
//Opponent auto movement

//for outer loop
if(g_dirOc==1 && g_xoc>=arena[6][0] && g_xoc-20<=arena[6][4] && g_yoc>=arena[6][1] && g_yoc<=arena[7][5] ){
		g_oyMov=-g_ospeed;
		g_oxMov=0;

	} //left


if(g_dirOc==2 && g_xoc>=arena[4][0] && g_xoc<=arena[5][4] && g_yoc+67>=arena[5][1] && g_yoc<=arena[5][5] )
	{
		//g_yoc+=2;
		g_oyMov=0;
		g_oxMov=-g_ospeed;	 
	} //up

if(g_dirOc==3 && g_xoc+60>=arena[2][0] && g_xoc<=arena[2][4] && g_yoc>=arena[2][1] && g_yoc<=arena[3][5] )
	{
		g_oyMov=+g_ospeed;
		g_oxMov=0;

	} //right

if(g_dirOc==4 && g_xoc>=arena[0][0] && g_xoc+20<=arena[1][4] && g_yoc>=arena[0][1] && g_yoc-10<=arena[0][5] )
	{
		g_oxMov=+g_ospeed;
		g_oyMov=0;
	
	} //down

/////////////////////////
//automovement
// for inner loops
for(int i=8 ;i<40 ;i+=8)
{
if(g_dirOc==1 && g_xoc>=arena[i+6][0] && g_xoc-20<=arena[i+6][4] && g_yoc>=arena[i+6][1] && g_yoc<=arena[i+6][5] ){
		g_oyMov=-g_ospeed;
		g_oxMov=0;

	} //left
if(g_dirOc==1 && g_xoc>=arena[i+7][0] && g_xoc-20<=arena[i+7][4] && g_yoc+60>=arena[i+7][1] && g_yoc<=arena[i+7][5] ){
		g_oyMov=-g_ospeed;
		g_oxMov=0;

	} //left


if(g_dirOc==2 && g_xoc>=arena[i+4][0] && g_xoc<=arena[i+4][4] && g_yoc+65>=arena[i+4][1] && g_yoc<=arena[i+4][5] )
	{
		//g_yoc+=2;
		g_oyMov=0;
		g_oxMov=-g_ospeed;	 
	} //up

if(g_dirOc==2 && g_xoc>=arena[i+5][0] && g_xoc<=arena[i+5][4] && g_yoc+65>=arena[i+5][1] && g_yoc<=arena[i+5][5] )
	{
		//g_yoc+=2;
		g_oyMov=0;
		g_oxMov=-g_ospeed;	 
	} //up
if(g_dirOc==3 && g_xoc+60>=arena[i+2][0] && g_xoc<=arena[i+2][4] && g_yoc>=arena[i+2][1] && g_yoc<=arena[i+2][5] )
	{
		g_oyMov=+g_ospeed;
		g_oxMov=0;

	} //right
if(g_dirOc==3 && g_xoc+60>=arena[i+3][0] && g_xoc<=arena[i+3][4] && g_yoc+60>=arena[i+3][1] && g_yoc<=arena[i+3][5] )
	{
		g_oyMov=+g_ospeed;
		g_oxMov=0;

	} //right

if(g_dirOc==4 && g_xoc>=arena[i+0][0] && g_xoc<=arena[i+0][4] && g_yoc>=arena[i+0][1] && g_yoc-10<=arena[i+0][5] )
	{
		g_oxMov=+g_ospeed;
		g_oyMov=0;
	
	} //down
if(g_dirOc==4 && g_xoc>=arena[i+1][0] && g_xoc<=arena[i+1][4] && g_yoc>=arena[i+1][1] && g_yoc-10<=arena[i+1][5] )
	{
		g_oxMov=+g_ospeed;
		g_oyMov=0;
	
	} //down

}
/////////////////////////////////////
//opponent lane change

	///for going to an outer lane	
	if ( loopo<loopp && lchange==false) {
		if(level!=1)
		{
	if(g_yoc>=arena[6][5] && g_yoc+55<=arena[7][1])
	{	

		if((g_xoc>=arena[6][4]+20 && g_xoc<=arena[(8*4)+7][0])||(g_xoc>=arena[(8*4)+2][0]-20 && g_xoc<=arena[2][4])){		
			
			if(g_xoc<=arena[(8*4)+7][0])
			{			
				loopo++;
				g_xoc-=90;
				lchange=true;		
			}			
			}
			}
		

if(g_yoc>=arena[6][5] && g_yoc+55<=arena[7][1])
		{	
			if((g_xoc>=arena[6][4] && g_xoc<=arena[(8*4)+7][0]-10)||(g_xoc>=arena[(8*4)+2][0]-20 && g_xoc<=arena[2][4]-20))	{
			if(!(g_xoc<=arena[(8*4)+7][0]))
			{
				g_xoc+=90;
				loopo++;
				lchange=true;
			}
			}
			}
}
if(g_xoc>=arena[4][4] && g_xoc+30<=arena[5][0])
	{	
		if((g_yoc>=arena[1][5] && g_yoc<=arena[(8*4)+4][5]-10)||(g_yoc>=arena[(8*4)+4][5]-10 && g_yoc<=arena[4][1]))	
		{
			if(!(g_yoc<=arena[(8*4)+4][5]-10))
			{		
				loopo++;
				g_yoc+=90;
				lchange=true;
			}
		}
	}
if(g_xoc>=arena[4][4] && g_xoc+30<=arena[5][0])
		{
		if((g_yoc>=arena[1][5] && g_yoc<=arena[(8*4)+1][5]-10)||(g_yoc>=arena[(8*4)+4][5]+20 && g_yoc<=arena[4][1])){

			if(g_yoc<=arena[(8*4)+4][5]-10)
			{			
				loopo++;
			g_yoc-=90;
				lchange=true;

			}
		}		
		}
		}
// for going to an inner lane
else if ( loopo>loopp && lchange==false) {
if(level!=1)
{
if(g_yoc>=arena[6][5] && g_yoc+55<=arena[7][1])
		{	
	
		if((g_xoc>=arena[6][4]+20 && g_xoc<=arena[(8*4)+7][0])||(g_xoc>=arena[(8*4)+2][0]-20 && g_xoc<=arena[2][4])){		
		
			if(!(g_xoc<=arena[(8*4)+7][0]))
			{			
				loopo--;
				g_xoc-=90;
				lchange=true;
			}			
			}
			}
		

if(g_yoc>=arena[6][5] && g_yoc+55<=arena[7][1])
		{	
			if((g_xoc>=arena[6][4] && g_xoc<=arena[(8*4)+7][0]-10)||(g_xoc>=arena[(8*4)+2][0]-20 && g_xoc<=arena[2][4]-20))	{
			if((g_xoc<=arena[(8*4)+7][0]))
			{
				g_xoc+=90;
				loopo--;
				lchange=true;
			}
			}
			}
		}
if(g_xoc>=arena[4][4] && g_xoc+30<=arena[5][0])
	{	
		if((g_yoc>=arena[1][5] && g_yoc<=arena[(8*4)+4][5]-10)||(g_yoc>=arena[(8*4)+4][5]-10 && g_yoc<=arena[4][1]))	
		{
			if((g_yoc<=arena[(8*4)+4][5]-10))
			{		
				loopo--;
				g_yoc+=90;
				lchange=true;
			}
		}
	}
if(g_xoc>=arena[4][4] && g_xoc+30<=arena[5][0])
		{
		if((g_yoc>=arena[1][5] && g_yoc<=arena[(8*4)+1][5]-10)||(g_yoc>=arena[(8*4)+4][5]+20 && g_yoc<=arena[4][1])){

			if(!(g_yoc<=arena[(8*4)+4][5]-10))
			{			
				loopo--;
			g_yoc-=90;
				lchange=true;
			}
		}		
		}
		}	

/////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//OPPONENT 2


if(level==4)
{
if(start==true)
{
	if(g_o2xMov>0)
	{
		g_dirO2c=3;			//right
		o2CarHorz=false;
	}
	if(g_o2xMov<0)
	{
		g_dirO2c=1;		//left
		o2CarHorz=false;
	}
	if(g_o2yMov>0)
	{
		g_dirO2c=2;			//up
		o2CarHorz=true;
	}
	if(g_o2yMov<0)
	{
		g_dirO2c=4;			//down
		o2CarHorz=true;
	}
	if(o2CarHorz==false &&  level==3 )
	{
		
		g_xo2c+=(g_o2xMov*3);
	}
	if(o2CarHorz==true &&  level==3 )
	{
		
		g_yo2c+=(g_o2yMov*3);
	}
	if(level!=3)
	{	
	g_yo2c+=g_o2yMov;
	g_xo2c+=g_o2xMov;
	}
	if(lchange==true)
	{	
	lChangecntr++;
	}	
/// need changes according to level ///
	if(lChangecntr>50)
	{
		lchange=false;
		lChangecntr=0;
	}
///////////////////////////////////////////////////////

}
	//Drawing the Opponent car 2
	coloro = colors[GREEN]; 
	if(o2CarHorz==false)
	{

	DrawRoundRect(g_xo2c,g_yo2c,width,height,coloro,radius); // bottom left tyre
	DrawRoundRect(g_xo2c+width*3,g_yo2c,width,height,coloro,radius); // bottom right tyre
	DrawRoundRect(g_xo2c+width*3,g_yo2c+height*4,width,height,coloro,radius); // top right tyre
	DrawRoundRect(g_xo2c,g_yo2c+height*4,width,height,coloro,radius); // top left tyre
	DrawRoundRect(g_xo2c, g_yo2c+height*2, width, height, coloro, radius/2); // body left rect
	DrawRoundRect(g_xo2c+width, g_yo2c+height, width*2, height*3, coloro, radius/2); // body center rect
	DrawRoundRect(g_xo2c+width*3, g_yo2c+height*2, width, height, coloro, radius/2); // body right rect

	}
	else
	{
	float tem=1;
	DrawRoundRect(g_xo2c,g_yo2c,widtha-1,heighta+1,coloro,radius); // bottom left tyre
	DrawRoundRect(g_xo2c+widtha*3+2*defb,g_yo2c,widtha-1,heighta+1,coloro,radius); // bottom right tyre
	DrawRoundRect(g_xo2c+widtha*3+2*defb,g_yo2c+heighta*4-defc,widtha-1,heighta+1,coloro,radius); // top right tyre
	DrawRoundRect(g_xo2c,g_yo2c+heighta*4-defc,widtha-1,heighta+1,coloro,radius); // top left tyre
	DrawRoundRect(g_xo2c+(widtha*3+2*defb)/2, g_yo2c+heighta*3+defb-1, widtha, heighta+defb+1, coloro, radius/2+1);//body top rec
	DrawRoundRect(g_xo2c+widtha-1, g_yo2c+heighta, widtha*2+defd/2+1, heighta*3-defd+1, coloro, radius/2+1); // body center rect
	DrawRoundRect(g_xo2c+(widtha*3+2*defb)/2, g_yo2c, widtha, heighta+defb, coloro, radius/2+1); // body bottom rect

	}

///////////////////////////
//Opponent2 auto movement
//for outer loop
if(g_dirO2c==1 && g_xo2c>=arena[6][0] && g_xo2c-20<=arena[6][4] && g_yo2c>=arena[6][1] && g_yo2c<=arena[7][5] ){
		g_o2yMov=-g_o2speed;
		g_o2xMov=0;

	} //left


if(g_dirO2c==2 && g_xo2c>=arena[4][0] && g_xo2c<=arena[5][4] && g_yo2c+67>=arena[5][1] && g_yo2c<=arena[5][5] )
	{
		//g_yo2c+=2;
		g_o2yMov=0;
		g_o2xMov=-g_o2speed;	 
	} //up

if(g_dirO2c==3 && g_xo2c+60>=arena[2][0] && g_xo2c<=arena[2][4] && g_yo2c>=arena[2][1] && g_yo2c<=arena[3][5] )
	{
		g_o2yMov=+g_o2speed;
		g_o2xMov=0;

	} //right

if(g_dirO2c==4 && g_xo2c>=arena[0][0] && g_xo2c+20<=arena[1][4] && g_yo2c>=arena[0][1] && g_yo2c-10<=arena[0][5] )
	{
		g_o2xMov=+g_o2speed;
		g_o2yMov=0;
	
	} //down

/////////////////////////
//Opponent2 auto movement
//for inner loops
for(int i=8 ;i<40 ;i+=8)
{
if(g_dirO2c==1 && g_xo2c>=arena[i+6][0] && g_xo2c-20<=arena[i+6][4] && g_yo2c>=arena[i+6][1] && g_yo2c<=arena[i+6][5] ){
		g_o2yMov=-g_o2speed;
		g_o2xMov=0;

	} //left
if(g_dirO2c==1 && g_xo2c>=arena[i+7][0] && g_xo2c-20<=arena[i+7][4] && g_yo2c+60>=arena[i+7][1] && g_yo2c<=arena[i+7][5] ){
		g_o2yMov=-g_o2speed;
		g_o2xMov=0;

	} //left


if(g_dirO2c==2 && g_xo2c>=arena[i+4][0] && g_xo2c<=arena[i+4][4] && g_yo2c+65>=arena[i+4][1] && g_yo2c<=arena[i+4][5] )
	{
		//g_yo2c+=2;
		g_o2yMov=0;
		g_o2xMov=-g_o2speed;	 
	} //up

if(g_dirO2c==2 && g_xo2c>=arena[i+5][0] && g_xo2c<=arena[i+5][4] && g_yo2c+65>=arena[i+5][1] && g_yo2c<=arena[i+5][5] )
	{
		//g_yo2c+=2;
		g_o2yMov=0;
		g_o2xMov=-g_o2speed;	 
	} //up
if(g_dirO2c==3 && g_xo2c+60>=arena[i+2][0] && g_xo2c<=arena[i+2][4] && g_yo2c>=arena[i+2][1] && g_yo2c<=arena[i+2][5] )
	{
		g_o2yMov=+g_o2speed;
		g_o2xMov=0;

	} //right
if(g_dirO2c==3 && g_xo2c+60>=arena[i+3][0] && g_xo2c<=arena[i+3][4] && g_yo2c+60>=arena[i+3][1] && g_yo2c<=arena[i+3][5] )
	{
		g_o2yMov=+g_o2speed;
		g_o2xMov=0;

	} //right

if(g_dirO2c==4 && g_xo2c>=arena[i+0][0] && g_xo2c<=arena[i+0][4] && g_yo2c>=arena[i+0][1] && g_yo2c-10<=arena[i+0][5] )
	{
		g_o2xMov=+g_o2speed;
		g_o2yMov=0;
	
	} //down
if(g_dirO2c==4 && g_xo2c>=arena[i+1][0] && g_xo2c<=arena[i+1][4] && g_yo2c>=arena[i+1][1] && g_yo2c-10<=arena[i+1][5] )
	{
		g_o2xMov=+g_o2speed;
		g_o2yMov=0;
	
	} //down

}
/////////////////////////////////////
// Opponent lane change
//for going into outer lanes
	if ( loopo2<loopp && lchange==false) {
if(level!=1)
{
if(g_yo2c>=arena[6][5] && g_yo2c+55<=arena[7][1])
		{	

		if((g_xo2c>=arena[6][4]+20 && g_xo2c<=arena[(8*4)+7][0])||(g_xo2c>=arena[(8*4)+2][0]-20 && g_xo2c<=arena[2][4])){		
			
			if(g_xo2c<=arena[(8*4)+7][0])
			{			
				loopo2++;
				g_xo2c-=90;
				lchange=true;		
			}			
			}
			}
		

if(g_yo2c>=arena[6][5] && g_yo2c+55<=arena[7][1])
		{	
			if((g_xo2c>=arena[6][4] && g_xo2c<=arena[(8*4)+7][0]-10)||(g_xo2c>=arena[(8*4)+2][0]-20 && g_xo2c<=arena[2][4]-20))	{
			if(!(g_xo2c<=arena[(8*4)+7][0]))
			{
				g_xo2c+=90;
				loopo2++;
				lchange=true;
			}
			}
			}
}
if(g_xo2c>=arena[4][4] && g_xo2c+30<=arena[5][0])
	{	
		if((g_yo2c>=arena[1][5] && g_yo2c<=arena[(8*4)+4][5]-10)||(g_yo2c>=arena[(8*4)+4][5]-10 && g_yo2c<=arena[4][1]))	
		{
			if(!(g_yo2c<=arena[(8*4)+4][5]-10))
			{		
				loopo2++;
				g_yo2c+=90;
				lchange=true;
			}
		}
	}
if(g_xo2c>=arena[4][4] && g_xo2c+30<=arena[5][0])
		{
		if((g_yo2c>=arena[1][5] && g_yo2c<=arena[(8*4)+1][5]-10)||(g_yo2c>=arena[(8*4)+4][5]+20 && g_yo2c<=arena[4][1])){

			if(g_yo2c<=arena[(8*4)+4][5]-10)
			{			
				loopo2++;
			g_yo2c-=90;
				lchange=true;

			}
		}		
		}
		}
//for going into inner lanes
else if ( loopo2>loopp && lchange==false) {
if(level!=1)
{
if(g_yo2c>=arena[6][5] && g_yo2c+55<=arena[7][1])
		{	
	
		if((g_xo2c>=arena[6][4]+20 && g_xo2c<=arena[(8*4)+7][0])||(g_xo2c>=arena[(8*4)+2][0]-20 && g_xo2c<=arena[2][4]))
		{	
			if(!(g_xo2c<=arena[(8*4)+7][0]))
			{			
				loopo2--;
				g_xo2c-=90;
				lchange=true;
			}			
			}
			}
		

if(g_yo2c>=arena[6][5] && g_yo2c+55<=arena[7][1])
		{	
		if((g_xo2c>=arena[6][4] && g_xo2c<=arena[(8*4)+7][0]-10)||(g_xo2c>=arena[(8*4)+2][0]-20 && g_xo2c<=arena[2][4]-20))
		{
			if((g_xo2c<=arena[(8*4)+7][0]))
			{
				g_xo2c+=90;
				loopo2--;
				lchange=true;
			}
			}
			}
		}
if(g_xo2c>=arena[4][4] && g_xo2c+30<=arena[5][0])
	{	
		if((g_yo2c>=arena[1][5] && g_yo2c<=arena[(8*4)+4][5]-10)||(g_yo2c>=arena[(8*4)+4][5]-10 && g_yo2c<=arena[4][1]))	
		{
			if((g_yo2c<=arena[(8*4)+4][5]-10))
			{		
				loopo2--;
				g_yo2c+=90;
				lchange=true;
			}
		}
	}
if(g_xo2c>=arena[4][4] && g_xo2c+30<=arena[5][0])
		{
		if((g_yo2c>=arena[1][5] && g_yo2c<=arena[(8*4)+1][5]-10)||(g_yo2c>=arena[(8*4)+4][5]+20 && g_yo2c<=arena[4][1])){

			if(!(g_yo2c<=arena[(8*4)+4][5]-10))
			{			
				loopo2--;
			g_yo2c-=90;
				lchange=true;
			}
		}		
		}
		}	

}
/////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Setting parameters for Arena

	int gap_turn = 110;
	int sx = 45;
	int sy = 10;
	int temp=720;
	int wa=70;
	int swidth = temp/2 - gap_turn/2;
	int swidtha =wa+ temp/2 - gap_turn/2;// half width
	int sheight = 10;
	int xh=10;
	int def=20;
	int defa=2;
	float *scolor=colors[RED];
	scolor+=6;
//Storing the parameters of arena in an array
	for(int i=0,j=0 ; i<40 ;i+=8,j++ )
	{
		if(j!=0)
		{
		sx+=90;
		sy+=90;
		temp-=180;
		swidth = temp/2 - gap_turn/2;
		swidtha =wa+ temp/2 - gap_turn/2;
		}		
		if(j==4)
		{
			gap_turn=0;
			wa=70;
			xh=10;
			def=20;
			defa=2;
			swidth = temp/2 - gap_turn/2;
			swidtha =wa+ temp/2 - gap_turn/2;
		}

		// bottom left
		arena[i][0]=sx;
		arena[i][1]=sy-xh;
		arena[i][2]=swidtha;
		arena[i][3]=sheight+xh;
		arena[i][4]=arena[i][0]+arena[i][2];
		arena[i][5]=arena[i][1]+arena[i][3];

		// bottom right
		arena[i+1][0]=sx + swidtha + gap_turn ;
		arena[i+1][1]=sy-xh ;
		arena[i+1][2]=swidtha ;
		arena[i+1][3]=sheight+xh ;
		arena[i+1][4]=arena[i+1][0]+arena[i+1][2];
		arena[i+1][5]=arena[i+1][1]+arena[i+1][3];

		// right down
		arena[i+2][0]=sx+swidtha*2+gap_turn-defa ;
		arena[i+2][1]=sy+sheight-def ;
		arena[i+2][2]=sheight*2+defa ;
		arena[i+2][3]=swidth+def ; 
		arena[i+2][4]=arena[i+2][0]+arena[i+2][2];
		arena[i+2][5]=arena[i+2][1]+arena[i+2][3];

		// right up
		arena[i+3][0]=sx+swidtha*2+gap_turn-defa ;
		arena[i+3][1]=sy+sheight+swidth+gap_turn ;
		arena[i+3][2]=sheight*2+defa ;
		arena[i+3][3]=swidth+def ; 
		arena[i+3][4]=arena[i+3][0]+arena[i+3][2];
		arena[i+3][5]=arena[i+3][1]+arena[i+3][3];

		// top left
		arena[i+4][0]=sx ;
		arena[i+4][1]=sy+temp+10 ;
		arena[i+4][2]=swidtha ;
		arena[i+4][3]=sheight+xh ; 
		arena[i+4][4]=arena[i+4][0]+arena[i+4][2];
		arena[i+4][5]=arena[i+4][1]+arena[i+4][3];

		// top right		
		arena[i+5][0]=sx + swidtha + gap_turn ;
		arena[i+5][1]=sy+temp+10 ;
		arena[i+5][2]=swidtha ;
		arena[i+5][3]=sheight+xh ; 
		arena[i+5][4]=arena[i+5][0]+arena[i+5][2];
		arena[i+5][5]=arena[i+5][1]+arena[i+5][3];
		
		// left down
		arena[i+6][0]=sx-sheight*2 ;
		arena[i+6][1]=sy+sheight-def ;
		arena[i+6][2]=sheight*2+defa ;
		arena[i+6][3]=swidth+def ; 
		arena[i+6][4]=arena[i+6][0]+arena[i+6][2];
		arena[i+6][5]=arena[i+6][1]+arena[i+6][3];

		// left up
		arena[i+7][0]=sx-sheight*2 ;
		arena[i+7][1]=sy+sheight+swidth+gap_turn ;
		arena[i+7][2]=sheight*2+defa ;
		arena[i+7][3]=swidth+def ; 
		arena[i+7][4]=arena[i+7][0]+arena[i+7][2];
		arena[i+7][5]=arena[i+7][1]+arena[i+7][3];


	}

//Drawing Arena
	for(int i=0 ;i<40;i++)
	{
		DrawRectangle(arena[i][0],arena[i][1],arena[i][2],arena[i][3],scolor);
	}




////////////////////
//
//to again store the original parameters of arena
	 gap_turn = 110;
	 sx = 45;
	 sy = 10;
	 temp=720;
	 wa=70;
	 swidth = temp/2 - gap_turn/2;
	 swidtha =wa+ temp/2 - gap_turn/2;// half width
	 sheight = 10;
	 xh=10;
	 def=20;
	 defa=2;

///////////////////////////
//  Store the correct coordinates of car movement after space is pressed
		g_pxMov=tempx;
		g_pyMov=tempy;
/////////////////////////////
//////////////////////////////
//Automovement of player car
//for outer lane
if(g_dirPc==1 && g_xpc>=arena[6][0] && g_xpc-20<=arena[6][4] && g_ypc>=arena[6][1] && g_ypc<=arena[7][5] ){
		g_pyMov=+g_pspeed;
		g_pxMov=0;

	} //left


if(g_dirPc==2 && g_xpc>=arena[4][0] && g_xpc<=arena[5][4] && g_ypc+67>=arena[5][1] && g_ypc<=arena[5][5] )
	{
		//g_ypc+=2;
		g_pyMov=0;
		g_pxMov=+g_pspeed;	 
	} //up

if(g_dirPc==3 && g_xpc+60>=arena[2][0] && g_xpc<=arena[2][4] && g_ypc>=arena[2][1] && g_ypc<=arena[3][5] )
	{
		g_pyMov=-g_pspeed;
		g_pxMov=0;

	} //right

if(g_dirPc==4 && g_xpc>=arena[0][0] && g_xpc+20<=arena[1][4] && g_ypc>=arena[0][1] && g_ypc-10<=arena[0][5] )
	{
		g_pxMov=-g_pspeed;
		g_pyMov=0;
	
	} //down

/////////////////////////
//Automovement of player car
//for inner lanes
for(int i=8 ;i<40 ;i+=8)
{
if(g_dirPc==1 && g_xpc>=arena[i+6][0] && g_xpc-20<=arena[i+6][4] && g_ypc>=arena[i+6][1] && g_ypc<=arena[i+6][5] ){
		g_pyMov=+g_pspeed;
		g_pxMov=0;

	} //left
if(g_dirPc==1 && g_xpc>=arena[i+7][0] && g_xpc-20<=arena[i+7][4] && g_ypc+60>=arena[i+7][1] && g_ypc<=arena[i+7][5] ){
		g_pyMov=+g_pspeed;
		g_pxMov=0;

	} //left


if(g_dirPc==2 && g_xpc>=arena[i+4][0] && g_xpc<=arena[i+4][4] && g_ypc+65>=arena[i+4][1] && g_ypc<=arena[i+4][5] )
	{
		g_pyMov=0;
		g_pxMov=+g_pspeed;	 
	} //up

if(g_dirPc==2 && g_xpc>=arena[i+5][0] && g_xpc<=arena[i+5][4] && g_ypc+65>=arena[i+5][1] && g_ypc<=arena[i+5][5] )
	{
		g_pyMov=0;
		g_pxMov=+g_pspeed;	 
	} //up
if(g_dirPc==3 && g_xpc+60>=arena[i+2][0] && g_xpc<=arena[i+2][4] && g_ypc>=arena[i+2][1] && g_ypc<=arena[i+2][5] )
	{
		g_pyMov=-g_pspeed;
		g_pxMov=0;

	} //right
if(g_dirPc==3 && g_xpc+60>=arena[i+3][0] && g_xpc<=arena[i+3][4] && g_ypc+60>=arena[i+3][1] && g_ypc<=arena[i+3][5] )
	{
		g_pyMov=-g_pspeed;
		g_pxMov=0;

	} //right

if(g_dirPc==4 && g_xpc>=arena[i+0][0] && g_xpc<=arena[i+0][4] && g_ypc>=arena[i+0][1] && g_ypc-10<=arena[i+0][5] )
	{
		g_pxMov=-g_pspeed;
		g_pyMov=0;
	
	} //down
if(g_dirPc==4 && g_xpc>=arena[i+1][0] && g_xpc<=arena[i+1][4] && g_ypc>=arena[i+1][1] && g_ypc-10<=arena[i+1][5] )
	{
		g_pxMov=-g_pspeed;
		g_pyMov=0;
	
	} //down

}

/////////////////////////////////////////////////////////////////

// Current check for cars colllision

	if(invincible==false)
	{
	if(abs(g_xpc-g_xoc)<=30 && abs(g_ypc-g_yoc)<=30)
	{
		g_crash=true;
	}
	if(level==4)
	{
		if(abs(g_xpc-g_xo2c)<=30 && abs(g_ypc-g_yo2c)<=30)
		{
			g_crash=true;
		}
	}
	}
//Conditions to change if cars crash

	if(g_crash==true)
	{
		if(lives>1) //player has not lost
		{
		
		lives--;
		g_xpc=inixpc;
		g_ypc=iniypc;

		g_pxMov=-g_pspeed;
		g_pyMov=0;		
		pCarHorz=false;
		loopp=4;
		loopo=4;
		loopo2=4;
		g_xoc=inixoc;
		g_yoc=iniyoc;
		g_oxMov=g_ospeed;
		g_oyMov=0;
		oCarHorz=false;
		g_xo2c=inixo2c;
		g_yo2c=iniyo2c;
		g_o2xMov=-g_o2speed;
		g_o2yMov=0;
		o2CarHorz=false;
		g_crash=false;

		}
		else //player lost
		{
			gameover=true;	
		}	
	}

	if(level>4) //player won
	{	
		gameover=true;
	}
///////////////////////////
//  To reset the value of space bar after a successful boost	
		spressed=false;

//////////////////////////
// do not modify this line.. or draw anything below this line
}
	
}
glutSwapBuffers(); 
}
/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if(pmenu==false && smenu==false)// if menu is opened
	{
	//Checks for lane chnage of player
	//When left arrow key is pressed
	if (key == GLUT_KEY_LEFT ) {
		start=true;
		
		if(g_ypc>=arena[6][5] && g_ypc+55<=arena[7][1])
		{	
		if((g_xpc>=arena[6][4]+20 && g_xpc<=arena[(8*4)+7][0])||(g_xpc>=arena[(8*4)+2][0]-20 && g_xpc<=arena[2][4])){		
			
			bool flag=true;
			if(g_xpc<=arena[(8*4)+7][0])
			{			
				loopp++;
			}
			else
			{
				loopp--;
			}
			if(loopp==0)
			{
				loopp++;
				flag=false;
			}
			if(loopp==5)
			{
				loopp--;
				flag=false;
			}
			if(flag==true)
			{
				g_xpc-=90;
			}
			}
		}
	} 
	//When right arrow key is pressed
	else if (key == GLUT_KEY_RIGHT) {
		start=true;
	
		if(g_ypc>=arena[6][5] && g_ypc+55<=arena[7][1])
		{	
			if((g_xpc>=arena[6][4] && g_xpc<=arena[(8*4)+7][0]-10)||(g_xpc>=arena[(8*4)+2][0]-20 && g_xpc<=arena[2][4]-20))	{
			
			bool flag=true;
			if(g_xpc<=arena[(8*4)+7][0])
			{			
				loopp--;
			}
			else
			{
				loopp++;
			}

			if(loopp==0)
			{
				loopp++;
				flag=false;
			}
			if(loopp==5)
			{
				loopp--;
				flag=false;
			}
			if(flag==true)
			{
			g_xpc+=90;
			}
			}
		}
	} 
	//When up arrow key is pressed
	else if (key == GLUT_KEY_UP) {
		start=true;

	if(g_xpc>=arena[4][4] && g_xpc+30<=arena[5][0])
	{	
		if((g_ypc>=arena[1][5] && g_ypc<=arena[(8*4)+4][5]-10)||(g_ypc>=arena[(8*4)+4][5]-10 && g_ypc<=arena[4][1]))	
		{
			bool flag=true;
			
			if(g_ypc<=arena[(8*4)+4][5]-10)
			{			
				loopp--;
			}
			else
			{
				loopp++;
			}
			if(loopp==0)
			{
				loopp++;
				flag=false;
			}
			if(loopp==5)
			{
				loopp--;
				flag=false;
			}
			if(flag==true)
			{
			g_ypc+=90;
			}
	}
	}
	}
		//When down arrow key is pressed
	else if (key == GLUT_KEY_DOWN) {
		start=true;
	
		if(g_xpc>=arena[4][4] && g_xpc+30<=arena[5][0])
		{
		if((g_ypc>=arena[1][5] && g_ypc<=arena[(8*4)+1][5]-10)||(g_ypc>=arena[(8*4)+4][5]+20 && g_ypc<=arena[4][1])){

			bool flag=true;
			
			if(g_ypc<=arena[(8*4)+4][5]-10)
			{			
				loopp++;
			}
			else
			{
				loopp--;
			}
			if(loopp==0)
			{
				loopp++;
				flag=false;
			}
			if(loopp==5)
			{
				loopp--;
				flag=false;
			}
			if(flag==true)
			{
			g_ypc-=90;
			}
		}		
		}
		}
	
	glutPostRedisplay();
	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
}
else	// for navigation in menu
{
	if(key == GLUT_KEY_LEFT && pmenu==true) //for secret menu left key counter
	{
		if(smlcntr<3 && smrcntr==2)
		{
			if(smlcntr==2)
			{
				smrcntr=0;
				smenu=true;
				pmenu=false;
				smlcntr=0;
			}
			else
			{
			smlcntr++;
			}
		}
		else if( smrcntr!=2)
		{
			smrcntr=0;
			smlcntr=0;

		}
	}
	if(key == GLUT_KEY_RIGHT && pmenu==true)//for secret menu right key counter
	{
		if(smlcntr==0 && smrcntr<3)
		{
			smrcntr++;
		}
		else if(smlcntr!=0)
		{
			smlcntr=0;
			smrcntr=0;
		}
	}
	if (key == GLUT_KEY_UP && pmenu==true) { //navigating upwards in pause menu
	pmenucntr-=1;
	if(pmenucntr<1)
	{
		pmenucntr=5;
	}
	}
	if (key == GLUT_KEY_DOWN && pmenu==true) { //navigating downwards in pause menu
	pmenucntr+=1;
	if(pmenucntr>5)
	{
		pmenucntr=1;
	}
	}
	if (key == GLUT_KEY_UP && smenu==true) { //navigating upwards in secret menu
	smenucntr-=1;
	if(smenucntr<1)
	{
		smenucntr=5;
	}
	}
	if (key == GLUT_KEY_DOWN && smenu==true) { //navigating downwards in secret menu
	smenucntr+=1;
	if(smenucntr>5)
	{
		smenucntr=1;
	}
	}
}

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
	if(hlpscreen==true && (key=='q' || key=='Q')) //going back from help screen
	{
		pmenu=true;
		hlpscreen=false;
	}
	if(scorescreen==true && (key=='q' || key=='Q')) //going back from high score screen
	{
		scorescreen=false;
		pmenu=true;
	}
	if(gameover==true && key=='.')   //proceeding screens after game is over
	{
		if(sentryscreen==false)
		{
			sentryscreen=true;
		}

	}
	if(sentryscreen==true && key!='.') //for typing letters in name for high scores
	{	
		if(hscntr<=6)
		{
			if(hscntr<=5)
			{
			hsname[hscntr]=key;
			if(hscntr+1>5)
			{
				hsname[6]='\0';
			}
			}
		hscntr++;
		}
		else
		{
		for(int i=0 ;i<6;i++)
		{
		hsname[i]=' ';
		}
		hsname[6]='\0';
		hscntr=0;
		sentryscreen=false;
		gameover=false;
		pmenu=false;
		scorescreen=true;
		menu=true;
		}
	}
	//To open or close pause menu
	if (key == 'p' || key == 'P')
		{
		if(pmenu==false && smenu==false)
		{		
		pmenu=true;
		menu=true;
		pmenucntr=1;
		}	}
	// to boost the car
	if (key == ' ' && pmenu==false && smenu==false ){
		//do something if space is pressed
		spressed=true;
	}
	// to select an option in menu
	if (key == ' ' && pmenu==true){
		pmselected=true;
	}
	if ((key == 'q' || key == 'Q') && smenu==true && passmenu==true){// for going back from pin screen in secret menu
		smenu=false;
		pmenu=true;
		pin=0;
		correctpass=true;
		pincntr=0;
	}
	if (key == ' ' && smenu==true){ //something is selected in secret menu
		smselected=true;
	}
	if (key=='1' ||key=='2' ||key=='3' ||key=='4' ||key=='5' ||key=='6' ||key=='7' ||key=='8' ||key=='9' ||key=='0' )
	{	// typing of pin in authentication screen for secret menu
	if(smenu==true && passmenu==true)
	{
		pincntr++;
		int temp=0;
		if(pincntr==1)
		{
			temp=1000;
		}
		if(pincntr==2)
		{
			temp=100;
		}
		if(pincntr==3)
		{
			temp=10;
		}
		if(pincntr==4)
		{
			temp=1;
		}
		if(key=='1')
		{
			pin+=1*temp;
		}
		if(key=='2')
		{
			pin+=2*temp;
		}
		if(key=='3')
		{
			pin+=3*temp;
		}
		if(key=='4')
		{
			pin+=4*temp;
		}
		if(key=='5')
		{
			pin+=5*temp;
		}
		if(key=='6')
		{
			pin+=6*temp;
		}
		if(key=='7')
		{
			pin+=7*temp;
		}
		if(key=='8')
		{
			pin+=8*temp;
		}
		if(key=='9')
		{
			pin+=9*temp;
		}
		if(key=='0')
		{
			pin+=0*temp;
		}
	}
	}

	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here
	glutPostRedisplay();
	// once again we tell the library to call our Timer function after next 1/FPS
	glutTimerFunc(1.0, Timer, 0); //the value of fps is 1 to have smooth animations
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{
	
	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	//b = new Board(60, 60); // create a new board object to use in the Display Function ...

	int width = 950, height = 840; // i have set my window size to be 840 X 950
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Dodge Em"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
