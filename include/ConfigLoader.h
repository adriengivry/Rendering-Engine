#pragma once

#include <string>
#include <fstream>

namespace Gyvr
{
	namespace Util
	{
		/*
		* ConfigLoader is a static class which can extract data associated to an attribute in different config files
		*
		* Files are stored in an enum :
		*		WINDOW: window.ini
		*		ENGINE: engine.ini
		*		GENERAL: general.ini
		*
		* All of those files are in the "[ProjectFolder]..\config" folder
		*/
		class ConfigLoader
		{
			/*
			* Those macros help to make the code reading clearer and faster for config loading
			*/
			#pragma region __Get_Integer
			/// <summary> Get an integer from a config file </summary>
			/// <param name="file"> [Util::ConfigLoader::ConfigFile] File type in ConfigFile enum </param>
			/// <param name="attribute"> [std::string] Attribute to search for and get data from </param>
			/// <returns> [int] Value associated to the attribute </returns>
			#define GET_INT(file, attribute)	Util::ConfigLoader::GetInt(Util::ConfigLoader::ConfigFile::file, attribute)
			#pragma endregion __Get_Integer
			#pragma region __Get_Float
			/// <summary> Get a float from a config file </summary>
			/// <param name="file"> [Util::ConfigLoader::ConfigFile] File type in ConfigFile enum </param>
			/// <param name="attribute"> [std::string] Attribute to search for and get data from </param>
			/// <returns> [float] Value associated to the attribute </returns>
			#define GET_FLOAT(file, attribute)	Util::ConfigLoader::GetFloat(Util::ConfigLoader::ConfigFile::file, attribute)
			#pragma endregion __Get_Float
			#pragma region __Get_String
			/// <summary> Get a string from a config file </summary>
			/// <param name="file"> [Util::ConfigLoader::ConfigFile] File type in ConfigFile enum </param>
			/// <param name="attribute"> [std::string] Attribute to search for and get data from </param>
			/// <returns> [std::string] Value associated to the attribute </returns>
			#define GET_STRING(file, attribute) Util::ConfigLoader::GetString(Util::ConfigLoader::ConfigFile::file, attribute)
			#pragma endregion __Get_String
			#pragma region __Get_Boolean
			/// <summary> Get a boolean from a config file </summary>
			/// <param name="file"> [Util::ConfigLoader::ConfigFile] File type in ConfigFile enum </param>
			/// <param name="attribute"> [std::string] Attribute to search for and get data from </param>
			/// <returns> [bool] Value associated to the attribute </returns>
			#define GET_BOOL(file, attribute)	Util::ConfigLoader::GetBool(Util::ConfigLoader::ConfigFile::file, attribute)
			#pragma endregion __Get_Boolean

		public:
			enum class ConfigFile
			{
				WINDOW,
				ENGINE,
				GENERAL
			};

			static int GetInt(ConfigFile p_configFile, const std::string& p_attribute);
			static float GetFloat(ConfigFile p_configFile, const std::string& p_attribute);
			static std::string GetString(ConfigFile p_configFile, const std::string& p_attribute);
			static bool GetBool(ConfigFile p_configFile, const std::string& p_attribute);

		private:
			static std::string GetData(ConfigFile p_configFile, const std::string& p_attribute);
			static std::string GetAttributeLine(const std::string& p_confPath, const std::string& p_attribute);
			static std::string GetAttributeValue(std::string p_line);
			static std::string GetAttributeName(std::string p_line);
			static std::string GetConfPath(ConfigFile p_configFile);
		};
	}
}