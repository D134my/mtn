//
// Created by void on 12/30/22.
//
#include "include/notification.hpp"
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>


void notify::notification(int hour, int min, std::string_view task, std::string const &music_path) {

    std::cout << "task -> " << task << "will finish at " << hour << ':' << min << std::endl;
    std::this_thread::sleep_for(std::chrono::hours(hour));
    std::this_thread::sleep_for(std::chrono::minutes(min));

    std::string msg = "dunstify  task'-> " + std::string(task) + "'";


    std::jthread t1(&notify::play_sound, music_path);
    std::jthread t2(&notify::show_msg, msg);
}


void notify::play_sound(std::string const &music_path) {
    auto instance = VLC::Instance(0, nullptr);
    auto media = VLC::Media(instance, music_path, VLC::Media::FromPath);
    auto player = VLC::MediaPlayer(media);
    player.play();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    player.stop();
}

void notify::show_msg(std::string const &msg) {
    auto p_result = popen(msg.c_str(), "r");
    int ch{};
    if (!p_result) {
        std::cerr << "popen failed\n";
        exit(EXIT_FAILURE);
    }
    while ((ch = fgetc(p_result)) != EOF)
        putchar(ch);

    pclose(p_result);
}
