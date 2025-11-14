#include <raylib.h>
#include <iostream>
#include <fstream>

using namespace std;

const int screen_x = 1200;
const int screen_y = 600;
const int screeny = 700;
const int singscreen_x = 700;
const int singscreen_y = 800;
const int singscreeny = 1000;
int score_player1;
int score_player2;
int score_ai;
bool five5 = true;
bool ten10 = true;
bool fifteen15 = true;

Color TRANS = Color{0, 0, 0, 0};
Color NEONWHITE = Color{240, 255, 255, 255};
Color NEONBLUE = Color{0, 255, 255, 255};
Color NEONGREEN = Color{57, 255, 20, 255};
Color NEONYELLOW = Color{255, 255, 20, 255};
Color NEONRED = Color{255, 16, 60, 255};
Color NEONPURPLE = Color{181, 0, 255, 255};
Color NEONPINK = Color{255, 0, 204, 255};
Color NEONORANGE = Color{255, 102, 0, 255};

int main();
void difficulty();
void aiplayereasy();
void aiplayermed();
void aiplayerhard();
void single();
void multi();
void Gameover();
void Gamewin();
void firsttomulti();

class Ball
{
public:
	float x, y;
	int speed_x;
	int speed_y;
	int r;

	void Draw()
	{
		DrawCircleGradient(x, y, r, BLACK, NEONPINK);
	}

	void Update(Sound s)
	{
		x += speed_x;
		y += speed_y;

		if (x + r >= GetScreenWidth() - 1 || x - r <= 1)
		{
			PlaySound(s);
			speed_x *= -1;

			if (x + r >= GetScreenWidth() - 1)
			{
				score_ai++;
				score_player1++;
				Reset();
			}

			else if (x - r <= 1)
			{
				score_player2++;
				Reset();
			}
		}

		if (y + r >= screen_y || y - r <= 1)
		{
			PlaySound(s);
			speed_y *= -1;
		}
	}

	void Reset()
	{
		x = GetScreenWidth() / 2;
		y = screen_y / 2;

		int choice[2] = {-1, 1};
		speed_x *= choice[GetRandomValue(0, 1)];
		speed_y *= choice[GetRandomValue(0, 1)];
	}
};

Ball ball;

class singBall
{
public:
	float x, y;
	int speed_x;
	int speed_y;
	int r;

	void Draw()
	{
		DrawCircleGradient(x, y, r, BLACK, NEONPINK);
	}

	void Update(Sound s, Sound p)
	{

		x += speed_x;
		y += speed_y;

		if (x + r >= GetScreenWidth() - 1 || x - r <= 1)
		{
			PlaySound(s);
			speed_x *= -1;
		}
		if (y + r >= singscreen_y || y - r <= 1)
		{
			speed_y *= -1;

			if (y - r <= 1)
			{
				PlaySound(s);
				score_player1++;
			}

			else if (y + r >= singscreen_y - 1)
			{
				ofstream Score("Score.txt",ios::app);
				if(!Score)
				{
					main();
				}
				Score<<score_player1<<endl;
				Score.close();
				PlaySound(p);
				CloseAudioDevice();
				Gameover();
			}
		}
	}

	void speed()
	{
		if(score_player1==10)
		{
			if(speed_x<0)
			{
				speed_x = -7;
			}
			else
			{
				speed_x = 7;
			}
			if(speed_y<0)
			{
				speed_y = -7;
			}
			else
			{
				speed_y = 7;
			}
		}

		if(score_player1==20)
		{
			if(speed_x<0)
			{
				speed_x = -8;
			}
			else
			{
				speed_x = 8;
			}
			if(speed_y<0)
			{
				speed_y = -8;
			}
			else
			{
				speed_y = 8;
			}
		}

		if(score_player1==40)
		{
			if(speed_x<0)
			{
				speed_x = -9;
			}
			else
			{
				speed_x = 9;
			}
			if(speed_y<0)
			{
				speed_y = -9;
			}
			else
			{
				speed_y = 9;
			}
		}
	}
};

singBall singball;

class BackBall
{
public:
	float x,y;
	float r;
	int speed_x,speed_y;

	void Draw()
	{
		DrawCircleGradient(x, y, r , BLACK, WHITE);
	}

	void Update()
	{
		x += speed_x;
		y += speed_y;

		if (x + r >= 1094 || x - r <= 103)
		{
			speed_x *= -1;
		}

		if (y + r >= 544 || y - r <= 202)
		{
			speed_y *= -1;
		}
	}
};

BackBall backball;

class Paddle
{
public:
	float x, y;
	float w, l;
	int speed;

	void Draw()
	{
		DrawRectangleRoundedLines(Rectangle{x, y, w, l}, 7, 2, 2, NEONBLUE);
	}

	void Update()
	{
		if (IsKeyDown(KEY_W))
		{
			y = y - speed;
		}
		if (IsKeyDown(KEY_S))
		{
			y = y + speed;
		}

		if (y <= 1)
		{
			y = 0;
		}

		if (y + l >= screen_y)
		{
			y = screen_y - l;
		}
	}
};

Paddle paddle;

class singPaddle
{
public:
	float x, y;
	float w, l;
	int speed;

	void Draw()
	{
		DrawRectangleRoundedLines(Rectangle{x, y, w, l}, 7, 2, 2, NEONBLUE);
	}

	void Update()
	{
		if (IsKeyDown(KEY_LEFT))
		{
			x = x - speed;
		}
		if (IsKeyDown(KEY_RIGHT))
		{
			x = x + speed;
		}

		if (x <= 1)
		{
			x = 0;
		}

		if (x + w >= singscreen_x)
		{
			x = singscreen_x - w;
		}
	}
};

singPaddle singpaddle;

class Paddle2
{
public:
	float x, y;
	float w, l;
	int speed;

	void Draw()
	{
		DrawRectangleRoundedLines(Rectangle{x, y, w, l}, 7, 2, 2, NEONBLUE);
	}

