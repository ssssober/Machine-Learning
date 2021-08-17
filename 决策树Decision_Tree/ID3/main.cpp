#include "decision.h"
using namespace DECTREE;

int main()
{
	string path = "..\\example\\lenses.txt";
	ID3 test;
	test.init(path);
	test.calEntropy();
	test.functionTest();	
	return 0;
}
