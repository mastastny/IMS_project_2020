//
// Created by marek on 01.12.20.
//

# include "split.h"


string preprocessFloat(string number){
    replace( number.begin(), number.end(), ',', '.'); // replace all 'x' to 'y'
    if(number == ""){
        number = "0";
    }
    if(number[0] == ',' ){
        number = "0" + number;
    }
    if(number[0] == ';'){
        number = "0" + number;
    }
    if(number[0] == '-'){
        if(number[1] == ','){
            number.insert(1,"0");
        }
        number = "0" + number;
    }
    return number;
}

vector<string> split(string myStr, string delimeter){
    size_t substrStart = 0;
    size_t substrEnd = 0;
    size_t res;

    vector<string> subStrings;

    while((res = myStr.find(delimeter, substrStart)) != string::npos){
        substrEnd = res + delimeter.length();
        subStrings.push_back(myStr.substr(substrStart, substrEnd-substrStart-1));
        substrStart = substrEnd;
    }
    subStrings.push_back(myStr.substr(substrStart));

    return subStrings;
}
