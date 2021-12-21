#include <stdio.h>
#include <string.h> //문자열 함수 strcpy를 사용하기 위해 필요한 헤더파일
#include <conio.h> //_getch를 사용하기 위해 필요한 헤더파일
#pragma warning(disable:4996) //strcpy를 사용했을때 오류가 나지 않기 위해 사용, 전처리기 대신 strcpy_s라고 사용해도 됨

//함수 원형 정의 
void SetMaze(char Maze[20][21], struct point* pplayer, struct point* pstart, struct point* pend); //미로를 설정하는 함수
void Print(char Maze[20][21], struct point* pplayer); //미로를 출력하는 함수
void MoveUp(char Maze[20][21], struct point* pplayer); //플레이어의 위치를 위로 올라가게 하는 함수
void MoveDown(char Maze[20][21], struct point* pplayer); //플레이어의 위치를 아래로 내려가게 하는 함수
void MoveRight(char Maze[20][21], struct point* pplayer); //플레이어의 위치를 오른쪽으로 가게 하는 함수
void MoveLeft(char Maze[20][21], struct point* pplayer); //플레이어의 위치를 왼쪽으로 가게 하는 함수
void MovePlayer(char Maze[20][21], struct point* pplayer, char clnput); //플레이어의 위치를 움직이게 하는 함수

struct point {
	int x;
	int y;
}player, start, end; //좌표를 나타내는 구조체 정의와 변수 선언


int main() {
	//20x20 미로를 만들어 준다
	char Maze[20][21]; //문자형 배열은 마지막에 null문자가 필요하므로 열부분 인덱스는 21로 원소의 개수를 만듦

	//미로를 설정한다
	SetMaze(Maze, &player, &start, &end);
	while (1) {
		system("cls");//화면을 깨끗하게 해주는 함수,콘솔창에 무언가를 계속 출력하는데 계속 출력한 것이 쌓이고 쌓이다보면 다음 출력물에게 지장을 끼침

		//미로를 출력한다
		Print(Maze, &player);

		if (player.x == end.x && player.y == end.y) {
			printf("도착했습니당^-^\n");
			break;
		}

		printf("w:위 s:아래 a:왼쪽 d:오른쪽 q:종료");
		char clnput = _getch(); //화면에 문자를 출력해주지 않고(에코x), 버퍼를 사용하지 않음(입력된 키값을 즉시 반환), 즉각적인 반응을 보여야하기 때문에 사용

		if (clnput == 'q' || clnput == 'Q') //종료 키
			break;

		//사용자를 움직이게 하는 함수
		MovePlayer(Maze, &player, clnput);
	}

	return 0;
}

void SetMaze(char Maze[20][21], struct point* pplayer, struct point* pstart, struct point* pend) {
	/*
	0:벽 1:길 2:시작점 3:도착점
	*/

	//(*pstart).x와 동일한 의미,간접맴버 연산자,구조체 포인터를 이용하여 맴버에 접근하기 위하여 사용
	pstart->x = 0; //시작점은 (0,0)
	pstart->y = 0;

	pend->x = 19; //종료지점은 (19,19)
	pend->y = 19;

	pplayer->x = 0; //플레이어 시작점 (0,0)
	pplayer->y = 0;

	/*
	strcpy는 strcpy(s1,s2)가 있다면 s2를 s1에 복사해 주는 함수
	strcpy를 사용하지 않는다면 요소를 하나하나 넣어줘야 함
	2차원 문자열 배열 Maze의 각각의 행은 Maze[0],Maze[1]과 같이 접근할 수 있음
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
				printf("☆"); //플레이어의 현재 위치라면

			else if (Maze[i][j] == '0') //벽이라면
				printf("■");

			else if (Maze[i][j] == '1') //길이라면
				printf("  "); //특수문자는 2바이트를 차지함

			else if (Maze[i][j] == '2') //시작점이라면
				printf("★");

			else if (Maze[i][j] == '3') //도착점이라면
				printf("◎");

		}
		printf("\n");
	}
}

void MoveUp(char Maze[20][21], struct point* pplayer) {
	if (pplayer->y - 1 >= 0) { //화면에서 위로 올라갈때마다 행부분의 인덱스는 1씩 감소, 행부분 인덱스는 0부터 시작

		if (Maze[pplayer->y - 1][pplayer->x] != '0') { //벽이 아니라면
			--pplayer->y; //player의 y는 1감소
		}
	}
}

void MoveDown(char Maze[20][21], struct point* pplayer) {
	if (pplayer->y + 1 < 20) { //화면에서 아래로 내려갈때마다 행부분의 인덱스는 1씩 증가, 행부분 인덱스는 19까지 존재함 

		if (Maze[pplayer->y + 1][pplayer->x] != '0') { //벽이 아니라면
			++pplayer->y; //player의 y는 1증가
		}
	}
}

void MoveRight(char Maze[20][21], struct point* pplayer) {
	if (pplayer->x + 1 < 20) { //화면에서 오른쪽으로 갈때마다 열부분의 인덱스는 1씩 증가, 열부분 인덱스는 19까지 사용가능(20은 null자리)

		if (Maze[pplayer->y][pplayer->x + 1] != '0') { //벽이 아니라면
			++pplayer->x; //player의 x는 1증가
		}
	}
}

void MoveLeft(char Maze[20][21], struct point* pplayer) {
	if (pplayer->x - 1 >= 0) { //화면에서 왼쪽으로 갈때마다 열부분의 인덱스는 -1씩 감소, 열부분 인덱스는 0부터 시작

		if (Maze[pplayer->y][pplayer->x - 1] != '0') { //벽이 아니라면
			--pplayer->x; //player의 x는 -1감소
		}
	}
}

//입력받은 변수에 따라서 함수를 실행하여 플레이어의 위치를 변경시킴
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