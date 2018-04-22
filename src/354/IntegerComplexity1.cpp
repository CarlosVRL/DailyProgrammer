#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>


/**
 * Challenge #354 [Easy] Integer Complexity 1
 * 
 * https://www.reddit.com/r/dailyprogrammer/comments/83uvey/20180312_challenge_354_easy_integer_complexity_1/
 * 
 * Given a number A, find the smallest possible value of B+C, if B*C = A. Here A, B, and C must all be positive integers. It's okay to use brute force by checking every possible value of B and C. You don't need to handle inputs larger than six digits. Post the return value for A = 345678 along with your solution.
 * 
 * For instance, given A = 12345 you should return 838. Here's why. There are four different ways to represent 12345 as the product of two positive integers:
 * 
 * 12345 = 1*12345
 * 12345 = 3*4115
 * 12345 = 5*2469
 * 12345 = 15*823
 * 
 * The sum of the two factors in each case is:
 * 
 * 1*12345 => 1+12345 = 12346
 * 3*4115 => 3+4155 = 4158
 * 5*2469 => 5+2469 = 2474
 * 15*823 => 15+823 = 838
 * 
 * The smallest sum of a pair of factors in this case is 838.
 * 
 * Start : 12:06 PM April 22nd, 2018
 * Stop  :  1:14 AM April 22nd, 2018
 */

/**
 * Prototypes.
 */
int bruteforceIntegerComplexity(int num);
void examples(void);

/**
 * Constants.
 */
const int MAX_DIGITS = 6;
const int MAX_VALUE  = 999999;

/**
 * Main program.
 */
int main(int argc, char** argv)
{    
    std::cout << "Challenge #354 [Easy] Integer Complexity 1" << std::endl;
    std::cout << "Please enter an integer [1-";
    for (int i = 0; i < MAX_DIGITS; ++i) { std::cout << "9"; }
    std::cout << " or 0 for examples]: ";
    int num;
    std::cin >> num;
    
    if (num > MAX_VALUE || num < 0)
    {
        std::cout << "Invalid input" << std::endl;
        return EXIT_FAILURE;
    }
    else if (num == 0)
    {
        examples();
        return EXIT_SUCCESS;
    }
    std::cout << num << " => " << bruteforceIntegerComplexity(num) << std::endl;
    return EXIT_SUCCESS;
}

/**
 * This algorithm loops on integers less than half of the input, checking for
 * equivalence on an inner loop that is linearly incremented until the mult. 
 * is greater than the target. Sums are stored on an array and sorted for min.
 */
int bruteforceIntegerComplexity(int num)
{
    if (num <= 0) return 0;
    int halfNum = num / 2;
    
    std::vector<int> a;
    for (int i = 1; i <= halfNum; ++i)
    {
        int j = 1;
        while (i * j <= num)
        {
            int check = i * j;
            if (check == num)
            {
                a.push_back(i + j);
            }
            j++;
        }
    }
    
    if (a.size() == 0) { return 0; }
    return *std::min_element(a.begin(), a.end());
}

/**
 * Algorithm examples.
 */
void examples()
{
    std::vector<int> a;
    a.push_back(12);
    a.push_back(456);
    a.push_back(4567);
    a.push_back(12345);
    std::vector<int>::iterator it = a.begin();
    std::vector<int>::iterator et = a.end();
    for (; it != et; ++it)
    {
        std::cout << std::setw(MAX_DIGITS) << *it << " => " << bruteforceIntegerComplexity(*it) << std::endl;
    }
}
