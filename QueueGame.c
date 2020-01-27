#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

#define QUEUE_SIZE 100 /*�L���[�̑傫��*/

/*�z��ŃL���[��\������*/
int front, rear;
int queue[QUEUE_SIZE];


void error(char* s);/*�G���[���b�Z�[�W���v�����g����exit����*/
void init_queue();/*queue.c �z��ŃL���[�����*/
void enqueue(int x);/*�L���[�Ƀf�[�^������*/
int dequeue();/*�L���[����f�[�^�����o��*/
int empty_queue();/*�L���[���󂩂ǂ����𒲂ׂ�*//*��Ȃ�1�A��łȂ����0��Ԃ�*/
int next(int val);/*�L���[��z��ŕ\������Ƃ��A���݂̎��̔z���index��Ԃ�*/
void Ready();//�������ł��Ă��邩�ǂ�����₤�֐�
int Game();
bool PlayAgain();//������x�T�����s�����ǂ�����₤�֐�
int CheckAnswer();//���͂�Yes��No�Ȃ̂��A�܂��͂���ȊO�Ȃ̂����𔻒f����֐�

void main() {
	printf("�悤�����A���X�g�����Q�[���ցI");
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
		printf("�r��p�ӂ��܂����B\n");
		///////////////////////////
		Out = Game();
		printf("���Ȃ��͍Ō�̈�{���Ƃ��Ă��܂��܂����I���Ȃ��͕����ł��I\n");
		PlayLoop = PlayAgain();//������x�s�����ǂ���
	}
}


void Ready() {//�������ł��Ă��邩�ǂ�����₤�֐�
	printf("�����͂ł��Ă��܂���?---Yes/No�F");
	if (CheckAnswer() == 1) {//Yes�̂Ƃ�
		printf("�Q�[�������y���݂��������B\n");
	}
	else {//No�̂Ƃ�
		printf("���悤�Ȃ�I\n");
		exit(1);
	}
}



/*�G���[���b�Z�[�W���v�����g����exit����*/
void error(char* s) {
	fprintf(stderr, s);
	exit(1);
}

/*�L���[�̏�����������*/
void init_queue() {
	/*�ۑ�͂���������*/
	front = 0;
	rear = 0;

}

/*�L���[�Ƀf�[�^������*/
void enqueue(int x) {
	/*�ۑ�͂���������*/
	queue[rear] = x;
	rear = next(rear);
	if (rear == QUEUE_SIZE) {
		error("����ȏ�X�^�b�N�ɐςނ��Ƃ��ł��܂���B");
	}
}

/*�L���[����f�[�^�����o��*/
int dequeue() {
	/*�ۑ�͂���������*/
	int pop;
	pop = queue[front];
	front = next(front);
	if (empty_queue() == 1) {
		return -1;
	}
	return pop;
}
/*�L���[���󂩂ǂ����𒲂ׂ�*/
/*��Ȃ�1�A��łȂ����0��Ԃ�*/
int empty_queue() {
	/*�ۑ�͂���������*/
	if (front == rear) {
		return 1;
	}
	else
		return 0;
}

/*�L���[��z��ŕ\������Ƃ��A���݂̎��̔z���index��Ԃ�*/
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
			printf("�v���C���[A�̔Ԃł��B\n");
			printf("�r�����{�Ƃ�܂����H(1-10�{�܂ł������܂���)\n");
			scanf("%d", &num);
		}
		for (i = 0; i < num; i++) {
			value = dequeue();
			if (value == -1) {
				return 1;
			}
			printf("%d�{��\n", value + 1);
		}
		printf("�����ł�\n");
		num = 0;
		while (num <= 0 || 10 < num) {
			printf("�v���C���[B�̔Ԃł��B\n");
			printf("�r�����{�Ƃ�܂����H(1-10�{�܂ł������܂���)\n");
			scanf("%d", &num);
		}
		for (i = 0; i < num; i++) {
			value = dequeue();
			if (value == -1) {
				return 1;
			}
			printf("%d�{��\n", value + 1);
		}
		num = 0;
		printf("�����ł�\n");
	}
}

bool PlayAgain() {
	int Answer;
	printf("������x�����܂����H---Yes/No�F");
	Answer = CheckAnswer();
	if (Answer == 0) {//No�̂Ƃ�
		printf("���悤�Ȃ�I\n");
		exit(1);
		return false;
	}
	else {//Yes�̂Ƃ�
		return true;
	}
}

int CheckAnswer() {//���͂�yes��no���A����ȊO���𔻒肷��
	char* s[3];
	scanf("%s", &s);
	if (strcmp(s, "YES") == 0 || strcmp(s, "Yes") == 0 || strcmp(s, "yes") == 0) {//yes�̎�
		return 1;
	}
	else if (strcmp(s, "NO") == 0 || strcmp(s, "No") == 0 || strcmp(s, "no") == 0) {//no�̎�
		return 0;
	}
	else {//����ȊO
		error("Yes��No�œ����Ă��������B");
	}
}