	void Update()
	{
		if (IsKeyDown(KEY_UP))
		{
			y = y - speed;
		}
		if (IsKeyDown(KEY_DOWN))
		{
			y = y + speed;
		}

		if (y <= 1)
		{
			y = 0;
		}

		if (y + l >= screen_y)
		{
			y = screen_y - l;
		}
	}
};

Paddle2 paddle2;

class AI
{
public:
	float x, y;
	float w, l;
	float speed;

	void Draw()
	{
		DrawRectangleRoundedLines(Rectangle{x, y, w, l}, 7, 2, 2, NEONBLUE);
	}

	void Update(int y_ball)
	{
		if (y + l / 2 > y_ball)
		{
			y = y - speed;
		}
		if (y + l / 2 < y_ball)
		{
			y = y + speed;
		}

		if (y <= 1)
		{
			y = 0;
		}

		if (y + l >= screen_y)
		{
			y = screen_y - l;
		}
	}
};

AI ai;

class Gamename
{
public:
	float x, y;
	float w, l;

	void Draw(Font t)
	{
		DrawTextEx(t, "NEON BOUNCE", Vector2{362, 68}, 70, 5, NEONBLUE);
	}
};

Gamename gamename;

class AIbut
{
public:
	float x, y;
	float w, l;

	void Draw()
	{
		DrawRectangle(x, y, w, l, TRANS);
	}

	void Glow(int i, Color glow)
	{
		DrawRectangleLinesEx(Rectangle{x - i * 5, y - i * 5, w + i * 10, l + i * 10},i*2, glow);
	}

	void Text(Font s)
	{
		DrawTextEx(s, "Player VS AI", Vector2{screen_x / 2 - 420, screen_y / 2 + 9}, 35, 3, NEONPINK);
	}
};

AIbut aibut;

class Singlebut
{
public:
	float x, y;
	float w, l;

	void Draw()
	{
		DrawRectangle(x, y, w, l, TRANS);
	}

	void Glow(int i, Color glow)
	{
		DrawRectangleLinesEx(Rectangle{x - i * 5, y - i * 5, w + i * 10, l + i * 10},i*2, glow);
	}

	void Text(Font s)
	{
		DrawTextEx(s, "Single Player", Vector2{screen_x / 2 + 123, screen_y / 2 + 9}, 35, 3, NEONYELLOW);
	}
};

Singlebut singlebut;

class Multibut
{
public:
	float x, y;
	float w, l;

	void Draw()
	{
		DrawRectangle(x, y, w, l, TRANS);
	}

	void Glow(int i, Color glow)
	{
		DrawRectangleLinesEx(Rectangle{x - i * 5, y - i * 5, w + i * 10, l + i * 10},i*2, glow);
	}

	void Text(Font s)
	{
		DrawTextEx(s, "Multiplayer", Vector2{screen_x / 2 - 148, screen_y / 2 + 160}, 35, 3, NEONRED);
	}
};

Multibut multibut;

class Difficulty
{
public:
	float x, y;
	float w, l;

	void Draw(Font s)
	{
		DrawTextEx(s, "Difficulty", Vector2{400, 65}, 70, 5, NEONPURPLE);
	}
};

Difficulty diff;

class Easybut
{
public:
	float x, y;
	float w, l;

	void Draw()
	{
		DrawRectangle(x, y, w, l, TRANS);
	}

	void Glow(int i, Color glow)
	{
		DrawRectangleLinesEx(Rectangle{x - i * 5, y - i * 5, w + i * 10, l + i * 10},i*2, glow);
	}

	void Text(Font s)
	{
		DrawTextEx(s, "Easy", Vector2{screen_x / 2 - 320, screen_y / 2 + 9}, 35, 3, NEONGREEN);
	}
};

Easybut easybut;

class Mediumbut
{
public:
	float x, y;
	float w, l;

	void Draw()
	{
		DrawRectangle(x, y, w, l, TRANS);
	}

	void Glow(int i, Color glow)
	{
		DrawRectangleLinesEx(Rectangle{x - i * 5, y - i * 5, w + i * 10, l + i * 10},i*2, glow);
	}

	void Text(Font s)
	{
		DrawTextEx(s, "Medium", Vector2{screen_x / 2 + 180, screen_y / 2 + 9}, 35, 3, NEONORANGE);
	}
};

Mediumbut medbut;

class Hardbut
{
public:
	float x, y;
	float w, l;

	void Draw()
	{
		DrawRectangle(x, y, w, l, TRANS);
	}

	void Glow(int i, Color glow)
	{
		DrawRectangleLinesEx(Rectangle{x - i * 5, y - i * 5, w + i * 10, l + i * 10},i*2, glow);
	}

	void Text(Font s)
	{
		DrawTextEx(s, "Hard", Vector2{screen_x / 2 - 55, screen_y / 2 + 160}, 35, 3, NEONRED);
	}
};

Hardbut hardbut;

class Best
{
public:
	float x, y;
	float w, l;

	void Draw(Font s)
	{
		DrawTextEx(s, "First to score", Vector2{370, 68}, 60, 3, NEONGREEN);
	}
};

Best best;

class Fivebut
{
public:
	float x, y;
	float w, l;

	void Draw()
	{
		DrawRectangle(x, y, w, l, TRANS);
	}

	void Glow(int i, Color glow)
	{
		DrawRectangleLinesEx(Rectangle{x - i * 5, y - i * 5, w + i * 10, l + i * 10},i*2, glow);
	}

	void Text(Font s)
	{
		DrawTextEx(s, "First to 5", Vector2{screen_x / 2 - 410, screen_y / 2 + 9}, 35, 3, NEONPURPLE);
	}
};

Fivebut fivebut;

class Tenbut
{
public:
	float x, y;
	float w, l;

	void Draw()
	{
		DrawRectangle(x, y, w, l, TRANS);
	}

	void Glow(int i, Color glow)
	{
		DrawRectangleLinesEx(Rectangle{x - i * 5, y - i * 5, w + i * 10, l + i * 10},i*2, glow);
	}

