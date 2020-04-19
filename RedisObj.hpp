#include "AVLTree.hpp"

#ifndef REDISOBJ_H
#define REDISOBJ_H
class RedisObj{
	std::string val;
	AVLTree *sset;
	int exp;
	bool type;

public:
	RedisObj();

	bool getType();

	void setVal(std::string val);
	void setAdd(double score, std::string value);

	std::string getVal();

	int getRank(std::string value);
	int getExp();

	std::vector<std::string> getRange(int st, int en);

	void setExpire(int limit);
	void serialize(std::string key, std::string &dump);
	void makeSet(std::vector<std::string> &data);

	~RedisObj();
};
#endif