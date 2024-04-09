/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** GameSnake
*/

#ifndef GAMESNAKE_HPP_
#define GAMESNAKE_HPP_

#include "AGame.hpp"
#include "Apple.hpp"
#include "Snake.hpp"

namespace arcade
{
    class GameSnake : public AGame
    {
    public:
        GameSnake();
        ~GameSnake() = default;

        void receiveDisplayData(const struct DisplayData &data) final;
        const struct GameData &getGameData() const final;
        std::vector<AEvent> getSystemEvents() const final;
        bool getIsRunning() const final;

        std::vector<AEntity> getStartInterface() const;
        std::vector<AEntity> getGameOverInterface() const;
        std::vector<AEntity> getWinInterface() const;

    private:
        bool _has_started = false;
        bool _has_lost = false;
        bool _has_won = false;
        bool _is_running;
        std::map<char, std::string> _textures;
        std::size_t _screen_size_x;
        std::size_t _screen_size_y;
        std::vector<AEvent> _system_events;

        std::vector<AEntity> _interface;
        std::vector<AEntity> _walls;
        std::vector<AEntity> _grass;

        Snake _snake = Snake();
        Apple _apple = Apple(0, 0, '@', Orientation::UP);
    };

    class GameSnakeException : public AGameException
    {
    public:
        GameSnakeException(const std::string &additionnal_message, const std::string &file_data);
        virtual ~GameSnakeException() = default;
    };
}

#endif /* !GAMESNAKE_HPP_ */
