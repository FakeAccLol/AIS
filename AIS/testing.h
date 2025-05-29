#pragma once
#include "AISbase.h"
#include "AISmod.h"

namespace testing
{
	struct Return {
		// ������� ������� �������� �����������
		vector<double> timeStamps;
		// ������� ��� ���������� ������� �������
		vector<size_t> calls;
		// ��� ������ ����������� �� ��� ���������� ������� ������� 
		vector<vector<pair<int, double>>> info;
	};

	Return testShrinkRate(std::shared_ptr<AIS> method);
	Return testPopulationSize(std::shared_ptr<AIS> method);
	Return testDimSize(std::shared_ptr<AIS> method);
	Return testMutationRate(std::shared_ptr<AIS> method);
	Return testGenAmount(std::shared_ptr<AIS> method);
};

