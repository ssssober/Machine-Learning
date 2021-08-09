#include "kmeans.h"

int main()
{
	string path = "..\\example\\testSet.txt";
	string save_path = "..\\example\\testSet_Result.txt";
	int k = 4; //预设：分为k个簇
	KMEAN means;
	means.init(path, k);
	means.kmeansCluster(save_path);
	return 0;
}
