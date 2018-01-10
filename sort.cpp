#include <iostream>
#include <vector>
using namespace std;

#define RESULT_OK 1
#define RESULT_FAIL 2
#define INDEX_WRONG 3
#define HEAP_EMPTY 4

class CSort {
public:
	vector<int> m_vTarget;
	int m_gHeapSort[10];
	int m_nHeapLen;

private:
	int __SmallHeapAdjustUp(int nGrid[], int nEleIndex);
	int __SmallHeapAdjustDown(int nGrid[], int nEleIndex, int nSize); 

public:
	CSort();
	~CSort();
	int QuickSort(vector<int> &vSource, int nLow, int nHigh);
	int MakeHeap(int nGrid[], int nSize);
	int SortHeap(int nGrid[], int &nSize);
    int RadixSort(int nGrid[], int nSize);
	bool CheckResult(vector<int> &vSource, vector<int> &vTarget);
};


int CSort::RadixSort(int nGrid[], int nSize) {


    return 0;
}



CSort::CSort() 
{
	/* quicksort initial */
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

	/* heap initial */
	m_gHeapSort[0] = 5;
	m_gHeapSort[1] = 7;
	m_gHeapSort[2] = 1;
	m_gHeapSort[3] = 9;
	m_gHeapSort[4] = 27;
	m_gHeapSort[5] = 35;
	m_gHeapSort[6] = 33;
	m_gHeapSort[7] = 12;
	m_gHeapSort[8] = 8;
	m_gHeapSort[9] = 5;
	
	m_nHeapLen = 10;
	MakeHeap(m_gHeapSort, m_nHeapLen);
}

CSort::~CSort() 
{
}

/*Summary: adjust element from bottom to top
 *parameters:
 *  grid:array used to store grid
 *  nEleIndex:element's index from which adjust begin
 *  nSize:heap's length 
 *Return: RESULT_OK is no error happens in process
 */
int CSort::__SmallHeapAdjustUp(int gGrid[], int nEleIndex)
{
	int nFather, nLittleChild, nMidData;

	nLittleChild = nEleIndex;
	nFather = (nEleIndex -1) / 2;

	nMidData = gGrid[nEleIndex];

	while (nFather >= 0 && nLittleChild != 0) {/* nLittleChild element is not root node */
		

		if (gGrid[nFather] < nMidData) {/* no need to adjust */
			break;
		}
		
		if (gGrid[nFather] > gGrid[nLittleChild]) {/* change the ele between father and child */
			gGrid[nLittleChild] = gGrid[nFather];
			nLittleChild = nFather;
			nFather = (nLittleChild - 1) / 2;
		}
	}
	gGrid[nLittleChild] = nMidData;

	return RESULT_OK;
}


/*Summary: adjust element from top to bottom
 *parameters:
 *  grid:array used to store grid
 *  nEleIndex:element's index from which adjust begin
 *  nSize:heap's length 
 *Return: RESULT_OK is no error happens in process
 */
int CSort::__SmallHeapAdjustDown(int gGrid[], int nEleIndex, int nSize)
{
	int nMidData, nLittleChild, nFather;

	nMidData = gGrid[nEleIndex];

	nFather = nEleIndex;
	nLittleChild = nEleIndex * 2 + 1;


	while (nLittleChild < nSize) {
	
		if (nLittleChild + 1 < nSize &&  gGrid[nLittleChild] > gGrid[nLittleChild + 1]) {
			nLittleChild++;
		}
		

		if (gGrid[nLittleChild] > nMidData) {/* meet small heap requirements, no need to adjust */
			break;
		}

		gGrid[nFather] = gGrid[nLittleChild];
		nFather = nLittleChild;
		nLittleChild = nFather * 2 + 1;
	}

	gGrid[nFather] = nMidData;
	return RESULT_OK;
}

int CSort::MakeHeap(int nGrid[], int nSize)
{
	int nIndex;

	for (nIndex = (nSize / 2) - 1; nIndex >= 0; nIndex--) {
		__SmallHeapAdjustUp(nGrid, nIndex);	
	}
	return RESULT_OK;
}

int CSort::SortHeap(int nGrid[], int &nSize)
{

	if (nSize == 0) {
		return HEAP_EMPTY;
	}

	nGrid[0] = nGrid[nSize - 1];
	nSize--;
	
	__SmallHeapAdjustDown(nGrid, 0, nSize);
	
	return RESULT_OK;
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
	return RESULT_OK;
}

bool CSort::CheckResult(vector<int> &vSource, vector<int> &vTarget)
{
	return true;
}


int main(void)
{
	int nIndex;
	CSort iSort;
	/* quick sort */
	iSort.QuickSort(iSort.m_vTarget, 0, iSort.m_vTarget.size() - 1);
	/* heap sort */
	cout << "heap sort begin" << endl;
	for (nIndex = iSort.m_nHeapLen - 1; nIndex >=0; nIndex--) {
		cout << iSort.m_gHeapSort[0] << '\t';
		iSort.SortHeap(iSort.m_gHeapSort, iSort.m_nHeapLen);
	} 
	iSort.SortHeap(iSort.m_gHeapSort, iSort.m_nHeapLen);
	return RESULT_OK;
}
