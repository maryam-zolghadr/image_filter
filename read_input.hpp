#ifndef READ_INPUT_H
#define READ_INPUT_H
#include "filter.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

View handle_view_input(const string& views);
void handle_input(int argc, char* argv[], vector<char>& filters, vector<View>& views);

#endif