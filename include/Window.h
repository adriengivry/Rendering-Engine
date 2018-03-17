#pragma once

#include <memory>

#include "IManager.h"
#include "SharedContext.h"
#include "Driver.h"
#include "Device.h"
#include "ConfigLoader.h"

namespace Gyvr
{
	namespace Core
	{
		namespace System
		{
			/*
			 * Window class manage the Device and Driver creation
			 */
			class Window : public IManager
			{
			public:
				explicit Window(Util::SharedContext& p_sharedContext);
				~Window();

				void Setup() override;
				void Update() override;
				void Close() override;

				void SendDataToDevice() const;

				Context::Device* GetDevice() const;
				Context::Driver* GetDriver() const;
				bool IsOpen() const;

			private:
				int m_width;
				int m_height;
				std::string m_title;
				std::unique_ptr<Context::Device> m_device;
				std::unique_ptr<Context::Driver> m_driver;
				Util::SharedContext& m_sharedContext;
			};
		}
	}
}
