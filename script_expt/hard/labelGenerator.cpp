#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main (int argc, char *argv[]) {
	if (argc < 3) {
		cout << "args: vfile range" << endl;
		return 0;
	}

	string inputname = argv[1];
	string range_str = argv[2];
	

	cout << "inputname = " << inputname << endl;
	cout << "range_str = " << range_str << endl;

	int range = atoi(argv[2]);

	string suffix = "-l" + range_str + "-law28.v";
	string outputname = inputname.substr(0, inputname.find_last_of(".")) + suffix;

	ifstream fin(inputname.c_str());
	ofstream fout(outputname.c_str());

	string line;
	int vid, vlabel;
	int split = (int)range * 0.2;

	while (getline(fin, line)) {
		stringstream ss(line);
		ss >> vid;

		int r28 = rand() % 10;
		if (r28 < 8) {
			vlabel = rand() % split;
		}
		else {
			vlabel = rand() % (range - split) + split;
		}
		fout << vid << "\t" << vlabel << endl;
	}
}