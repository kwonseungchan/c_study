#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#pragma warning (disable : 4996)

#define TEL_SIZE 100
#define NAME_LEN 20
#define PHONE_LEN 20

typedef struct {
	int no;
	char name[NAME_LEN];	//이름
	char phone[PHONE_LEN];	//전화번호

}TEL;
void modify_number(TEL*, int);
void modify_name(TEL*,int);
void file_open(TEL*, int*);
void add(TEL *, int *);
void showMenu();
void printList(TEL *, int);
void change(TEL*, int);
void removeInfor(TEL*, int*);
void sort(TEL*, int);
void file_save(TEL*, int);


int main() {
	TEL tel[TEL_SIZE];
	int choice;
	int index = 0;		//저장하려는 위치

	while (1) {
		showMenu();
		scanf("%d", &choice);
		
		while (getchar() != '\n');

		switch (choice) {
		case 1:
			add(tel, &index);
			break;
		case 2:
			printList(tel, index);
			break;
		case 3:
			change(tel, index);
			break;
		case 4:
			removeInfor(tel, &index);
			break;
		case 5:
			sort(tel, index);
			break;
		case 6:
			break;
		case 7:
			file_save(tel, index);
			break;
		case 8:
			file_open(tel, &index);
			break;
		case 0:
			printf("\n\n\t\t프로그램을 종료합니다\n");
			exit(0);
			break;
		}
		
		printf("계속 하시려면 아무키나 눌러주세요!!!!! \n");
		getch();
		system("cls");
	}
	return 0;
}
void file_save(TEL* tel, int index) {
	FILE* fp;
	int i;
	char file_name[80];

	system("cls");
	printf("저장 파일명 입력 : ");
	gets(file_name, 79);
	strcat(file_name, ".txt");

	fp = fopen(file_name, "w");
	if (fp == NULL) {
		printf("file open fail\n");
		exit(-1);
	}
	
	for (i = 0; i < index; i++) {
		fprintf(fp, "%d %s %s\n", tel[i].no, tel[i].name, tel[i].phone);
	}

	printf("\n\n\t\t %s.txt파일에 저장 완료!!!\n", file_name);

	fclose(fp);

}

