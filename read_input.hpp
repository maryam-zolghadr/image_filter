#include "bmp.hpp"
#include "filter.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

View handle_view_input(const string& views);
void handle_input(int argc, char* argv[], vector<char>& filters, vector<View>& views);
