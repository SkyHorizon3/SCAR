#include "CombatBehaviorTreeUtils.h"

namespace RE
{
	CombatBehaviorTreeUtils::CombatBehaviorAttacker::operator Actor*()
	{
		using func_t = decltype(&CombatBehaviorTreeUtils::CombatBehaviorAttacker::operator Actor*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46264, 47519) };
		return func(this);
	}

	CombatBehaviorTreeUtils::CombatBehaviorTarget::operator Actor*()
	{
		using func_t = decltype(&CombatBehaviorTreeUtils::CombatBehaviorTarget::operator Actor*);
		static REL::Relocation<func_t> func{ RELOCATION_ID(46265, 47520) };
		return func(this);
	}
}