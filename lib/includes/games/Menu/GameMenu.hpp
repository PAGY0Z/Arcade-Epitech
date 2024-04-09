/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** GameMenu
*/

#ifndef GAMEMENU_HPP_
#define GAMEMENU_HPP_

#include "AGame.hpp"

namespace arcade
{
    class GameMenu : public AGame
    {
    public:
        GameMenu();
        ~GameMenu() = default;

        bool getIsRunning() const final;
        void receiveDisplayData(const struct DisplayData &data) final;
        const struct GameData &getGameData() const final;
        std::vector<AEvent> getSystemEvents() const final;

    private:
        void loadInterface();
        bool collide_with_buttons(std::vector<AEntity> buttons, std::size_t pos_x, std::size_t pos_y) const;
        std::vector<AEntity> getTextEntities(std::string text, std::size_t pos_y) const;
        const std::size_t max_player_name_size = 10;
        bool _is_running;

        std::map<char, std::string> _textures;
        std::vector<AEvent> _system_events;

        std::size_t _screen_size_x;
        std::size_t _screen_size_y;

        std::vector<AEntity> _interface;
        std::vector<AEntity> _buttons_up;
        std::vector<AEntity> _buttons_down;
        std::vector<AEntity> _buttons_left;
        std::vector<AEntity> _buttons_right;
    };

    class GameMenuException : public AGameException
    {
    public:
        GameMenuException(const std::string &additionnal_message, const std::string &file_data);
        virtual ~GameMenuException() = default;
    };
}

#endif /* !GAMEMENU_HPP_ */
