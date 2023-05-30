//
// Created by omer on 5/28/23.
//

#ifndef ROBOT_NAVIGATION_WORKSHOP_CLIENT_H
#define ROBOT_NAVIGATION_WORKSHOP_CLIENT_H
#include <iostream>
#include <string>
#include <curl/curl.h>
#include <curl/curlver.h>
#include <jsoncpp/json/json.h>

// Define the client class
class Client {



public:
    // Constructor
    Client() {}

    // Send an HTTP request to the Node.js server
    std::string get(const std::string& url) {
        // Create a CURL handle
        CURL* curl = curl_easy_init();

        // Set the URL
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        // Set the HTTP method
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");

        // Set the response type
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeResponse);

        // Execute the request
        CURLcode res = curl_easy_perform(curl);

        // Check the response code
        if (res != CURLE_OK) {
            std::cerr << "Error: " << curl_easy_strerror(res) << std::endl;
            return "";
        }

        // Get the response from the Node.js server
        std::string response;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_STRING, &response);

        // Close the CURL handle
        curl_easy_cleanup(curl);

        return response;
    }

private:
    // Function that will write the response to a string
    size_t writeResponse(void* ptr, size_t size, size_t nmemb, void* stream) {
        // Cast the stream pointer to a string pointer
        std::string* response = static_cast<std::string*>(stream);

        // Write the response data to the string
        response->append((char*)ptr, size * nmemb);

        // Return the number of bytes written
        return size * nmemb;
    }
};

// Define the function that will get information from the Node.js server in JSON
std::string getInfoFromNodejsServer(const std::string& url) {
    // Create a client object
    Client client;

    // Get the response from the Node.js server
    std::string response = client.get(url);

    // Parse the response as JSON
    std::string info;
    if (response != "") {
        info = JSON::parse(response).dump();
    }

    return info;
}


#endif //ROBOT_NAVIGATION_WORKSHOP_CLIENT_H
