#include <iostream>
#include <string>
#include <math.h>
#include <sstream>
#include <conio.h>
#include <list>

using namespace std;

int main(int argc, char* argv[])
{
	string s;
    int count = 0;
	int left = 0;
	int right = 0;
	//getline(cin, s);
    s = argv[1];
    cout << s << endl;
	int tab= 0;
	int line = 0;
	int space = 0;

    for (int i = 0; i < s.length(); i++)
    {
        tab = s.find("\t", left);
        line = s.find("\n", left);
        space = s.find(" ", left);
        if (tab == -1)
        {
            tab = s.length() + 1;
        }
        if (line == -1)
        {
            line = s.length() + 1;
        }
        if (space == -1)
        {
            space = s.length() + 1;
        }
        right = min(space, tab);
        right = min(right, line);
        if (right == s.length() + 1)
        {
            break;
        }
        count+=1;

        left = right + 1;
    }
    if (left < s.length())
    {
        count+=1;
    }
    cout <<"The number of words in the string:"<< count;
}