	void Text(Font s)
	{
		DrawTextEx(s, "First to 10", Vector2{screen_x / 2 + 150, screen_y / 2 + 9}, 35, 3, NEONYELLOW);
	}
};

Tenbut tenbut;

class Fifteenbut
{
public:
	float x, y;
	float w, l;

	void Draw()
	{
		DrawRectangle(x, y, w, l, TRANS);
	}

	void Glow(int i, Color glow)
	{
		DrawRectangleLinesEx(Rectangle{x - i * 5, y - i * 5, w + i * 10, l + i * 10},i*2, glow);
	}

	void Text(Font s)
	{
		DrawTextEx(s, "First to 15", Vector2{screen_x / 2 - 125, screen_y / 2 + 160}, 35, 3, NEONPINK);
	}
};

Fifteenbut fifteenbut;

class Gamefinish
{
public:
	float x, y;
	float w, l;

	void Draw(Font s)
	{
		DrawTextEx(s, "GAME OVER!", Vector2{screen_x / 4 - 142, screen_y / 4 - 135}, 45, 3, NEONPURPLE);
	}
};

Gamefinish gamefinish;

class Exitbut
{
public:
	float x, y;
	float w, l;

	void Draw()
	{
		DrawRectangle(x, y, w, l, TRANS);
	}

	void Glow(int i, Color glow)
	{
		DrawRectangleLinesEx(Rectangle{x - i * 5, y - i * 5, w + i * 10, l + i * 10},i*2, glow);
	}

	void Text(Font s)
	{
		DrawTextEx(s, "Exit", Vector2{screen_x / 4 - 40, screen_y / 4 + 74}, 25, 3, NEONRED);
	}
};

Exitbut exitbut;

class Replaybut
{
public:
	float x, y;
	float w, l;

	void Draw()
	{
		DrawRectangle(x, y, w, l, TRANS);
	}

	void Glow(int i, Color glow)
	{
		DrawRectangleLinesEx(Rectangle{x - i * 5, y - i * 5, w + i * 10, l + i * 10},i*2, glow);
	}

	void Text(Font s)
	{
		DrawTextEx(s, "Replay", Vector2{screen_x / 4 - 51, screen_y / 4 + 2}, 25, 3, NEONBLUE);
	}
};

Replaybut replaybut;

void difficulty()
{
	// Making Window

	InitWindow(screen_x, screen_y, "Difficulty Selection");
	InitAudioDevice();
	SetTargetFPS(60);

	Font title = LoadFont("SamuraiBlast.ttf");

	Sound button = LoadSound("butound.WAV");
	SetSoundVolume(button, 0.5f);
	Texture back2 = LoadTexture("back.png");

	// Initializing for Easy button

	easybut.x = screen_x / 2 - 350;
	easybut.y = screen_y / 2 - 3;
	easybut.w = 150;
	easybut.l = 60;

	// Initializing for Medium button

	medbut.x = screen_x / 2 + 148;
	medbut.y = screen_y / 2 - 3;
	medbut.w = 200;
	medbut.l = 60;

	// Initializing for Hard button

	hardbut.x = screen_x / 2 - 100;
	hardbut.y = screen_y / 2 + 150;
	hardbut.w = 180;
	hardbut.l = 60;

	// Main menu loop

	while (WindowShouldClose() == false)
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexture(back2, 0, 0, NEONWHITE);

		backball.Draw();

		backball.Update();

		diff.Draw(title);

		easybut.Draw();

		easybut.Text(title);

		medbut.Draw();

		medbut.Text(title);

		hardbut.Draw();

		hardbut.Text(title);

		bool MouseOverEasyButton = CheckCollisionPointRec(GetMousePosition(), Rectangle{easybut.x, easybut.y, easybut.w, easybut.l});

		if(MouseOverEasyButton)
		{
			BeginBlendMode(BLEND_ADDITIVE);
			for(int i=0;i<=2;i++)
			{
				Color glow=(Color){(unsigned char)255,(unsigned char)255,(unsigned char)255,(unsigned char)(100 - i * 8)};
				easybut.Glow(i,glow);
			}
		}

		if (MouseOverEasyButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			PlaySound(button);
			CloseAudioDevice();
			aiplayereasy();
		}

		bool MouseOverMedButton = CheckCollisionPointRec(GetMousePosition(), Rectangle{medbut.x, medbut.y, medbut.w, medbut.l});

		if(MouseOverMedButton)
		{
			BeginBlendMode(BLEND_ADDITIVE);
			for(int i=0;i<=2;i++)
			{
				Color glow=(Color){(unsigned char)255,(unsigned char)255,(unsigned char)255,(unsigned char)(100 - i * 8)};
				medbut.Glow(i,glow);
			}
		}

		if (MouseOverMedButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			PlaySound(button);
			CloseAudioDevice();
			aiplayermed();
		}

		bool MouseOverHardButton = CheckCollisionPointRec(GetMousePosition(), Rectangle{hardbut.x, hardbut.y, hardbut.w, hardbut.l});

		if(MouseOverHardButton)
		{
			BeginBlendMode(BLEND_ADDITIVE);
			for(int i=0;i<=2;i++)
			{
				Color glow=(Color){(unsigned char)255,(unsigned char)255,(unsigned char)255,(unsigned char)(100 - i * 8)};
				hardbut.Glow(i,glow);
			}
		}

		if (MouseOverHardButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			PlaySound(button);
			CloseAudioDevice();
			aiplayerhard();
		}

		EndDrawing();
	}
	UnloadTexture(back2);
	UnloadSound(button);
	UnloadFont(title);

	CloseAudioDevice();
	CloseWindow();
	main();
}

