#pragma once
#include<cmath>
#include<vector>
#include<algorithm>
#include<iostream>

#include"struts.h"


class DecisionTree {
public:
	DecisionTree() {
		maxDepth = 100;
		std::cout << maxDepth << std::endl;
	}
	void train(const std::vector<trainSample> &samples);
	void clear();
	bool judgeSam(const trainSample &sample);
	int allDepth = 0;
	int nodeNum = 0;
	int leafNum = 0;
	int sampleNum = 0;
	double *logs;
	TreeNode *root = NULL;

	double calculs(const std::vector<trainSample> &sample, int type, int totalPos, int &indexs, bool flass);
	double calS(int ap, int an);
private:
	void train(std::vector<trainSample> &sample, TreeNode* &extNode, int dep, int type);
	void clear(TreeNode *node);
	int  flag = 0;
	bool vec_same(std::vector<trainSample> &sample, int type);
	std::vector<int>tepp;
	int maxDepth;
};