/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** GraphicNCurses
*/

#include "GraphicNCurses.hpp"
#include <unistd.h>

namespace arcade
{
    extern "C"
    {
        IDisplayModule *entryPoint()
        {
            return new GraphicNCurses();
        }

        int getType()
        {
            return 1;
        }
    }

    GraphicNCurses::GraphicNCurses()
    {
        try
        {
            _is_running = true;
            _window = initscr();
            if (_window == NULL)
                throw GraphicNCursesException("Failed to initialize ncurses window", FILE_DATA);
            curs_set(0);
            noecho();
            keypad(stdscr, TRUE);
            nodelay(stdscr, TRUE);
            scrollok(stdscr, TRUE);
            start_color();
            erase();
            auto now = std::chrono::system_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
            _last_time_microseconds = duration.count();
        }
        catch (AException &except)
        {
            std::cerr << except.what() << std::endl;
            exit(except.getReturnValue());
        }
    }

    GraphicNCurses::~GraphicNCurses()
    {
        erase();
        refresh();
    }

    bool GraphicNCurses::getIsRunning() const
    {
        return _is_running;
    }

    const struct DisplayData &GraphicNCurses::getDisplayData() const
    {
        struct DisplayData *data = new struct DisplayData;
        auto now = std::chrono::system_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
        int64_t new_last_time_microseconds = duration.count();
        data->delta = (float)(new_last_time_microseconds - _last_time_microseconds) / 1000000.0;
        _last_time_microseconds = new_last_time_microseconds;

        data->events = std::vector<AEvent>();
        if (kbhit())
        {
            int ch = getch();
            if (ncurses_event_matcher.find(ch) != ncurses_event_matcher.end())
            {
                AEvent new_event = AEvent(ncurses_event_matcher.at(ch), 0, 0);
                data->events.push_back(new_event);
            }
        }
        return *data;
    }

    void GraphicNCurses::receiveGameData(const struct GameData &data)
    {
        erase();
        char texture[] = {0, 0};
        int _height = 0;
        int _width = 0;
        getmaxyx(stdscr, _height, _width);
        int start_x = (_width - data.screen_size_x) / 2;
        int start_y = (_height - data.screen_size_y) / 2;

        for (auto &entity : data.entities)
        {
            texture[0] = entity.getTexture();
            mvprintw((int)(entity.getPosY()) + start_y, (int)(entity.getPosX()) + start_x, texture);
        }

        WINDOW *tmp_win = subwin(stdscr, data.screen_size_y + 2, data.screen_size_x + 2, start_y - 1, start_x - 1);
        box(tmp_win, 0, 0);
        delwin(tmp_win);
        delete &data;
        refresh();
    }

    bool GraphicNCurses::kbhit() const
    {
        int ch = getch();
        if (ch != ERR)
        {
            ungetch(ch);
            return true;
        }
        return false;
    }

    GraphicNCursesException::GraphicNCursesException(const std::string &additionnal_message, const std::string &file_data) : AGraphicException(additionnal_message, file_data)
    {
        _message = "GraphicNCursesException : " + _message;
    }
}
