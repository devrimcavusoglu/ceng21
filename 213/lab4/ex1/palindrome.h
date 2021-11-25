#ifndef PALINDROME_H
#define PALINDROME_H

#include "Stack.h"

/*
- Palindrome is a string that has the same order of characters when read from the front as well as the behind.

- Normally the case sensitivity is ignored. 
- However, in order to reduce the complexity, each character should match EXACTLY the same in this implementation.
- For example; "anna" is a palindrome, but (in this implementation) "anNa" is not a palindrome.

- Edge Cases:
    - Single charactered strings considered as palindromes.
    - Empty strings are NOT considered as palindromes.

- If the given string is a palindrome, return true. Otherwise, return false.

- Examples:
    - "anna"        -> true (is palindrome)
    - "anNa"        -> false (not palindrome)
    - "elevate"     -> false (not palindrome)
    - ""            -> false (not palindrome)
    - "a"           -> true (is palindrome)
    - "indorodni"   -> true (is palindrome)
*/

bool isPalindrome(string str) {
    int len_str = (int) str.size();
    if (len_str == 0)
        return false;

    Stack<char> my_stack; 

    int middle = (int) (len_str / 2);
    int i = 0;
    do {
        if (i < middle) {
            my_stack.push(str[i]);
        }
        else if (len_str % 2 != 0 and i == middle) {
            i++;
            continue;
        }
        else if (str[i] == my_stack.peek())
            my_stack.pop();
        else
            return false;
        i++;
    } while (!my_stack.isEmpty());
    return true;
}

#endif //PALINDROME_H