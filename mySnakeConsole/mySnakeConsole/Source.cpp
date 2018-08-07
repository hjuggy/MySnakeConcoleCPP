#include <iostream>
#include <vector>
#include <conio.h>
#include <thread>
#include <ctime>

using namespace std;

// определяем размеры окна игры 
const int height = 20;
const int width = 30;

// Предварительно объявим класс фрукты, что бы не спамил MVS об ошибке. Определение класса ниже 
class Fruit;


// Определим класс Point для координат игрового поля,  тела змейки, и координат фруктов 
class Point
{
public:
	int X, Y;

	Point() {}
	Point(int X, int Y)
	{
		this->X = X;
		this->Y = Y;
	}
};
// Определим класс фрукт 
class Fruit
{

public:
	Point FrPoint;
	static int id; // Статический аргумент класса является счетчиком игры, при поедании фрукта, создается новый фрукт  и  Id++

	Fruit() //Конструктор класса 
	{
		srand((unsigned)time(NULL));//При запуске игры конструктор создаёт фрукт со случайными координатами типа Point(x,y) 
		FrPoint.X = 1 + rand() % (width - 1);
		FrPoint.Y = 1 + rand() % (height - 2);

	};
	bool graphic(const int &i, const int &j)
	{
		/*Метод класса который выводит на консоль фрукт.
		В метод класса передаётся координата игрового поля,
		если координаты совпадают с координатой фрукта, то cout выводит на консоль  символ  фрукта “O”
		Тип возвращаемой переменной специально определен bool для того что бы участвовать в логике
		функции void graphic( Snake &sn,  Fruit &fr) по отображению игрового поля
		*/
		if (FrPoint.Y == i && FrPoint.X == j)
		{
			cout << 'O';
			return true;
		}
		return false;
	}
	void RefreshFruit(bool eat)
	{
		// метод создания нового фрукта, если змейка съела 
		if (eat)
		{
			srand((unsigned)time(NULL));
			id++;
			FrPoint.X = 1 + rand() % (width - 1);
			FrPoint.Y = 1 + rand() % (height - 2);
		}
	}
};

int Fruit::id = 0;// Объявление статического аргумента класса вне класса (счётчик игры )

class Snake
{
public:

	/*
	Класс змейка имеет :
	аргументы  тело (body), в виде вектора поинтов
	методы: 1) движения по координатам
	2) рисования тела змейки
	3) условия проигрыша змейки

	*/
	vector<Point> body
	{
		//Стартовое положение змейки  
		Point(width / 2, height / 2),
		Point(width / 2 - 1, height / 2),
		Point(width / 2 - 2, height / 2)

	};
	void DriveSn(int &tempDS, bool ate)
	{
		/*
		&tempDS - переменая типа int из ascii code указывает направление движения
		ate - переменая типа bool указывает, что фрукт был съеден

		*/
		Point tempPointDrive = body.front(); // копируем в темп координаты головы 

											 // копируем в темп координаты хвоста, если Если фрукт съеден, 
											 //то будет добавлен в конец и змейка вырастит на один элемент тела 
		Point tempPointEta = body[body.size() - 1];

		// операции с передвижением головы через switch
		switch (tempDS)
		{
		case 162:tempPointDrive.X++; break; // 162 pravo - d 
		case 228:tempPointDrive.X--; break; // 228 levo - a
		case 230:tempPointDrive.Y--; break; // 230 verh - w
		case 235:tempPointDrive.Y++; break; // 235 niz	- s
		}

		/*
		выполняем перемещение тела змейки, координат элемента тела копируется в следующий за ним элемент тела
		для оптимального решения этой задачи цикл выполняется в обратном порядке
		выполняется для всех элементов кроме головы (первого под индексом 0)
		*/
		for (int i = body.size(); i > 1; i--)
		{
			body[i - 1] = body[i - 2];
		}

		// Присваиваем новые координаты головы  после выполнения блока условий switch
		body[0] = tempPointDrive;


		// Если фрукт съеден, то в конец тела змейки добавляем новый элемент с координатами хвоста, которые скопировали в темп 
		if (ate)
		{
			body.push_back(tempPointEta);
		}
	}


