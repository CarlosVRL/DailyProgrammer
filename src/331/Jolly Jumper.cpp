/**
 * Challenge #311 [Easy] Jolly Jumper
 * 
 * Problem Statement:
 * 
 * https://www.reddit.com/r/dailyprogrammer/comments/65vgkh/20170417_challenge_311_easy_jolly_jumper/
 * 
 * Solution by: CarlosVRL
 * 
 * Example "in" file:
 *  
 * 4 1 4 2 3
 * 5 1 4 2 -1 6
 * 4 19 22 24 21
 * 4 19 22 24 25
 * 4 2 -1 0 2
 * 
 * Output "out" file:
 * 
 * 4 1 4 2 3 JOLLY
 * 5 1 4 2 -1 6 NOT JOLLY
 * 4 19 22 24 21 NOT JOLLY
 * 4 19 22 24 25 JOLLY
 * 4 2 -1 0 2 JOLLY
 */

#include <iostream> // optional print to console, useful for debugging
#include <fstream>
#include <sstream>

#include <cstdlib>
#include <vector>
#include <set>

std::ifstream fin("in");
std::ofstream out("out");

#define cout out    // comment this line out to write to console

using namespace std;

/**
 * reads a spaced " " string of integers into vector
 */
vector<int> parse_int_line(string line);

int main()
{
    // read input text from file
    string line;
    while (getline(fin,line))
    {
        cout << line << " "; // OUTPUT initialization
        
        vector<int> a = parse_int_line(line);
        
        if (a.size() == 1) { break; } // trivial case
        
        set<int> b; // ordered set of integers
        
        for (int i = 1; i < a.size() - 1; ++i)
        {
            b.insert(abs(a[i] - a[i+1]));
        }
        
        // check minimum jolly criteria
        int jolly = 0;
        for (set<int>::iterator it = b.begin(); it != b.end(); ++it)
            if (*it != ++jolly) { cout << "NOT "; break; }
        
        cout << "JOLLY" << endl;
    }
    return 0;
}

/**
 * reads a spaced " " string of integers into vector
 * 
 * @param  line a space-separated character stream containing integers
 * @return      STL vector containing the integer values
 *
 * implicit conversion: will not throw error for invalid (non-digit) characters
 */

vector<int> parse_int_line(string line)
{
    vector<int> a; int b;   
    
    std::istringstream iss(line);
    
    while (iss >> b) { a.push_back(b); }
    
    return a;
};
