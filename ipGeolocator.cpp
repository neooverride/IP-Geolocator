#include <iostream>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <thread>
#include <chrono>
#include "asciiArt.hpp"

using namespace std;

#define BOLD_WHITE "\033[1;97m"
#define RESET "\033[0m"

size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void typewriter(const string& text, int delay_ms = 50) {
    cout << BOLD_WHITE; 
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay_ms));
    }
    cout << RESET << endl;  
}

string getPublicIP() {
    string ip;
    CURL *curl;
    CURLcode res;
    string response_string;

    string api_url = "https://api.ipify.org?format=json";

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, api_url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        } else {
            try {
                nlohmann::json json_response = nlohmann::json::parse(response_string);
                ip = json_response["ip"];
            } catch (const exception &e) {
                cerr << "Error parsing JSON: " << e.what() << endl;
            }
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return ip;
}

void getIPInfo(const string &ip) {
    string api_url = "https://ipinfo.io/" + ip + "/json";
    CURL *curl;
    CURLcode res;
    string response_string;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, api_url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
        } else {
            try {
                nlohmann::json json_response = nlohmann::json::parse(response_string);
                typewriter("[+] IP: " + json_response["ip"].get<string>());
                typewriter("[+] Country: " + json_response["country"].get<string>());
                typewriter("[+] City: " + json_response["city"].get<string>());
                typewriter("[+] Region: " + json_response["region"].get<string>());
            
                if (json_response.contains("timezone")) {
                    typewriter("[+] Timezone: " + json_response["timezone"].get<string>());
                } else {
                    typewriter("[+] Timezone: Not available");
                }
            
                string loc = json_response["loc"];
                typewriter("[+] Location: " + loc);

                size_t comma_pos = loc.find(",");

                if (json_response.contains("org")) {
                    typewriter("[+] Organization: " + json_response["org"].get<string>());
                } else {
                    typewriter("[+] Organization: Not available");
                }

                if (json_response.contains("postal")) {
                    typewriter("[+] Zip Code: " + json_response["postal"].get<string>());
                } else {
                    typewriter("[+] Zip Code: Not available");
                }

                cout << '\n'; 

                if (comma_pos != string::npos) {
                    string lat = loc.substr(0, comma_pos);
                    string lon = loc.substr(comma_pos + 1);
                    typewriter("Google Maps Link: https://www.google.com/maps?q=" + lat + "," + lon);
                }

            } catch (const exception &e) {
                cerr << "Error parsing JSON: " << e.what() << endl;
            }
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
}

int main() {
    string ip;
    printAsciiArt();
    typewriter("Do you want to use your public IP address (y/n)? ", 30);
    char choice;
    cout << BOLD_WHITE; 
    cin >> choice;
    cout << RESET; 

    
    if (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N') {
        cerr << BOLD_WHITE << "Invalid Input, termination has been terminated." << RESET << endl;
        return 1; 
    }

    if (choice == 'y' || choice == 'Y') {
        ip = getPublicIP();
        if (ip.empty()) {
            cerr << BOLD_WHITE << "Failed to fetch public IP." << RESET << endl;
            exit(1);
        }
        typewriter("Your public IP: " + ip);
    } else {
        typewriter("Enter the IP address you want to geolocate: ", 30);
        cout << BOLD_WHITE; 
        cin >> ip;
        cout << RESET; 
    }

    thread ipInfoThread([&]() {
        getIPInfo(ip);
    });

    ipInfoThread.join();

    return 0;
}
