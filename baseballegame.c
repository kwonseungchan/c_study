#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#pragma warning (disable : 4996)

int billboard(int[],int[], int);
int gameStrike(int[],int[]);
int gameBall(int[], int[]);
int gameOut(int[], int[]);
int gameContinue();
int isitInteger(int);
void printBoard(int);
void Start();
int main() {
	int arr[3] = { 0 }; //랜덤으로 뽑은 수
	int input[3] = { 0 }; //넣는 값
	int i,j;
	int overlap;		//중복
	int game_cnt = 1;	//게임 ~회
	int result;
	int isit = 0; //입력받은수가 1~9사이의 정수인지 판단

	
	srand((unsigned int)time(NULL));

	while (1) {
		Start();
		//중복처리
		for (i = 0; i < 3; i++) {
			arr[i] = rand() % 9 + 1;
			while (1) {
				overlap = 0;
				for (j = 0; j < i; j++) {
					if (arr[i] == arr[j]) {
						overlap = 1;
						break;
					}
				}
				if (overlap == 1)i--;
				if (overlap == 0)break;
			}
		}
		//// 정답 
		//printf(" 정답은 : ");
		//for (i = 0; i < 3; i++) {
		//	printf("%d ", arr[i]);
		//}
		puts("");

		while (1) {
			if (game_cnt == 10) {
				printf("라운드가 모두 종료되었습니다 .... 졌습니다.\n");
				break;
			}
			
			printf(" 숫자 3개를 입력해주세요 : ");
			scanf("%d %d %d", &input[0], &input[1], &input[2]);
			
			for(i = 0; i <3; i++){
				isit += isitInteger(input[i]);
			}
			if (isit != 3) {
				printf("1~9사이의 수를 입력하셔야합니다!! 다시 입력해주세요\n");
			
				for (i = 0; i < 3; i++) {
					input[i] = 0;
				}
				continue;
			}
			isit = 0;
			while (getchar() != '\n');
			result = 0;
			result = billboard(arr, input, game_cnt);

			
			if (result == 1) {
				printf("승리하셨습니다!!!!\n");
				break;
			}
			else if (result == 100) {
				printf("목숨을 하나도 잃지않고 승리하셨습니다 축하합니다!!!\n");
				break;
			}
			else if (result == -1) {
				printf("3개의 아웃을 3번 하셨습니다... 졌습니다.\n");
				break;
			}
			game_cnt++;
			
		}
		while (1) {
			if (gameContinue()) {
				printf("게임을 계속합니다!!!\n");
				game_cnt = 0;
				system("cls");
				break;
			}
			else if (gameContinue() == -1) {
				printf("게임을 종료합니다.....");
				return;
			}
			else {
				printf("Y/y N/n중에 입력해주세요!!!\n");
			}
		}

	}
	return 0;
}
int billboard(int arr[], int input[], int game_cnt) {
	static cnt_out3 = 0;
	int i;
	int result = 0;
	
	puts(" ");
	if (gameOut(arr, input) == 3) {
		cnt_out3++;
		printf("목숨을 잃으셨습니다!! 잘 생각해보세요\n");
	}
	if (cnt_out3 == 0 && gameStrike(arr, input) == 3)return 100; //퍼팩트 스코어
	if (cnt_out3 == 3)return -1;
	if (gameStrike(arr, input) == 3)return 1; //성공

	printf("\t\t\t\t\t 목숨 :");
	for (i = 0; i < 3 - cnt_out3; i++) {
		printf("♡");
	}
	puts("");
	puts("");
	printf("\t\t\t   %d회\n", game_cnt);
	result = gameBall(arr, input);
	printBoard(result);
	result = gameStrike(arr, input);
	printBoard(result);	
	result = gameOut(arr, input);
	printBoard(result);
	
	
	return 0;
}
int gameStrike(int arr[],int input[]) {
	int i;
	int cnt = 0;
	for (i = 0; i < 3; i++) {
		if (arr[i] == input[i])cnt++;
	}
	return cnt;
}
int gameBall(int arr[],int input[]) {
	int i, j;
	int cnt = 0;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (i != j && arr[i] == input[j])cnt++;
		}
	}
	return cnt;
}
int gameOut(int arr[], int input[]) {
	return 3 - gameStrike(arr, input) - gameBall(arr, input);
}
int gameContinue() {
	char ch = 0;

	printf("게임을 계속 하시겠습니까(Y/y, N/n)??  : ");
	scanf("%c", &ch);
	
	if (ch == 'Y' || ch == 'y')	return 1;

	else if (ch == 'N' || ch == 'n')return 0;
	else return -1;
	ch = 0;
}
int isitInteger(int number) {
	if (number <= 9 && number >= 1)return 1; //1~9사이 정수
	else {
		return 0;
	}
}
void printBoard(int result) {
	int i;
	static int cnt = 1;
	if (cnt%3 == 1) {
		printf("\n\t\t\t   ㅡㅡㅡㅡㅡㅡㅡㅡ\n");
		printf("\t\t\tB  |");
	}
	else if(cnt%3 == 2)
	{
		printf("\t\t\tS  |");
	}
	else if (cnt % 3 == 0) {
		printf("\t\t\tO  |");

	}
	for (i = 0; i < 3; i++) {
		if (result > 0) {
			printf(" ● |");
			result--;
		}
		else {
			printf("    |");
		}
	}
	printf("\n\t\t\t   ㅡㅡㅡㅡㅡㅡㅡㅡ");
	puts("");
	cnt++;
}
void Start() {
	printf("\t\t\t\t ---------------------------------------\n");
	printf("\t\t\t\t|\t\t야구 게임\t\t|\n");
	printf("\t\t\t\t ---------------------------------------\n");
}
