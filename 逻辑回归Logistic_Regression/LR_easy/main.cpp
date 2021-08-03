#include "LR.h"
int main()
{	
	string trainPath = "..\\example\\horseColic\\testSet_train.txt";
	string testPath = "..\\example\\horseColic\\testSet_test.txt";
	string testSavePath = "..\\example\\horseColic\\testSet_test_result.txt";
	Logistic loghorse;
	loghorse.dataLoad(loghorse.dataTrain, trainPath);//train
	loghorse.stoGradDescent(500, 0.001);
	loghorse.dataLoad(loghorse.dataTest, testPath);//test
	loghorse.logTest(testSavePath);
	return 0;
}
