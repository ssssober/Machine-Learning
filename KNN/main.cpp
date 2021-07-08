#include "knn.h"
/*
*** Function:	KNN算法的c++实现
*** Platform:   Windows10+VS2013
*** Time:		2021/07/07
*** Result:		已通过
***
1、以knn_traindata.txt中的数据作为训练原始数据，样本示例 x y label为坐标值x和y，其对应所述的标签分0和1两类；
2、计算testdata[x, y]和每一组traindata[x, y]的欧氏距离，进行从小到大的排序；
3、根据给定的K值，取出前K个最小的距离进行；
4、根据K个距离对应的标签，将标签中占据比例最大的label作为testdata所属的类；
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

