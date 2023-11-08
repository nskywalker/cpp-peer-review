#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <iomanip>
#include <sstream>
#include <numeric>

class IntentReading {
    std::vector<int> user_pages;
    std::vector<int> reader_pages;
    int amount_readers = 0;
public:
    IntentReading() : user_pages(1e5), reader_pages(1e3){}
    double CheerUser(int user);
    void SavePageUser(int user, int page);
    static int GetFirstNumberFromInput(std::string_view& str);
};

void IntentReading::SavePageUser(int user, int page) {
    if (user_pages[user - 1] == 0){
        ++amount_readers;
    }
    ++reader_pages[page - 1];
    if (reader_pages[user_pages[user - 1] - 1] != 0) {
        --reader_pages[user_pages[user - 1] - 1];
    }
    user_pages[user - 1] = page;
}

double IntentReading::CheerUser(int user) {
    if (user_pages[user - 1] == 0) {
        return 0;
    }
    if (user_pages[user - 1] != 0 and amount_readers == 1) {
        return 1;
    }
    return static_cast<double>(std::accumulate(reader_pages.begin(), reader_pages.begin() + user_pages[user - 1] - 1, 0)) / (amount_readers - 1);
}

int IntentReading::GetFirstNumberFromInput(std::string_view& str) {
    size_t pos = str.find(' ');
    std::string num;
    if (pos < std::string_view::npos) {
        num = std::string{str.substr(0, pos)};
        str.remove_prefix(pos + 1);
        return std::stoi(num);
    }
    else {
        return std::stoi(std::string{str});
    }
}

void process(std::istream& in) {
    IntentReading reading;
    std::string request;
    std::string_view request_view;
    std::getline(in, request, '\n');
    int all_requests = std::stoi(request);
    for (int i = 0; i < all_requests; ++i) {
        std::getline(in, request, '\n');
        request_view = request;
        if (request_view.substr(0, 4) == "READ") {
            request_view.remove_prefix(5);
            int user = IntentReading::GetFirstNumberFromInput(request_view);
            int page = IntentReading::GetFirstNumberFromInput(request_view);
            reading.SavePageUser(user, page);
        } else if (request_view.substr(0, 5) == "CHEER") {
            request_view.remove_prefix(6);
            int user = IntentReading::GetFirstNumberFromInput(request_view);
            std::cout << std::setprecision(6) << reading.CheerUser(user) << std::endl;
        } else {
            throw std::invalid_argument("Denied request");
        }
    }
}

void Main() {
    process(std::cin);
}

void Test() {
    std::istringstream ss("12\n"
                          "CHEER 5\n"
                          "READ 1 10\n"
                          "CHEER 1\n"
                          "READ 2 5\n"
                          "READ 3 7\n"
                          "CHEER 2\n"
                          "CHEER 3\n"
                          "READ 3 10\n"
                          "CHEER 3\n"
                          "READ 3 11\n"
                          "CHEER 3\n"
                          "CHEER 1\n");
    process(ss);
}

int main() {
    Main();
//    Test();
}


