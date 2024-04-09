/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** GamePacman
*/

#include "GamePacman.hpp"
#include <fstream>
namespace arcade
{
    extern "C"
    {
        IGameModule *entryPoint()
        {
            return new GamePacman();
        }

        int getType()
        {
            return 0;
        }
    }

    GamePacman::GamePacman()
    {
        _is_running = true;
        _player_name = "";
        _screen_size_x = 0;
        _screen_size_y = 0;
        initGame();
    }

    void GamePacman::initGame()
    {
        try
        {
            std::vector<std::string> map;
            std::string line;
            std::ifstream file("./assets/pacman/map/map.txt");
            if (!file.is_open())
                throw GamePacmanException("Cannot open map file", FILE_DATA);
            while (std::getline(file, line))
            {
                map.push_back(line);
                if (line.size() > _screen_size_x)
                    _screen_size_x = line.size();
                _screen_size_y++;
            }
            file.close();
            initTextures();
            initEntities(map);
        }
        catch (const AException &except)
        {
            std::cerr << except.what() << std::endl;
            exit(except.getReturnValue());
        }
    }

    void GamePacman::initTextures()
    {
        for (char c = 'A'; c <= 'Z'; c++)
        {
            _textures[c] = "assets/common/" + std::string(1, c) + ".png";
        }
        for (char c = '0'; c <= '9'; c++)
            _textures[c] = "assets/common/" + std::string(1, c) + ".png";
        _textures[' '] = "assets/common/blank.png";
        _textures['_'] = "assets/pacman/map/background.png";
        _textures['>'] = "assets/common/blank.png";
        _textures['<'] = "assets/common/blank.png";

        _textures['/'] = "assets/pacman/map/corner_top_left.png";
        _textures['\\'] = "assets/pacman/map/corner_top_right.png";
        _textures['['] = "assets/pacman/map/corner_bottom_left.png";
        _textures[']'] = "assets/pacman/map/corner_bottom_right.png";
        _textures['|'] = "assets/pacman/map/line_vertical.png";
        _textures['-'] = "assets/pacman/map/line_horizontal.png";
        _textures['+'] = "assets/pacman/map/line_horizontal.png";

        _textures['p'] = "assets/pacman/player/pacman_open.png";

        _textures['g'] = "assets/pacman/enemies/ghost.png";
        _textures['!'] = "assets/pacman/enemies/dead.png";
        _textures['s'] = "assets/pacman/enemies/scared.png";

        _textures['.'] = "assets/pacman/items/pacgum_normal.png";
        _textures['o'] = "assets/pacman/items/pacgum_super.png";

        _textures['?'] = "assets/common/Z.png";
    }

    void GamePacman::initEntities(std::vector<std::string> map)
    {
        bool player_set = false;
        int ghost_count = 0;
        try
        {
            for (std::size_t y = 0; y < map.size(); y++)
            {
                for (std::size_t x = 0; x < map[y].size(); x++)
                {
                    if (map[y][x] == 'p')
                    {
                        if (player_set == true)
                            throw GamePacmanException("Multiple Players in map", FILE_DATA);
                        _player = Player(x, y, map[y][x], Orientation::RIGHT);
                        player_set = true;
                    }
                    else if (map[y][x] == 'g')
                    {
                        _ghosts.push_back(Ghost(x, y, map[y][x], Orientation::UP, 10 + ghost_count * 2));
                        ghost_count++;
                    }
                    else if (map[y][x] == '.')
                    {
                        _pacgums.push_back(Pacgum(x, y, map[y][x], Orientation::UP, false));
                    }
                    else if (map[y][x] == 'o')
                    {
                        _pacgums.push_back(Pacgum(x, y, map[y][x], Orientation::UP, true));
                    }
                    else if (map[y][x] == '/' || map[y][x] == '\\' || map[y][x] == '[' || map[y][x] == ']' || map[y][x] == '|' || map[y][x] == '-')
                    {
                        _walls.push_back(Wall(x, y, map[y][x], Orientation::UP, false));
                    }
                    else if (map[y][x] == '+')
                    {
                        _walls.push_back(Wall(x, y, map[y][x], Orientation::UP, true));
                    }
                    else if (map[y][x] == '>' || map[y][x] == '<')
                    {
                        _teleporters.push_back(Teleporter(x, y, map[y][x], (map[y][x] == '>') ? Orientation::RIGHT : Orientation::LEFT));
                    }
                    else if (('A' <= map[y][x] && map[y][x] <= 'Z') || ('0' <= map[y][x] && map[y][x] <= '9'))
                    {
                        _interface.push_back(AEntity(x, y, map[y][x], Orientation::UP));
                    }
                    else
                    {
                        if (_textures.find(map[y][x]) == _textures.end())
                            throw GamePacmanException("Texture not found for entity '" + std::string(1, map[y][x]) + "'", FILE_DATA);
                    }
                }
            }
            if (player_set == false)
                throw GamePacmanException("No Player in map", FILE_DATA);
            if (ghost_count == 0)
                throw GamePacmanException("No Ghost in map", FILE_DATA);
            if (_teleporters.size() != 2)
                throw GamePacmanException("Invalid number of teleporters in map", FILE_DATA);
            _teleporters[0].setDest(_teleporters[1].getPosX(), _teleporters[1].getPosY());
            _teleporters[1].setDest(_teleporters[0].getPosX(), _teleporters[0].getPosY());
        }
        catch (const AException &except)
        {
            std::cerr << except.what() << std::endl;
            exit(except.getReturnValue());
        }
    }

