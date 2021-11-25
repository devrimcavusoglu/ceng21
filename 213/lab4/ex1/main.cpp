#include "palindrome.h"

using namespace std;

int main() {
    
    string expr = "annb";

    //string expr = "qabaq";

    if (isPalindrome(expr))
        cout << "Palindrome\n";
    else
        cout << "Not Palindrome\n";
    
    return 0;
}