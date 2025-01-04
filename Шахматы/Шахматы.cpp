#include <iostream>
#include <Windows.h>
#include<conio.h>
using namespace std;

//TO DO:
//СДЕЛАТЬ МЕТОД BIT ДЛЯ ВСЕХ КЛАССОВ
//НАЧАТЬ ДЕЛАТЬ КЛАСС END И GAME


enum Colors { BLACK, DARKBLUE, DARKGREEN, DARKCYAN, DARKRED, DARKMAGENTA, DARKYELLOW, GREY, DARKGREY, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE };
enum Control {ENTER = 13, ESC = 27};

class Peshka;
__interface IFigure 
{
	virtual void Move() {}
	virtual void Bit(Peshka& figure) {}
};

class Field 
{ 
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
public:
	const int height = 8;
	const int width = 8;
	char** mass;

	Field() 
	{
		mass = new char* [height];
		for (int i = 0; i < height; i++)
			mass[i] = new char[width];
	}

	void CreateField() 
	{
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
					mass[i][j] = '#';

				if (i == 0 && j % 2 != 0 || j == 0 && i % 2 != 0 || i % 2 == 0 && j % 2 != 0 || j % 2 == 0 && i % 2 != 0)
					mass[i][j] = '#';

				else
					mass[i][j] = ' ';
			}

		}
	}

	void Print() 
	{
		COORD cursor;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				cursor.Y = i + 1;
				cursor.X = j + 1;
				SetConsoleCursorPosition(h, cursor);
				cout << mass[i][j];
			}
			cout << "\n";
		}
	}
};

class Peshka : public IFigure
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
protected:
	string name;
	COORD position;
	Field* field = nullptr;
	Colors color;
public:
	bool isAlive = true;

	Peshka(Field* field, COORD& position) 
	{
		this->field = field;
		this->position = position;
	}

	void SetColor(Colors& color) 
	{
		this->color = color;
	}

	Colors GetColor()
	{
		return color;
	}

	virtual void Move() 
	{
		if(isAlive)
		{
			bool move = true;
			int code = 0;
			int x = position.X;
			int y = position.Y;
			int prevY = 0;
			int prevX = 0;
			while (move)
			{
				prevX = position.X - 1;
				prevY = position.Y - 1;
				x = position.X - 1;
				y = position.Y - 1;
				if(color == WHITE)
				{
					if (field->mass[position.Y - 1][position.X] == ' ' || field->mass[position.Y - 1][position.X] == '#')
					{
						code = _getch();
						//cout << code << "\n";			
							//cout << code << "\n";			
						if (code == 224)
						{
							code = _getch();
							if (prevX % 2 == 0 && prevY % 2 != 0)
							{
								field->mass[prevY][prevX] = '#';
							}
							else
							{
								field->mass[prevY][prevX] = ' ';
							}
							if (code == 72) {
								if (position.Y > 1)
								{
									SetCursor(position.X, position.Y--);
									field->mass[--y][x] = 'p';
								}
							}
						}
						else if (code == ENTER && position.X != prevX && position.Y != prevY)
						{
							move = false;
						}
					}
				}
				else
				{
					if (field->mass[position.Y + 1][position.X] == ' ' || field->mass[position.Y + 1][position.X] == '#')
					{
						code = _getch();
						//cout << code << "\n";			
							//cout << code << "\n";			
						if (code == 224)
						{
							code = _getch();
							if (prevX % 2 == 0 && prevY % 2 != 0)
							{
								field->mass[prevY][prevX] = '#';
							}
							else
							{
								field->mass[prevY][prevX] = ' ';
							}
							if (code == 72) {
								if (position.Y > 1)
								{
									SetCursor(position.X, position.Y++);
									field->mass[++y][x] = 'p';
								}
							}
						}
						else if (code == ENTER && position.X != prevX && position.Y != prevY)
						{
							move = false;
						}
					}
				}
				field->Print();
				}
			}
	}

	virtual void Bit(Peshka& figure) 
	{
		if(isAlive)
		{
			int bit = true;
			int prevX = position.X;
			int prevY = position.Y;
			while (bit)
			{
				prevX = position.X - 1;
				prevY = position.Y - 1;
				int code = _getch();
				if (field->mass[position.Y - 1][position.X + 1] != ' ' || field->mass[position.Y - 1][position.X - 1] != ' ' || field->mass[position.Y - 1][position.X + 1] != '#' || field->mass[position.Y - 1][position.X - 1] != '#')
				{
					if (code == 224)
					{
						code = _getch();

						if (code == 77)
						{
							position.X++;
							position.Y--;
						}
						else if (code == 75)
						{
							position.X--;
							position.Y--;
						}
						SetCursor(position.X, position.Y);
						figure.isAlive = false;
						bit = false;
					}
				}
				field->Print();
			}
		}
	}
	

	void SetColor(Colors color) 
	{
		SetConsoleTextAttribute(h, color);
	}

	void SetCursor(int x, int y) 
	{
		COORD position;
		position.X = x;
		position.Y = y;
		SetConsoleCursorPosition(h, position);
	}
};

