//
// Created by void on 12/30/22.
//

#ifndef TODO_NOTIFY_NOTIFICATION_HPP
#define TODO_NOTIFY_NOTIFICATION_HPP
#include <string>
#include <string_view>
#include <tuple>
#include <vector>
#include <vlcpp/vlc.hpp>

class notify {
public:
    void notification(int hour, int min, std::string_view task, std::string const &music_path);

public:
    static void play_sound(std::string const &music_path);
    static void show_msg(std::string const &msg);
};

#endif//TODO_NOTIFY_NOTIFICATION_HPP