void sort(TEL* tel, int index) {
	int i = 0;
	int j;
	

	char temp;
	
	for (i = 0; i < index - 1; i++) {
		for (j = i; j < index; j++) {
			if (tel[i].name[0] < tel[j].name[0]) {
				temp = tel[i].name[0];
				tel[i].name[0] = tel[j].name[0];
				tel[j].name[0] = temp;
			}
		}
	}


}
void removeInfor(TEL* tel, int* index) {
	int i=0;
	int j = 1;
	int num;
	char ch;
	printList(tel, *index);
	puts("");
	while (1) {
		printf("진짜 삭제하실건가요?\n (Y/y는 삭제 N/n는 메뉴로 이동) : ");
		scanf("%c", &ch);
		
		if (ch == 'Y' || ch == 'y') {
			break;
		}
		else if (ch == 'N' || ch == 'n') {
			return;
		}
		else {
			printf("Y/y N/n 중에 입력해주세요!!!");
			continue;
		}
		while (getchar() != '\n');
	}
	puts("");
	while (getchar() != '\n');
	printf("삭제하실 번호를 입력해주세요 : ");
	scanf("%d", &num);

	

	if (index == 1) {
		tel[i].no = NULL;
		strcpy(tel[i].name, "");
		strcpy(tel[i].phone, "");
	}
	else if (num == index) {
		tel[i].no = NULL;
		strcpy(tel[i].name, "");
		strcpy(tel[i].phone, "");
	}
	j = num + 1;
	else {
		for (i = num; i < index - 1; i++) {
			tel[i].no = tel[j].no;
			strcpy(tel[i].name, tel[j].name);
			strcpy(tel[i].phone, tel[j].phone);
			j++;
		}
	}

	

	
	(*index)--;


}
void file_open(TEL* tel, int* index) {
	FILE* fp;
	char ch;
	if (*index != 0) {
		do {
			printf("\n\n\t\t저장되지 않은 데이터는 모두 사라집니다.\n\t\t계속 하시겠습니까???(Y/N)\n");
			ch = getchar();
			while (getchar() != '\n');
			if (ch == "N" || ch == 'n')
				return;
		} while (ch != 'Y' || ch != 'y' || ch != 'N' || ch != 'n');
		*index = 0;
	}

	fp = fopen("tel.txt", "r");


	if (fp == NULL) {
		printf("\n\n\t\tfile open\n");
		return;
		//exit(-1);
	}
	while (fscanf(fp, "%d %s %s", &tel[*index].no, tel[*index].name, tel[*index].phone) != EOF) {
		++(*index);
	}

	fclose(fp);
}
void change(TEL* tel, int index) {
	int num;
	int ask;
	system("cls");
	printList(tel, index);
	puts(" ");
	printf("\n\n\t\t****수정할 번호를 입력해주세요****\n");
	printf("\t\t1. 번지    2. 이름     3.전화번호 4. 이전 메뉴\n");
	scanf("%d", &ask);
	printf("수정할 번호를 입력해주세요 !!!\n");
	
	while (getchar() != '\n');

	switch (ask) {
	case 1:
		modify_number(tel, index);
		break;
	case 2:
		modify_name(tel, index);
		break;
	case 3:
		break;
	case 4:
		return;
		break;
	}

	
	
}
void modify_number(TEL* tel, int index) {
	int num;

	scanf("%d", &num);

	while (getchar() != '\n');

	printf("이름 : ");
	gets(tel[num - 1].name, NAME_LEN - 1);

	puts("");

	printf("전화번호 : ");
	gets(tel[num - 1].phone, PHONE_LEN - 1);

	puts("");
	printf("수정 완료했습니다\n");
}
void modify_name(TEL* tel, int index) {
	char sech_name[20];
	char modify_names[20];
	int i = 0;

	printf("수정할 이름 검색 : ");
	gets_s(sech_name, 19);

	for (i = 0; i < index; i++) {
		if (strcmp(sech_name, tel[i].name) == 0) {
			printf("수정할 이름 입력 : ");
			gets_s(modify_names, 19);
			strcpy(tel[i].name, modify_names);
			printf("%s을 %s로 바꿨습니다!\n", sech_name, modify_names);https://github.com/kwonseungchan/c_study
			break;
		}
	}


}
void printList(TEL* tel, int index) {
	int i;
	if (index == 0) {
		printf("\n\n\t\t저장 데이터가 없습니다.\n\t\t등록 후 다시 이용해주세요.\n");
	}
	printf("\t\t고객번호\t이름\t\t전화번호\n");
	printf("-------------------------------------------------------------------------\n");
	for (i = 0; i < index; i++) {
		printf("\t\t   %03d\t\t%s\t\t%s\n", tel[i].no, tel[i].name, tel[i].phone);
	}
}

void showMenu() {
	system("cls");
	printf("전화번호 관리 프로그램\n\n");
	printf("1. 등록\n");
	printf("2. 리스트 출력\n");
	printf("3. 수정\n");
	printf("4. 삭제\n");
	printf("5. 정렬\n");
	printf("6. 검색\n");
	printf("7. 파일저장\n");
	printf("8. 파일열기\n");
	printf("0. 프로그램 종료\n");
	printf("메뉴선택 : [ ]\b\b");
}
void add(TEL* tel, int *pIndex) {
	
	if (*pIndex == TEL_SIZE) {
		printf("저장 공간이 꽉찼습니다.\n데이터 삭제 후 이용 하세요\n");
		return;
	}

	system("cls");
	
	tel[*pIndex].no = *pIndex + 1;
	
	printf("이름 : ");
	gets(tel[*pIndex].name, NAME_LEN - 1);

	printf("전화번호 : ");
	gets(tel[*pIndex].phone, PHONE_LEN - 1);

	printf("\n\n\t\t %d번지 저장 완료!!!\n", *pIndex);

	++(*pIndex);
	getch();
}
