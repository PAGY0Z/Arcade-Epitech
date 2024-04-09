/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** Snake
*/

#include "Snake.hpp"

namespace arcade
{
    void Snake::init(std::vector<AEntity> _grass)
    {
        float min_x = _grass[0].getPosX();
        float min_y = _grass[0].getPosY();
        float max_x = _grass[_grass.size() - 1].getPosX();
        float max_y = _grass[_grass.size() - 1].getPosY();

        int middle_x = (max_x - min_x) / 2;
        int middle_y = (max_y - min_y) / 2;

        _head = AEntity(middle_x + min_x, middle_y, '>' , Orientation::RIGHT);
        _body.push_back(AEntity(middle_x - 1 + min_x, middle_y, 'O', Orientation::RIGHT));
        _body.push_back(AEntity(middle_x - 2 + min_x, middle_y, 'O', Orientation::RIGHT));
        _body.push_back(AEntity(middle_x - 3 + min_x, middle_y, 'O', Orientation::RIGHT));
        _body.push_back(AEntity(middle_x - 4 + min_x, middle_y, 'O', Orientation::RIGHT));
    }

    std::vector<AEntity> Snake::getEntities() const
    {
        std::vector<AEntity> entities;
        entities.push_back(_head);
        for (auto &entity : _body) {
            entities.push_back(entity);
        }
        return entities;
    }

    void Snake::grow_body()
    {
        AEntity last = _body.back();
        AEntity new_entity = AEntity(last.getPosX(), last.getPosY(), 'O', last.getOrientation());
        _body.push_back(new_entity);
    }

    void Snake::move(float delta_time, std::vector<AEntity> _walls)
    {
        remaining_delta_time += delta_time;
        if (remaining_delta_time < 1 / speed_per_second)
            return;
        int move_count = remaining_delta_time / (1 / speed_per_second);
        remaining_delta_time -= move_count * (1 / speed_per_second);

        for (int i = 0; i < move_count; i++) {
            for (int i = _body.size() - 1; i > 0; i--) {
                _body[i].setPosX(_body[i - 1].getPosX());
                _body[i].setPosY(_body[i - 1].getPosY());
                _body[i].setOrientation(_body[i - 1].getOrientation());
            }
            _body[0].setPosX(_head.getPosX());
            _body[0].setPosY(_head.getPosY());
            _body[0].setOrientation(_head.getOrientation());

            switch (_head.getOrientation()) {
                case Orientation::UP:
                    _head.setPosY(_head.getPosY() - 1);
                    break;
                case Orientation::RIGHT:
                    _head.setPosX(_head.getPosX() + 1);
                    break;
                case Orientation::DOWN:
                    _head.setPosY(_head.getPosY() + 1);
                    break;
                case Orientation::LEFT:
                    _head.setPosX(_head.getPosX() - 1);
                    break;
            }
            for (auto &wall : _walls) {
                if (_head.collide_with(wall)) {
                    _is_alive = false;
                    return;
                }
            }
            for (auto &body : _body) {
                if (_head.collide_with(body)) {
                    _is_alive = false;
                    return;
                }
            }
        }
    }

    void Snake::change_orientation(Orientation orientation)
    {
        if (orientation == _head.getOrientation())
            return;
        if (orientation == Orientation::UP && _body[0].getOrientation() == Orientation::DOWN)
            return;
        if (orientation == Orientation::RIGHT && _body[0].getOrientation() == Orientation::LEFT)
            return;
        if (orientation == Orientation::DOWN && _body[0].getOrientation() == Orientation::UP)
            return;
        if (orientation == Orientation::LEFT && _body[0].getOrientation() == Orientation::RIGHT)
            return;
        if (orientation == Orientation::UP && _head.getOrientation() != Orientation::DOWN){
            _head.setOrientation(orientation);
            _head.setTexture('^');
        }
        else if (orientation == Orientation::RIGHT && _head.getOrientation() != Orientation::LEFT) {
            _head.setOrientation(orientation);
            _head.setTexture('>');
        }
        else if (orientation == Orientation::DOWN && _head.getOrientation() != Orientation::UP) {
            _head.setOrientation(orientation);
            _head.setTexture('v');
        }
        else if (orientation == Orientation::LEFT && _head.getOrientation() != Orientation::RIGHT) {
            _head.setOrientation(orientation);
            _head.setTexture('<');
        }
    }

    AEntity Snake::getHead() const
    {
        return _head;
    }

    bool Snake::is_alive() const
    {
        return _is_alive;
    }
}