#include "Hooks.h"
#include "Keycode.h"

namespace AttackInputSwap
{
	namespace Hooks
	{
		uint32_t GetLeftAttackBlock(const RE::INPUT_DEVICE& a_device)
		{
			if (a_device == RE::INPUT_DEVICE::kKeyboard) {
				return RE::ControlMap::GetSingleton()->GetMappedKey("Left Attack/Block", RE::INPUT_DEVICE::kKeyboard);
			} else if (a_device == RE::INPUT_DEVICE::kMouse) {
				return RE::ControlMap::GetSingleton()->GetMappedKey("Left Attack/Block", RE::INPUT_DEVICE::kMouse) + KEY_OFFSETS::kTotal;
			} else if (a_device == RE::INPUT_DEVICE::kGamepad) {
				return GamepadMaskToKeycode(RE::ControlMap::GetSingleton()->GetMappedKey("Left Attack/Block", RE::INPUT_DEVICE::kGamepad));
			} else {
				return 0;
			}
		}

		uint32_t GetRightAttackBlock(const RE::INPUT_DEVICE& a_device)
		{
			if (a_device == RE::INPUT_DEVICE::kKeyboard) {
				return RE::ControlMap::GetSingleton()->GetMappedKey("Right Attack/Block", RE::INPUT_DEVICE::kKeyboard);
			} else if (a_device == RE::INPUT_DEVICE::kMouse) {
				return RE::ControlMap::GetSingleton()->GetMappedKey("Right Attack/Block", RE::INPUT_DEVICE::kMouse) + KEY_OFFSETS::kTotal;
			} else if (a_device == RE::INPUT_DEVICE::kGamepad) {
				return GamepadMaskToKeycode(RE::ControlMap::GetSingleton()->GetMappedKey("Right Attack/Block", RE::INPUT_DEVICE::kGamepad));
			} else {
				return 0;
			}
		}

		uint32_t GetKeycode(const RE::INPUT_DEVICE& a_device, const uint32_t& a_idCode)
		{
			uint32_t keyCode;

			if (a_device == RE::INPUT_DEVICE::kKeyboard) {
				keyCode = a_idCode;
			} else if (a_device == RE::INPUT_DEVICE::kMouse) {
				keyCode = KEY_OFFSETS::kTotal + a_idCode;
			} else if (a_device == RE::INPUT_DEVICE::kGamepad) {
				keyCode = GamepadMaskToKeycode(a_idCode);
			} else {
				keyCode = 0;
			}

			return keyCode;
		}

		RE::ButtonEvent* SwapInput(RE::ButtonEvent* a_event)
		{
			RE::INPUT_DEVICE deviceType = a_event->device.get();
			RE::ButtonEvent* mockEvent = nullptr;

			const uint16_t SkyrimLeftHand = (uint16_t)GetLeftAttackBlock(deviceType);
			const uint16_t SkyrimRightHand = (uint16_t)GetRightAttackBlock(deviceType);

			const uint32_t keyCode = GetKeycode(deviceType, a_event->idCode);

			if (keyCode == SkyrimRightHand) {
				mockEvent = RE::ButtonEvent::Create(deviceType, RE::UserEvents::GetSingleton()->leftAttack, a_event->idCode, a_event->value, a_event->HeldDuration());
			}

			if (keyCode == SkyrimLeftHand) {
				mockEvent = RE::ButtonEvent::Create(deviceType, RE::UserEvents::GetSingleton()->rightAttack, a_event->idCode, a_event->value, a_event->HeldDuration());
			}

			return mockEvent;
		}

		void HookAttackBlockHandler::ProcessButton(RE::ButtonEvent* a_event, void* a_data)
		{
			FnProcessButton fn = fnHash.at(*(uintptr_t*)this);

#ifdef ATTACK_INPUT_SWITCH_TWOHANDED
			if (const auto& player = RE::PlayerCharacter::GetSingleton()) {
				if (const auto& weapon = player->GetEquippedObject(true)) {
					if (const auto& weaponForm = weapon->As<RE::TESObjectWEAP>()) {
						if (weaponForm->IsBow() || weaponForm->IsCrossbow() || weaponForm->IsTwoHandedAxe() || weaponForm->IsTwoHandedSword()) {
							auto mockEvent = SwapInput(a_event);

							if (fn && mockEvent) {
								(this->*fn)(mockEvent, a_data);
							}

							return;
						}
					}
				}
			}

			if (fn && a_event) {
				(this->*fn)(a_event, a_data);
			}
#endif

#ifdef ATTACK_INPUT_SWITCH_ALL
			auto mockEvent = SwapInput(a_event);

			if (fn && mockEvent) {
				(this->*fn)(mockEvent, a_data);
			}
#endif
		}

		// Hook into the AttackBlockHandler vtable to process attack and block events.
		void HookAttackBlockHandler::Hook()
		{
			REL::Relocation<uintptr_t> vtable{ RE::VTABLE_AttackBlockHandler[0] };
			FnProcessButton fn =
				stl::unrestricted_cast<FnProcessButton>(vtable.write_vfunc(4, &HookAttackBlockHandler::ProcessButton));
			fnHash.insert(std::pair<uintptr_t, FnProcessButton>(vtable.address(), fn));
		}

		void Install()
		{
			HookAttackBlockHandler::Hook();
		};
	}

}