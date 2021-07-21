#include "opencv2/opencv.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <conio.h>
#include <chrono>
using namespace std;
using namespace cv;


//功能：给定图像中的一组点(x, y) 两种方法进行拟合曲线，并将曲线画在图上

//2、多项式拟合+绘制		一组点进行拟合
void PointFittingXX(vector<Point>& in_point, int n, Mat & img, Mat & img_mask)
{
	//1、拟合散点多项式系数
	int size_p = in_point.size();
	//所求未知数个数
	int x_num = n + 1;
	//构造矩阵U和Y
	Mat mat_u(size_p, x_num, CV_64F);
	Mat mat_y(size_p, 1, CV_64F);

	for (int i = 0; i < mat_u.rows; ++i)
	for (int j = 0; j < mat_u.cols; ++j)
	{
		mat_u.at<double>(i, j) = pow(in_point[i].x, j);
	}

	for (int i = 0; i < mat_y.rows; ++i)
	{
		mat_y.at<double>(i, 0) = in_point[i].y;
	}

	//矩阵运算，获得系数矩阵K
	Mat mat_k(x_num, 1, CV_64F);
	mat_k = (mat_u.t()*mat_u).inv()*mat_u.t()*mat_y;

	cout << mat_k << endl;
	cout << "--------" << endl;

	//2、连接散点，绘制多项式拟合曲线
	// 按照x方向：从xmin到xmax逐点根据拟合出的公式计算新的y值，得到所有新的坐标点(x, y)，然后画出来
	vector<Point> xxPoints;

	for (int i = in_point[0].x; i < in_point[in_point.size() - 1].x; ++i)
	{
		Point2d ipt;
		ipt.x = i;
		ipt.y = 0;
		for (int j = 0; j < n + 1; ++j)
		{
			ipt.y += mat_k.at<double>(j, 0)*pow(i, j);
		}
		xxPoints.push_back(ipt);
	}

	cout << "xx.size(): " << xxPoints.size() << endl;
	//绘制方法1
	for (int i = 0; i < xxPoints.size(); i++)
	{
		circle(img, xxPoints[i], 1, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);
		circle(img_mask, xxPoints[i], 1, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);
	}
	//polylines(img, xxPoints, false, cv::Scalar(255, 0, 0), 1, 8, 0);//绘制方法2
	cout << "cricle finished!" << endl;

}

///4、最小二乘
void PolyCurveFit(Mat& img, vector<Point>& key_point, int n)
{
	//Number of key points
	int N = key_point.size();

	//构造矩阵X
	cv::Mat X = cv::Mat::zeros(n + 1, n + 1, CV_64FC1);
	for (int i = 0; i < n + 1; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			for (int k = 0; k < N; k++)
			{
				X.at<double>(i, j) = X.at<double>(i, j) +
					std::pow(key_point[k].x, i + j);
			}
		}
	}

	//构造矩阵Y
	cv::Mat Y = cv::Mat::zeros(n + 1, 1, CV_64FC1);
	for (int i = 0; i < n + 1; i++)
	{
		for (int k = 0; k < N; k++)
		{
			Y.at<double>(i, 0) = Y.at<double>(i, 0) +
				std::pow(key_point[k].x, i) * key_point[k].y;
		}
	}

	Mat A = cv::Mat::zeros(n + 1, 1, CV_64FC1);
	//求解矩阵A
	cv::solve(X, Y, A, cv::DECOMP_LU);

	// 绘制
	std::vector<cv::Point> points_fitted;

	for (int i = key_point[0].x; i < key_point[key_point.size() - 1].x; ++i)
	{
		Point2d ipt;
		ipt.x = i;
		ipt.y = 0;
		for (int j = 0; j < n + 1; ++j)
		{
			ipt.y += A.at<double>(j, 0)*pow(i, j);
		}
		points_fitted.push_back(ipt);
	}

	//绘制方法1
	for (int i = 0; i < points_fitted.size(); i++)
		circle(img, points_fitted[i], 1, Scalar(255, 0, 0, 0), CV_FILLED, CV_AA, 0);
	//绘制方法2
	//cv::polylines(img, points_fitted, false, cv::Scalar(255, 0, 0), 1, 8, 0);
}





