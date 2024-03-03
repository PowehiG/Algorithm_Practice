#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;

int main() {
    int n, q, i;
    cin >> n >> q;
    string temp;
    vector<string> hrml;    // stores the HRML tags
    vector<string> quer;    // stores the queries
    cin.ignore();           // ignores an end of line character from an input stream

    for (i = 0; i < n; i++)
    {
        getline(cin, temp);
        hrml.push_back(temp);
    }

    for (i = 0; i < q; i++)
    {
        getline(cin, temp);
        quer.push_back(temp);
    }

    map<string, string> m;
    vector<string> tag;

    for (i = 0; i < n; i++)
    {
        temp = hrml[i];
        temp.erase(remove(temp.begin(), temp.end(), '\"'), temp.end());
        temp.erase(remove(temp.begin(), temp.end(), '>'), temp.end());

        if (temp.substr(0, 2) == "</")
        {
            tag.pop_back();
        }
        else
        {
            stringstream ss;
            ss.str("");
            ss << temp;
            string t1, p1, v1;
            char ch;                            // takes the '<' '=' out of the input stream
            ss >> ch >> t1 >> p1 >> ch >> v1;   // inputs like <tag1 value = "HelloWorld">
                                                // ch == '.'; t1 == tag1; p1 == value; v1 == HelloWorld
            string temp1 = "";
            if (tag.size() > 0)     // checks whether the tag vector contains any tag names
            {
                temp1 = *tag.rbegin();
                temp1 = temp1 + "." + t1;
            }
            else
                temp1 = t1;
            tag.push_back(temp1);
            m[*tag.rbegin() + "~" + p1] = v1;
            while (ss)
            {
                ss >> p1 >> ch >> v1;
                m[*tag.rbegin() + "~" + p1] = v1;
            }
        }
    }

    for (i = 0; i < q; i++)
    {
        if (m.find(quer[i]) == m.end())
            cout << "Not Found!\n";
        else
            cout << m[quer[i]] << endl;
    }

    return 0;
}
