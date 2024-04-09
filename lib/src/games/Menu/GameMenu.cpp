/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** GameMenu
*/

#include "GameMenu.hpp"
#include <fstream>
#include <iostream>

namespace arcade
{
    extern "C"
    {
        IGameModule *entryPoint()
        {
            return new GameMenu();
        }

        int getType()
        {
            return 0;
        }
    }

    GameMenu::GameMenu()
    {
        _is_running = true;
        _player_name = "";
        for (char c = 'A'; c <= 'Z'; c++)
        {
            _textures[c] = "assets/common/" + std::string(1, c) + ".png";
        }
        for (char c = '0'; c <= '9'; c++)
            _textures[c] = "assets/common/" + std::string(1, c) + ".png";
        _textures[' '] = "assets/common/blank.png";
        _textures['_'] = "assets/common/blank.png";
        _textures['^'] = "assets/common/arrow_up.png";
        _textures['v'] = "assets/common/arrow_up.png";
        _textures['>'] = "assets/common/arrow_up.png";
        _textures['<'] = "assets/common/arrow_up.png";
        _screen_size_x = 0;
        _screen_size_y = 0;
        _player_name = "";
        loadInterface();
    }

    bool GameMenu::getIsRunning() const
    {
        return _is_running;
    }

    void GameMenu::loadInterface()
    {
        try
        {
            std::string line;
            std::ifstream file("assets/menu/map.txt");
            if (!file.is_open())
                throw GameMenuException("Could not open the map file for the menu", FILE_DATA);
            while (std::getline(file, line))
            {
                for (std::size_t i = 0; i < line.size(); i++)
                {
                    if (line[i] == ' ')
                    {
                        continue;
                    }
                    else if (('A' <= line[i] && line[i] <= 'Z') || ('0' <= line[i] && line[i] <= '9'))
                    {
                        _interface.push_back(AEntity(i, _screen_size_y, line[i], Orientation::UP));
                    }
                    else if (line[i] == '^' || line[i] == 'v' || line[i] == '<' || line[i] == '>')
                    {
                        if (line[i] == '^')
                            _buttons_up.push_back(AEntity(i, _screen_size_y, line[i], Orientation::UP));
                        if (line[i] == '>')
                            _buttons_right.push_back(AEntity(i, _screen_size_y, line[i], Orientation::RIGHT));
                        if (line[i] == 'v')
                            _buttons_down.push_back(AEntity(i, _screen_size_y, line[i], Orientation::DOWN));
                        if (line[i] == '<')
                            _buttons_left.push_back(AEntity(i, _screen_size_y, line[i], Orientation::LEFT));
                    }
                }
                if (line.size() > _screen_size_x)
                    _screen_size_x = line.size();
                _screen_size_y++;
            }
            file.close();
        }
        catch (AException &except)
        {
            std::cerr << except.what() << std::endl;
            exit(except.getReturnValue());
        }
    }

    bool GameMenu::collide_with_buttons(std::vector<AEntity> buttons, std::size_t pos_x, std::size_t pos_y) const
    {
        AEntity click = AEntity(pos_x, pos_y, ' ', Orientation::UP);
        for (auto &button : buttons)
        {
            if (click.collide_with(button))
                return true;
        }
        return false;
    }

