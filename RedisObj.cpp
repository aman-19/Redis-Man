#include "RedisObj.hpp"
#include <ctime>

RedisObj::RedisObj(){
	sset = nullptr;
	val = "";
	type = true;
	exp = 0;
}

bool RedisObj::getType(){
	return type;
}

void RedisObj::setVal(std::string value){
	type = false;

	delete(sset);
	sset = nullptr;

	val = value;
}

std::string RedisObj::getVal(){
	return type? "$-1\r": val;
}

void RedisObj::setAdd(double score, std::string value){
	if(type == false)
		return;
	if(sset == nullptr)
		sset = new AVLTree();

	sset ->insert(score, value);
}

int RedisObj::getRank(std::string value){
	return type? sset ->rank(value): -1;
}

std::vector<std::string> RedisObj::getRange(int st, int en){
	std::vector<std::string> v;

	if(type == false){
		v.push_back("$-1\r");
		return v;
	}

	if(st < 0)
		st = (st + sset ->size());
	if(en < 0)
		en = (en + sset ->size());

	if(en < st){
		v.push_back("$-1\r");
		return v;
	}

	sset ->sRange(st, en, v);

	return v;
}

int RedisObj::getExp(){
	return exp;
}

void RedisObj::setExpire(int limit){
	if(type == false)
		exp = time(0) + limit;
}

void RedisObj::serialize(std::string key, std::string &dump){
	std::string sp = " ";

	dump.append(key);
	dump.append(sp);

	if(type){
		Node *temp = sset ->Index(0);

		dump.append("1 ");

		while(temp){
			dump.append(std::to_string(temp ->score));
			dump.append(sp);

			dump.append(temp ->val);
			dump.append(sp);

			temp = temp ->suc;
		}
	}
	else{
		dump.append("0 ");
		dump.append(val);
	}
}

void RedisObj::makeSet(std::vector<std::string> &data){
	if(sset)
		return;

	sset = new AVLTree();

	sset ->recMake(data);
}

RedisObj::~RedisObj(){
	val = "";
	delete(sset);
}