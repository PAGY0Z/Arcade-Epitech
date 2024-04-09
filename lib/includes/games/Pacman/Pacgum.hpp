/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** Pacgum
*/

#ifndef PACGUM_HPP_
#define PACGUM_HPP_

#include "AEntity.hpp"

namespace arcade
{
    class Pacgum : public AEntity
    {
    public:
        Pacgum(float pos_x, float pos_y, char texture, Orientation orientation, bool is_super);
        ~Pacgum() = default;

        bool getIsEaten() const;
        void eaten();
        bool getIsSuper() const;

        void reset();

    private:
        bool _is_super;
        bool _is_eaten;
    };
}

#endif /* !PACGUM_HPP_ */