	bool graphic(const int &i, const int &j)
	{
		/*
		Метод класса который выводит на консоль тело змейки.
		В метод класса передаётся координата игрового поля,
		если координаты совпадают с координатой элемента тела, то cout выводит на консоль  символ  фрукта “*”
		Тип возвращаемой переменной специально определен bool для того что бы участвовать в логике
		функции void graphic( Snake &sn,  Fruit &fr) по отображению игрового поля
		*/
		for (auto item : body)
		{
			if (item.Y == i && item.X == j) { cout << '*'; return true; }
		}
		return false;
	}
	bool GameOverSn()
	{
		//Конец игре, если голова столкнулась с границей игрового поля


		Point tempPointGameOverSn = body.front();
		if (tempPointGameOverSn.Y == 0 || tempPointGameOverSn.Y == height || tempPointGameOverSn.X == 0 || tempPointGameOverSn.X == width)
		{
			return true;
		}

		//Конец игре, если голова столкнулась с телом змейки
		for (int i = 1; i<body.size(); i++)
		{
			if (body[0].X == body[i].X&&body[0].Y == body[i].Y)
			{
				return true;
			}
		}
		return false;
	}

};


void graphic(Snake &sn, Fruit &fr)
{
	for (int i = 0; i < width + 1; i++) //Рисуем верхнюю границу игрового поля
	{
		cout << '#';
	}
	cout << "\t\t point=\t" << fr.id; //Отображаем текущий счет в игре
	cout << endl;
	for (int i = 1; i < height; i++)
	{
		for (int j = 0; j < width + 1; j++)
		{
			if (j == 0 || j == width) //Рисуем левую и правую границу игрового поля
			{
				cout << '#';
			}
			else
			{
				//Если методы sn.graphic(i, j) и fr.graphic(i, j) возвращают false, то заполняем игровое поле пробелом 
				if (!sn.graphic(i, j) && !fr.graphic(i, j))
				{
					cout << ' ';
				}
			}

		}
		cout << endl;
	}
	for (int i = 0; i < width + 1; i++) // Рисуем нижнюю границу игрового поля  
	{
		cout << '#';
	}
	cout << endl;
}

void DirectionDrive(int &tempD)
{
	int a = _getch();//Считываем нажатую клавишу, функция _getch() возвращает тип int который соответствует типу char в ascii коде 


					 //Выполняем проверку, если змейка двигается в лево, то мы не можем ей указать двигаться в право и наоборот,
					 //аналогично с движениями вверх/вниз  
	if (tempD == 228 && a != 162 || tempD == 162 && a != 228 || tempD == 235 && a != 230 || tempD == 230 && a != 235)
	{
		//Дополнительная проверка, что бы записывать в переменную  только необходимые для нас значения. 
		if (a == 235 || a == 228 || a == 162 || a == 230)
		{
			tempD = a;
		}
	}
}

//функция сравнивает координаты фрукта и головы змейки, если они совпали, то фрукт был съеден
bool EtaFr(const Snake &sn, const Fruit &fr)
{
	return sn.body[0].X == fr.FrPoint.X && sn.body[0].Y == fr.FrPoint.Y;
}




int main()
{
	setlocale(LC_ALL, "ru");

	int temp = 162;//Стартовое направление движения змейки  вправо 
	Snake sn;
	Fruit fr;
	// В отдельном потоке выполняем считывание с клавиатуры направления движения 
	//и записываем в переменную темп, которая передана лямбда функцию по ссылке 
	thread t([&]() {
		while (!sn.GameOverSn())//Проверка на GameOver
		{
			DirectionDrive(temp); //Ввод направление движения
			this_thread::sleep_for(chrono::milliseconds(50));
		}
	});


	while (!sn.GameOverSn())//Проверка на GameOver
	{
		system("cls");// Очистка экрана 
		graphic(sn, fr);//заполнение экрана 
		this_thread::sleep_for(chrono::milliseconds(200)); // скорость движения змейки 
		bool EAT = EtaFr(sn, fr); // Проверка : съеден фрукт 
		sn.DriveSn(temp, EAT); // Выполнение логики по изменению координат змейки 
		fr.RefreshFruit(EAT);// Функция по обновлению фрукт (если его съела змейка  ) 
	}
	t.join(); //Ждем поток 

	system("cls");
	cout << "\n\n\t\tGameOver" << endl << endl;
	system("pause");

	return 0;
}