#pragma once
#include <iostream>
using namespace std;

class Logger{
private:
	Logger() {};
	Logger(const Logger&) = delete;
public:
	static Logger* get_logger() {
		static Logger* singletone = new Logger();
		return singletone;
	}

	void info(string msg) {
		cout << "[Info] : " << msg << endl;
	}

	void error(string msg) {
		cout << "!!![ERROR]!!! : " << msg << endl;
	}
};

