#pragma once
#include"decisionTree.h"
using namespace std;

void DecisionTree::train(const std::vector<trainSample> &samples) {
	int num = samples.size();
	if (samples.empty()) {
		return;
	}
	if (root != NULL) {
		clear();
	}
	sampleNum = num;
	logs = (double *)malloc(sizeof(double) * (num + 1));
	logs[0] = 0;
	for (int i = 1; i <= num; ++i)
		logs[i] = log2(i);
	vector<trainSample> temp(samples);
	train(temp, root, 0, 0);
};

void DecisionTree::clear() {
	allDepth = 0;
	nodeNum = 0;
	leafNum = 0;
	delete logs;
	sampleNum = 0;
	clear(root);
	root = NULL;
};

bool DecisionTree::judgeSam(const trainSample &sample) {
	TreeNode *tempNode = root;
	while (tempNode->tp != Type::LEAF) {
		int index = 1;
		if (needDiv[tempNode->tp]) {
			if (tempNode->val[0] >= sample.value[tempNode->tp])
				tempNode = tempNode->sons[0];
			else
				tempNode = tempNode->sons[1];
			//for (; sample.value[tempNode->tp] > tempNode->val[index]; ++index);
			//tempNode = tempNode->sons[index - 1];
		}
		else {
			tempNode = tempNode->sons[sample.value[tempNode->tp]];
		}
	}
	//cout << "hade" << endl;
	return (*tempNode->val == 0) ? false : true;
};

bool judgepair(const std::pair<int, int> &a, const std::pair<int, int> &b){
	return a.first < b.first;
}

void DecisionTree::train(std::vector<trainSample> &samples, TreeNode* &extNode, int dep, int type) {
	if (dep > allDepth)
		allDepth = dep;
	int minType = 0, sizess = samples.size();
	extNode = (TreeNode *)malloc(sizeof(TreeNode));
	if (sizess == 0) {
		extNode->tp = Type::LEAF;
		extNode->val = (int *)malloc(sizeof(int));
		*extNode->val = type;
		return;
	}
	int totalPos = 0, divVal, minVal;
	for (int i = 0; i < sizess; ++i) {
		totalPos += samples[i].answer;
	}
	if (totalPos > (sizess / 2))
		type = 1;
	else
		type = 0;
	if (dep > maxDepth) {
		extNode->tp = Type::LEAF;
		extNode->val = (int*)malloc(sizeof(int));
		extNode->val[0] = type;
		return;
	}
	double minS = 10000.0, tempS;
	if (totalPos == 0 ) {
	//	cout << sizess << "\tdsa" << endl;
		extNode->tp = Type::LEAF;
		extNode->val = (int *)malloc(sizeof(int));
		*extNode->val = 0;
		return;
	}
	else if (totalPos == sizess) {
	//	cout << sizess << "\t" << "asd" << endl;
		extNode->tp = Type::LEAF;
		extNode->val = (int *)malloc(sizeof(int));
		*extNode->val = 1;
		/*if (flag == false) {
			flag = true;
			cout << "\n";
			for (int i = 0; i < 20; ++i)
				cout << samples[0].value[i] << "\t";
			cout << endl << samples[0].answer << endl;
			cout << endl;
			cout << endl;
			for (int i = 0; i < dep; ++i)
				tepp.push_back(0);
		}*/
		return;
	}
	for (int i = 0; i < 22; ++i) {
		tempS = calculs(samples, i, totalPos, divVal, false);
		if (minS > tempS) {
			minS = tempS;
			minType = i;
			minVal = divVal;
		}
	}
	//if (dep > 10) {
	//	cout << minType << "\t" << minVal << endl;
	//}
	/*if (minType == 0 && minVal == 52 && dep > 10) {
		if (flag++ == 0) {
			calculs(samples, minType, totalPos, minVal, true);
		};
		cout << "\tSize: " << sizess << "\n";
		for (int i = 0; i < sizess; ++i)
		{
			cout << samples[i].value[minType] << "\t";
		}
		cout << endl;
	}*/
	if (vec_same(samples, minType)) {
		extNode->tp = Type::LEAF;
		extNode->val = (int*)malloc(sizeof(int));
		extNode->val[0] = type;
		return;
	}
	else {
		if (needDiv[minType]) {
			extNode->tp = Type(minType);
			extNode->val = (int *)malloc(2 * sizeof(int));
			extNode->sons = (TreeNode **)malloc(2 * sizeof(TreeNode *));
			vector<trainSample> sam1, sam2;
			for (int i = 0; i < sizess; ++i) {
				if (samples[i].value[minType] <= minVal)
					sam1.push_back(samples[i]);
				else
					sam2.push_back(samples[i]);
			}


			extNode->val[0] = minVal;
			extNode->val[1] = INT_MAX;
			samples.clear();
			train(sam1, extNode->sons[0], dep + 1, type);
			//if (flag && dep < tepp.size() && !tepp[dep]) {
			//	tepp[dep] = 1;
			//	cout << "\t-------";
			//	cout << minType << "\t" << minVal << "\ta" << endl;
			//}
			train(sam2, extNode->sons[1], dep + 1, type);
			//if (flag && dep < tepp.size() && !tepp[dep]) {
			//	tepp[dep] = 1;
			//	cout << "\t-------";
			//	cout << minType << "\t" << minVal << "\tb"<< endl;
			//}
			//cout << samples.size() << "\tabc\t"<< sam1.size() << "\t" << sam2.size() << endl;
		}
		else {
			extNode->tp = Type(minType);
			extNode->sons = (TreeNode **)malloc(sizeof(TreeNode *) * cateCount[minType]);
			vector<trainSample> sam[20];
			for (int j = 0; j < samples.size(); ++j) {
				sam[samples[j].value[minType]].push_back(samples[j]);
			}
			samples.clear();
			//cout << samples.size() << "\tabc\t";
			for (int i = 0; i < cateCount[minType]; ++i) {
				train(sam[i], extNode->sons[i], dep + 1, type);
				//if (flag && dep < tepp.size() && !tepp[dep]) {
				//	tepp[dep] = 1;
				//	cout << "\t-------";
				//	cout << minType << "\t" << i << "\tc" << endl;
				//}
			//cout << sam[i].size() << "\t";
			}
			//cout << endl;
		}
	}
};

