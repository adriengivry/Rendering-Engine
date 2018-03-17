#include "ConfigLoader.h"

using namespace Gyvr::Util;

int ConfigLoader::GetInt(const ConfigFile p_configFile, const std::string& p_attribute)
{
	return std::stoi(GetData(p_configFile, p_attribute));
}

float ConfigLoader::GetFloat(const ConfigFile p_configFile, const std::string& p_attribute)
{
	return std::stof(GetData(p_configFile, p_attribute));
}

std::string ConfigLoader::GetString(const ConfigFile p_configFile, const std::string& p_attribute)
{
	return GetData(p_configFile, p_attribute);
}

bool ConfigLoader::GetBool(const ConfigFile p_configFile, const std::string& p_attribute)
{
	const auto strValue = GetData(p_configFile, p_attribute);
	if (strValue == "true") return true;
	if (strValue == "false") return false;
	return false;
}

std::string ConfigLoader::GetData(const ConfigFile p_configFile, const std::string& p_attribute)
{
	const auto confPath = GetConfPath(p_configFile);
	std::string data = "0";

	if (!confPath._Equal("UNKNOWN"))
	{
		const auto line = GetAttributeLine(confPath, p_attribute);
		data = GetAttributeValue(line);
	}
	return data;
}

std::string ConfigLoader::GetAttributeLine(const std::string& p_confPath, const std::string& p_attribute)
{
	std::string line;
	std::ifstream file;
	file.open(p_confPath, std::ofstream::out | std::ofstream::app);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			if (GetAttributeName(line) == p_attribute)
				return line;
		}

		file.close();
	}
	return line;
}

std::string ConfigLoader::GetAttributeValue(std::string p_line)
{
	std::string result;
	bool rightSide = false;

	for (auto c : p_line)
	{
		if (rightSide) result.push_back(c);
		if (c == '=') rightSide = true;
	}

	return result;
}

std::string ConfigLoader::GetAttributeName(std::string p_line)
{
	std::string result;

	for (auto c : p_line)
	{
		if (c == '=') return result;
		result.push_back(c);
	}

	return result;
}

std::string ConfigLoader::GetConfPath(const ConfigFile p_configFile)
{
	const std::string CONFIG_PATH = "../config/";

	switch (p_configFile)
	{
	case ConfigFile::WINDOW: return CONFIG_PATH + "window.ini";
	case ConfigFile::ENGINE: return CONFIG_PATH + "engine.ini";
	case ConfigFile::GENERAL: return CONFIG_PATH + "general.ini";
	}

	return "UNKNOWN";
}
