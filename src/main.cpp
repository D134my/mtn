#include "include/date.hpp"
#include "include/notification.hpp"
#include "include/parser.hpp"
#include <thread>

int main(int argc, char **argv) {
    if (argc == 1) {
        std::cerr << "enter your markdown path " << std::endl;
        std::exit(EXIT_FAILURE);
    }

    noty_parser parser(argv[1]);
    parser.parse();
    auto tasks = parser.get_task();
    auto times = parser.get_time();
    noty_date date;

    for (int i = 0; i < times.size(); i++) {
        date.start(times.at(i), tasks.at(i));
    }

    auto info = date.get_info();
    std::vector<std::jthread> thread_pool;

    std::string music_path{"../resource/ringtone.mp3"};
    notify notification;


    for (auto const &[hour, min, task]: info) {
        //std::cout << "hour:" << hour << " min:" << min << " task: " << task << std::endl;
        thread_pool.push_back(
                std::jthread(&notify::notification, &notification, hour, min, task, music_path)

        );
    }
}
