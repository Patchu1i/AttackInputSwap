#pragma once

#include <PCH.h>

namespace AttackInputSwap
{
	namespace Hooks
	{
		void Install();

		class HookAttackBlockHandler
		{
		public:
			typedef void (HookAttackBlockHandler::*FnProcessButton)(RE::ButtonEvent*, void*);
			void ProcessButton(RE::ButtonEvent* a_event, void* a_data);
			static void Hook();

		private:
			static inline std::unordered_map<uintptr_t, FnProcessButton> fnHash;
		};

	}
}