//
// Created by void on 12/29/22.
//
#include "include/date.hpp"
#include "include/parser.hpp"
#include <algorithm>


using namespace std::chrono_literals;

std::pair<int, int> noty_date::extract_time_from_str(std::string str_time) {

    extract_spaces(str_time);
    int hour, min;
    auto time_it = str_time.find(':');
    if (time_it != std::string::npos) {
        std::string tmp_str;
        std::copy(str_time.begin(), str_time.begin() + time_it, std::back_inserter(tmp_str));
        hour = std::stoi(tmp_str);
        tmp_str.clear();
        std::copy(str_time.begin() + time_it + 1, str_time.end(), std::back_inserter(tmp_str));
        min = std::stoi(tmp_str);
    } else {
        std::cerr << "bad time format ! " << std::endl;
        std::exit(EXIT_FAILURE);
    }

    return {hour, min};
}

void noty_date::start(std::string str_time, std::string const &task) {
    std::lock_guard lock(mutex);
    extract_spaces(str_time);
    std::time_t t = std::time(nullptr);
    std::tm *now = std::localtime(&t);

    auto hour = now->tm_hour;
    auto min = now->tm_min;

    std::tm tm = {};
    std::stringstream ss(str_time);
    ss >> std::get_time(&tm, "%H:%M");

    auto tp = std::mktime(&tm);
    std::tm *custom_time = std::localtime(&tp);

    auto result_min = custom_time->tm_min - min;
    auto result_hour = custom_time->tm_hour - hour;

    if (result_min < 0) {
        custom_time->tm_hour -= 1;
        custom_time->tm_min += 60;
    }

    if (result_hour < 0) {
        std::cout << "time for task " << task << " has been expired.\n";
        goto end;
    }

    custom_time->tm_hour -= hour;
    custom_time->tm_min -= min;

    sleep_hour = custom_time->tm_hour;
    sleep_min = custom_time->tm_min;

    if (sleep_hour < 0) {
        std::cout << "time for task " << task << " has been expired.\n";
        goto end;
    }

    info.emplace_back(sleep_hour, sleep_min, task);
end:
    std::cout << "";
}

void noty_date::extract_spaces(std::string &str) {
    //removing all spaces
    str.erase(std::remove_if(str.begin(),
                             str.end(),
                             [](unsigned char x) { return std::isspace(x); }),
              str.end());
}


std::vector<std::tuple<int, int, std::string>> noty_date::get_info() {
    return info;
}
