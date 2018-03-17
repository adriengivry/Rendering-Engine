#pragma once

#include <string>

namespace Gyvr
{
	namespace Object
	{
		/*
		 * AObject is the base class for every object instancied. It has a unique ID that can identify him
		 */
		class AObject
		{
			static uint64_t ID_INCREMENT;
		public:
			AObject();
			virtual ~AObject() = 0;

			uint64_t GetInstanceID() const;
			virtual std::string& GetName();

			void SetName(const std::string& p_name);

		private:
			uint64_t m_instanceID = 0;

		protected:
			std::string m_name;
		};

		inline AObject::~AObject() = default;
	}
}
