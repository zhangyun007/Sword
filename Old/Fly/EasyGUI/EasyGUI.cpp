#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "json.hpp"
// for convenience
using json = nlohmann::json;

using namespace std;

int main() {
	
	// read a JSON file
	std::ifstream i("test.json");
	json j;
	i >> j;
	cout << j["Name"];

	return 0;
}