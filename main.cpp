#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <ctime>
#include "RedisObj.hpp"
using namespace std;

void split(const string &s, vector<string> &tokens, char delimiter){
	string token;
	istringstream tokenStream(s);
 
	while (getline(tokenStream, token, delimiter))
	  tokens.push_back(token);
}

void save(unordered_map<string, RedisObj*> &RDB){
	ofstream fout;

	fout.open("dump.txt");

	string line;

	for(auto &i: RDB){
		i.second ->serialize(i.first, line);

		fout <<line <<"\n";
		line.clear();
	}

	fout.close();
}

void load(unordered_map<string, RedisObj*> &RDB){
	ifstream fin;

	fin.open("dump.txt");

	string line, tok, key, type;
	vector<string> data;

	while(fin){
		getline(fin, line);

		if(line.length() == 0)
			break;

		istringstream sline(line);

		getline(sline, tok, ' ');
		key = tok;

		getline(sline, tok, ' ');
		type = tok;

		RDB[key] = new RedisObj();

		if(tok == "0"){
			getline(sline, tok, ' ');

			RDB[key] ->setVal(tok);
		}
		else{
			while(getline(sline, tok, ' '))
				data.push_back(tok);

			RDB[key] ->makeSet(data);
			data.clear();
		}
	}

	fin.close();
}

void chkExpiry(unordered_map<string, RedisObj*> &RDB, string key){
	if(RDB.count(key) && RDB[key] ->getType() == false && time(0) > RDB[key] ->getExp() && RDB[key] ->getExp())
		RDB.erase(key);
}

int main(){
	unordered_map<string, RedisObj*> RDB;

	load(RDB);

	string query, key, value;
	vector<string> tokens;

	double score;
	int st, en;

	while(true){
		getline(cin, query);

		tokens.clear();
		split(query, tokens, ' ');

		if(tokens.size() < 2)
			continue;

		query = tokens[0];
		key = tokens[1];

		transform(query.begin(), query.end(), query.begin(), ::toupper);

		chkExpiry(RDB, key);

		if(query == "GET"){
			if(RDB.count(key))
				cout <<RDB[key] ->getVal() <<"\n";
			else
				cout <<"(nil)\n";
		}
		else if(query == "SET"){
			value = tokens[2];

			if(RDB.count(key) == 0)
				RDB[key] = new RedisObj();

			RDB[key] ->setVal(value);
			cout <<"OK\n";
		}

		else if(query == "ZRANK"){
			value = tokens[2];

			if(RDB.count(key))
				cout <<RDB[key] ->getRank(value) <<"\n";
			else
				cout <<"(nil)\n";
		}
		else if(query == "ZADD"){
			if(RDB.count(key) && RDB[key] ->getType() == false || tokens.size()%2)
				cout <<"(nil)\n";

			else{
				if(RDB.count(key) == 0)
					RDB[key] = new RedisObj();

				for(int i = 2; i < tokens.size() ; i += 2){
					score = stod(tokens[i]), value = tokens[i+1];
					RDB[key] ->setAdd(score, value);
				}
				cout <<"OK\n";
			}
		}
		else if(query == "ZRANGE"){
			st = stoi(tokens[2]);
			en = stoi(tokens[3]);

			vector<string> strs;

			if(RDB.count(key)){
				strs = RDB[key] ->getRange(st, en);

				for(string &i: strs)
					cout <<i <<"\n";

				if(strs.size() == 0)
					cout <<"(nil)\n";
			}
			else
				cout <<"(nil)\n";
		}
		else if(query == "EXPIRE"){
			if(RDB.count(key))
				RDB[key] ->setExpire(stoi(tokens[2]));
			else
				cout <<"(nil)\n";
		}

		else if(query == "EXIT")
			break;
		else if(query == "SAVE")
			save(RDB);
		else cout <<"INVALID QUERY\n";
	}

	save(RDB);

	return 0;
}