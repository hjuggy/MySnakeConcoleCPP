#include <iostream>
#include <vector>
#include <conio.h>
#include <thread>
#include <ctime>

using namespace std;

// ���������� ������� ���� ���� 
const int height = 20;
const int width = 30;

// �������������� ������� ����� ������, ��� �� �� ������ MVS �� ������. ����������� ������ ���� 
class Fruit;


// ��������� ����� Point ��� ��������� �������� ����,  ���� ������, � ��������� ������� 
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
// ��������� ����� ����� 
class Fruit
{

public:
	Point FrPoint;
	static int id; // ����������� �������� ������ �������� ��������� ����, ��� �������� ������, ��������� ����� �����  �  Id++

	Fruit() //����������� ������ 
	{
		srand((unsigned)time(NULL));//��� ������� ���� ����������� ������ ����� �� ���������� ������������ ���� Point(x,y) 
		FrPoint.X = 1 + rand() % (width - 1);
		FrPoint.Y = 1 + rand() % (height - 2);

	};
	bool graphic(const int &i, const int &j)
	{
		/*����� ������ ������� ������� �� ������� �����.
		� ����� ������ ��������� ���������� �������� ����,
		���� ���������� ��������� � ����������� ������, �� cout ������� �� �������  ������  ������ �O�
		��� ������������ ���������� ���������� ��������� bool ��� ���� ��� �� ����������� � ������
		������� void graphic( Snake &sn,  Fruit &fr) �� ����������� �������� ����
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
		// ����� �������� ������ ������, ���� ������ ����� 
		if (eat)
		{
			srand((unsigned)time(NULL));
			id++;
			FrPoint.X = 1 + rand() % (width - 1);
			FrPoint.Y = 1 + rand() % (height - 2);
		}
	}
};

int Fruit::id = 0;// ���������� ������������ ��������� ������ ��� ������ (������� ���� )

class Snake
{
public:

	/*
	����� ������ ����� :
	���������  ���� (body), � ���� ������� �������
	������: 1) �������� �� �����������
	2) ��������� ���� ������
	3) ������� ��������� ������

	*/
	vector<Point> body
	{
		//��������� ��������� ������  
		Point(width / 2, height / 2),
		Point(width / 2 - 1, height / 2),
		Point(width / 2 - 2, height / 2)

	};
	void DriveSn(int &tempDS, bool ate)
	{
		/*
		&tempDS - ��������� ���� int �� ascii code ��������� ����������� ��������
		ate - ��������� ���� bool ���������, ��� ����� ��� ������

		*/
		Point tempPointDrive = body.front(); // �������� � ���� ���������� ������ 

											 // �������� � ���� ���������� ������, ���� ���� ����� ������, 
											 //�� ����� �������� � ����� � ������ �������� �� ���� ������� ���� 
		Point tempPointEta = body[body.size() - 1];

		// �������� � ������������� ������ ����� switch
		switch (tempDS)
		{
		case 162:tempPointDrive.X++; break; // 162 pravo - d 
		case 228:tempPointDrive.X--; break; // 228 levo - a
		case 230:tempPointDrive.Y--; break; // 230 verh - w
		case 235:tempPointDrive.Y++; break; // 235 niz	- s
		}

		/*
		��������� ����������� ���� ������, ��������� �������� ���� ���������� � ��������� �� ��� ������� ����
		��� ������������ ������� ���� ������ ���� ����������� � �������� �������
		����������� ��� ���� ��������� ����� ������ (������� ��� �������� 0)
		*/
		for (int i = body.size(); i > 1; i--)
		{
			body[i - 1] = body[i - 2];
		}

		// ����������� ����� ���������� ������  ����� ���������� ����� ������� switch
		body[0] = tempPointDrive;


		// ���� ����� ������, �� � ����� ���� ������ ��������� ����� ������� � ������������ ������, ������� ����������� � ���� 
		if (ate)
		{
			body.push_back(tempPointEta);
		}
	}


	bool graphic(const int &i, const int &j)
	{
		/*
		����� ������ ������� ������� �� ������� ���� ������.
		� ����� ������ ��������� ���������� �������� ����,
		���� ���������� ��������� � ����������� �������� ����, �� cout ������� �� �������  ������  ������ �*�
		��� ������������ ���������� ���������� ��������� bool ��� ���� ��� �� ����������� � ������
		������� void graphic( Snake &sn,  Fruit &fr) �� ����������� �������� ����
		*/
		for (auto item : body)
		{
			if (item.Y == i && item.X == j) { cout << '*'; return true; }
		}
		return false;
	}
	bool GameOverSn()
	{
		//����� ����, ���� ������ ����������� � �������� �������� ����


		Point tempPointGameOverSn = body.front();
		if (tempPointGameOverSn.Y == 0 || tempPointGameOverSn.Y == height || tempPointGameOverSn.X == 0 || tempPointGameOverSn.X == width)
		{
			return true;
		}

		//����� ����, ���� ������ ����������� � ����� ������
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
	for (int i = 0; i < width + 1; i++) //������ ������� ������� �������� ����
	{
		cout << '#';
	}
	cout << "\t\t point=\t" << fr.id; //���������� ������� ���� � ����
	cout << endl;
	for (int i = 1; i < height; i++)
	{
		for (int j = 0; j < width + 1; j++)
		{
			if (j == 0 || j == width) //������ ����� � ������ ������� �������� ����
			{
				cout << '#';
			}
			else
			{
				//���� ������ sn.graphic(i, j) � fr.graphic(i, j) ���������� false, �� ��������� ������� ���� �������� 
				if (!sn.graphic(i, j) && !fr.graphic(i, j))
				{
					cout << ' ';
				}
			}

		}
		cout << endl;
	}
	for (int i = 0; i < width + 1; i++) // ������ ������ ������� �������� ����  
	{
		cout << '#';
	}
	cout << endl;
}

void DirectionDrive(int &tempD)
{
	int a = _getch();//��������� ������� �������, ������� _getch() ���������� ��� int ������� ������������� ���� char � ascii ���� 


					 //��������� ��������, ���� ������ ��������� � ����, �� �� �� ����� �� ������� ��������� � ����� � ��������,
					 //���������� � ���������� �����/����  
	if (tempD == 228 && a != 162 || tempD == 162 && a != 228 || tempD == 235 && a != 230 || tempD == 230 && a != 235)
	{
		//�������������� ��������, ��� �� ���������� � ����������  ������ ����������� ��� ��� ��������. 
		if (a == 235 || a == 228 || a == 162 || a == 230)
		{
			tempD = a;
		}
	}
}

//������� ���������� ���������� ������ � ������ ������, ���� ��� �������, �� ����� ��� ������
bool EtaFr(const Snake &sn, const Fruit &fr)
{
	return sn.body[0].X == fr.FrPoint.X && sn.body[0].Y == fr.FrPoint.Y;
}




int main()
{
	setlocale(LC_ALL, "ru");

	int temp = 162;//��������� ����������� �������� ������  ������ 
	Snake sn;
	Fruit fr;
	// � ��������� ������ ��������� ���������� � ���������� ����������� �������� 
	//� ���������� � ���������� ����, ������� �������� ������ ������� �� ������ 
	thread t([&]() {
		while (!sn.GameOverSn())//�������� �� GameOver
		{
			DirectionDrive(temp); //���� ����������� ��������
			this_thread::sleep_for(chrono::milliseconds(50));
		}
	});


	while (!sn.GameOverSn())//�������� �� GameOver
	{
		system("cls");// ������� ������ 
		graphic(sn, fr);//���������� ������ 
		this_thread::sleep_for(chrono::milliseconds(200)); // �������� �������� ������ 
		bool EAT = EtaFr(sn, fr); // �������� : ������ ����� 
		sn.DriveSn(temp, EAT); // ���������� ������ �� ��������� ��������� ������ 
		fr.RefreshFruit(EAT);// ������� �� ���������� ����� (���� ��� ����� ������  ) 
	}
	t.join(); //���� ����� 

	system("cls");
	cout << "\n\n\t\tGameOver" << endl << endl;
	system("pause");

	return 0;
}