class Queen : public Peshka, public IFigure 
{ 
public:
	Queen(Field* field, COORD& position) : Peshka(field, position) {}

	virtual void Move() 
	{
		if(isAlive)
		{

			bool move = true;
			int x = position.X - 1;
			int y = position.Y - 1;
			int prevX = 0;
			int prevY = 0;
			while (move)
			{
				field->Print();
				prevX = position.X - 1;
				prevY = position.Y - 1;
				int code = _getch();
				//cout << code << "\n";
				if (code == 224)
				{
					code = _getch();
					
					if (code == 72)
					{
						if (position.Y > 1)
						{
							if (field->mass[y - 1][x] == ' ' || field->mass[y - 1][x] == '#')
							{
								position.Y--;	
								SetCursor(position.X, position.Y);
								field->mass[--y][x] = 'q';
							}
						}
					}

					else if (code == 77)
					{
						if (position.X < field->width)
						{
							if (field->mass[y][x + 1] == ' ' || field->mass[y][x + 1] == '#')
							{
								position.X++;							
								SetCursor(position.X, position.Y);
								field->mass[y][++x] = 'q';
							}
						}
					}

					else if (code == 75)
					{
						if (position.X > 1)
						{
							if (field->mass[y][x - 1] == ' ' || field->mass[y][x - 1] == '#')
							{
								position.X--;
								SetCursor(position.X, position.Y);
								field->mass[y][--x] = 'q';
							}
						}
					}

					else if (code == 80)
					{
						if (position.Y < field->height)
						{
							if (field->mass[y + 1][x] == ' ' || field->mass[y + 1][x] == '#')
							{
								position.Y++;
								SetCursor(position.X, position.Y);
								field->mass[++y][x] = 'q';
							}
						}
					}
				}

				else if (code == 55)
				{
					if (position.Y > 1 && position.X > 1)
					{
						if (field->mass[y - 1][x - 1] == ' ' || field->mass[y - 1][x - 1] == '#')
						{
							SetCursor(--position.X, --position.Y);
							field->mass[--y][--x] = 'q';
						}
					}						
				}

				else if (code == 49)
				{
					if (position.Y < field->height && position.X > 1)
					{
						if (field->mass[y + 1][x - 1] == ' ' || field->mass[y + 1][x - 1] == '#')
						{						
							SetCursor(--position.X, ++position.Y);
							field->mass[++y][--x] = 'q';
						}
					}
				}

				else if (code == 57)
				{
					if (position.Y > 1 && position.X < field->width)
					{
						if (field->mass[y - 1][x + 1] == ' ' || field->mass[y - 1][x + 1] == '#')
						{						
							SetCursor(++position.X, --position.Y);
							field->mass[--y][++x] = 'q';
						}
					}
				}

				else if(code == 51)
				{
					if (position.Y < field->height && position.X < field->width)
					{
						if (field->mass[y + 1][x + 1] == ' ' || field->mass[y + 1][x + 1] == '#')
						{
							SetCursor(++position.X, ++position.Y);
							field->mass[++y][++x] = 'q';
						}
					}
				}

				else if (code == ENTER && prevX != position.X && prevY != position.Y)
				{
					move = false;
				}

				if (prevY == y && prevX == x)
				{
					field->mass[prevY][prevX] = 'q';
				}
				else if (prevX % 2 == 0 && prevY % 2 == 0 || prevY == prevX || prevX % 2 != 0 && prevY % 2 != 0)
				{
					field->mass[prevY][prevX] = ' ';
				}
				else
				{
					field->mass[prevY][prevX] = '#';
				}
			}
		}
			
	}
	
