//
// Created by omer on 5/31/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_HELPER_H
#define ROBOT_NAVIGATION_WORKSHOP_HELPER_H
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <unistd.h>
#include <openssl/bio.h>
#include <openssl/evp.h>


typedef unsigned char BYTE;
size_t WriteCallback(void*, unsigned long, unsigned long, std::string*);
class Helper {
    std::string base64_chars;

public:
    Helper();
    ~Helper();
    std::string getResponse(const std::string&);
    std::string base64_decode(const std::string &in);
    std::string base64Img_decode(const std::string &in);
    bool saveAsPng(std::string base64Data, const std::string& filePath);
    bool writeToFile(const std::string& filePath, const std::string& dataInAscii);

};


#endif //ROBOT_NAVIGATION_WORKSHOP_HELPER_H
