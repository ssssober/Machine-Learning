#include "LR.h"

//载入数据
void Logistic::dataLoad(vector<point>& vec, string filepath)
{
	// 载入traindata.txt
	std::ifstream list_path(filepath);
	std::vector<std::string> fileNames;
	std::string stemp;
	while (getline(list_path, stemp))
	{
		fileNames.push_back(stemp);
	}
	
	for (int i = 0; i < fileNames.size(); i++)
	{
		const char* sep = ",";
		int posFirst = fileNames[i].find(sep); 
		int posLast = fileNames[i].find_last_of(sep);
		//分别取出坐标x,y和label
		string xx = fileNames[i].substr(0, posFirst);
		string yy = fileNames[i].substr(posFirst + 1, posLast);
		string lab = fileNames[i].substr(posLast + 1, fileNames[i].size());
		int labint = atoi(lab.c_str());//atof
		point c;
		c.x0 = 1.0;
		c.x1 = stod(xx);
		c.x2 = stod(yy);
		c.label = labint;
		vec.push_back(c);
	}
}

//方法1：随机梯度下降 ---> 一次取一组数据
void Logistic::stoGradDescent(int iters, float steps)
{
	weights = { 1.0, 1.0, 1.0 };//权重初始化为1.0，待求参数w个数=特征x数目+1
	
	for (int n = 0; n < iters; n++)//一次迭代将所有组数据取完
	{
		cout <<"迭代次数：" << n << "  参数w：" << "w0: " << weights[0] << "  w1: " << weights[1] << "  w2: " << weights[2] << endl;
		for (int i = 0; i < dataTrain.size(); i++)//一次取一组，更新一次参数w
		{

			//参数w更新：需要一次更新w0,w1,w2三个参数
			float z = weights[0] * dataTrain[i].x0 + weights[1] * dataTrain[i].x1 + weights[2] * dataTrain[i].x2;//sigmoid函数的输入
			float p = sigmoid(z); // sigmoid预测输出y
			vector<float> w_delt;//梯度：对w求偏导 
			//偏导计算
			w_delt.push_back(-(dataTrain[i].label - p)*dataTrain[i].x0);
			w_delt.push_back(-(dataTrain[i].label - p)*dataTrain[i].x1);
			w_delt.push_back(-(dataTrain[i].label - p)*dataTrain[i].x2);
			add_vector(weights, w_delt, steps);//更新参数w0, w1, w2
		}
	}
}

//sigmoid   --->单点计算
float Logistic::sigmoid(float wx)
{
	return 1 / (1 + exp(-wx));
}


//一维向量对应位置加法运算
void Logistic::add_vector(vector<float> &vec_w, vector<float>& vec_wdelt,float steps)
{
	for (int i = 0; i < weights.size(); i++)
	{
		vec_wdelt[i] *= -steps; //w_delt乘以步长
		vec_w[i] += vec_wdelt[i];//向量对应位加法
	}
}

//回归曲线
void Logistic::plotFilters()
{
	
}

//回归测试
void Logistic::logTest(string savepath)
{
	ofstream fout(savepath);
	fout << "特征X1，" << "特征X2，" << "原始标签，" << "预测概率P," << "预测标签" << endl;
	int trueNum = 0;
	for (int i = 0; i < dataTest.size(); i++)
	{
		float z = weights[0] * dataTest[i].x0 + weights[1] * dataTest[i].x1 + weights[2] * dataTest[i].x2;//sigmoid函数的输入
		float p = sigmoid(z); // sigmoid预测输出y
		int prediction = p > 0.5 ? 1 : 0;
		if (prediction == dataTest[i].label)
		{
			trueNum++;
		}
		//写入txt存入本地
		fout << dataTest[i].x1 << "," << dataTest[i].x2 << "," << dataTest[i].label << "," << p << "," << prediction << endl;

	}
	cout << "正确预测率： " << 1.0*trueNum / dataTest.size()  << endl;
}
