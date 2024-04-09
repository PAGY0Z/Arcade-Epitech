/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** GraphicSDL2
*/

#include "GraphicSDL2.hpp"

namespace arcade
{
	extern "C"
	{
		IDisplayModule *entryPoint()
		{
			return new GraphicSDL2();
		}

		int getType()
		{
			return 1;
		}
	}

	GraphicSDL2::GraphicSDL2()
	{
		try
		{
			_win = nullptr;
			_renderer = nullptr;
			if (SDL_Init(SDL_INIT_VIDEO) < 0)
				throw GraphicSDL2Exception("Failed to initialize SDL2", FILE_DATA);
			if (SDL_CreateWindowAndRenderer(1, 1, SDL_WINDOW_SHOWN, &_win, &_renderer) != 0)
				throw GraphicSDL2Exception("Failed to create window and renderer" + std::string(SDL_GetError()), FILE_DATA);
			if (_win == nullptr)
				throw GraphicSDL2Exception("Failed to create window", FILE_DATA);
			if (_renderer == nullptr)
				throw GraphicSDL2Exception("Failed to create renderer", FILE_DATA);
			SDL_SetWindowTitle(_win, "Arcade");
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
			_isRunning = true;
            _last_time_microseconds = SDL_GetTicks();
		}
		catch (AException &except)
		{
			std::cerr << except.what() << std::endl;
			exit(except.getReturnValue());
		}
	}

	GraphicSDL2::~GraphicSDL2()
	{
		SDL_QuitSubSystem(SDL_INIT_VIDEO);
		SDL_Quit();
	}

	bool GraphicSDL2::getIsRunning() const
	{
		return _isRunning;
	}

	void GraphicSDL2::_setIsRunning(bool val) const
	{
		_isRunning = val;
	}

	const struct DisplayData &GraphicSDL2::getDisplayData() const
	{
		struct DisplayData *data = new DisplayData;
		SDL_Event event;
		auto new_last_time_microseconds = SDL_GetTicks();
		data->delta = (float)(new_last_time_microseconds - _last_time_microseconds) / 1000.0;
		_last_time_microseconds = new_last_time_microseconds;
		data->events = std::vector<AEvent>();

		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				_setIsRunning(false);
			}
			else if (event.type == SDL_KEYDOWN)
			{
				if (sdl_event_matcher.find(event.key.keysym.sym) != sdl_event_matcher.end())
				{
					AEvent new_event = AEvent(sdl_event_matcher.at(event.key.keysym.sym), 0, 0);
					data->events.push_back(new_event);
				}
			}
		}
		return *data;
	}

	void GraphicSDL2::receiveGameData(const struct GameData &data)
	{
		try
		{
			SDL_Texture *texture = NULL;
			int texture_width = 0;
			int texture_height = 0;
			Orientation orientation = Orientation::UP;
			double angle = 0;
			SDL_SetWindowSize(_win, data.screen_size_x * _width_factor, data.screen_size_y * _height_factor);
			SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
			SDL_SetWindowPosition(_win, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
			SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
			SDL_RenderClear(_renderer);
			update_texture_map(data.textures);

			for (auto &entity : data.entities)
			{
				if (_textures.find(entity.getTexture()) == _textures.end())
					throw GraphicSDL2Exception("Texture not found for entity '", entity.getTexture() + "'");
				texture = _textures[entity.getTexture()].first;

				SDL_QueryTexture(texture, NULL, NULL, &texture_width, &texture_height);

				SDL_Rect texture_rect = {0, 0, texture_width, texture_height};

				SDL_Rect goal_rect = {
					(int)(entity.getPosX() * (float)_width_factor),
					(int)(entity.getPosY() * (float)_height_factor),
					(int)(_width_factor),
					(int)(_height_factor)};
				SDL_Point center = {(int)(_width_factor / 2), (int)(_height_factor / 2)};

				orientation = entity.getOrientation();
				angle = (int)orientation;

				SDL_RenderCopyEx(_renderer, texture, &texture_rect, &goal_rect, angle, &center, SDL_FLIP_NONE);
			}

			SDL_RenderPresent(_renderer);
			delete &data;
		}
		catch (AException &except)
		{
			std::cerr << except.what() << std::endl;
			_setIsRunning(false);
		}
	}

	void GraphicSDL2::update_texture_map(std::map<char, std::string> new_textures)
	{
		try
		{
			SDL_Texture *new_texture = nullptr;
			SDL_Surface *surface = nullptr;

			for (auto &texture_to_load : new_textures)
			{
				if (_textures.find(texture_to_load.first) == _textures.end())
				{
					surface = IMG_Load(texture_to_load.second.c_str());
					if (surface == nullptr)
						throw GraphicSDL2Exception("Error while loading texture_to_load \"" + texture_to_load.second + "\"", FILE_DATA);
					new_texture = SDL_CreateTextureFromSurface(_renderer, surface);
					if (new_texture == nullptr)
						throw GraphicSDL2Exception("Error while creating texture_to_load from surface", FILE_DATA);
					_textures[texture_to_load.first] = std::pair<SDL_Texture *, std::string>(new_texture, texture_to_load.second);
				} else if (_textures[texture_to_load.first].second != texture_to_load.second) {
					surface = IMG_Load(texture_to_load.second.c_str());
					if (surface == nullptr)
						throw GraphicSDL2Exception("Error while loading texture_to_load \"" + texture_to_load.second + "\"", FILE_DATA);
					new_texture = SDL_CreateTextureFromSurface(_renderer, surface);
					if (new_texture == nullptr)
						throw GraphicSDL2Exception("Error while creating texture_to_load from surface", FILE_DATA);
					_textures[texture_to_load.first] = std::pair<SDL_Texture *, std::string>(new_texture, texture_to_load.second);
				}
			}
		}
		catch (AException &except)
		{
			std::cerr << except.what() << std::endl;
			_setIsRunning(false);
		}
	}

	GraphicSDL2Exception::GraphicSDL2Exception(const std::string &additionnal_message, const std::string &file_data) : AGraphicException(additionnal_message, file_data)
	{
		_message = "GraphicSDL2Exception : " + _message;
	}
}
