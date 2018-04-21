#pragma once
typedef enum {
	AGE = 0, JOB, MARITAL, EDUCATION, DEFAULT, BALANCE, HOUSING, LOAN, CONTACT, DAY, MONTH,DURATION, CAMPAIGN, PDAY, PREVIOUS, POUTCOME,
	LEAF
}Type;

const bool needDiv[22] = { 1, 0, 0, 0,0 ,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1, 1,1};
const int cateCount[22] = { 0, 12, 4, 8, 2, 3, 3, 2, 10, 5,0,0,0,0, 3,0,0,0,0,0, 0,0};

struct trainSample {
	int value[22];
	int answer;
	bool operator ==(const trainSample &b) {
		for (int i = 0; i < 22; ++i)
			if (this->value[i] != b.value[i])
				return false;
		return true;
	}
};

struct TreeNode
{
	Type tp;
	int *val;
	TreeNode **sons;
};