void firsttomulti()
{
	// Making Window

	InitWindow(screen_x, screen_y, "First To ");
	InitAudioDevice();
	SetTargetFPS(60);

	Font title = LoadFont("SamuraiBlast.ttf");

	Sound button = LoadSound("butound.WAV");
	SetSoundVolume(button, 0.5f);
	Texture back2 = LoadTexture("back.png");

	score_ai = 0;
	score_player1 = 0;
	score_player2 = 0;

	// Initializing for Easy button

	fivebut.x = screen_x / 2 - 425;
	fivebut.y = screen_y / 2 - 3;
	fivebut.w = 230;
	fivebut.l = 60;

	// Initializing for Medium button

	tenbut.x = screen_x / 2 + 135;
	tenbut.y = screen_y / 2 - 3;
	tenbut.w = 250;
	tenbut.l = 60;

	// Initializing for Hard button

	fifteenbut.x = screen_x / 2 - 140;
	fifteenbut.y = screen_y / 2 + 150;
	fifteenbut.w = 250;
	fifteenbut.l = 60;

	// Main menu loop

	while (WindowShouldClose() == false)
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexture(back2, 0, 0, NEONWHITE);

		backball.Draw();

		backball.Update();

		best.Draw(title);

		fivebut.Draw();

		fivebut.Text(title);

		tenbut.Draw();

		tenbut.Text(title);

		fifteenbut.Draw();

		fifteenbut.Text(title);

		bool MouseOverfiveButton = CheckCollisionPointRec(GetMousePosition(), Rectangle{fivebut.x, fivebut.y, fivebut.w, fivebut.l});

		if(MouseOverfiveButton)
		{
			BeginBlendMode(BLEND_ADDITIVE);
			for(int i=0;i<=2;i++)
			{
				Color glow=(Color){(unsigned char)255,(unsigned char)255,(unsigned char)255,(unsigned char)(100 - i * 8)};
				fivebut.Glow(i,glow);
			}
		}

		if (MouseOverfiveButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			five5 = true;
			ten10 = false;
			fifteen15 = false;
			PlaySound(button);
			CloseAudioDevice();
			multi();
		}

		bool MouseOvertenButton = CheckCollisionPointRec(GetMousePosition(), Rectangle{tenbut.x, tenbut.y, tenbut.w, tenbut.l});

		if(MouseOvertenButton)
		{
			BeginBlendMode(BLEND_ADDITIVE);
			for(int i=0;i<=2;i++)
			{
				Color glow=(Color){(unsigned char)255,(unsigned char)255,(unsigned char)255,(unsigned char)(100 - i * 8)};
				tenbut.Glow(i,glow);
			}
		}

		if (MouseOvertenButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			five5 = false;
			ten10 = true;
			fifteen15 = false;
			PlaySound(button);
			CloseAudioDevice();
			multi();
		}

		bool MouseOverfifteenButton = CheckCollisionPointRec(GetMousePosition(), Rectangle{fifteenbut.x, fifteenbut.y, fifteenbut.w, fifteenbut.l});

		if(MouseOverfifteenButton)
		{
			BeginBlendMode(BLEND_ADDITIVE);
			for(int i=0;i<=2;i++)
			{
				Color glow=(Color){(unsigned char)255,(unsigned char)255,(unsigned char)255,(unsigned char)(100 - i * 8)};
				fifteenbut.Glow(i,glow);
			}
		}

		if (MouseOverfifteenButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			five5 = false;
			ten10 = false;
			fifteen15 = true;
			PlaySound(button);
			CloseAudioDevice();
			multi();
		}

		EndDrawing();
	}
	UnloadTexture(back2);
	UnloadSound(button);
	UnloadFont(title);

	CloseAudioDevice();
	CloseWindow();
	main();
}

void Gameover()
{
	// Making Window

	InitWindow(screen_x / 2, screen_y / 2, "Game Over");
	InitAudioDevice();
	SetTargetFPS(60);

	Font title = LoadFont("SamuraiBlast.ttf");
	Texture back = LoadTexture("back2.png");

	// Initializing for Replay button

	replaybut.x = screen_x / 4 - 55;
	replaybut.y = screen_y / 4;
	replaybut.w = 100;
	replaybut.l = 30;

	// Initializing for Exit button

	exitbut.x = screen_x / 4 - 55;
	exitbut.y = screen_y / 4 + 70;
	exitbut.w = 100;
	exitbut.l = 30;

	//Highest Score

	int maxscore = 0;
	int count = 0;
	int a[10000];
	ifstream RScore("Score.txt");
	while(RScore >> a[count])
	{
		if(a[count]>maxscore)
		{
			maxscore=a[count];
		}
	}
	RScore.close();

	// Main menu loop

	while (WindowShouldClose() == false)
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexture(back,0,0,WHITE);

		gamefinish.Draw(title);

		replaybut.Draw();

		replaybut.Text(title);

		exitbut.Draw();

		exitbut.Text(title);

		DrawTextEx(title,"Your Score",Vector2{ 20, screen_y / 4 - 40}, 35,1, NEONYELLOW);

		DrawTextEx(title,TextFormat("%i",score_player1),Vector2{95,screen_y / 4}, 40,2,NEONORANGE);

		DrawTextEx(title,"Highest Score",Vector2{ screen_x/4 + 60, screen_y / 4 - 40}, 30,1, NEONGREEN);

		DrawTextEx(title,TextFormat("%i",maxscore),Vector2{screen_x/4 + 160,screen_y / 4}, 40,2,NEONPINK);

		bool MouseOverReplayButton = CheckCollisionPointRec(GetMousePosition(), Rectangle{replaybut.x, replaybut.y, replaybut.w, replaybut.l});

		if(MouseOverReplayButton)
		{
			BeginBlendMode(BLEND_ADDITIVE);
			for(int i=0;i<=2;i++)
			{
				Color glow=(Color){(unsigned char)255,(unsigned char)255,(unsigned char)255,(unsigned char)(100 - i * 8)};
				replaybut.Glow(i,glow);
			}
		}

		if (MouseOverReplayButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			CloseAudioDevice();
			single();
		}

		bool MouseOverExitButton = CheckCollisionPointRec(GetMousePosition(), Rectangle{exitbut.x, exitbut.y, exitbut.w, exitbut.l});

		if(MouseOverExitButton)
		{
			BeginBlendMode(BLEND_ADDITIVE);
			for(int i=0;i<=2;i++)
			{
				Color glow=(Color){(unsigned char)255,(unsigned char)255,(unsigned char)255,(unsigned char)(100 - i * 8)};
				exitbut.Glow(i,glow);
			}
		}

		if (MouseOverExitButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			CloseWindow();
			main();
		}

		EndDrawing();
	}
	UnloadFont(title);
	UnloadTexture(back);
	CloseAudioDevice();
	CloseWindow();
}

