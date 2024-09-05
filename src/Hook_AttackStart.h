#pragma once

namespace SCAR
{
	class AIAttackStartHook
	{
	public:
		static void InstallHook()
		{
			SKSE::AllocTrampoline(1 << 4);
			auto& trampoline = SKSE::GetTrampoline();

			REL::Relocation<std::uintptr_t> CombatBehaviorAttackBase{ RELOCATION_ID(48147, 49178) };  //1.5.97 14080D8C0
			_StartAttack = trampoline.write_call<5>(CombatBehaviorAttackBase.address() + REL::Relocate(0x164, 0x148), StartAttack);
			INFO("{} Done!", __FUNCTION__);
		}

	private:
		static bool StartAttack(RE::CombatBehaviorContextMelee* a_context);

		static inline REL::Relocation<decltype(StartAttack)> _StartAttack;
	};
}
