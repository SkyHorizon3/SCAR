#pragma once

inline const float GetBoundRadius(RE::Actor* a_this)
{
	using func_t = decltype(&GetBoundRadius);
	static REL::Relocation<func_t> func{ RELOCATION_ID(36444, 37439) };
	return func(a_this);
}

inline std::int32_t RequestLOS(RE::Actor* a_attacker, RE::Actor* a_target, float a_viewCone = 2.f * std::numbers::pi)
{
	using func_t = decltype(&RequestLOS);
	static REL::Relocation<func_t> func{ RELOCATION_ID(36752, 37768) };
	return func(a_attacker, a_target, a_viewCone);
}

inline float QTimer()
{
	using func_t = decltype(&QTimer);
	static REL::Relocation<func_t> func{ RELOCATION_ID(47089, 48253) };
	return func();
}

inline bool IsPathing(RE::Actor* a_this)
{
	using func_t = decltype(&IsPathing);
	static REL::Relocation<func_t> func{ RELOCATION_ID(36812, 37828) };
	return func(a_this);
}