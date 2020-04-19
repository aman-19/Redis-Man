# Redis-Man

This is a basic implementation of Redis in C++14 with some queries like -
1. **GET**(https://redis.io/commands/get)
2. **SET**(https://redis.io/commands/set)
3. **EXPIRE**(https://redis.io/commands/expire)
4. **ZADD**(https://redis.io/commands/zadd)
5. **ZRANK**(https://redis.io/commands/zrank)
6. **ZRANGE**(https://redis.io/commands/zrange)

**Note:** The database is saved in a file named **dump.txt**. Therefore, the data is persistent and will load the next time you run the program. But because of the same reason the data can be lost if this file is deleted. You need to have g++(x >= 11) to avoid any errors.

## Clone the current repo <br>
`https://github.com/aman-19/Redis-Man.git`

## Run program on Linux
`g++ -o main main.cpp RedisObj.cpp AVLTree.cpp Node.cpp`<br>
`./main`

## Run program on Windows
`g++ -o main main.cpp RedisObj.cpp AVLTree.cpp Node.cpp`<br>
`main.exe`

## Commands
```
SET <key> value(string)
GET <key>
EXPIRE <key> <time-in-sec>
ZADD <set-name> <score1(float)> <element1(string)> <score2> <element2> ...
ZRANK <set-name> <element(string)>
ZRANGE <set-name> <start(int)> <end(int)>
SAVE NOW
EXIT NOW
```
### Example Commands
```
SET key val
GET key
ZADD setKey 1 val1 2 val2....
SAVE NOW
ZRANK setKey val
ZRANGE setKey 0 9
EXIT NOW
```
```