void Gamewin()
{
	// Making Window

	InitWindow(screen_x / 2, screen_y / 2, "Game Won");
	InitAudioDevice();
	SetTargetFPS(60);

	Font title = LoadFont("SamuraiBlast.ttf");
	Texture back = LoadTexture("back2.png");

	// Initializing for Replay button

	replaybut.x = screen_x / 4 - 55;
	replaybut.y = screen_y / 4;
	replaybut.w = 100;
	replaybut.l = 30;

	// Initializing for Exit button

	exitbut.x = screen_x / 4 - 55;
	exitbut.y = screen_y / 4 + 70;
	exitbut.w = 100;
	exitbut.l = 30;

	// Main menu loop

	while (WindowShouldClose() == false)
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexture(back,0,0,WHITE);

		replaybut.Draw();

		replaybut.Text(title);

		exitbut.Draw();

		exitbut.Text(title);

		if (score_player1 > score_player2)
		{
			DrawTextEx(title,"PLAYER 1 WON",Vector2 { screen_x / 4 - 82, screen_y / 4 - 105}, 25,2, NEONWHITE);
		}

		else if (score_player2 > score_player1)
		{
			DrawTextEx(title,"PLAYER 2 WON",Vector2 { screen_x / 4 - 82, screen_y / 4 - 105}, 25,2, NEONWHITE);
		}

		bool MouseOverReplayButton = CheckCollisionPointRec(GetMousePosition(), Rectangle{replaybut.x, replaybut.y, replaybut.w, replaybut.l});

		if(MouseOverReplayButton)
		{
			BeginBlendMode(BLEND_ADDITIVE);
			for(int i=0;i<=2;i++)
			{
				Color glow=(Color){(unsigned char)255,(unsigned char)255,(unsigned char)255,(unsigned char)(100 - i * 8)};
				replaybut.Glow(i,glow);
			}
		}

		if (MouseOverReplayButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			CloseAudioDevice();
			firsttomulti();
		}

		bool MouseOverExitButton = CheckCollisionPointRec(GetMousePosition(), Rectangle{exitbut.x, exitbut.y, exitbut.w, exitbut.l});

		if(MouseOverExitButton)
		{
			BeginBlendMode(BLEND_ADDITIVE);
			for(int i=0;i<=2;i++)
			{
				Color glow=(Color){(unsigned char)255,(unsigned char)255,(unsigned char)255,(unsigned char)(100 - i * 8)};
				exitbut.Glow(i,glow);
			}
		}

		if (MouseOverExitButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			CloseWindow();
			main();
		}

		EndDrawing();
	}
	UnloadFont(title);
	UnloadTexture(back);
	CloseAudioDevice();
	CloseWindow();
}

void aiplayereasy()
{
	score_ai = 0;
	score_player1 = 0;
	score_player2 = 0;
	
	// Initializing for ball

	ball.x = screen_x / 2;
	ball.y = screen_y / 2;
	ball.r = 10;
	ball.speed_x = 6;
	ball.speed_y = 6;

	// Initializing for paddle

	paddle.l = 100;
	paddle.w = 20;
	paddle.x = 8;
	paddle.y = (screen_y / 2) - (paddle.l / 2);
	paddle.speed = 8;

	// Initializing for AI paddle

	ai.l = 100;
	ai.w = 20;
	ai.x = screen_x - (ai.w + 8);
	ai.y = (screen_y / 2) - (ai.l / 2);
	ai.speed = 4;

	// Making Window

	InitWindow(screen_x, screeny, "Player vs AI");
	InitAudioDevice();
	SetTargetFPS(60);

	Font title = LoadFont("SamuraiBlast.ttf");

	Sound ping = LoadSound("sound_1.WAV");
	Sound ping2 = LoadSound("sound_2.WAV");
	Sound s_udwall = LoadSound("walls.WAV");

	SetSoundVolume(ping, 0.1f);
	SetSoundVolume(ping2, 0.1f);
	SetSoundVolume(s_udwall, 0.1f);

	// Game Loop

	while (WindowShouldClose() == false)
	{

		BeginDrawing();

		// Drawing

		ClearBackground(BLACK);

		DrawCircleLines(screen_x / 2, screen_y / 2, 200, NEONPURPLE);

		DrawRectangleLines(0, 100, 100, 400, NEONORANGE);

		DrawRectangleLines(screen_x - 100, 100, 100, 400, NEONORANGE);

		DrawLine(1, 0, 1, screen_y, NEONWHITE);

		DrawLine(0, 1, screen_x, 1, NEONWHITE);

		DrawLine(screen_x - 1, 0, screen_x - 1, screen_y, NEONWHITE);

		DrawLineEx(Vector2{screen_x / 2, 0}, Vector2{screen_x / 2, screen_y}, 3, NEONGREEN);

		DrawTextEx(title,TextFormat("%i", score_ai),Vector2{ screen_x / 4 - 20, screen_y + 20}, 80,2, NEONRED);

		DrawLine(0, screen_y, screen_x, screen_y, NEONWHITE);

		DrawTextEx(title,TextFormat("%i", score_player2), Vector2 {screen_x - screen_x / 4, screen_y + 20}, 80,2, NEONRED);

		ball.Draw();

		paddle.Draw();

		ai.Draw();

		// Updating

		paddle.Update();

		ball.Update(s_udwall);

		ai.Update(ball.y);

		// Checking Collision

		if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.r, Rectangle{paddle.x, paddle.y, paddle.w, paddle.l}))
		{
			PlaySound(ping);
			ball.speed_x *= -1;
		}

		if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.r, Rectangle{ai.x, ai.y, ai.w, ai.l}))
		{
			PlaySound(ping2);
			ball.speed_x *= -1;
		}

		EndDrawing();
	}
	UnloadSound(ping);
	UnloadSound(ping2);
	UnloadSound(s_udwall);
	UnloadFont(title);

	CloseAudioDevice();
	CloseWindow();
	difficulty();
}

