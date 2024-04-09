/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** GraphicSFML
*/

#ifndef GRAPHICSFML_HPP_
#define GRAPHICSFML_HPP_

#include "AGraphic.hpp"
#include <SFML/Graphics.hpp>

namespace arcade
{
    static const std::map<sf::Keyboard::Key, Type_e> sfml_event_matcher = {
        {sf::Keyboard::A, Type_e::KEY_A},
        {sf::Keyboard::B, Type_e::KEY_B},
        {sf::Keyboard::C, Type_e::KEY_C},
        {sf::Keyboard::D, Type_e::KEY_D},
        {sf::Keyboard::E, Type_e::KEY_E},
        {sf::Keyboard::F, Type_e::KEY_F},
        {sf::Keyboard::G, Type_e::KEY_G},
        {sf::Keyboard::H, Type_e::KEY_H},
        {sf::Keyboard::I, Type_e::KEY_I},
        {sf::Keyboard::J, Type_e::KEY_J},
        {sf::Keyboard::K, Type_e::KEY_K},
        {sf::Keyboard::L, Type_e::KEY_L},
        {sf::Keyboard::M, Type_e::KEY_M},
        {sf::Keyboard::N, Type_e::KEY_N},
        {sf::Keyboard::O, Type_e::KEY_O},
        {sf::Keyboard::P, Type_e::KEY_P},
        {sf::Keyboard::Q, Type_e::KEY_Q},
        {sf::Keyboard::R, Type_e::KEY_R},
        {sf::Keyboard::S, Type_e::KEY_S},
        {sf::Keyboard::T, Type_e::KEY_T},
        {sf::Keyboard::U, Type_e::KEY_U},
        {sf::Keyboard::V, Type_e::KEY_V},
        {sf::Keyboard::W, Type_e::KEY_W},
        {sf::Keyboard::X, Type_e::KEY_X},
        {sf::Keyboard::Y, Type_e::KEY_Y},
        {sf::Keyboard::Z, Type_e::KEY_Z},
        {sf::Keyboard::Numpad0, Type_e::NUM0},
        {sf::Keyboard::Numpad1, Type_e::NUM1},
        {sf::Keyboard::Numpad2, Type_e::NUM2},
        {sf::Keyboard::Numpad3, Type_e::NUM3},
        {sf::Keyboard::Numpad4, Type_e::NUM4},
        {sf::Keyboard::Numpad5, Type_e::NUM5},
        {sf::Keyboard::Numpad6, Type_e::NUM6},
        {sf::Keyboard::Numpad7, Type_e::NUM7},
        {sf::Keyboard::Numpad8, Type_e::NUM8},
        {sf::Keyboard::Numpad9, Type_e::NUM9},
        {sf::Keyboard::Space, Type_e::SPACE},
        {sf::Keyboard::Enter, Type_e::ENTER},
        {sf::Keyboard::BackSpace, Type_e::BACKSPACE},
        {sf::Keyboard::Escape, Type_e::ESCAPE},
        {sf::Keyboard::Up, Type_e::UP},
        {sf::Keyboard::Down, Type_e::DOWN},
        {sf::Keyboard::Left, Type_e::LEFT},
        {sf::Keyboard::Right, Type_e::RIGHT},
    };

    class GraphicSFML : public AGraphic
    {
    public:
        GraphicSFML();
        ~GraphicSFML() override;

        bool getIsRunning() const final;
        const struct DisplayData &getDisplayData() const final;
        void receiveGameData(const struct GameData &data) final;

        void update_texture_map(std::map<char, std::string> textures);

    private:
        sf::RenderWindow _window;
        sf::Clock _clock;
        const std::size_t _width_factor = 24;
        const std::size_t _height_factor = 24;
        std::map<char, std::pair<sf::Texture, std::string>> _textures;
    };

    class GraphicSFMLException : public AGraphicException
    {
    public:
        GraphicSFMLException(const std::string &additionnal_message, const std::string &file_data);
        virtual ~GraphicSFMLException() = default;
    };
}

#endif /* !GRAPHICSFML_HPP_ */
