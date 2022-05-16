#pragma once

namespace SCAR
{
	static constexpr char NEXT_ATTACK_CHANCE[] = "SCAR_nextattackchance";
	//static constexpr float startAngle = -std::numbers::pi / 3.0f, endAngle = std::numbers::pi / 3.0f;

	bool GetDistanceVariable(RE::Actor* a_actor, std::map<const std::string, float>& a_map);

	bool ShouldNextAttack(RE::Actor* a_actor);

	class AttackRangeCheck
	{
	private:
		//����һ��չ������|A|
		static float getA(float arcs[3][3], int n);

		//����ÿһ��ÿһ�е�ÿ��Ԫ������Ӧ������ʽ�����A*
		static void getAStart(float arcs[3][3], int n, float ans[3][3]);

		//�õ���������src������󱣴浽des�С�
		static bool GetMatrixInverse(float src[3][3], float des[3][3], int n = 3);

	public:
		static bool WithinAttackRange(RE::Actor* a_attacker, RE::Actor* a_targ, float max_distance, float min_distance, float a_startAngle, float a_endAngle);

		static void DrawOverlay(RE::Actor* a_attacker, RE::Actor* a_targ, float max_distance, float min_distance, float a_startAngle, float a_endAngle);
	};
}
