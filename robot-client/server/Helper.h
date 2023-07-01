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

    /**
     * Constructor for the helper class for the WebSocketServer.cpp
     */
    Helper();

    ~Helper() = default;

    /**
     * HTTP Get request, get the url of the request
     * @return string of the response
     */
    std::string getResponse(const std::string&);

    /**
     * HTTP Post request
     * @param url - url of the request
     * @param data - the data to post
     * @return true / false if succeed
     */
    bool postRequest(const std::string& url, const std::string& data);

    /**
     * decode text in base64 to normal text.
     * @param in
     * @return
     */
    std::string base64_decode(const std::string &in);

    /**
     * decoding string base64 image to png format
     * @param in
     * @return
     */
    std::string base64Img_decode(const std::string &in);

    /**
     * saving the base64Data as an png image
     * @param base64Data - the base64 image
     * @param filePath - the path to save the file
     * @return
     */
    bool saveAsPng(std::string base64Data, const std::string& filePath);

    /**
     * writing normal text and saving the in a specify location
     * @param filePath - string
     * @param dataInAscii - the data in ascii format to write.
     * @return
     */
    bool writeToFile(const std::string& filePath, const std::string& dataInAscii);

};


#endif //ROBOT_NAVIGATION_WORKSHOP_HELPER_H
