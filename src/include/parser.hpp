//
// Created by void on 12/29/22.
//

#ifndef TODO_NOTIFY_PARSER_HPP
#define TODO_NOTIFY_PARSER_HPP

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class noty_parser {
public:
    explicit noty_parser(fs::path const &file);
    void parse();
    std::vector<std::string> get_task();
    std::vector<std::string> get_time();

private:
    void parse_task(std::string_view str);
    void parse_time(std::string_view str);
    bool is_todo(std::string_view str);

private:
    std::string md_file;

    std::vector<std::string> tasks;
    std::vector<std::string> times;
};
#endif//TODO_NOTIFY_PARSER_HPP
