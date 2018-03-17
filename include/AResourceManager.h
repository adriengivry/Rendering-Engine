#pragma once

#include <string>
#include <unordered_map>
#include <fstream>
#include <sstream>

#include "Log.h"

namespace Gyvr
{
	namespace Resource
	{
		/*
		 * Base class for every ResourceManager
		 */
		template<typename Derived, typename T>
		class AResourceManager
		{
		public:
			explicit AResourceManager(const std::string& l_pathsFile)
			{
				LoadPaths(l_pathsFile);
			}

			virtual ~AResourceManager() { PurgeResources(); }

			T* RequireAndGet(const std::string& l_id)
			{
				if (RequireResource(l_id))
					return GetResource(l_id);

				return nullptr;
			}

			T* GetResource(const std::string& l_id)
			{
				auto res = Find(l_id);
				return(res ? res->first : nullptr);
			}

			std::string GetPath(const std::string& l_id)
			{
				const auto path = m_paths.find(l_id);
				return(path != m_paths.end() ? path->second : "");
			}

			bool RequireResource(const std::string& l_id)
			{
				auto res = Find(l_id);
				if (res) {
					Gyvr::Core::Debug::Log::Process(l_id + " required but already loaded", Gyvr::Core::Debug::Log::LogLevel::LOG_WARNING);
					++res->second;
					return true;
				}
				const auto path = m_paths.find(l_id);
				if (path == m_paths.end()) { return false; }
				T* resource = Load(path->second);
				if (!resource) { return false; }
				m_resources.emplace(l_id, std::make_pair(resource, 1));
				Gyvr::Core::Debug::Log::Process(l_id + " loaded", Gyvr::Core::Debug::Log::LogLevel::LOG_INFO);
				return true;
			}

			bool ReleaseResource(const std::string& l_id)
			{
				auto res = Find(l_id);

				if (!res)
					return false;

				--res->second;

				if (!res->second)
					Unload(l_id);

				return true;
			}

			void PurgeResources() {
				Gyvr::Core::Debug::Log::Process("Start purging all resources", Gyvr::Core::Debug::Log::LogLevel::LOG_INFO);
				while (m_resources.begin() != m_resources.end())
				{
					Gyvr::Core::Debug::Log::Process("Removing: " + m_resources.begin()->first, Gyvr::Core::Debug::Log::LogLevel::LOG_INFO);
					delete m_resources.begin()->second.first;
					m_resources.erase(m_resources.begin());
				}
				Gyvr::Core::Debug::Log::Process("Purging completed", Gyvr::Core::Debug::Log::LogLevel::LOG_INFO);
			}

		protected:
			virtual T* Load(const std::string& l_path) = 0;

		private:
			std::pair<T*, unsigned int>* Find(const std::string& l_id)
			{
				auto itr = m_resources.find(l_id);
				return (itr != m_resources.end() ? &itr->second : nullptr);
			}

			bool Unload(const std::string& l_id)
			{
				auto itr = m_resources.find(l_id);
				if (itr == m_resources.end()) { return false; }
				delete itr->second.first;
				m_resources.erase(itr);
				return true;
			}

			void LoadPaths(const std::string& l_pathFile)
			{
				std::ifstream paths;
				paths.open(l_pathFile);
				if (paths.is_open()) {
					std::string line;
					while (std::getline(paths, line)) {
						std::stringstream keystream(line);
						std::string pathName;
						std::string path;
						keystream >> pathName;
						keystream >> path;
						m_paths.emplace(pathName, path);
					}
					paths.close();
					return;
				}
				Gyvr::Core::Debug::Log::Process("Failed loading the path file: " + l_pathFile, Gyvr::Core::Debug::Log::LogLevel::LOG_ERROR);
			}

			std::unordered_map<std::string,
				std::pair<T*, unsigned int>> m_resources;
			std::unordered_map<std::string, std::string> m_paths;
		};
	}
}