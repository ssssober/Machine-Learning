#include "dist.h"

int main()
{
	DISTANCE dic;
	dic.Init();
	dic.CalEuclideanDis();
	dic.DisPlay();
	dic.CalManhattanDis();
	dic.DisPlay();
	dic.CalChebyshevDis();
	dic.DisPlay();
	system("pause");
	return 0;
}
