/*
 * Author: Kabir Pamnani
 * Date: 04/11/2022
 * File Purpose: Implementation of the stringProcessing class
 */

#include "stringProcessing.h"
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <iostream>

using namespace std;

// testing main tests functionality of stripNonAlphaNum
// int main() {
//     std::string test = "!!!comp__7969?@?";
//     int x = startChar(test);
//     std::cout << x << endl;
//     int y = endChar(test);
//     std::cout << y << endl;
//     std::string result = stripNonAlphaNum(test);
//     std::cout << result;
//     return 0;
// }


/*
 * name:      stripNonAlphaNum
 * purpose:   strips all leading non-alpha numeric chars from a given word
 * arguments: string reference to var s
 * returns:   stripped string 
 */
std::string stripNonAlphaNum(std::string &s) {
    // declare a string of all possible alpha nums
    string all_alpha_num_chars = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890";

    // find and record the pos of the first and last 
    size_t start = s.find_first_of(all_alpha_num_chars);
    size_t end = s.find_last_of(all_alpha_num_chars);

    // try to take the string in between start and end position
    try {
        s = s.substr(start, end - start + 1);
    // catch error if cannot perform substring (out of range)
    // example: a string like "!!!!"" or ""
    } catch (const out_of_range &oor) {
        return "WORDNOTINTABLE";
    }

    return s;
}

//     if (s.length() == 1) {
//         if (isalnum(s[0])) {
//             return s;
//         } else {
//             return newString;
//         }
//     } 

//     for (unsigned long x = 0; x < s.length(); x++) {
//         if (not isalnum(s[x])) {
//             count++;
//         }
//         if (count == s.length()) {
//             return newString;
//         }
//     }


//     start = startChar(s);
//     end = endChar(s);
    
//     return newString;
// }

// int startChar(std::string s) {
//     int start;
//     bool found = false;
//         for (unsigned long i = 0; i < s.length() and found == false; i++) {
//             if (isalnum(s[i])) {
//                 start = i;
//                 found = true;
//             }
//         }
//     return start;
// }

// int endChar(std::string s) {
//     int end;
//     bool found = false;
//         for (int x = s.size(); x > 0 and found == false; x--) {
//             if (isalnum(s[x])) {
//                 end = x;
//                 found = true;
//             }
//         }
//     return end;
// } 