    std::vector<AEntity> GamePacman::getStartInterface() const
    {
        std::vector<AEntity> interface;
        std::string start = "PRESS ANY KEY TO START";
        int x = (_screen_size_x - start.size()) / 2;
        int y = _screen_size_y / 2;
        int text_size = start.size();
        for (int box_y = y - 2; box_y < y + 3; box_y++)
            for (int box_x = x - 2; box_x < x + text_size + 2; box_x++)
                interface.push_back(AEntity(box_x, box_y, '_', Orientation::UP));
        for (int i = 0; i < text_size; i++)
            interface.push_back(AEntity(x + i, y, start[i], Orientation::UP));
        return interface;
    }

    std::vector<AEntity> GamePacman::getGameOverInterface() const
    {
        std::vector<AEntity> interface;
        std::string game_over = "GAME OVER";
        int x = (_screen_size_x - game_over.size()) / 2;
        int y = _screen_size_y / 2;
        int text_size = game_over.size();
        for (int box_y = y - 2; box_y < y + 3; box_y++)
            for (int box_x = x - 2; box_x < x + text_size + 2; box_x++)
                interface.push_back(AEntity(box_x, box_y, '_', Orientation::UP));
        for (int i = 0; i < text_size; i++)
            interface.push_back(AEntity(x + i, y, game_over[i], Orientation::UP));
        return interface;
    }

    std::vector<AEntity> GamePacman::getWinInterface() const
    {
        std::vector<AEntity> interface;
        std::string win = "YOU WIN";
        std::string score = "WITH A SCORE OF " + std::to_string(_score);
        int win_text_size = win.size();
        int score_text_size = score.size();
        int win_x = (_screen_size_x - win_text_size) / 2;
        int win_y = _screen_size_y / 2;
        int score_x = (_screen_size_x - score_text_size) / 2;
        int score_y = win_y + 2;
        int min_start_x = (win_x < score_x) ? win_x : score_x;
        int max_width = (win_text_size > score_text_size) ? win_text_size : score_text_size;
        for (int box_y = win_y - 2; box_y < win_y + 4; box_y++)
            for (int box_x = min_start_x - 2; box_x < min_start_x + max_width + 2; box_x++)
                interface.push_back(AEntity(box_x, box_y, '_', Orientation::UP));
        for (int i = 0; i < win_text_size; i++)
            interface.push_back(AEntity(win_x + i, win_y, win[i], Orientation::UP));
        for (int i = 0; i < score_text_size; i++)
            interface.push_back(AEntity(score_x + i, score_y, score[i], Orientation::UP));
        return interface;
    }

