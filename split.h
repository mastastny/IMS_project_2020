//
// Created by marek on 01.12.20.
//

#ifndef IMS_PROJECT_2020_SPLIT_H
#define IMS_PROJECT_2020_SPLIT_H

#include "string"
#include "vector"
#include <algorithm>

using namespace std;

string preprocessFloat(string number);

/**
 * Finds substrings ending with the delimeter and stores them into vector.
 * Substring ends at the end of the delimeter.
 * End of the message without delimeter is not stored.
 * @param message string in which the substring will be searched
 * @param subStrings vector in which substrings will be stored
 * @param delimeter
 */
vector<string>  split(string myStr,  string delimeter);

#endif //IMS_PROJECT_2020_SPLIT_H
