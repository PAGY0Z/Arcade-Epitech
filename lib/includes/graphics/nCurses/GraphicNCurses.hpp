/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** GraphicNCurses
*/

#ifndef GRAPHICNCURSES_HPP_
#define GRAPHICNCURSES_HPP_

#include "AGraphic.hpp"
#include <chrono>
#include <ncurses.h>
#include <map>

namespace arcade
{
    static const std::map<int, Type_e> ncurses_event_matcher = {
        {'a', Type_e::KEY_A},
        {'b', Type_e::KEY_B},
        {'c', Type_e::KEY_C},
        {'d', Type_e::KEY_D},
        {'e', Type_e::KEY_E},
        {'f', Type_e::KEY_F},
        {'g', Type_e::KEY_G},
        {'h', Type_e::KEY_H},
        {'i', Type_e::KEY_I},
        {'j', Type_e::KEY_J},
        {'k', Type_e::KEY_K},
        {'l', Type_e::KEY_L},
        {'m', Type_e::KEY_M},
        {'n', Type_e::KEY_N},
        {'o', Type_e::KEY_O},
        {'p', Type_e::KEY_P},
        {'q', Type_e::KEY_Q},
        {'r', Type_e::KEY_R},
        {'s', Type_e::KEY_S},
        {'t', Type_e::KEY_T},
        {'u', Type_e::KEY_U},
        {'v', Type_e::KEY_V},
        {'w', Type_e::KEY_W},
        {'x', Type_e::KEY_X},
        {'y', Type_e::KEY_Y},
        {'z', Type_e::KEY_Z},
        {'A', Type_e::KEY_A},
        {'B', Type_e::KEY_B},
        {'C', Type_e::KEY_C},
        {'D', Type_e::KEY_D},
        {'E', Type_e::KEY_E},
        {'F', Type_e::KEY_F},
        {'G', Type_e::KEY_G},
        {'H', Type_e::KEY_H},
        {'I', Type_e::KEY_I},
        {'J', Type_e::KEY_J},
        {'K', Type_e::KEY_K},
        {'L', Type_e::KEY_L},
        {'M', Type_e::KEY_M},
        {'N', Type_e::KEY_N},
        {'O', Type_e::KEY_O},
        {'P', Type_e::KEY_P},
        {'Q', Type_e::KEY_Q},
        {'R', Type_e::KEY_R},
        {'S', Type_e::KEY_S},
        {'T', Type_e::KEY_T},
        {'U', Type_e::KEY_U},
        {'V', Type_e::KEY_V},
        {'W', Type_e::KEY_W},
        {'X', Type_e::KEY_X},
        {'Y', Type_e::KEY_Y},
        {'Z', Type_e::KEY_Z},
        {'0', Type_e::NUM0},
        {'1', Type_e::NUM1},
        {'2', Type_e::NUM2},
        {'3', Type_e::NUM3},
        {'4', Type_e::NUM4},
        {'5', Type_e::NUM5},
        {'6', Type_e::NUM6},
        {'7', Type_e::NUM7},
        {'8', Type_e::NUM8},
        {'9', Type_e::NUM9},
        {' ', Type_e::SPACE},
        {'\n', Type_e::ENTER},
        {27, Type_e::ESCAPE},
        {KEY_BACKSPACE, Type_e::BACKSPACE},
        {KEY_UP, Type_e::UP},
        {KEY_DOWN, Type_e::DOWN},
        {KEY_LEFT, Type_e::LEFT},
        {KEY_RIGHT, Type_e::RIGHT},
    };

    class GraphicNCurses : public AGraphic
    {
    public:
        GraphicNCurses();
        ~GraphicNCurses() override;

        bool getIsRunning() const final;
        const struct DisplayData &getDisplayData() const final;
        void receiveGameData(const struct GameData &data) final;

    private:
        bool kbhit() const;
        WINDOW *_window;
        bool _is_running;
        mutable int64_t _last_time_microseconds;
    };

    class GraphicNCursesException : public AGraphicException
    {
    public:
        GraphicNCursesException(const std::string &additionnal_message, const std::string &file_data);
        virtual ~GraphicNCursesException() = default;
    };
}

#endif /* !GRAPHICNCURSES_HPP_ */
