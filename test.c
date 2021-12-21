#include <stdio.h>
#include <string.h> //���ڿ� �Լ� strcpy�� ����ϱ� ���� �ʿ��� �������
#include <conio.h> //_getch�� ����ϱ� ���� �ʿ��� �������
#pragma warning(disable:4996) //strcpy�� ��������� ������ ���� �ʱ� ���� ���, ��ó���� ��� strcpy_s��� ����ص� ��

//�Լ� ���� ���� 
void SetMaze(char Maze[20][21], struct point* pplayer, struct point* pstart, struct point* pend); //�̷θ� �����ϴ� �Լ�
void Print(char Maze[20][21], struct point* pplayer); //�̷θ� ����ϴ� �Լ�
void MoveUp(char Maze[20][21], struct point* pplayer); //�÷��̾��� ��ġ�� ���� �ö󰡰� �ϴ� �Լ�
void MoveDown(char Maze[20][21], struct point* pplayer); //�÷��̾��� ��ġ�� �Ʒ��� �������� �ϴ� �Լ�
void MoveRight(char Maze[20][21], struct point* pplayer); //�÷��̾��� ��ġ�� ���������� ���� �ϴ� �Լ�
void MoveLeft(char Maze[20][21], struct point* pplayer); //�÷��̾��� ��ġ�� �������� ���� �ϴ� �Լ�
void MovePlayer(char Maze[20][21], struct point* pplayer, char clnput); //�÷��̾��� ��ġ�� �����̰� �ϴ� �Լ�

struct point {
	int x;
	int y;
}player, start, end; //��ǥ�� ��Ÿ���� ����ü ���ǿ� ���� ����


int main() {
	//20x20 �̷θ� ����� �ش�
	char Maze[20][21]; //������ �迭�� �������� null���ڰ� �ʿ��ϹǷ� ���κ� �ε����� 21�� ������ ������ ����

	//�̷θ� �����Ѵ�
	SetMaze(Maze, &player, &start, &end);
	while (1) {
		system("cls");//ȭ���� �����ϰ� ���ִ� �Լ�,�ܼ�â�� ���𰡸� ��� ����ϴµ� ��� ����� ���� ���̰� ���̴ٺ��� ���� ��¹����� ������ ��ħ

		//�̷θ� ����Ѵ�
		Print(Maze, &player);

		if (player.x == end.x && player.y == end.y) {
			printf("�����߽��ϴ�^-^\n");
			break;
		}

		printf("w:�� s:�Ʒ� a:���� d:������ q:����");
		char clnput = _getch(); //ȭ�鿡 ���ڸ� ��������� �ʰ�(����x), ���۸� ������� ����(�Էµ� Ű���� ��� ��ȯ), �ﰢ���� ������ �������ϱ� ������ ���

		if (clnput == 'q' || clnput == 'Q') //���� Ű
			break;

		//����ڸ� �����̰� �ϴ� �Լ�
		MovePlayer(Maze, &player, clnput);
	}

	return 0;
}

