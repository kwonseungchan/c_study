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
	int arr[3] = { 0 }; //�������� ���� ��
	int input[3] = { 0 }; //�ִ� ��
	int i,j;
	int overlap;		//�ߺ�
	int game_cnt = 1;	//���� ~ȸ
	int result;
	int isit = 0; //�Է¹������� 1~9������ �������� �Ǵ�

	
	srand((unsigned int)time(NULL));

	while (1) {
		Start();
		//�ߺ�ó��
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
		//// ���� 
		//printf(" ������ : ");
		//for (i = 0; i < 3; i++) {
		//	printf("%d ", arr[i]);
		//}
		puts("");

		while (1) {
			if (game_cnt == 10) {
				printf("���尡 ��� ����Ǿ����ϴ� .... �����ϴ�.\n");
				break;
			}
			
			printf(" ���� 3���� �Է����ּ��� : ");
			scanf("%d %d %d", &input[0], &input[1], &input[2]);
			
			for(i = 0; i <3; i++){
				isit += isitInteger(input[i]);
			}
			if (isit != 3) {
				printf("1~9������ ���� �Է��ϼž��մϴ�!! �ٽ� �Է����ּ���\n");
			
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
				printf("�¸��ϼ̽��ϴ�!!!!\n");
				break;
			}
			else if (result == 100) {
				printf("����� �ϳ��� �����ʰ� �¸��ϼ̽��ϴ� �����մϴ�!!!\n");
				break;
			}
			else if (result == -1) {
				printf("3���� �ƿ��� 3�� �ϼ̽��ϴ�... �����ϴ�.\n");
				break;
			}
			game_cnt++;
			
		}
		while (1) {
			if (gameContinue()) {
				printf("������ ����մϴ�!!!\n");
				game_cnt = 0;
				system("cls");
				break;
			}
			else if (gameContinue() == -1) {
				printf("������ �����մϴ�.....");
				return;
			}
			else {
				printf("Y/y N/n�߿� �Է����ּ���!!!\n");
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
		printf("����� �����̽��ϴ�!! �� �����غ�����\n");
	}
	if (cnt_out3 == 0 && gameStrike(arr, input) == 3)return 100; //����Ʈ ���ھ�
	if (cnt_out3 == 3)return -1;
	if (gameStrike(arr, input) == 3)return 1; //����

	printf("\t\t\t\t\t ��� :");
	for (i = 0; i < 3 - cnt_out3; i++) {
		printf("��");
	}
	puts("");
	puts("");
	printf("\t\t\t   %dȸ\n", game_cnt);
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

	printf("������ ��� �Ͻðڽ��ϱ�(Y/y, N/n)??  : ");
	scanf("%c", &ch);
	
	if (ch == 'Y' || ch == 'y')	return 1;

	else if (ch == 'N' || ch == 'n')return 0;
	else return -1;
	ch = 0;
}
int isitInteger(int number) {
	if (number <= 9 && number >= 1)return 1; //1~9���� ����
	else {
		return 0;
	}
}
void printBoard(int result) {
	int i;
	static int cnt = 1;
	if (cnt%3 == 1) {
		printf("\n\t\t\t   �ѤѤѤѤѤѤѤ�\n");
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
			printf(" �� |");
			result--;
		}
		else {
			printf("    |");
		}
	}
	printf("\n\t\t\t   �ѤѤѤѤѤѤѤ�");
	puts("");
	cnt++;
}
void Start() {
	printf("\t\t\t\t ---------------------------------------\n");
	printf("\t\t\t\t|\t\t�߱� ����\t\t|\n");
	printf("\t\t\t\t ---------------------------------------\n");
}
