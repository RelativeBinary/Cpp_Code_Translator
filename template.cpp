#include "template.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>

bool checkLatin(char &newChar) { //makes sure latin is valid and in lower case, 
//when white space is read in readLatFile it will be converted to an '_'
//when '_' is being sent to an outfile with writeLatFile it will be converted to whitespace
    char validLatin[27] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_'};
    for (int i = 0; i < 27; i++)
    {
        if (newChar == validLatin[i])
        {
            return true;
        }
    }
    std::cerr << "ERROR: the char passed to checkLatin '" << newChar << "' is not valid. aborting program.\n";
    return false;
}

morseChar::morseChar(std::string newChar, char latin) {
    mChar = newChar;
    lChar = latin;
}

brailleChar::brailleChar(std::string newChar, char latin) {
    bChar = newChar;
    lChar = latin;
}

bool readLatFile(std::vector<char> &latinMsg, std::string &inFile) {
    //load file
    std::ifstream in;
    in.open(inFile);
    std::string line;
    bool error = false;
    //split file into chars as you put them into vector
    if (in) {
        while(getline(in, line)) {
            for (int i = 0; i < line.size(); i++){//loop through each line of the file
                char newLat = line[i]; 
                if (newLat == ' '){//convert whitespace
                    newLat = '_';
                }
                if (checkLatin(newLat)){ //add to inMsg vector if valid character
                    latinMsg.push_back(newLat);
                } else {
                    std::cerr << "ERROR: readLatFile failed.\n";
                    error = true;
                    break;
                }
            }
        }
    } else {
        std::cerr << "ERROR: was not able to open '" << inFile << '\n';
        return false;
    }
    if (error) {
        std::cerr << "ERROR: readFile failed to read the latin text.\n";
        return false;
    }

    return true;
}

bool reportLatMsg(std::vector<char> &latinMsg){
    //report on length of message
    std::cout << "\t\t:REPORT:\n\n";
    std::cout << "Message Size:\t" << latinMsg.size() << '\n';
    //gathering data
    if(!latinMsg.empty()){
        //display message
        std::cout << "Message:\t";
        for (auto const& item : latinMsg){
            if (item == '_'){
                std::cout << ' ';
            } else {
                std::cout << item;
            }
        }
        std::cout << '\n';
        //display character distributions
        std::cout << "Character Distribution:\n";
        std::map<char, int> dist;
        std::map<char, int>::iterator it;
        for(int i = 0; i < latinMsg.size(); i++){
            if(dist.empty()){
                dist[latinMsg[i]] = 1;
            } else if (dist.find(latinMsg[i]) != dist.end()){
                //map contains key, increment its value
                it = dist.find(latinMsg[i]);
                it->second++;
            } else if (dist.find(latinMsg[i]) == dist.end()){
                //map doesnt contain key, add to map
                dist[latinMsg[i]] = 1;
            }
        }
        std::cout << "Character:\tCount\n";
        for (auto const& item : dist){//output the distbution results
            std::cout << item.first << " \t:\t" << item.second << '\n';
        }
    } else {
        std::cout << "There are no characters logged to latinMsg.\n";
        return false;
    }
    return true;
}

bool writeLatFile(std::vector<char> &latinMsg, std::string &outFile){
    std::ofstream oFile(outFile);
    if(oFile.is_open()){//check for access
        for (int i = 0; i < latinMsg.size(); i++){
            if(latinMsg[i] == '_'){
                oFile << ' ';
            } else {
                oFile << latinMsg[i];
            }
        } 
    } else {
        return false;
    }
    return true;
}