void SetMaze(char Maze[20][21], struct point* pplayer, struct point* pstart, struct point* pend) {
	/*
	0:�� 1:�� 2:������ 3:������
	*/

	//(*pstart).x�� ������ �ǹ�,�����ɹ� ������,����ü �����͸� �̿��Ͽ� �ɹ��� �����ϱ� ���Ͽ� ���
	pstart->x = 0; //�������� (0,0)
	pstart->y = 0;

	pend->x = 19; //���������� (19,19)
	pend->y = 19;

	pplayer->x = 0; //�÷��̾� ������ (0,0)
	pplayer->y = 0;

	/*
	strcpy�� strcpy(s1,s2)�� �ִٸ� s2�� s1�� ������ �ִ� �Լ�
	strcpy�� ������� �ʴ´ٸ� ��Ҹ� �ϳ��ϳ� �־���� ��
	2���� ���ڿ� �迭 Maze�� ������ ���� Maze[0],Maze[1]�� ���� ������ �� ����
	*/


	strcpy(Maze[0], "21100000111111101111");
	strcpy(Maze[1], "01111111100000111000");
	strcpy(Maze[2], "01001010101111101110");
	strcpy(Maze[3], "01000010111010111000");
	strcpy(Maze[4], "01111111100010001110");
	strcpy(Maze[5], "01000100100000001011");
	strcpy(Maze[6], "01101111111111001000");
	strcpy(Maze[7], "00111100100001001111");
	strcpy(Maze[8], "01100001001111100101");
	strcpy(Maze[9], "00111111111000110100");
	strcpy(Maze[10], "00000100001111001110");
	strcpy(Maze[11], "11100111111000001010");
	strcpy(Maze[12], "00111101001111111000");
	strcpy(Maze[13], "01010101011000000111");
	strcpy(Maze[14], "01000101001111111101");
	strcpy(Maze[15], "01111111111001000100");
	strcpy(Maze[16], "01000000010111110100");
	strcpy(Maze[17], "01011110010100011111");
	strcpy(Maze[18], "11110011011111010101");
	strcpy(Maze[19], "10010010010001110003");
}

void Print(char Maze[20][21], struct point* pplayer) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (pplayer->x == j && pplayer->y == i)
				printf("��"); //�÷��̾��� ���� ��ġ���

			else if (Maze[i][j] == '0') //���̶��
				printf("��");

			else if (Maze[i][j] == '1') //���̶��
				printf("  "); //Ư�����ڴ� 2����Ʈ�� ������

			else if (Maze[i][j] == '2') //�������̶��
				printf("��");

			else if (Maze[i][j] == '3') //�������̶��
				printf("��");

		}
		printf("\n");
	}
}

void MoveUp(char Maze[20][21], struct point* pplayer) {
	if (pplayer->y - 1 >= 0) { //ȭ�鿡�� ���� �ö󰥶����� ��κ��� �ε����� 1�� ����, ��κ� �ε����� 0���� ����

		if (Maze[pplayer->y - 1][pplayer->x] != '0') { //���� �ƴ϶��
			--pplayer->y; //player�� y�� 1����
		}
	}
}

void MoveDown(char Maze[20][21], struct point* pplayer) {
	if (pplayer->y + 1 < 20) { //ȭ�鿡�� �Ʒ��� ������������ ��κ��� �ε����� 1�� ����, ��κ� �ε����� 19���� ������ 

		if (Maze[pplayer->y + 1][pplayer->x] != '0') { //���� �ƴ϶��
			++pplayer->y; //player�� y�� 1����
		}
	}
}

void MoveRight(char Maze[20][21], struct point* pplayer) {
	if (pplayer->x + 1 < 20) { //ȭ�鿡�� ���������� �������� ���κ��� �ε����� 1�� ����, ���κ� �ε����� 19���� ��밡��(20�� null�ڸ�)

		if (Maze[pplayer->y][pplayer->x + 1] != '0') { //���� �ƴ϶��
			++pplayer->x; //player�� x�� 1����
		}
	}
}

void MoveLeft(char Maze[20][21], struct point* pplayer) {
	if (pplayer->x - 1 >= 0) { //ȭ�鿡�� �������� �������� ���κ��� �ε����� -1�� ����, ���κ� �ε����� 0���� ����

		if (Maze[pplayer->y][pplayer->x - 1] != '0') { //���� �ƴ϶��
			--pplayer->x; //player�� x�� -1����
		}
	}
}

//�Է¹��� ������ ���� �Լ��� �����Ͽ� �÷��̾��� ��ġ�� �����Ŵ
void MovePlayer(char Maze[20][21], struct point* pplayer, char clnput) {
	switch (clnput) {
	case 'w':
	case 'W':
		MoveUp(Maze, pplayer);
		break;
	case 'S':
	case 's':
		MoveDown(Maze, pplayer);
		break;
	case 'A':
	case 'a':
		MoveLeft(Maze, pplayer);
		break;
	case 'D':
	case 'd':
		MoveRight(Maze, pplayer);
		break;
	}
}