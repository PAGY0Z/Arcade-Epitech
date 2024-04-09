/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** GraphicSFML
*/

#include "GraphicSFML.hpp"

namespace arcade
{
    extern "C"
    {
        IDisplayModule *entryPoint()
        {
            return new GraphicSFML();
        }

        int getType()
        {
            return 1;
        }
    }

    GraphicSFML::GraphicSFML()
    {
        _window.create(sf::VideoMode(1, 1), "Arcade");
        _window.setFramerateLimit(60);
        _clock.restart();
    }

    GraphicSFML::~GraphicSFML()
    {
        if (_window.isOpen())
            _window.close();
    }

    bool GraphicSFML::getIsRunning() const
    {
        return _window.isOpen();
    }

    const struct DisplayData &GraphicSFML::getDisplayData() const
    {
        struct DisplayData *data = new DisplayData;
        data->delta = const_cast<sf::Clock *>(&_clock)->getElapsedTime().asSeconds();
        const_cast<sf::Clock *>(&_clock)->restart();
        data->events = std::vector<AEvent>();
        sf::Event event;
        while (const_cast<sf::RenderWindow *>(&_window)->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                const_cast<sf::RenderWindow *>(&_window)->close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (sfml_event_matcher.find(event.key.code) != sfml_event_matcher.end())
                {
                    AEvent new_event = AEvent(sfml_event_matcher.at(event.key.code), 0, 0);
                    data->events.push_back(new_event);
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    AEvent new_event = AEvent(Type_e::MOUSE_LEFT, event.mouseButton.x / _width_factor, event.mouseButton.y / _height_factor);
                    data->events.push_back(new_event);
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    AEvent new_event = AEvent(Type_e::MOUSE_RIGHT, event.mouseButton.x / _width_factor, event.mouseButton.y / _height_factor);
                    data->events.push_back(new_event);
                }
            }
        }
        return *data;
    }

    void GraphicSFML::receiveGameData(const struct GameData &data)
    {
        try
        {
            _window.setSize(sf::Vector2u(data.screen_size_x * _width_factor, data.screen_size_y * _height_factor));
            _window.setView(sf::View(sf::FloatRect(0, 0, data.screen_size_x * _width_factor, data.screen_size_y * _height_factor)));
            _window.setPosition(sf::Vector2i(1920 / 2 - data.screen_size_x * _width_factor / 2, 1080 / 2 - data.screen_size_y * _height_factor / 2));
            _window.clear(sf::Color::Black);
            update_texture_map(data.textures);
            for (auto &entity : data.entities)
            {
                sf::Sprite sprite;
                if (_textures.find(entity.getTexture()) == _textures.end())
                    throw GraphicSFMLException("Texture not found for entity '" + std::to_string(entity.getTexture()) + "'", FILE_DATA);
                sprite.setTexture(_textures[entity.getTexture()].first);
                sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y / 2);
                sprite.setRotation(static_cast<float>(entity.getOrientation()));
                sprite.setScale((float)_width_factor / (float)sprite.getTexture()->getSize().x, (float)_height_factor / (float)sprite.getTexture()->getSize().y);
                sprite.setPosition(entity.getPosX() * _width_factor + _width_factor / 2, entity.getPosY() * _height_factor + _height_factor / 2);
                _window.draw(sprite);
            }
            _window.display();
            delete &data;
        }
        catch (AException &except)
        {
            std::cerr << except.what() << std::endl;
            _window.close();
        }
    }

    void GraphicSFML::update_texture_map(std::map<char, std::string> textures)
    {
        try
        {
            for (auto &texture : textures)
            {
                if (_textures.find(texture.first) == _textures.end())
                {
                    sf::Texture new_texture;
                    if (!new_texture.loadFromFile(texture.second))
                        throw GraphicSFMLException("Error while loading texture '" + texture.second + "'", FILE_DATA);
                    _textures[texture.first] = std::pair<sf::Texture, std::string>(new_texture, texture.second);
                }
                else if (_textures[texture.first].second != texture.second)
                {
                    sf::Texture new_texture;
                    if (!new_texture.loadFromFile(texture.second))
                        throw GraphicSFMLException("Error while loading texture '" + texture.second + "'", FILE_DATA);
                    _textures[texture.first] = std::pair<sf::Texture, std::string>(new_texture, texture.second);
                }
            }
        }
        catch (AException &except)
        {
            std::cerr << except.what() << std::endl;
            _window.close();
        }
    }

    GraphicSFMLException::GraphicSFMLException(const std::string &additionnal_message, const std::string &file_data) : AGraphicException(additionnal_message, file_data)
    {
        _message = "GraphicSFMLException : " + _message;
    }
}
