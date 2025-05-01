#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
#include <httplib.h>
#include <sstream>

class Database {
public:
    explicit Database(const std::string& conninfo);
    std::string serverUrl;
    ~Database();

    void logIn(const std::string& username, const std::string& email);
    void uploadRun(int userId, int levelId, int score, int runTime);
private:
    httplib::Client client;
    std::string conninfo;
    std::string getErrorMessage(int errorCode) const;
    void handleError(int errorCode, const std::string& message) const;
};
