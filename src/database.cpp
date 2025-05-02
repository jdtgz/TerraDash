#include "database.h"


Database::Database(const std::string& serverUrl) : serverUrl(serverUrl), client(serverUrl) {
    /** still nothing to do here
     * post to probably: localhost:5000
     *      post:           "/bridge/upload_run"
     *      body:           "{"user_id": int, "level_id": int, "score": int, "run_time": int}"
     *      content-type:   "application/json"
     * 
     *      post:           "/bridge/login_game"
     *      body:           "{"username": string, "password": string}"
     *      content-type:   "application/json"
     * 
     */

}

Database::~Database() {
    // No cleanup needed for cpr
}

void Database::logIn(const std::string& username, const std::string& email) {
    auto res = client.Post("/login_game", 
                            "{ \"username\": \"" + username + "\", \"email\": \"" + email + "\" }", 
                            "application/json");
}

void Database::uploadRun(int userId, int levelId, int score, int runTime) {
    auto res = client.Post("/upload_run", 
                            "{ \"user_id\": " + std::to_string(userId) + 
                            ", \"level_id\": " + std::to_string(levelId) + 
                            ", \"score\": " + std::to_string(score) + 
                            ", \"run_time\": " + std::to_string(runTime) + " }", 
                            "application/json");
}
