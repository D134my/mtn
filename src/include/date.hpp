//
// Created by void on 12/29/22.
//

#ifndef TODO_NOTIFY_DATE_HPP
#define TODO_NOTIFY_DATE_HPP
#include <chrono>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <thread>
#include <tuple>
#include <vector>

class noty_date {
public:
    std::pair<int, int> extract_time_from_str(std::string str_time);
    void extract_spaces(std::string &str);
    void start(std::string str_time, std::string const &task);
    std::vector<std::tuple<int, int, std::string>> get_info();

private:
    int sleep_hour, sleep_min;
    std::vector<std::tuple<int, int, std::string>> info;
    std::mutex mutex;
};

#endif//TODO_NOTIFY_DATE_HPP
