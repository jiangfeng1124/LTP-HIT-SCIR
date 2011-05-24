
#define STL_USING_ALL
#include "stl.h"

#ifndef _DATA_INFORMATION_
#define  _DATA_INFORMATION_

struct DATA
{
	int id;						// id of node
	bool mark;					// status of node
	string word;				// word of node
	string tag;					// POS of node
	string ctag;				// coarse-grained tag
	string feature;				// morphological or syntatic features
	string relation;			// relation of the node
	int ldegree;				// left governing degree
	int rdegree;				// right governing degree
	float lprob;				// prob of left governing degree
	float rprob;				// prob of right governing degree
	vector < DATA* > lchild;	// all the left children of node
	vector < DATA* > rchild;	// all the right children of node
};
 
struct PAIR
{
	int index1; // the first
	int index2; // the second
	string relation;
	float prob;
	int wait;
	int delay;
	int block;
	int level;
	// overload operator < to sort ascending
	bool operator < (const PAIR &myPair) const { return prob < myPair.prob;}
};

struct PROB
{
	string relation;
	float ftd,ftt,ftttt,ftw,fwt,fww;
	bool operator == (const string myRelation) const {return relation == myRelation;}
	PROB(string relation)
	{
		this->relation = relation;
		this->ftt = 0;
		this->ftd = 0;
		this->ftttt = 0;
		this->ftw = 0;
		this->fwt = 0;
		this->fww = 0;
	};
	void SetProb(int num, float prob)
	{
		switch(num)
		{
		case 1: this->ftd = prob;
			break;
		case 2: this->ftt = prob;
			break;
		case 3: this->ftttt = prob;
			break;
		case 4: this->ftw = prob;
			break;
		case 5: this->fwt = prob;
			break;
		default: this->fww = prob;
		}
	};
};

#endif