void aiplayermed()
{
	score_ai = 0;
	score_player1 = 0;
	score_player2 = 0;

	// Initializing for ball

	ball.x = screen_x / 2;
	ball.y = screen_y / 2;
	ball.r = 10;
	ball.speed_x = 6;
	ball.speed_y = 6;

	// Initializing for paddle

	paddle.l = 80;
	paddle.w = 20;
	paddle.x = 8;
	paddle.y = (screen_y / 2) - (paddle.l / 2);
	paddle.speed = 8;

	// Initializing for AI paddle

	ai.l = 80;
	ai.w = 20;
	ai.x = screen_x - (ai.w + 8);
	ai.y = (screen_y / 2) - (ai.l / 2);
	ai.speed = 6;

	// Making Window

	InitWindow(screen_x, screeny, "Player vs AI");
	InitAudioDevice();
	SetTargetFPS(90);

	Font title = LoadFont("SamuraiBlast.ttf");

	Sound ping = LoadSound("sound_1.WAV");
	Sound ping2 = LoadSound("sound_2.WAV");
	Sound s_udwall = LoadSound("walls.WAV");

	SetSoundVolume(ping, 0.1f);
	SetSoundVolume(ping2, 0.1f);
	SetSoundVolume(s_udwall, 0.1f);

	// Game Loop

	while (WindowShouldClose() == false)
	{

		BeginDrawing();

		// Drawing

		ClearBackground(BLACK);

		DrawCircleLines(screen_x / 2, screen_y / 2, 200, NEONPURPLE);

		DrawRectangleLines(0, 100, 100, 400, NEONORANGE);

		DrawRectangleLines(screen_x - 100, 100, 100, 400, NEONORANGE);

		DrawLine(1, 0, 1, screen_y, NEONWHITE);

		DrawLine(0, 1, screen_x, 1, NEONWHITE);

		DrawLine(screen_x - 1, 0, screen_x - 1, screen_y, NEONWHITE);

		DrawLineEx(Vector2{screen_x / 2, 0}, Vector2{screen_x / 2, screen_y}, 3, NEONGREEN);

		DrawLine(0, screen_y, screen_x, screen_y, NEONWHITE);

		DrawTextEx(title,TextFormat("%i", score_ai),Vector2 {screen_x / 4 - 20, screen_y + 20}, 80,2, NEONRED);

		DrawTextEx(title,TextFormat("%i", score_player2), Vector2 {screen_x - screen_x / 4, screen_y + 20}, 80,2, NEONRED);

		ball.Draw();

		paddle.Draw();

		ai.Draw();

		// Updating

		paddle.Update();

		ball.Update(s_udwall);

		ai.Update(ball.y);

		// Checking Collision

		if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.r, Rectangle{paddle.x, paddle.y, paddle.w, paddle.l}))
		{
			PlaySound(ping);
			ball.speed_x *= -1;
		}

		if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.r, Rectangle{ai.x, ai.y, ai.w, ai.l}))
		{
			PlaySound(ping2);
			ball.speed_x *= -1;
		}

		EndDrawing();
	}
	UnloadSound(ping);
	UnloadSound(ping2);
	UnloadSound(s_udwall);
	UnloadFont(title);

	CloseAudioDevice();
	CloseWindow();
	difficulty();
}

void aiplayerhard()
{
	score_ai = 0;
	score_player1 = 0;
	score_player2 = 0;

	// Initializing for ball

	ball.x = screen_x / 2;
	ball.y = screen_y / 2;
	ball.r = 10;
	ball.speed_x = 6;
	ball.speed_y = 6;

	// Initializing for paddle

	paddle.l = 60;
	paddle.w = 20;
	paddle.x = 8;
	paddle.y = (screen_y / 2) - (paddle.l / 2);
	paddle.speed = 8;

	// Initializing for AI paddle

	ai.l = 60;
	ai.w = 20;
	ai.x = screen_x - (ai.w + 8);
	ai.y = (screen_y / 2) - (ai.l / 2);
	ai.speed = 8;

	// Making Window

	InitWindow(screen_x, screeny, "Player vs AI");
	InitAudioDevice();
	SetTargetFPS(120);

	Font title = LoadFont("SamuraiBlast.ttf");

	Sound ping = LoadSound("sound_1.WAV");
	Sound ping2 = LoadSound("sound_2.WAV");
	Sound s_udwall = LoadSound("walls.WAV");

	SetSoundVolume(ping, 0.1f);
	SetSoundVolume(ping2, 0.1f);
	SetSoundVolume(s_udwall, 0.1f);

	// Game Loop

	while (WindowShouldClose() == false)
	{

		BeginDrawing();

		// Drawing

		ClearBackground(BLACK);

		DrawCircleLines(screen_x / 2, screen_y / 2, 200, NEONPURPLE);

		DrawRectangleLines(0, 100, 100, 400, NEONORANGE);

		DrawRectangleLines(screen_x - 100, 100, 100, 400, NEONORANGE);

		DrawLine(1, 0, 1, screen_y, NEONWHITE);

		DrawLine(0, 1, screen_x, 1, NEONWHITE);

		DrawLine(screen_x - 1, 0, screen_x - 1, screen_y, NEONWHITE);

		DrawLineEx(Vector2{screen_x / 2, 0}, Vector2{screen_x / 2, screen_y}, 3, NEONGREEN);

		DrawLine(0, screen_y, screen_x, screen_y, NEONWHITE);

		DrawTextEx(title,TextFormat("%i", score_ai), Vector2 {screen_x / 4 - 20, screen_y + 20}, 80,2, NEONRED);

		DrawTextEx(title,TextFormat("%i", score_player2), Vector2 {screen_x - screen_x / 4, screen_y + 20}, 80,2, NEONRED);

		ball.Draw();

		paddle.Draw();

		ai.Draw();

		// Updating

		paddle.Update();

		ball.Update(s_udwall);

		ai.Update(ball.y);

		// Checking Collision

		if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.r, Rectangle{paddle.x, paddle.y, paddle.w, paddle.l}))
		{
			PlaySound(ping);
			ball.speed_x *= -1;
		}

		if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.r, Rectangle{ai.x, ai.y, ai.w, ai.l}))
		{
			PlaySound(ping2);
			ball.speed_x *= -1;
		}

		EndDrawing();
	}
	UnloadSound(ping);
	UnloadSound(ping2);
	UnloadSound(s_udwall);
	UnloadFont(title);

	CloseAudioDevice();
	CloseWindow();
	difficulty();
}

