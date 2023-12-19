#include "read_input.hpp"

View handle_view_input(const string& views)
{
    string viewString = views;
    stringstream ss(viewString);
    string token;
    View separatedView;
    if (viewString.find(':') != string::npos)
    {
        getline(ss, token, ':');
        separatedView.x = stoi(token);

        getline(ss, token, ':');
        separatedView.y = stoi(token);

        getline(ss, token, ':');
        separatedView.w = stoi(token);

        getline(ss, token, ':');
        separatedView.h = stoi(token);
    }
    else
    {
        separatedView.h = 0;
        separatedView.w = 0;
        separatedView.x = 0;
        separatedView.y = 0;
    }
    return separatedView;
}

void handle_input(int argc, char* argv[], vector<char>& filters, vector<View>& views)
{
    string tmp;
    int cnt = 0;
    for(int i = 1; i < argc; i++)
    {
        if(argv[i][0] == '-')
        {
            filters.push_back(argv[i][1]);
            if(i + 1 < argc)
            {
                if(argv[i + 1][0] != '-')
                {
                    tmp = argv[i + 1];
                }
                else if(argv[i + 1][0] == '-')
                {
                    tmp = " ";
                }
                views.push_back(handle_view_input(tmp)); 
            }
            else
            {
                tmp = " ";
                views.push_back(handle_view_input(tmp)); 
            }
            cnt++;
        }
    }    
}