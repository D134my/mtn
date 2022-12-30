//
// Created by void on 12/29/22.
//

#include "include/parser.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>


namespace rg = std::ranges;

noty_parser::noty_parser(fs::path const &file) {
    std::ifstream input{file};
    if (!input.is_open()) {
        std::cerr << "failed to open " << file << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::string str((std::istreambuf_iterator<char>(input)),
                    std::istreambuf_iterator<char>());

    md_file = str;
    input.close();
}
void noty_parser::parse() {
    std::string result;

    std::istringstream iss(md_file);

    for (std::string line; std::getline(iss, line);) {
        result = line + "\n";

        if (is_todo(result)) {
            parse_task(result);
            parse_time(result);
        }
    }
}

std::vector<std::string> noty_parser::get_time() {
    return times;
}
std::vector<std::string> noty_parser::get_task() {
    return tasks;
}

void noty_parser::parse_task(std::string_view str) {
    std::string task;
    auto it = str.find(']');
    auto it2 = str.find("->");

    if (it != std::string::npos && it2 != std::string::npos) {
        std::copy(str.begin() + it + 1, str.begin() + it2, std::back_inserter(task));

        tasks.push_back(task);
    }
}

bool noty_parser::is_todo(std::string_view str) {
    if (str.starts_with("- ["))
        return true;
    else
        return false;
}

void noty_parser::parse_time(std::string_view str) {
    static int count = 1;
    std::string time;
    auto result = str.find("->");
    if (result != std::string::npos) {
        std::copy(str.begin() + result + 2, str.end(), std::back_inserter(time));
        times.push_back(time);

    } else {
        std::cerr << "no time given at your:" << count << "th task" << std::endl;
    }
    count++;
}