void single()
{
	score_ai = 0;
	score_player1 = 0;
	score_player2 = 0;

	// Initializing for ball

	singball.x = singscreen_x / 2;
	singball.y = singscreen_y/2 - 200;
	singball.r = 15;
	singball.speed_x = 6;
	singball.speed_y = 6;

	// Initializing for paddle

	singpaddle.w = 100;
	singpaddle.l = 20;
	singpaddle.y = singscreen_y - 24;
	singpaddle.x = (singscreen_x / 2) - (singpaddle.w / 2);
	singpaddle.speed = 8;

	score_ai = 0;
	score_player1 = 0;
	score_player2 = 0;

	// Making Window

	InitWindow(singscreen_x, singscreeny, "Single Player");
	InitAudioDevice();
	SetTargetFPS(60);

	Font title = LoadFont("SamuraiBlast.ttf");

	Sound ping = LoadSound("sound_1.WAV");
	Sound ping2 = LoadSound("sound_2.WAV");
	Sound s_udwall = LoadSound("walls.WAV");
	Sound lose = LoadSound("Gameover.WAV");

	SetSoundVolume(lose, 0.5f);
	SetSoundVolume(ping, 0.1f);
	SetSoundVolume(ping2, 0.1f);
	SetSoundVolume(s_udwall, 0.1f);

	// Game Loop

	while (WindowShouldClose() == false)
	{
		BeginDrawing();

		// Drawing

		ClearBackground(BLACK);

		DrawCircleLines(singscreen_x / 2, singscreen_y / 2, 200, NEONPURPLE);

		DrawRectangleLines(singscreen_x/2 - 195, singscreen_y - 100, 400, 100, NEONORANGE);

		DrawLine(1, 1, 1, singscreen_y, NEONWHITE);

		DrawLine(1, 1, singscreen_x - 1, 1, NEONWHITE);

		DrawLine(singscreen_x - 1, 1, singscreen_x - 1, singscreen_y, NEONWHITE);

		DrawLineEx(Vector2{1, singscreen_y/2}, Vector2{singscreen_x, singscreen_y/2}, 3, NEONGREEN);

		DrawLine(0, singscreen_y, singscreen_x, singscreen_y, NEONWHITE);

		DrawTextEx(title,TextFormat("%i", score_player1), Vector2 {singscreen_x / 2 - 20, singscreen_y + 20}, 80,2, NEONRED);

		singpaddle.Draw();

		singball.Draw();

		// Updating

		singpaddle.Update();

		singball.Update(s_udwall, lose);

		singball.speed();

		// Checking Collision

		if (CheckCollisionCircleRec(Vector2{singball.x, singball.y}, singball.r, Rectangle{singpaddle.x, singpaddle.y, singpaddle.w, singpaddle.l}))
		{
			PlaySound(ping);
			singball.speed_y *= -1;
		}

		EndDrawing();
	}
	UnloadSound(ping);
	UnloadSound(ping2);
	UnloadSound(s_udwall);
	UnloadSound(lose);
	UnloadFont(title);

	CloseAudioDevice();
	CloseWindow();
	main();
}

