#pragma once
#include "API/PrecisionAPI.h"
#include "API/TrueHUDAPI.h"
#include "SCARActionData.h"

namespace SCAR
{
	using namespace PRECISION_API;
	using namespace TRUEHUD_API;

	class DataHandler
	{
		struct Settings
		{
			Settings();

			bool enableDebugLog{ false };
			bool enableDebugOverlay{ false };
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

		static RE::hkbClipGenerator* GetSCARDataClip(RE::Actor* a_actor);
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
