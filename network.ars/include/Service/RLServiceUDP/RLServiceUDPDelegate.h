#ifndef RL_SERVICE_UDP_DELEGATE_H
#define RL_SERVICE_UDP_DELEGATE_H

#include "RLServiceUDPbase.h"
#include "RLServiceUDPNet.hpp"
#include "RLServiceUDPUserManager.h"

namespace RL {
namespace Service{
namespace RLServiceUDP {
	class RLServiceUDP {
	public:
		RLServiceUDP();
		~RLServiceUDP();
		virtual bool Initialize();
		virtual bool Start();
		virtual bool Stop();
		virtual bool Started();
		virtual bool SetHandler(HandlerType handler, void *param);
		//set handler to deal with next bitrate
		virtual bool Clear(Usertag addr);
		virtual bool DealWith(STATE &state, Usertag addr);
		virtual bool DealWith(STATE &state, Usertag addr, int fps);

	protected:
		virtual void task() = 0;
		bool      m_started = false;

	private:
		RLServiceUserManager m_pUserManager;
		RLServiceUDPNet      m_pNetDelegate;
		std::thread m_thread;
	};
}
}
}

#endif