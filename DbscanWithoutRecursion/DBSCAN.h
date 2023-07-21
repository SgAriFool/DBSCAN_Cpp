#pragma once
#ifndef DBSCAN_H
#define DBSCAN_H

#include <iostream>
#include <math.h>
#include <vector>
#include <stack>

static int S_temp = 0;

enum  POINT_TYPE
{
	POINT_DEFAULT,		// δ����
	POINT_CORE,			// ���Ķ���
	POINT_BOUNDARY,		// �߽����
	POINT_NOISE			// ����
};
enum POINT_CALCULATE
{
	CALCULATE_NO,		//δ������
	CALCULATE_YES		//�ѱ�����
};
enum POINT_VISIT
{
	VISIT_NO,			// δ������
	VISIT_YES			// �ѱ�����
};


/*
DbscanPoint��ʼ����Ҫ����һ��std::vector<double>���͵�����
���￼�ǵ�Point����������һ����ά�ĵ㣬����������ά��
һ��������ά�ȵ����갴��һ��˳������std::vector<double>��
*/
class DbscanPoint
{
	//friend double CalculateDistance(DbscanPoint* point1, DbscanPoint* point2);
	//friend void Dbscan(DbscanPoint* dbscan_point_ptr, int cluster_current);
	//friend void DBSCAN(std::vector<DbscanPoint>& vec_dbscan_point, double Eps, int MinPts);

public:
	DbscanPoint() = default;
	DbscanPoint(std::vector<double> xn) :xn(xn) { }

public:
	std::vector<double> xn;//���꣨�������ڶ�ά��
	int cluster = 0;//�ڼ�����
	int num_pts = 1;//��¼�������ж��ٸ��㣨�����Լ������Գ�ʼֵΪ1��
	int point_type = POINT_DEFAULT;//�������
	int calculated = CALCULATE_NO;//���Ƿ񱻼���
	int  visited = VISIT_NO;//���Ƿ񱻱���
	std::vector<DbscanPoint*> vec_dbscan_point_ptr;//���ڴ�������ڵĵ�
};


double CalculateDistance(DbscanPoint* point1, DbscanPoint* point2);


/*
������
vec_dbscan_point	��Ҫ����һ��DbscanPoint���͵�vector�����vector�������DbscanPointӦ�����Ѿ���ʼ�����������
Eps					����������ķ�ΧEps
MinPts				������������MinPts���㣨�����Լ������ܽ������ĵ�
*/
void DbscanMethod(std::vector<DbscanPoint>& vec_dbscan_point, const double& Eps, const int& MinPts);

#endif