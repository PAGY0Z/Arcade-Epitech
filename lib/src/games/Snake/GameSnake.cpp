/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** GameSnake
*/

#include "GameSnake.hpp"
#include <fstream>

namespace arcade
{
    extern "C"
    {
        IGameModule *entryPoint()
        {
            return new GameSnake();
        }

        int getType()
        {
            return 0;
        }
    }

    GameSnake::GameSnake()
    {
        _is_running = true;
        _player_name = "";
        _screen_size_x = 0;
        _screen_size_y = 0;
        for (char c = 'A'; c <= 'Z'; c++)
        {
            _textures[c] = "assets/common/" + std::string(1, c) + ".png";
        }
        for (char c = '0'; c <= '9'; c++)
            _textures[c] = "assets/common/" + std::string(1, c) + ".png";
        _textures[' '] = "assets/common/blank.png";
        _textures['_'] = "assets/common/blank.png";

        _textures['#'] = "assets/snake/map/wall.png";
        _textures['.'] = "assets/snake/map/grass.png";

        _textures['@'] = "assets/snake/item/apple.png";

        _textures['>'] = "assets/snake/snake/head.png";
        _textures['v'] = "assets/snake/snake/head.png";
        _textures['<'] = "assets/snake/snake/head.png";
        _textures['^'] = "assets/snake/snake/head.png";
        _textures['o'] = "assets/snake/snake/body.png";

        std::string line;
        std::ifstream file("assets/snake/map/map.txt");
        if (!file.is_open())
            throw GameSnakeException("Cannot open map file", FILE_DATA);
        while (std::getline(file, line))
        {
            for (std::size_t i = 0; i < line.size(); i++)
            {
                if (_textures.find(line[i]) == _textures.end())
                    throw GameSnakeException("Invalid character in map file", FILE_DATA);
                else if ('A' <= line[i] && line[i] <= 'Z')
                {
                    _interface.push_back(AEntity(i, _screen_size_y, line[i], Orientation::UP));
                }
                else if ('0' <= line[i] && line[i] <= '9')
                {
                    _interface.push_back(AEntity(i, _screen_size_y, line[i], Orientation::UP));
                }
                else if (line[i] == '#')
                {
                    _walls.push_back(AEntity(i, _screen_size_y, line[i], Orientation::UP));
                }
                else if (line[i] == '.')
                {
                    _grass.push_back(AEntity(i, _screen_size_y, line[i], Orientation::UP));
                }
            }

            if (line.size() > _screen_size_x)
                _screen_size_x = line.size();
            _screen_size_y++;
        }
        file.close();
        _snake.init(_grass);
        _apple.eaten(_grass, _snake.getEntities());
    }

    void GameSnake::receiveDisplayData(const struct DisplayData &data)
    {
        _system_events.clear();
        for (auto &event : data.events)
        {
            if (event.getType() == Type_e::UP)
                _snake.change_orientation(Orientation::UP);
            else if (event.getType() == Type_e::DOWN)
                _snake.change_orientation(Orientation::DOWN);
            else if (event.getType() == Type_e::LEFT)
                _snake.change_orientation(Orientation::LEFT);
            else if (event.getType() == Type_e::RIGHT)
                _snake.change_orientation(Orientation::RIGHT);
            else if (event.getType() == Type_e::ESCAPE)
                _is_running = false;
            else
                _system_events.push_back(event);
            _has_started = true;
            if (_has_lost == true)
                _is_running = false;
        }
        if (_has_started == false || _has_won == true || _has_lost == true)
        {
            delete &data;
            return;
        }
        _snake.move(data.delta, _walls);
        if (_snake.getHead().collide_with(_apple))
        {
            _apple.eaten(_grass, _snake.getEntities());
            _snake.grow_body();
            _score += 10;
        }
        if (_snake.is_alive() == false)
        {
            _has_lost = true;
        }
        delete &data;
    }

    const struct GameData &GameSnake::getGameData() const
    {
        struct GameData *data = new struct GameData;
        data->textures = _textures;
        data->screen_size_x = _screen_size_x;
        data->screen_size_y = _screen_size_y;
        for (auto &entity : _interface)
            data->entities.push_back(entity);
        for (auto &entity : _walls)
            data->entities.push_back(entity);
        for (auto &entity : _grass)
            data->entities.push_back(entity);
        data->entities.push_back(_apple);
        for (auto &entity : _snake.getEntities())
            data->entities.push_back(entity);
        data->entities.push_back(_snake.getHead());

        std::string score = std::to_string(_score);
        std::string high_score = std::to_string((_score > _highscore) ? _score : _highscore);

        for (std::size_t i = 0; i < score.size(); i++)
            data->entities.push_back(AEntity(7 + i, 1, score[i], Orientation::UP));
        for (std::size_t i = 0; i < high_score.size(); i++)
            data->entities.push_back(AEntity(16 + i, 1, high_score[i], Orientation::UP));
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

    std::vector<AEvent> GameSnake::getSystemEvents() const
    {
        return _system_events;
    }

    bool GameSnake::getIsRunning() const
    {
        return _is_running;
    }

    std::vector<AEntity> GameSnake::getStartInterface() const
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

    std::vector<AEntity> GameSnake::getGameOverInterface() const
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

    std::vector<AEntity> GameSnake::getWinInterface() const
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

    GameSnakeException::GameSnakeException(const std::string &additionnal_message, const std::string &file_data) : AGameException(additionnal_message, file_data)
    {
        _message = "GameSnakeException : " + _message;
    }
}