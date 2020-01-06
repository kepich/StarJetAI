#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;

class Logger{
private:

	ofstream file_output;

public:
	Logger(string file_name) {
		this->file_output.open(file_name);
	};

	~Logger() {
		this->file_output.close();
	}

	void info(string msg) {
		time_t timer = time(NULL);
		tm* time_struct = new tm();
		localtime_s(time_struct, &timer);
		char time_string[40];
		strftime(time_string, 40, "%Y.%m.%d %H:%M:%S ", time_struct);

		file_output << time_string << "[Info] : " << msg << endl;
	}

	void error(string msg) {
		time_t timer = time(NULL);
		tm* time_struct = new tm();
		localtime_s(time_struct, &timer);
		char time_string[40];
		strftime(time_string, 40, "%Y.%m.%d %H:%M:%S ", time_struct);

		file_output << time_string << "[ERROR] : " << msg << endl;
	}
};

