#pragma once
#include "DKUtil/Config.hpp"
#include "PrecisionAPI/PrecisionAPI.h"
#include "RE/CombatAnimation.h"
#include "SCARActionData.h"
#include "TrueHUD/TrueHUDAPI.h"

namespace SCAR
{
	using namespace DKUtil::Alias;
	using namespace PRECISION_API;
	using namespace TRUEHUD_API;

	class DataHandler
	{
		struct Settings
		{
		private:
			template <class T>
			static void PrintSettingValue(const T& a_setting)
			{
				INFO("Setting:\"{}\" is {}"sv, a_setting.get_key(), a_setting.get_data());
			}

		public:
			Settings();

			Boolean enableDebugLog{ "EnableDebugLog", "Debug" };
			Boolean enableDebugOverlay{ "EnableDebugOverlay", "Debug" };

		private:
		};

	public:
		static DataHandler* GetSingleton()
		{
			static DataHandler singleton;
			return std::addressof(singleton);
		}

		std::unique_ptr<Settings> settings;
		IVPrecision1* precisionPtr = nullptr;
		IVTrueHUD5* trueHUD_API = nullptr;

		static RE::hkbClipGenerator*
			GetSCARDataClip(RE::Actor* a_actor);
		static std::vector<SCARActionData> GetSCARActionData(const RE::hkbClipGenerator* a_clip);
		static bool HasSCARActionData(const RE::hkbClipGenerator* a_clip);

	private:
		DataHandler();

		~DataHandler() = default;

		DataHandler(const DataHandler&) = delete;

		DataHandler(DataHandler&&) = delete;

		DataHandler& operator=(const DataHandler&) = delete;

		DataHandler& operator=(DataHandler&&) = delete;
	};

}
