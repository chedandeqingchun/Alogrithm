#include <iostream>
#include <vector>
using namespace std;


class CSort {

public:
	vector<int> m_vTarget;
public:
	CSort();
	~CSort();
	int QuickSort(vector<int> &vSource, int nLow, int nHigh);
	bool CheckResult(vector<int> &vSource, vector<int> &vTarget);
};

CSort::CSort() 
{
	m_vTarget.push_back(1);
	m_vTarget.push_back(3);
	m_vTarget.push_back(7);
	m_vTarget.push_back(35);
	m_vTarget.push_back(14);
	m_vTarget.push_back(18);
	m_vTarget.push_back(45);
	m_vTarget.push_back(1);
	m_vTarget.push_back(56);
	m_vTarget.push_back(13);	
}

CSort::~CSort() 
{
}


int CSort::QuickSort(vector<int> &vSource, int nLow, int nHigh) 
{
	int nKey, nLeft, nRight;
	nKey = vSource[nLow];
	nLeft = nLow;
	nRight = nHigh;

	if (nLeft >= nRight) {
		return 0;
	}

	while (nLeft < nRight) {
		while (nLeft < nRight && nKey <= vSource[nRight]) {/* the equility sign is very important */
			nRight--;
		}
		vSource[nLeft] = vSource[nRight];
		
		while (nLeft < nRight && nKey >= vSource[nLeft]) {
			nLeft++;
		}
		vSource[nRight] = vSource[nLeft];
	}

	vSource[nLeft] = nKey;
	QuickSort(vSource, nLow, nLeft - 1);
	QuickSort(vSource, nRight + 1, nHigh);
	return 1;
}

bool CSort::CheckResult(vector<int> &vSource, vector<int> &vTarget)
{
	return true;
}


int main(void)
{
	CSort iSort;
	/* quick sort */
	iSort.QuickSort(iSort.m_vTarget, 0, iSort.m_vTarget.size() - 1);
	return 1;
}