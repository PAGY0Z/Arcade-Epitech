/*
** EPITECH PROJECT, 2024
** B-OOP-400-RUN-4-1-arcade-etienne.techer
** File description:
** GraphicSDL2
*/

#ifndef GRAPHICSDL2_HPP_
#define GRAPHICSDL2_HPP_

#include "AGraphic.hpp"
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace arcade
{
	static const std::map<SDL_Keycode, Type_e> sdl_event_matcher = {
		{SDLK_a, Type_e::KEY_A},
		{SDLK_b, Type_e::KEY_B},
		{SDLK_c, Type_e::KEY_C},
		{SDLK_d, Type_e::KEY_D},
		{SDLK_e, Type_e::KEY_E},
		{SDLK_f, Type_e::KEY_F},
		{SDLK_g, Type_e::KEY_G},
		{SDLK_h, Type_e::KEY_H},
		{SDLK_i, Type_e::KEY_I},
		{SDLK_j, Type_e::KEY_J},
		{SDLK_k, Type_e::KEY_K},
		{SDLK_l, Type_e::KEY_L},
		{SDLK_m, Type_e::KEY_M},
		{SDLK_n, Type_e::KEY_N},
		{SDLK_o, Type_e::KEY_O},
		{SDLK_p, Type_e::KEY_P},
		{SDLK_q, Type_e::KEY_Q},
		{SDLK_r, Type_e::KEY_R},
		{SDLK_s, Type_e::KEY_S},
		{SDLK_t, Type_e::KEY_T},
		{SDLK_u, Type_e::KEY_U},
		{SDLK_v, Type_e::KEY_V},
		{SDLK_w, Type_e::KEY_W},
		{SDLK_x, Type_e::KEY_X},
		{SDLK_y, Type_e::KEY_Y},
		{SDLK_z, Type_e::KEY_Z},
		{SDLK_KP_0, Type_e::NUM0},
		{SDLK_KP_1, Type_e::NUM1},
		{SDLK_KP_2, Type_e::NUM2},
		{SDLK_KP_3, Type_e::NUM3},
		{SDLK_KP_4, Type_e::NUM4},
		{SDLK_KP_5, Type_e::NUM5},
		{SDLK_KP_6, Type_e::NUM6},
		{SDLK_KP_7, Type_e::NUM7},
		{SDLK_KP_8, Type_e::NUM8},
		{SDLK_KP_9, Type_e::NUM9},
		{SDLK_SPACE, Type_e::SPACE},
		{SDLK_RETURN, Type_e::ENTER},
		{SDLK_BACKSPACE, Type_e::BACKSPACE},
		{SDLK_ESCAPE, Type_e::ESCAPE},
		{SDLK_UP, Type_e::UP},
		{SDLK_DOWN, Type_e::DOWN},
		{SDLK_LEFT, Type_e::LEFT},
		{SDLK_RIGHT, Type_e::RIGHT},
	};

	class GraphicSDL2 : public AGraphic
	{
	public:
		GraphicSDL2();
		~GraphicSDL2() override;

		bool getIsRunning() const final;
		const struct DisplayData &getDisplayData() const final;
		void receiveGameData(const struct GameData &data) final;

		void update_texture_map(std::map<char, std::string> textures);

	private:
		SDL_Window *_win;
		SDL_Renderer *_renderer;
		mutable bool _isRunning;
		const std::size_t _width_factor = 24;
		const std::size_t _height_factor = 24;
		std::map<char, std::pair<SDL_Texture *, std::string>> _textures;
		mutable int64_t _last_time_microseconds;

		void _setIsRunning(bool val) const;
	};

	class GraphicSDL2Exception : public AGraphicException
	{
	public:
		GraphicSDL2Exception(const std::string &additionnal_message, const std::string &file_data);
		virtual ~GraphicSDL2Exception() = default;
	};
}

#endif /* !GRAPHICSDL2_HPP_ */
