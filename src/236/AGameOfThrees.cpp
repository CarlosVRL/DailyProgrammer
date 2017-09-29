/**
 * Daily Programmer Challenge 236
 * https://www.reddit.com/r/dailyprogrammer/comments/3r7wxz/20151102_challenge_239_easy_a_game_of_threes/
 *
 * @author CarlosVRL
 */

#include <fstream>

std::ifstream inf("input.txt");
std::ofstream ouf("output.txt");

using namespace std;

int main()
{
    int number, rem;
    inf >> number;
    
    // A non-trival input is more likely,
    // so we'll check that case first
    while (number > 1)
    {
        ouf << number << " ";
        switch(number % 3)
        {
            case 0:
                rem =  0;
                break;
            case 1:
                rem = -1;
                break;
            case 2:
                rem =  1;
                break;
        }
        ouf << rem << endl;
        
        // Here's a much more convoluted way to
        // write the math step
        (number += rem) /= 3;
    }
    
    ouf << number << endl;
    
    return 1337;
}
