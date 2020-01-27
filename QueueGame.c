#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

#define QUEUE_SIZE 100 /*キューの大きさ*/

/*配列でキューを表現する*/
int front, rear;
int queue[QUEUE_SIZE];


void error(char* s);/*エラーメッセージをプリントしてexitする*/
void init_queue();/*queue.c 配列でキューを作る*/
void enqueue(int x);/*キューにデータを入れる*/
int dequeue();/*キューからデータを取り出す*/
int empty_queue();/*キューが空かどうかを調べる*//*空なら1、空でなければ0を返す*/
int next(int val);/*キューを配列で表現するとき、現在の次の配列のindexを返す*/
void Ready();//準備ができているかどうかを問う関数
int Game();
bool PlayAgain();//もう一度探索を行うかどうかを問う関数
int CheckAnswer();//入力がYesかNoなのか、またはそれ以外なのかをを判断する関数

void main() {
	printf("ようこそ、ラストワンゲームへ！");
	bool PlayLoop = true;
	Ready();
	
	init_queue();
	int Out;
	while (PlayLoop == true) {
		////////////////////////////
		srand((unsigned)time(NULL));
		int Random = rand() % 90 + 10;
		
		int i;
		for (i = 0; i < Random; i++) {
			enqueue(i);
		}
		printf("瓶を用意しました。\n");
		///////////////////////////
		Out = Game();
		printf("あなたは最後の一本をとってしまいました！あなたは負けです！\n");
		PlayLoop = PlayAgain();//もう一度行うかどうか
	}
}


void Ready() {//準備ができているかどうかを問う関数
	printf("準備はできていますか?---Yes/No：");
	if (CheckAnswer() == 1) {//Yesのとき
		printf("ゲームをお楽しみください。\n");
	}
	else {//Noのとき
		printf("さようなら！\n");
		exit(1);
	}
}



/*エラーメッセージをプリントしてexitする*/
void error(char* s) {
	fprintf(stderr, s);
	exit(1);
}

/*キューの初期化をする*/
void init_queue() {
	/*課題はここを書く*/
	front = 0;
	rear = 0;

}

/*キューにデータを入れる*/
void enqueue(int x) {
	/*課題はここを書く*/
	queue[rear] = x;
	rear = next(rear);
	if (rear == QUEUE_SIZE) {
		error("これ以上スタックに積むことができません。");
	}
}

/*キューからデータを取り出す*/
int dequeue() {
	/*課題はここを書く*/
	int pop;
	pop = queue[front];
	front = next(front);
	if (empty_queue() == 1) {
		return -1;
	}
	return pop;
}
/*キューが空かどうかを調べる*/
/*空なら1、空でなければ0を返す*/
int empty_queue() {
	/*課題はここを書く*/
	if (front == rear) {
		return 1;
	}
	else
		return 0;
}

/*キューを配列で表現するとき、現在の次の配列のindexを返す*/
int next(int val) {
	int next;
	next = (val + 1) % QUEUE_SIZE;
	return(next);
}

int Game() {
	int num=0;
	int i;
	int value;
	bool loop = true;
	while (loop == true) {
		while (num<=0 || 10<num ) {
			printf("プレイヤーAの番です。\n");
			printf("瓶を何本とりますか？(1-10本までしか取れません)\n");
			scanf("%d", &num);
		}
		for (i = 0; i < num; i++) {
			value = dequeue();
			if (value == -1) {
				return 1;
			}
			printf("%d本目\n", value + 1);
		}
		printf("成功です\n");
		num = 0;
		while (num <= 0 || 10 < num) {
			printf("プレイヤーBの番です。\n");
			printf("瓶を何本とりますか？(1-10本までしか取れません)\n");
			scanf("%d", &num);
		}
		for (i = 0; i < num; i++) {
			value = dequeue();
			if (value == -1) {
				return 1;
			}
			printf("%d本目\n", value + 1);
		}
		num = 0;
		printf("成功です\n");
	}
}

bool PlayAgain() {
	int Answer;
	printf("もう一度続けますか？---Yes/No：");
	Answer = CheckAnswer();
	if (Answer == 0) {//Noのとき
		printf("さようなら！\n");
		exit(1);
		return false;
	}
	else {//Yesのとき
		return true;
	}
}

int CheckAnswer() {//入力がyesかnoか、それ以外かを判定する
	char* s[3];
	scanf("%s", &s);
	if (strcmp(s, "YES") == 0 || strcmp(s, "Yes") == 0 || strcmp(s, "yes") == 0) {//yesの時
		return 1;
	}
	else if (strcmp(s, "NO") == 0 || strcmp(s, "No") == 0 || strcmp(s, "no") == 0) {//noの時
		return 0;
	}
	else {//それ以外
		error("YesかNoで答えてください。");
	}
}