double DecisionTree::calculs(const vector<trainSample> &samples, int type, int totalPos, int  &val, bool flass) {
	int sizes = samples.size();
	int totalNeg = sizes - totalPos;
	double minS = 100000.0;

	if (needDiv[type]) {
		int lowPos = 0, lowNeg = 0, highPos = totalPos, highNeg = totalNeg;
		double tempS;
		vector<pair<int, int>> temp;
		for (int i = 0; i < sizes; ++i)
			temp.push_back(pair<int, int>(samples[i].value[type], i));
		sort(temp.begin(), temp.end(), judgepair);
		//if (type == 0) {
		//	for (int i = 0; i < temp.size(); ++i)
		//		cout << temp[i].first << "\t"<< temp[i].second << endl;
		//}
		int oldVal = temp[0].first;
		for (int i = 0; i < sizes; ++i) {
			if (oldVal != temp[i].first) {
				tempS = (calS(lowPos, lowNeg) * (i + 1) + calS(highNeg, highPos) * (sizes - 1 - i)) / sizes;
				if (flass)
					cout << highNeg << "\t" << lowNeg << "\t" << highPos << "\t" << lowPos << "\t" << tempS << "\n";
				if (tempS < minS) {
					minS = tempS;
					val = oldVal;
				}
				oldVal = temp[i].first;
			}
			highNeg -= 1 - samples[temp[i].second].answer;
			lowNeg += 1 - samples[temp[i].second].answer;
			highPos -= samples[temp[i].second].answer;
			lowPos += samples[temp[i].second].answer;
			
		}
	}
	else {
		int tempPos = 0, tempNeg = 0;
		double tempS = 0;
		for (int i = 0; i < cateCount[type]; ++i) {
			tempPos = 0, tempNeg = 0;
			for (int j = 0; j < sizes; ++j) {
				if (samples[j].value[type] == i) {
					if (samples[j].answer == 1)
						tempPos++;
					else
						tempNeg++;
				}
			}
			tempS += (tempPos + tempNeg) * calS(tempPos, tempNeg);
		}
		minS = tempS / sizes;
	}
	return minS;
}

void DecisionTree::clear(TreeNode *node) {
	if (node->tp == Type::LEAF) {
		delete node->val;
		delete node;
		return;
	}
	if (needDiv[node->tp]) {
		clear(node->sons[0]);
		clear(node->sons[1]);
		delete(node->val);
	}
	else {
		for (int i = 0; i < cateCount[node->tp]; ++i)
			clear(node->sons[i]);
	}
	delete(node->sons);
	delete(node);
};

double DecisionTree::calS(int ap, int an) {
	if (ap == 0 || an == 0)
		return 0;
	return logs[ap + an] - (ap * logs[ap] + an * logs[an]) / (ap + an);
}

bool DecisionTree::vec_same(std::vector<trainSample> &sample, int type) {
	int val = sample[0].value[type];
	for (int i = 0; i < sample.size(); ++i) {
		if (val != sample[i].value[type])
			return false;
	}
	return true;
}