void multi()
{
	score_ai = 0;
	score_player1 = 0;
	score_player2 = 0;

	// Initializing for ball

	ball.x = screen_x / 2;
	ball.y = screen_y / 2;
	ball.r = 10;
	ball.speed_x = 7;
	ball.speed_y = 7;

	// Initializing for paddle

	paddle.l = 80;
	paddle.w = 20;
	paddle.x = 8;
	paddle.y = (screen_y / 2) - (paddle.l / 2);
	paddle.speed = 7;

	// Initializing for paddle player

	paddle2.l = 80;
	paddle2.w = 20;
	paddle2.x = screen_x - (paddle2.w + 8);
	paddle2.y = (screen_y / 2) - (paddle.l / 2);
	paddle2.speed = 7;

	// Making Window

	InitWindow(screen_x, screeny, "Multiplayer");
	InitAudioDevice();
	SetTargetFPS(60);

	Font title = LoadFont("SamuraiBlast.ttf");

	Sound ping = LoadSound("sound_1.WAV");
	Sound ping2 = LoadSound("sound_2.WAV");
	Sound s_udwall = LoadSound("walls.WAV");
	Sound win = LoadSound("wingame.WAV");

	SetSoundVolume(ping, 0.1f);
	SetSoundVolume(ping2, 0.1f);
	SetSoundVolume(s_udwall, 0.1f);
	SetSoundVolume(win, 0.1f);

	// Game Loop

	while (WindowShouldClose() == false)
	{
		BeginDrawing();

		// Drawing

		ClearBackground(BLACK);

		DrawRectangleLines(0, 100, 100, 400, NEONORANGE);

		DrawRectangleLines(screen_x - 100, 100, 100, 400, NEONORANGE);

		DrawCircleLines(screen_x / 2, screen_y / 2, 200, NEONPURPLE);

		DrawLine(1, 0, 1, screen_y, NEONWHITE);

		DrawLine(0, 1, screen_x, 1, NEONWHITE);

		DrawLine(screen_x - 1, 0, screen_x - 1, screen_y, NEONWHITE);

		DrawLineEx(Vector2{screen_x / 2, 0}, Vector2{screen_x / 2, screen_y}, 3, NEONGREEN);

		DrawLine(0, screen_y, screen_x, screen_y, NEONWHITE);

		DrawTextEx(title,TextFormat("%i", score_player1),Vector2 { screen_x / 4 - 20, screen_y + 20}, 80,2, NEONRED);

		DrawTextEx(title,TextFormat("%i", score_player2), Vector2 {screen_x - screen_x / 4, screen_y + 20}, 80,2, NEONRED);

		ball.Draw();

		paddle.Draw();

		paddle2.Draw();

		// Updating

		paddle.Update();

		ball.Update(s_udwall);

		paddle2.Update();

		// Checking Collision

		if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.r, Rectangle{paddle.x, paddle.y, paddle.w, paddle.l}))
		{
			PlaySound(ping);
			ball.speed_x *= -1;
		}

		if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.r, Rectangle{paddle2.x, paddle2.y, paddle2.w, paddle2.l}))
		{
			PlaySound(ping2);
			ball.speed_x *= -1;
		}
		if (five5 == true && ten10 == false && fifteen15 == false) // for five
		{		
			if (score_player1 == 6 || score_player2 == 6)
			{
				PlaySound(win);
				CloseAudioDevice();
				Gamewin();
			}
		}
		else if (five5 == false && ten10 == true && fifteen15 == false) // for ten
		{
			if (score_player1 == 11 || score_player2 == 11)
			{
				PlaySound(win);
				CloseAudioDevice();
				Gamewin();
			}
		}

		else if (five5 == false && ten10 == false && fifteen15 == true) // for fifteen
		{
			if (score_player1 == 16 || score_player2 == 16)
			{
				PlaySound(win);
				CloseAudioDevice();
				Gamewin();
			}
		}

		EndDrawing();
	}
	UnloadSound(ping);
	UnloadSound(ping2);
	UnloadSound(s_udwall);
	UnloadFont(title);

	CloseAudioDevice();
	CloseWindow();
	main();
}

int main()
{
	// Making Window

	InitWindow(screen_x, screen_y, "BOING BOING BATTLE");
	InitAudioDevice();
	SetTargetFPS(60);

	score_ai = 0;
	score_player1 = 0;
	score_player2 = 0;

	Font title = LoadFont("SamuraiBlast.ttf");
	Sound button = LoadSound("butound.WAV");
	SetSoundVolume(button, 0.5f);
	Texture back = LoadTexture("Background.png");

	// Initializing for Player Vs AI button

	aibut.x = screen_x / 2 - 425;
	aibut.y = screen_y / 2 - 18;
	aibut.w = 320;
	aibut.l = 80;

	// Initializing for Single player button

	singlebut.x = screen_x / 2 + 120;
	singlebut.y = screen_y / 2 - 18; 
	singlebut.w = 345;
	singlebut.l = 80;

	// Initializing for Multiplayer button

	multibut.x = screen_x / 2 - 155;
	multibut.y = screen_y / 2 + 135;
	multibut.w = 330;
	multibut.l = 75;

	//Initialzing for Baackground effects

	backball.x=screen_x/2 - 135;
	backball.y=screen_y/2 + 150;
	backball.r=15;
	backball.speed_x=5;
	backball.speed_y=5;

	// Main menu loop

	while (WindowShouldClose() == false)
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawTexture(back, 0, 0, NEONWHITE);

		backball.Draw();

		gamename.Draw(title);

		aibut.Draw();

		aibut.Text(title);

		singlebut.Draw();

		singlebut.Text(title);

		multibut.Draw();

		multibut.Text(title);
		
		backball.Update();
		
		bool MouseOverAIButton = CheckCollisionPointRec(GetMousePosition(), Rectangle{aibut.x, aibut.y, aibut.w, aibut.l});

		if(MouseOverAIButton)
		{
			BeginBlendMode(BLEND_ADDITIVE);
			for(int i=0;i<=2;i++)
			{
				Color glow=(Color){(unsigned char)255,(unsigned char)255,(unsigned char)255,(unsigned char)(100 - i * 8)};
				aibut.Glow(i,glow);
			}
		}

		if (MouseOverAIButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			PlaySound(button);
			CloseAudioDevice();
			difficulty();
		}

		bool MouseOverSingleButton = CheckCollisionPointRec(GetMousePosition(), Rectangle{singlebut.x, singlebut.y, singlebut.w, singlebut.l});

		if(MouseOverSingleButton)
		{
			BeginBlendMode(BLEND_ADDITIVE);
			for(int i=0;i<=2;i++)
			{
				Color glow=(Color){(unsigned char)255,(unsigned char)255,(unsigned char)255,(unsigned char)(100 - i * 8)};
				singlebut.Glow(i,glow);
			}
		}

		if (MouseOverSingleButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			PlaySound(button);
			CloseAudioDevice();
			single();
			score_ai = 0;
			score_player1 = 0;
			score_player2 = 0;
		}

		bool MouseOverMultiButton = CheckCollisionPointRec(GetMousePosition(), Rectangle{multibut.x, multibut.y, multibut.w, multibut.l});

		if(MouseOverMultiButton)
		{
			BeginBlendMode(BLEND_ADDITIVE);
			for(int i=0;i<=2;i++)
			{
				Color glow=(Color){(unsigned char)255,(unsigned char)255,(unsigned char)255,(unsigned char)(100 - i * 8)};
				multibut.Glow(i,glow);
			}
		}

		if (MouseOverMultiButton && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			PlaySound(button);
			CloseAudioDevice();
			firsttomulti();
			score_ai = 0;
			score_player1 = 0;
			score_player2 = 0;
		}

		EndDrawing();
	}

	UnloadTexture(back);
	UnloadSound(button);
	UnloadFont(title);

	CloseAudioDevice();
	CloseWindow();

	return 0;
}