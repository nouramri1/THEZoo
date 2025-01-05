#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;

#include <algorithm> 
#include <cctype>
#include <locale>

// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch) && ch != '.';
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

string askGPT(string q) {
        cout << "q: " << q << endl;
        const string body = "{\"model\": \"gpt-4\", \"messages\": [{\"role\": \"user\", \"content\": \"" + q + "\"}], \"temperature\": 0.25, \"max_tokens\": 50}";
        cpr::Response r = cpr::Post(cpr::Url{"https://api.openai.com/v1/chat/completions"},
                        cpr::Header{{"Authorization", "Bearer [INSERT API TOKEN HERE]"},
                            {"Content-type", "application/json"}},
                        cpr::Body{body});
        auto d = json::parse(r.text);
        string answer = d["choices"][0]["message"]["content"];
        trim(answer);
        cout << "response: " << answer << endl;
        return answer;
}

int main() {
    cout << askGPT("What is your name?") << endl;

    return 0;
}

