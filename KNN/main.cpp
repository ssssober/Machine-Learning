#include "knn.h"
/*
*** Function:	KNN�㷨��c++ʵ��
*** Platform:   Windows10+VS2013
*** Time:		2021/07/07
*** Result:		��ͨ��
***
1����knn_traindata.txt�е�������Ϊѵ��ԭʼ���ݣ�����ʾ�� x y labelΪ����ֵx��y�����Ӧ�����ı�ǩ��0��1���ࣻ
2������testdata[x, y]��ÿһ��traindata[x, y]��ŷ�Ͼ��룬���д�С���������
3�����ݸ�����Kֵ��ȡ��ǰK����С�ľ�����У�
4������K�������Ӧ�ı�ǩ������ǩ��ռ�ݱ�������label��Ϊtestdata�������ࣻ
*/
int main()
{
	KNN knn_test;
	string traindata_path = "..\\example\\knn_traindata.txt";
	knn_test.Init(5, 5.0, 5.0, traindata_path);
	knn_test.GetDistanceAll();
	knn_test.SmallSort();
	knn_test.SeekProb();
	system("pause");
	return 0;
}