    void GameMenu::receiveDisplayData(const struct DisplayData &data)
    {
        _system_events.clear();
        for (auto &event : data.events)
        {
            if (Type_e::KEY_A <= event.getType() && event.getType() <= Type_e::KEY_Z)
            {
                if (_player_name.size() < max_player_name_size)
                    _player_name += static_cast<char>(static_cast<int>(event.getType()) + 'A');
            }
            else if (Type_e::NUM0 <= event.getType() && event.getType() <= Type_e::NUM9)
            {
                if (_player_name.size() < max_player_name_size)
                    _player_name += static_cast<char>(static_cast<int>(event.getType()) - static_cast<int>(Type_e::NUM0) + '0');
            }
            else if (event.getType() == Type_e::SPACE)
            {
                if (_player_name.size() < max_player_name_size)
                    _player_name += ' ';
            }
            else if (event.getType() == Type_e::ENTER)
            {
                _is_running = false;
            }
            else if (event.getType() == Type_e::BACKSPACE)
            {
                if (_player_name.size() > 0)
                    _player_name.erase(_player_name.size() - 1);
            }
            else if (event.getType() == Type_e::ESCAPE)
            {
                _system_events.push_back(AEvent(Type_e::ESCAPE, 0, 0));
            }
            else if (event.getType() == Type_e::UP)
            {
                _system_events.push_back(AEvent(Type_e::GET_NEXT_GAME_LIBRARY, 0, 0));
            }
            else if (event.getType() == Type_e::DOWN)
            {
                _system_events.push_back(AEvent(Type_e::GET_PREVIOUS_GAME_LIBRARY, 0, 0));
            }
            else if (event.getType() == Type_e::LEFT)
            {
                _system_events.push_back(AEvent(Type_e::GET_PREVIOUS_GRAPHIC_LIBRARY, 0, 0));
            }
            else if (event.getType() == Type_e::RIGHT)
            {
                _system_events.push_back(AEvent(Type_e::GET_NEXT_GRAPHIC_LIBRARY, 0, 0));
            }
            else if (event.getType() == Type_e::MOUSE_LEFT)
            {
                if (collide_with_buttons(_buttons_up, event.getValueX(), event.getValueY()))
                    _system_events.push_back(AEvent(Type_e::GET_NEXT_GAME_LIBRARY, 0, 0));
                if (collide_with_buttons(_buttons_down, event.getValueX(), event.getValueY()))
                    _system_events.push_back(AEvent(Type_e::GET_PREVIOUS_GAME_LIBRARY, 0, 0));
                if (collide_with_buttons(_buttons_left, event.getValueX(), event.getValueY()))
                    _system_events.push_back(AEvent(Type_e::GET_PREVIOUS_GRAPHIC_LIBRARY, 0, 0));
                if (collide_with_buttons(_buttons_right, event.getValueX(), event.getValueY()))
                    _system_events.push_back(AEvent(Type_e::GET_NEXT_GRAPHIC_LIBRARY, 0, 0));
            }
            else if (event.getType() == Type_e::MOUSE_RIGHT)
            {
                if (collide_with_buttons(_buttons_up, event.getValueX(), event.getValueY()))
                    _system_events.push_back(AEvent(Type_e::GET_NEXT_GAME_LIBRARY, 0, 0));
                if (collide_with_buttons(_buttons_down, event.getValueX(), event.getValueY()))
                    _system_events.push_back(AEvent(Type_e::GET_PREVIOUS_GAME_LIBRARY, 0, 0));
                if (collide_with_buttons(_buttons_left, event.getValueX(), event.getValueY()))
                    _system_events.push_back(AEvent(Type_e::GET_PREVIOUS_GRAPHIC_LIBRARY, 0, 0));
                if (collide_with_buttons(_buttons_right, event.getValueX(), event.getValueY()))
                    _system_events.push_back(AEvent(Type_e::GET_NEXT_GRAPHIC_LIBRARY, 0, 0));
            }
        }
        if (_is_highscore_set == false) {
            _system_events.push_back(AEvent(Type_e::GET_HIGHSCORE, 0, 0));
            _is_highscore_set = true;
        }
        delete &data;
    }

    std::vector<AEntity> GameMenu::getTextEntities(std::string text, std::size_t pos_y) const
    {
        int pos_x = (_screen_size_x - text.size()) / 2;
        std::vector<AEntity> entities;
        for (std::size_t i = 0; i < text.size(); i++)
        {
            if ('a' <= text[i] && text[i] <= 'z')
                entities.push_back(AEntity(pos_x + i, pos_y, text[i] - 'a' + 'A', Orientation::UP));
            else if (_textures.find(text[i]) != _textures.end())
                entities.push_back(AEntity(pos_x + i, pos_y, text[i], Orientation::UP));
            else
                entities.push_back(AEntity(pos_x + i, pos_y, ' ', Orientation::UP));
        }
        return entities;
    }

    const struct GameData &GameMenu::getGameData() const
    {
        struct GameData *data = new GameData;
        data->screen_size_x = _screen_size_x;
        data->screen_size_y = _screen_size_y;
        data->textures = _textures;
        data->entities = _interface;

        for (auto &game_to_load : getTextEntities(_game_name, 10))
            data->entities.push_back(game_to_load);
        for (auto &game_highscore : getTextEntities(std::to_string(_highscore), 16))
            data->entities.push_back(game_highscore);
        for (auto &graphic_to_load : getTextEntities(_graphic_name, 23))
            data->entities.push_back(graphic_to_load);
        for (std::size_t i = 0; i < _player_name.size(); i++)
            data->entities.push_back(AEntity(12 + i, 29, _player_name[i], Orientation::UP));

        for (auto &button : _buttons_up)
            data->entities.push_back(button);
        for (auto &button : _buttons_down)
            data->entities.push_back(button);
        for (auto &button : _buttons_left)
            data->entities.push_back(button);
        for (auto &button : _buttons_right)
            data->entities.push_back(button);
        return *data;
    }

    std::vector<AEvent> GameMenu::getSystemEvents() const
    {
        return _system_events;
    }

    GameMenuException::GameMenuException(const std::string &additionnal_message, const std::string &file_data) : AGameException(additionnal_message, file_data)
    {
        _message = "GameMenuException : " + _message;
    }
}
