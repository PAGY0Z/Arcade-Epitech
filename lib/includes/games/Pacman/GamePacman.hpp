/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** GamePacman
*/

#ifndef GAMEPACMAN_HPP_
#define GAMEPACMAN_HPP_

#include "AGame.hpp"
#include "Player.hpp"
#include "Ghost.hpp"
#include "Pacgum.hpp"
#include "Wall.hpp"
#include "Teleporter.hpp"

namespace arcade
{
    class GamePacman : public AGame
    {
    public:
        GamePacman();
        ~GamePacman() = default;

        void initGame();
        void initTextures();
        void initEntities(std::vector<std::string> map);

        std::vector<AEntity> getStartInterface() const;
        std::vector<AEntity> getGameOverInterface() const;
        std::vector<AEntity> getWinInterface() const;

        void receiveDisplayData(const struct DisplayData &data) final;
        const struct GameData &getGameData() const final;
        std::vector<AEvent> getSystemEvents() const final;
        bool getIsRunning() const final;

        void reset();

    private:
        bool _has_started = false;
        bool _has_lost = false;
        bool _has_won = false;
        bool _is_running;
        int count_ghost_killed = 0;
        Player _player = Player(0, 0, 'P', Orientation::RIGHT);
        std::vector<Ghost> _ghosts;
        std::vector<Wall> _walls;
        std::vector<Teleporter> _teleporters;
        std::vector<Pacgum> _pacgums;
        std::vector<AEntity> _interface;
        std::vector<AEvent> _system_events;
        std::map<char, std::string> _textures;
        std::size_t _screen_size_x;
        std::size_t _screen_size_y;
    };

    class GamePacmanException : public AGameException
    {
    public:
        GamePacmanException(const std::string &additionnal_message, const std::string &file_data);
        virtual ~GamePacmanException() = default;
    };
}

#endif /* !GAMEPACMAN_HPP_ */
