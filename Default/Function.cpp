#include "stdafx.h"
#include "Function.h"


float GetRandomNum(float fStartNum, float fEndNum)
{
	// �õ尪�� ��� ���� random_device ����.
	std::random_device rd;

	// random_device �� ���� ���� ���� ������ �ʱ�ȭ �Ѵ�.
	std::mt19937 gen(rd());

	// 0 ���� 99 ���� �յ��ϰ� ��Ÿ���� �������� �����ϱ� ���� �յ� ���� ����.
	std::uniform_real_distribution<float> dis(fStartNum, fEndNum);

	return dis(gen);
}

int GetRandomNum(int fStartNum, int fEndNum)
{
	// �õ尪�� ��� ���� random_device ����.
	std::random_device rd;

	// random_device �� ���� ���� ���� ������ �ʱ�ȭ �Ѵ�.
	std::mt19937 gen(rd());

	// 0 ���� 99 ���� �յ��ϰ� ��Ÿ���� �������� �����ϱ� ���� �յ� ���� ����.
	std::uniform_int_distribution<int> dis(fStartNum, fEndNum);

	return dis(gen);
}