	virtual void Bit(Peshka& figure) 
	{
		if(isAlive)
		{
			bool bit = true;
			while (bit)
			{

				int code = _getch();
				//cout << code << "\n";
				if (code == 224)
				{
					code = _getch();

					if (code == 72)
					{
						if (position.Y > 0)
						{
							if (field->mass[position.Y - 1][position.X] != ' ' || field->mass[position.Y - 1][position.X] != '#')
							{
								position.Y--;
								
							}
						}
					}

					else if (code == 77)
					{
						if (position.X < field->width)
						{
							if (field->mass[position.Y][position.X + 1] != ' ' || field->mass[position.Y][position.X + 1] != '#')
							{
								position.X++;
								
							}
						}
					}

					else if (code == 75)
					{
						if (position.X > 1)
						{
							if (field->mass[position.Y][position.X - 1] != ' ' || field->mass[position.Y][position.X - 1] != '#')
							{
								position.X--;
							}
						}
					}

					else if (code == 80)
					{
						if (position.Y < field->height)
						{
							if (field->mass[position.Y + 1][position.X] != ' ' || field->mass[position.Y + 1][position.X] != '#')
							{
								position.Y++;
							}
						}
					}
				}

				else if (code == 0)
				{
					code = _getch();
					//cout << _getch();
					if (code == 79)
					{
						code = _getch();
						if (code == 224)
						{
							code = _getch();
							if (code == 80)
							{
								if (position.Y < field->height && position.X > 1)
								{
									if (field->mass[position.Y + 1][position.X - 1] != ' ' || field->mass[position.Y + 1][position.X - 1] != '#')
									{
										SetCursor(--position.X, ++position.Y);
									}
								}
							}
							else if (code == 72)
							{
								if (position.Y > 1 && position.X < field->width)
								{
									if (field->mass[position.Y - 1][position.X - 1] != ' ' || field->mass[position.Y - 1][position.X - 1] != '#')
									{
										SetCursor(--position.X, --position.Y);
									}
								}
							}
						}
					}
					else if (code == 80)
					{
						code = _getch();
						if (code == 224)
						{
							code = _getch();

							if (code == 72)
							{
								if (position.X < field->width && position.Y > 1)
								{
									if (field->mass[position.Y - 1][position.X + 1] != ' ' || field->mass[position.Y - 1][position.X + 1] != '#')
									{
										SetCursor(++position.X, --position.Y);
									}
								}
							}
							else if (code == 80) 
							{
								if (position.X < field->width && position.Y < field->height)
								{
									if (field->mass[position.Y + 1][position.X + 1] != ' ' || field->mass[position.Y + 1][position.X + 1] != '#')
									{
										SetCursor(++position.X, ++position.Y);
									}
								}
							}
						}
					}
				}
				SetCursor(position.X, position.Y);
				figure.isAlive = false;
				bit = false;
				field->Print();
			}
		}
	}
	
};

class Elephant : public Peshka, public IFigure
{
public:
	Elephant(Field* field, COORD& pos) : Peshka(field, pos) {}