    void GamePacman::receiveDisplayData(const struct DisplayData &data)
    {
        _system_events.clear();
        for (auto &event : data.events)
        {
            if (event.getType() == Type_e::UP)
                _player.setOrientation(Orientation::UP, _walls);
            else if (event.getType() == Type_e::DOWN)
                _player.setOrientation(Orientation::DOWN, _walls);
            else if (event.getType() == Type_e::LEFT)
                _player.setOrientation(Orientation::LEFT, _walls);
            else if (event.getType() == Type_e::RIGHT)
                _player.setOrientation(Orientation::RIGHT, _walls);
            else
                _system_events.push_back(event);

            _has_started = true;
            if (_has_lost == true)
                _is_running = false;
            if (_has_won == true)
            {
                reset();
                _has_won = false;
                _has_started = false;
            }
        }
        if (_has_started == false || _has_won == true || _has_lost == true)
        {
            delete &data;
            return;
        }
        _player.move(data.delta, _walls);
        _has_won = true;
        for (auto &pacgum : _pacgums)
            if (pacgum.getIsEaten() == false)
            {
                _has_won = false;
                if (_player.collide_with(pacgum))
                {
                    if (pacgum.getIsSuper() == true)
                        for (auto &ghost : _ghosts)
                            ghost.scare(_walls);
                    pacgum.eaten();
                    _score += (pacgum.getIsSuper() == true) ? 50 : 10;
                }
            }
        if (_has_won == true)
            _score += 1000 * _player.getLivesRemaining();
        for (auto &wall : _walls)
            if (wall.getIsTemporary() == true)
                if (wall.getIsOpen() == false)
                    wall.update(data.delta);
        for (auto &teleporter : _teleporters)
            if (_player.collide_with(teleporter))
                _player.teleport(teleporter);
        for (auto &ghost : _ghosts)
        {
            ghost.update(data.delta, _walls, _player);
            ghost.move(data.delta, _walls);
            if (_player.collide_with(ghost))
            {
                if (ghost.getIsAlive() == true)
                {
                    if (ghost.getIsScared() == true)
                    {
                        ghost.die(_walls);
                        count_ghost_killed++;
                        _score += 200 * count_ghost_killed;
                    }
                    else
                    {
                        _player.die();
                        _score -= 100;
                        if (_player.getLivesRemaining() == 0)
                        {
                            _has_lost = true;
                        }
                        for (auto &ghost : _ghosts)
                        {
                            ghost.respawn();
                        }
                        _player.respawn();
                    }
                }
            }
        }
        delete &data;
    }

    const struct GameData &GamePacman::getGameData() const
    {
        struct GameData *data = new GameData;
        data->screen_size_x = _screen_size_x;
        data->screen_size_y = _screen_size_y;
        data->textures = _textures;
        for (auto &entity : _interface)
            data->entities.push_back(entity);
        for (auto &wall : _walls)
            if (wall.getIsOpen() == false)
                data->entities.push_back(wall);
        for (auto &pacgum : _pacgums)
            if (pacgum.getIsEaten() == false)
                data->entities.push_back(pacgum);
        for (auto &ghost : _ghosts)
            data->entities.push_back(ghost);
        data->entities.push_back(_player);

        std::string lives = std::to_string(_player.getLivesRemaining());
        std::string score = std::to_string(_score);
        std::string high_score = std::to_string((_score > _highscore) ? _score : _highscore);

        for (std::size_t i = 0; i < score.size(); i++)
            data->entities.push_back(AEntity(0 + i, 1, score[i], Orientation::UP));
        for (std::size_t i = 0; i < high_score.size(); i++)
            data->entities.push_back(AEntity(9 + i, 1, high_score[i], Orientation::UP));
        for (std::size_t i = 0; i < lives.size(); i++)
            data->entities.push_back(AEntity(23 + i, 1, lives[i], Orientation::UP));
        if (_has_started == false)
            for (auto &entity : getStartInterface())
                data->entities.push_back(entity);
        if (_has_lost == true)
            for (auto &entity : getGameOverInterface())
                data->entities.push_back(entity);
        if (_has_won == true)
            for (auto &entity : getWinInterface())
                data->entities.push_back(entity);
        return *data;
    }

    void GamePacman::reset()
    {
        _player.reset();
        for (auto &ghost : _ghosts)
            ghost.reset();
        for (auto &pacgum : _pacgums)
            pacgum.reset();
        for (auto &wall : _walls)
            wall.reset();
        for (auto &teleporter : _teleporters)
            teleporter.reset();
    }

    std::vector<AEvent> GamePacman::getSystemEvents() const
    {
        return _system_events;
    }

    bool GamePacman::getIsRunning() const
    {
        return _is_running;
    }

    GamePacmanException::GamePacmanException(const std::string &additionnal_message, const std::string &file_data) : AGameException(additionnal_message, file_data)
    {
        _message = "GamePacmanException : " + _message;
    }
}
