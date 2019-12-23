#include "head.h"
//С����ƻ��
void program1() {
	int treeNum = 0;
	int opNum = 0;
	cin >> treeNum >>opNum;
	long** matrix = new long* [treeNum];
	for (int i = 0; i < treeNum; i++)
	{
		matrix[i] = new long[opNum + 1];
	}

	int totalSum = 0;
	int cutNum = 0;
	int maxCutNum = -1;
	int maxIndex = -1;
	int P = 0;
	for (int i = 0; i < treeNum; i++)
	{
		cin >> matrix[i][0];
		int totalNum = matrix[i][0];
		int thisCutNum = 0;
		for (int j = 0; j < opNum; j++)
		{
			cin >> matrix[i][j + 1];
			totalNum += matrix[i][j + 1];
			thisCutNum -= matrix[i][j + 1];
		}
		totalSum += totalNum;
		if (thisCutNum > maxCutNum) {
			maxCutNum = thisCutNum;
			maxIndex = i;
		}
		cutNum = thisCutNum;
	}
	cout << totalSum << " " << maxIndex+1 << " " << maxCutNum;
	delete []matrix;
}

//С����ƻ����
void program2() {
	int treeNum = 0;
	cin >> treeNum;
	
	//�������µĹ���
	int leftTotalNum = 0;
	//�����
	int dropNum = 0;
	//3���������
	int groupNum = 0;
	//�����������������ı��������������
	int dropArray[1000] = {0};

	//��������
	for (int i = 0; i < treeNum; i++)
	{
		dropArray[i] = 0;
		//���в�����
		int num = 0;
		cin >> num;

		//����1��ƻ����ʼ����
		int thisBegin = 0;
		cin >> thisBegin;

		//���ƻ����ǰ��ʣ����
		int previous = thisBegin;
		for (int j = 1; j < num; j++)
		{
			//�µ�������
			int newNum = 0;
			cin >> newNum;

			//�������ʾ����
			if (newNum>0) {
				//С����ǰ������ʾ���
				if (newNum < previous) {
					//��ֹ���ظ�������ظ�����
					dropArray[i] = 1;
					previous = newNum;
				}
			}
			//С�����ʾ���
			else {
				previous += newNum;
			}
		}
		//һ�����봦����Ͻ�ʣ������鲢
		leftTotalNum += previous;
	}

	//���ñ���������������������
	int flag = 0;
	//����ָ��
	int cursor = 0;
	//treeNum+2��ʾ�����ǻ�״���б߽�����
	for (int i = 0; i < treeNum+2; i++)
	{
		if (dropArray[cursor] == 1) {
			flag++;
			//�ڴ˴���������������
			if (i<treeNum) {
				dropNum++;
			}
		}
		//��δ���������ʾ�����¼����������
		else {
			flag = 0;
		}
		//3�����������������
		if (flag >=3) {
			groupNum++;
		}
		cursor++;
		//�߽������Ĵ�����Ҫָ���β���������ײ�
		cursor %= treeNum;
	}
	cout << leftTotalNum << " " << dropNum << " " << groupNum;

}

void program3() {

}

void program4() {

}

void program5() {

}

int main() {

	program2();
	return 0;
}