	virtual void Move()
	{
		if(isAlive)
		{
			int x = position.X - 1;
			int y = position.Y - 1;
			int prevX = position.X - 1;
			int prevY = position.Y - 1;
			bool move = true;
			while (move) {
				field->Print();
				prevX = position.X - 1;
				prevY = position.Y - 1;
				int code = _getch();
				
				if (code == 55)
				{
					if (position.X > 1 && position.Y > 1)
					{
						position.X--;
						position.Y--;
						field->mass[--y][--x] = 'e';
						SetCursor(position.X, position.Y);
					}
				}
				else if (code == 49)
				{
					if(position.Y < field->height && position.X > 1)
					{
						position.X--;
						position.Y++;
						field->mass[++y][--x] = 'e';
						SetCursor(position.X, position.Y);
					}
				}
				
				if (code == 57)
				{
					if (position.Y > 1 && position.X < field->width)
					{
						position.X++;
						position.Y--;
						field->mass[--y][++x] = 'e';
						SetCursor(position.X, position.Y);
					}
				}
				else if (code == 51)
				{
					if (position.Y < field->height && position.X < field->width)
					{
						position.X++;
						position.Y++;
						field->mass[++y][++x] = 'e';
						SetCursor(position.X, position.Y);
					}
				}
				
				else if (code == ENTER && prevX != position.X && prevY != position.Y)
				{
					move = false;
				}

				if (prevX == x && prevY == y)
				{
					continue;
				}

				else if (prevX % 2 == 0 && prevY % 2 == 0 || prevX == prevY || prevX % 2 != 0 && prevY % 2 != 0)
				{
					field->mass[prevY][prevX] = ' ';
				}

				else
				{
					field->mass[prevY][prevX] = '#';
				}						
			}
		}
	}

	virtual void Bit(Peshka& figure)
	{
		if(isAlive)
		{

		}
	}
};

class King : public Peshka, public IFigure
{
public:
	King(Field* field, COORD& pos) : Peshka(field, pos) {}

	virtual void Move()
	{
		if (isAlive)
		{
			int prevX = 0;
			int prevY = 0;
			bool move = true;
			int x = position.X - 1;
			int y = position.Y - 1;
			while (move) {
				field->Print();

				prevX = position.X - 1;
				prevY = position.Y - 1;
				int code = _getch();
				if (code == 224)
				{
					code = _getch();
					if (code == 72)
					{
						if(position.Y > 1)
						{
							SetCursor(position.X, --position.Y);
							field->mass[--y][x] = 'k';
						}
					}

					else if (code == 75)
					{
						if(position.X > 1)
						{
							SetCursor(--position.X, position.Y);
							field->mass[y][--x] = 'k';
						}
					}

					else if (code == 77)
					{
						if(position.X < field->width)
						{
							SetCursor(++position.X, position.Y);
							field->mass[y][++x] = 'k';
						}
					}

					else if (code == 80)
					{
						if(position.Y < field->height)
						{
							SetCursor(position.X, ++position.Y);
							field->mass[++y][x] = 'k';
						}
					}
				}

				else if (code == 55)
				{
					if(position.X > 1 && position.Y > 1)
					{
						SetCursor(--position.X, --position.Y);
						field->mass[--y][--x] = 'k';
					}
				}

				else if (code == 49)
				{
					if(position.X > 1 && position.Y < field->height)
					{
						SetCursor(--position.X, ++position.Y);
						field->mass[++y][--x] = 'k';
					}
				}

				else if (code == 57)
				{
					if(position.X < field->width && position.Y > 1)
					{
						SetCursor(++position.X, --position.Y);
						field->mass[--y][++x] = 'k';
					}
				}

				else if (code == 51)
				{
					if(position.X < field->width && position.Y < field->height)
					{
						SetCursor(++position.X, ++position.Y);
						field->mass[++y][++x] = 'k';
					}
				}

				else if (code == ENTER && prevX != position.X && prevY != position.Y)
				{
					move = false;
				}

				if (prevX % 2 == 0 && prevY % 2 == 0 || prevX % 2 != 0 && prevY % 2 != 0 || prevX == prevY)
				{
					field->mass[prevY][prevX] = ' ';
				}

				else if (prevX == x && prevY == y)
				{
					continue;
				}

				else
				{
					field->mass[prevY][prevX] = '#';
				}
			}
		}
	}
	virtual void Bit(Peshka& figure) 
	{
		if (isAlive)
		{

		}
	}
};

class Castle : public Peshka, public IFigure 
{
public:
	Castle(Field* field, COORD& pos) : Peshka(field, pos) {}

