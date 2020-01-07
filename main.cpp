#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<conio.h>
#include<Windows.h>
#include<vector>	// C++ vectror   : https://blockdmask.tistory.com/70
#include<fstream>	// C++ ��������� : https://blockdmask.tistory.com/322
using namespace std;

// [��� ����] by. BlockDMask
// �ȳ��ϼ���.BlockDMask �Դϴ�.
// ����ϽǶ� �� ��ó�� �����ּ���.
// ��α� : https://blockdmask.tistory.com/369

//�ܼ� ������ Ư�� ��ġ�� Ŀ���� �̵���Ű�� �Լ� �Դϴ�.
void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//keyboard �Է�
int GetKeyDown()
{
	if (_kbhit() != 0)
	{
		return _getch();
	}
	return 0;
}

//�ܼ� ����
void SetConsoleView()
{
	system("mode con:cols=50 lines=20");
	system("title [HangManGame] by.BlockDMask");
}

//����ȭ�� draw
void DrawReadyGame()
{
	system("cls");
	gotoxy(5, 2);
	cout << "==============================";
	gotoxy(5, 3);
	cout << "======= HANG MAN GAME ========";
	gotoxy(5, 4);
	cout << "==============================";
	gotoxy(6, 6);
	cout << "�����Ϸ��� 's'�� �����ּ���";
	gotoxy(6, 7);
	cout << "�����Ϸ��� 'q'�� �����ּ���";
	gotoxy(9, 14);
	cout << "by. BlockDMask" << endl;
}

//����ȭ�� draw
void DrawStartGame(int life, int score, vector<string>& pastWord)
{
	system("cls");
	gotoxy(5, 1);
	cout << "life = " << life;
	gotoxy(5, 2);
	cout << "score = " << score;
	gotoxy(5, 8);
	cout << "past = ";
	for (int i = 0; i < static_cast<int>(pastWord.size()); ++i)
	{
		cout << pastWord[i] << " ";
	}

	gotoxy(5, 12);
	cout << "input = ";
	gotoxy(13, 14);
	cout << "����ȭ�� 'qq'" << endl;
}

//������ �����ϴ� �Լ� �Դϴ�.
//[C++] ��������� ������ : https://blockdmask.tistory.com/322
void SetDictionary(vector<string>& strArr)
{
	static const int INIT_NUM = 4;
	static const string str[INIT_NUM] = { "apple", "banana", "code", "program" };	//���� �ܾ�
	ifstream readFromFile("words.txt");
	if (!readFromFile.is_open())
	{
		ofstream writeToFile("words.txt");
		for (int i = 0; i < INIT_NUM; ++i)
		{
			string tmp = str[i];
			if (i != INIT_NUM - 1)
			{
				tmp += "\n";
			}
			writeToFile.write(tmp.c_str(), tmp.size());
			strArr.push_back(str[i]);
		}
		writeToFile.close();
		return;
	}

	while (!readFromFile.eof())
	{
		string tmp;
		getline(readFromFile, tmp);
		strArr.push_back(tmp);
	}
	readFromFile.close();
	return;
}

//����ȭ�� ���
bool ReadyGame()
{
	DrawReadyGame();
	while (true)
	{
		int key = GetKeyDown();
		if (key == 's' || key == 'S')
		{
			return true;
		}
		else if (key == 'q' || key == 'Q')
		{
			break;
		}
	}
	return false;
}

//���� ���� �Լ�.
void StartGame()
{
	int score = 0;
	vector<string> pastWord;
	vector<string> strArr;
	SetDictionary(strArr);		//read from file

	while (true)	//�ϳ��� ź�� ǥ���ϴ� ����
	{
		//1 play
		int num = 0;
		srand((unsigned int)time(NULL));		//�����Լ� : https://blockdmask.tistory.com/308
		num = rand() % static_cast<int>(strArr.size());

		string strQuestion;
		const string strOriginal = strArr[num];	//�ܾ �´��� ����Ȯ�ο����� ����
		const int originLen = static_cast<int>(strOriginal.length());

		//init
		for (int i = 0; i < originLen; ++i)
		{
			strQuestion += "_";
		}

		int life = originLen + 2;

		//1 question
		while (true)
		{
			DrawStartGame(life, score, pastWord);

			//draw question
			gotoxy(5, 5);
			for (int i = 0; i < originLen; ++i)
			{
				cout << strQuestion[i] << " ";
			}
			cout << endl;

			//input
			gotoxy(9, 12);
			string strInput;
			cin >> strInput;
			if (strInput == "qq")
			{
				return;
			}
			pastWord.push_back(strInput);

			if (strInput.length() == 1)
			{
				//alphabet
				for (int i = 0; i < originLen; ++i)
				{
					if (strOriginal[i] == strInput[0])
					{
						strQuestion[i] = strInput[0];
					}
				}
			}
			else if (strInput.length() > 1)
			{
				//word
				if (strOriginal == strInput)
				{
					//score up !!
					score += 5;
					pastWord.clear();
					break;
				}
			}

			life -= 1;
			if (life < 0)
			{
				score -= 5;
				if (score < 0)
				{
					score = 0;
				}
				pastWord.clear();
				break;
			}
		}
	}
}

//�����Լ�
int main(void)
{
	SetConsoleView();
	bool isStart = false;
	while (true)
	{
		isStart = ReadyGame();
		if (isStart)
		{
			StartGame();		//���ӽ���
		}
		else
		{
			break;
		}
	}
	return 0;
}