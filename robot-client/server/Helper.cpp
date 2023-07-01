//
// Created by omer on 5/31/23.
//

#include "Helper.h"

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *response) {
    size_t totalSize = size * nmemb;
    response->append(static_cast<char *>(contents), totalSize);
    return totalSize;
}

Helper::Helper() {
    this->base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
}
std::string Helper::getResponse(const std::string &url) {
    CURL *curl;
    CURLcode res;
    std::string response;
    curl = curl_easy_init();
    if (curl) {
        long response_code;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            if (response_code == 200) {
                curl_easy_cleanup(curl);
                return response;
            } else {
                curl_easy_cleanup(curl);
                return "";
            }
        } else {
            curl_easy_cleanup(curl);
            return "";
        }
    }
    return "";
}


bool Helper::writeToFile(const std::string &filePath, const std::string &dataBase64) {
    // removing the start of the string that is not needed
    std::string data = dataBase64.substr(dataBase64.find(",") + 1);

    // opening the file using ofstream
    std::ofstream file(filePath);
    if(!file) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return false;
    }
    // converting from base64 to ascii
    std::string dataInAscii = this->base64_decode(data);

    // writing data to file
    file << dataInAscii;
    // closing file
    file.close();
    return true;
}

std::string Helper::base64_decode(const std::string &in) {
    std::string out;

    std::vector<int> T(256,-1);
    for (int i=0; i<64; i++) T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;

    int val=0, valb=-8;
    for (unsigned char c : in) {
        if (T[c] == -1) break;
        val = (val << 6) + T[c];
        valb += 6;
        if (valb >= 0) {
            out.push_back(char((val>>valb)&0xFF));
            valb -= 8;
        }
    }
    return out;
}


bool Helper::saveAsPng(std::string base64Data, const std::string &filePath) {
    std::ofstream imageFile(filePath, std::ios::binary);
    if (!imageFile) {
        std::cout << "Error opening file: " << filePath << std::endl;
        return false;
    }
    // deliemter is the comma
    base64Data = base64Data.substr(base64Data.find(",") + 1);
    std::string decodedData = base64Img_decode(base64Data);
    imageFile.write(decodedData.c_str(), decodedData.length());
    imageFile.close();
    std::cout << "Image saved as: " << filePath << std::endl;
    return true;
}

std::string Helper::base64Img_decode(const std::string &encoded_string) {
    const std::string base64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string decoded_string;
    std::vector<unsigned char> decoded_bytes;

    int i = 0;
    int j = 0;
    int in_len = encoded_string.length();
    unsigned char char_array_4[4], char_array_3[3];

    while (in_len-- && (encoded_string[i] != '=') && (isalnum(encoded_string[i]) || (encoded_string[i] == '+') || (encoded_string[i] == '/'))) {
        char_array_4[j++] = encoded_string[i++];

        if (j == 4) {
            for (j = 0; j < 4; j++) {
                char_array_4[j] = base64_chars.find(char_array_4[j]);
            }

            char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
            char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
            char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

            for (j = 0; j < 3; j++) {
                decoded_bytes.push_back(char_array_3[j]);
            }

            j = 0;
        }
    }

    if (j) {
        for (int i = j; i < 4; i++) {
            char_array_4[i] = 0;
        }
        for (int i = 0; i < 4; i++) {
            char_array_4[i] = base64_chars.find(char_array_4[i]);
        }
        char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (int i = 0; i < j - 1; i++) {
            decoded_bytes.push_back(char_array_3[i]);
        }
    }

    decoded_string.assign(decoded_bytes.begin(), decoded_bytes.end());
    return decoded_string;
}

bool Helper::postRequest(const std::string &url, const std::string &data) {
    // using curl to post data to the server
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        return true;
    }
    return false;
}


