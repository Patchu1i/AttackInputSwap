#pragma once

#include <PCH.h>
#include <Xinput.h>

// Source: One Click Power Attack  |  This is kind of used everywhere at this point lol.
// https://github.com/jarari/OneClickPowerAttack/blob/e2776b6c2fca42a3b62306aea51536c17f6350ff/src/Main.cpp#L132

namespace AttackInputSwap
{
	enum KEY_OFFSETS : uint32_t
	{
		KeyboardOffset = 0,  // Start
		kTotal = 256,

		MouseButtonOffset = kTotal,  // 256
		mTotal = 8,

		MouseWheelOffset = kTotal + mTotal,  // 264
		MouseWheelDirections = 2,

		GamepadOffset = MouseWheelOffset + MouseWheelDirections,  // 266
		gTotal = 16,

		kMaxMacros = GamepadOffset + gTotal  // 282
	};

	enum GAMEPAD_OFFSETS : uint32_t
	{
		kDPadUp = KEY_OFFSETS::GamepadOffset,  // 266
		kDPadDown,
		kDPadLeft,
		kDPadRight,
		kStart,
		kBack,
		kLeftThumb,
		kRightThumb,
		kLeftShoulder,
		kRightShoulder,
		kA,
		kB,
		kX,
		kY,
		kLT,
		kRT,
		kMax
	};

	static inline uint32_t GamepadMaskToKeycode(uint32_t keyMask)
	{
		switch (keyMask) {
		case XINPUT_GAMEPAD_DPAD_UP:
			return GAMEPAD_OFFSETS::kDPadUp;
		case XINPUT_GAMEPAD_DPAD_DOWN:
			return GAMEPAD_OFFSETS::kDPadDown;
		case XINPUT_GAMEPAD_DPAD_LEFT:
			return GAMEPAD_OFFSETS::kDPadLeft;
		case XINPUT_GAMEPAD_DPAD_RIGHT:
			return GAMEPAD_OFFSETS::kDPadRight;
		case XINPUT_GAMEPAD_START:
			return GAMEPAD_OFFSETS::kStart;
		case XINPUT_GAMEPAD_BACK:
			return GAMEPAD_OFFSETS::kBack;
		case XINPUT_GAMEPAD_LEFT_THUMB:
			return GAMEPAD_OFFSETS::kLeftThumb;
		case XINPUT_GAMEPAD_RIGHT_THUMB:
			return GAMEPAD_OFFSETS::kRightThumb;
		case XINPUT_GAMEPAD_LEFT_SHOULDER:
			return GAMEPAD_OFFSETS::kLeftShoulder;
		case XINPUT_GAMEPAD_RIGHT_SHOULDER:
			return GAMEPAD_OFFSETS::kRightShoulder;
		case XINPUT_GAMEPAD_A:
			return GAMEPAD_OFFSETS::kA;
		case XINPUT_GAMEPAD_B:
			return GAMEPAD_OFFSETS::kB;
		case XINPUT_GAMEPAD_X:
			return GAMEPAD_OFFSETS::kX;
		case XINPUT_GAMEPAD_Y:
			return GAMEPAD_OFFSETS::kY;
		case 0x9:
			return GAMEPAD_OFFSETS::kLT;
		case 0xA:
			return GAMEPAD_OFFSETS::kRT;
		default:
			return KEY_OFFSETS::kMaxMacros;  // Invalid
		}
	}
}