#pragma once

#include <vector>

#include <SDL.h>

#include "controls/controller_buttons.h"
#include "controls/game_controls.h"

namespace devilution {

struct Monster;

class GameController {
	static std::vector<GameController> controllers_;

public:
	static void Add(int joystickIndex);
	static void Remove(SDL_JoystickID instanceId);
	static GameController *Get(SDL_JoystickID instanceId);
	static GameController *Get(const SDL_Event &event);
	static const std::vector<GameController> &All();
	static bool IsPressedOnAnyController(ControllerButton button, SDL_JoystickID *which = nullptr);

	static void RumbleOnDead();
	static void RumbleOnDamage(int damage);
	static void RumbleOnBlock();
	static void RumbleOnSpell(int8_t spellID);
	static void RumbleOnHit(const Monster& monster, int damage);

	// Must be called exactly once at the start of each SDL input event.
	void UnlockTriggerState();

	ControllerButton ToControllerButton(const SDL_Event &event);

	bool IsPressed(ControllerButton button) const;
	static bool ProcessAxisMotion(const SDL_Event &event);
	static SDL_GameControllerButton ToSdlGameControllerButton(ControllerButton button);
	static GamepadLayout getLayout(const SDL_Event &event);

private:
	static void PlayRumble(Uint16 low_frequency_rumble, Uint16 high_frequency_rumble, Uint32 duration_ms);
	static void BigRumble(Uint16 force, Uint32 duration_ms) {
		PlayRumble(force, 0, duration_ms);
	}
	static void SmallRumble(Uint16 force, Uint32 duration_ms) {
		PlayRumble(0, force, duration_ms);
	}

private:
	SDL_GameController *sdl_game_controller_ = NULL;
	SDL_JoystickID instance_id_ = -1;

	ControllerButton trigger_left_state_ = ControllerButton_NONE;
	ControllerButton trigger_right_state_ = ControllerButton_NONE;
	bool trigger_left_is_down_ = false;
	bool trigger_right_is_down_ = false;
};

} // namespace devilution