	virtual void Move() 
	{
		if (isAlive)
		{
			int x = position.X - 1;
			int y = position.Y - 1;
			bool move = true;
			int prevX = position.X - 1;
			int prevY = position.Y - 1;
			while(move)
			{
				field->Print();
				SetCursor(position.X, position.Y);
				int code = _getch();
				if(code == 224)
				{
					code = _getch();
					prevX = position.X - 1;
					prevY = position.Y - 1;
					if (code == 72)
					{
						if(position.Y > 1)
						{
							y--;
							position.Y--;
							SetCursor(position.X, position.Y);
							field->mass[y][x] = 'c';
						}
					}

					else if (code == 75)
					{
						if(position.X > 1)
						{
							position.X--;
							x--;
							SetCursor(position.X, position.Y);
							field->mass[y][x] = 'c';
						}
					}

					else if (code == 77)
					{
						if(position.X < field->width)
						{
							position.X++;
							x++;
							SetCursor(position.X, position.Y);
							field->mass[y][x] = 'c';
						}
					}

					else if (code == 80)
					{
						if(position.Y < field->height)
						{
							position.Y++;
							y++;
							SetCursor(position.X, position.Y);
							field->mass[y][x] = 'c';
						}
					}
					
				}
				else if (code == ENTER && prevX != position.X && prevY != position.Y)
				{
					move = false;
				}

				if (prevX % 2 == 0 && prevY % 2 == 0 || prevX % 2 != 0 && prevY % 2 != 0 || prevX == prevY && prevX != x && prevY != y)
				{
					field->mass[prevY][prevX] = ' ';
				}

				else if (prevX == x && prevY == y)
				{
					continue;
				}

				else
				{
					field->mass[prevY][prevX] = '#';
				}
			}
		}
	}

	virtual void Bit(Peshka& figure) 
	{
		if (isAlive)
		{
				int x = position.X - 1;
				int y = position.Y - 1;
				bool move = true;
				int prevX = position.X - 1;
				int prevY = position.Y - 1;
				int code = 0;
				while (move)
				{
					field->Print();
					prevX = position.X - 1;
					prevY = position.Y - 1;
					SetCursor(position.X, position.Y);
					code = _getch();
					

					if (code == 224)
					{
						code = _getch();
						if (prevX % 2 == 0 && prevY % 2 != 0)
						{
							field->mass[prevY][prevX] = '#';
						}
						else
						{
							field->mass[prevY][prevX] = ' ';
						}
						prevX = position.X;
						prevY = position.Y;
						if (code == 72)
						{
							if (position.Y - 1 >= 1)
							{
								y--;
								position.Y--;
								SetCursor(position.X, position.Y);
								field->mass[y][x] = 'c';
							}
						}

						else if (code == 75)
						{
							if (position.X - 1 >= 1)
							{
								position.X--;
								x--;
								SetCursor(position.X, position.Y);
								field->mass[y][x] = 'c';
							}
						}

						else if (code == 77)
						{
							if (position.X + 1 < field->width)
							{
								position.X++;
								x++;
								SetCursor(position.X, position.Y);
								field->mass[y][x] = 'c';
							}
						}

						else if (code == 80)
						{
							if (position.Y + 1 < field->height)
							{
								position.Y++;
								y++;
								SetCursor(position.X, position.Y);
								field->mass[y][x] = 'c';
							}
						}

					}
					else if (code == ENTER && prevX != position.X && prevY != position.Y)
					{
						if(field->mass[y][x] != ' ' && field->mass[y][x] != '#')
						{
							move = false;
						}
					}
					
					if (prevX % 2 == 0 && prevY % 2 == 0 || prevX % 2 != 0 && prevY % 2 != 0 || prevX == prevY)
					{
						field->mass[prevY][prevX] = ' ';
					}

					else if (prevX == x && prevY == y)
					{
						field->mass[prevY][prevX] = 'c';
					}

					else
					{
						field->mass[prevY][prevX] = '#';
					}
				}
			}
		
	}
};

class Horse : public Peshka, public IFigure 
{
public:
	Horse(Field* field, COORD& position) : Peshka(field, position) {}

	virtual void Move() 
	{
		if (isAlive)
		{
			int prevX = position.X - 1;
			int prevY = position.Y - 1;
			int x = position.X - 1;
			int y = position.Y - 1;
			bool move = true;
			while(move) 
			{
				int code = _getch();
				if (prevX % 2 == 0 && prevY % 2 == 0)
				{
					field->mass[prevY][prevX] = '#';
				}
				else
				{
					field->mass[prevY][prevX] = ' ';
				}
				prevX = position.X;
				prevY = position.Y;
				if (code == 224)
				{
					code = _getch();
					if (code == 72)
					{
						code = _getch();
						if (code == 224)
						{
							code = _getch();
							if (position.Y - 3 > 0 && position.X - 1 > 0)
							{
								if (code == 75)
								{
									y -= 3;
									x -= 1;
									position.Y -= 3;
									position.X--;
									SetCursor(position.X, position.Y);
									field->mass[y][x] = 'c';
								}
							}
							else if (position.Y - 3 > 0 && position.X + 1 <= field->width)
							{
								if (code == 77)
								{
									y -= 3;
									x += 1;
									position.Y -= 3;
									position.X++;
									SetCursor(position.X, position.Y);
									field->mass[y][x] = 'c';
								}
							}
						}
					}
				
					else if (code == 75)
					{
						code = _getch();
						if (code == 224)
						{
							code = _getch();
							if(prevX % 2 == 0 && prevY % 2 != 0)
							{
								field->mass[prevY][prevX] = '#';
							}
							else
							{
								field->mass[prevY][prevX] = ' ';
							}

							if (position.X - 3 > 0 && position.Y - 1 > 0)
							{
								if (code == 72)
								{
									x -= 3;
									y -= 1;
									position.X -= 3;
									position.Y--;
									SetCursor(position.X, position.Y);
									field->mass[y][x] = 'c';
								}
							}
							else if (position.X - 3 > 0 && position.Y + 1 <= field->width)
							{
								if (code == 80)
								{
									x -= 3;
									y += 1;
									position.X -= 3;
									position.Y++;
									SetCursor(position.X, position.Y);
									field->mass[y][x] = 'c';
								}
							}
						}
					}

					else if (code == 77)
					{
						code = _getch();
						if (code == 224)
						{
							code = _getch();
							if (position.X + 3 <= field->width && position.Y - 1 > 0)
							{
								if (code == 72)
								{
									x += 3;
									y -= 1;
									position.X += 3;
									position.Y--;
									SetCursor(position.X, position.Y);
									field->mass[y][x] = 'c';
								}
							}
							else if (position.X + 3 <= field->width && position.Y + 1 <= field->width)
							{
								if (code == 80)
								{
									x += 3;
									y += 1;
									position.X += 3;
									position.Y++;
									SetCursor(position.X, position.Y);
									field->mass[y][x] = 'c';
								}
							}
						}
					}

					else if (code == 80)
					{
						code = _getch();
						if (code == 224)
						{
							code = _getch();
							if (position.Y + 3 <= field->height && position.X - 1 > 0)
							{
								if (code == 75)
								{
									y += 3;
									x -= 1;
									position.Y += 3;
									position.X--;
									SetCursor(position.X, position.Y);
									field->mass[y][x] = 'c';
								}
							}
							else if (position.Y + 3 <= field->height && position.X + 1 <= field->width)
							{
								if (code == 77)
								{
									y += 3;
									x += 1;
									position.Y += 3;
									position.X++;
									SetCursor(position.X, position.Y);
									field->mass[y][x] = 'c';
								}
							}
						}
					}
				}
				else if (code == ENTER && prevX != position.X && prevY != position.Y)
				{
					move = false;
				}
				field->Print();
				
			}
		}
	}

	virtual void Bit(Peshka& figure) 
	{
		if (isAlive)
		{

		}
	}
};

class End 
{

};

class Game 
{

};


int main() 
{
	Field field;
	field.CreateField();
	field.Print();
	COORD pos;
	pos.X = 1;
	pos.Y = 1;

	/*Peshka a(&field,pos);
	a.Move();*/
	//Queen b(&field, pos);
	//b.Move();
	Castle c(&field, pos);
	c.Move();
	/*Horse h(&field, pos);
	h.Move();*/
	/*Elephant e(&field, pos);
	e.Move();
	King k(&field, pos);
	k.Move();*/
}