#include "pch.h"
#include "network_ars.h"
#include "Service/RLServiceJanus/RLServiceJanusCInterface.h"
#include "Service/RLServiceUDP/RLServiceUDPUserManager.h"
#include "Service/RLServiceUDP/RLServiceUDPNet.hpp"
#include <string.h>

class RLJanusWarperCPP {
public:
	RLJanusWarperCPP(const std::string& remote_address = "127.0.0.1", unsigned int local_port = 0)
		:m_pNetDelegate(remote_address, local_port)
	{};
	~RLJanusWarperCPP() { Stop(); }
	virtual bool Initialize() {
		return m_pNetDelegate.Initialize();
	}
	virtual bool Start() {
		return m_pNetDelegate.Start();
	}
	virtual bool Stop() {
		return m_pNetDelegate.Stop();
	}
	virtual bool Started() {
		return m_pNetDelegate.Started();
	}
	virtual bool SetHandler(RL::Service::RLServiceUDP::HandlerType handler, void *param) {
		return m_pNetDelegate.SetHandler(handler, param);
	}
	//set handler to deal with next bitrate
	virtual bool Clear(RL::Service::RLServiceUDP::Usertag addr) {
		RL::Service::RLServiceUDP::RLServiceUDPStateManager *mgr = nullptr;
		if (m_pUserManager.GetStateManager(addr, mgr)) {
			return mgr->Clear();
		}

		return true;
	}
	virtual bool DealWith(RL::Service::RLServiceUDP::STATE &state
		, RL::Service::RLServiceUDP::Usertag addr) {
		RL::Service::RLServiceUDP::RLServiceUDPStateManager *mgr = nullptr;
		if (m_pUserManager.GetStateManager(addr, mgr)) {
			RL::Service::RLServiceUDP::SendType se = mgr->Pack(state);
			memset(se.addr, 0, ADDRLEN);
			memcpy(se.addr, addr, strlen(addr));
			//TODO: We need to send maxbitrate and min bitrate
			return m_pNetDelegate.Started() && m_pNetDelegate.DealWith(se);
		}
		return true;
	}
	virtual bool SetMaxBitrate(RL::Service::RLServiceUDP::Usertag addr, int maxbitrate) {
		RL::Service::RLServiceUDP::RLServiceUDPStateManager *mgr = nullptr;
		if (m_pUserManager.GetStateManager(addr, mgr)) {
			return mgr->SetMaxBitrate(maxbitrate);
		}
		else {
			return false;
		}
	}
	virtual bool SetMinBitrate(RL::Service::RLServiceUDP::Usertag addr, int minbitrate) {
		RL::Service::RLServiceUDP::RLServiceUDPStateManager *mgr = nullptr;
		if (m_pUserManager.GetStateManager(addr, mgr)) {
			return mgr->SetMinBitrate(minbitrate);
		}
		else {
			return false;
		}
	}
	virtual bool DealWith(RL::Service::RLServiceUDP::STATE &state
		, RL::Service::RLServiceUDP::Usertag addr, int fps) {
		RL::Service::RLServiceUDP::RLServiceUDPStateManager *mgr = nullptr;
		if (m_pUserManager.GetStateManager(addr, mgr)) {
			RL::Service::RLServiceUDP::SendType se = mgr->Pack(state);
			memset(se.addr, 0, ADDRLEN);
			memcpy(se.addr, addr, strlen(addr));
			//TODO: We need to send maxbitrate and min bitrate
			return m_pNetDelegate.Started() && m_pNetDelegate.DealWith(se, fps);
		}

		return true;
	}
	virtual bool StopUser(RL::Service::RLServiceUDP::Usertag addr) {
		return m_pUserManager.DestroyStateManager(addr);
	}

private:
	RL::Service::RLServiceUDP::RLServiceUserManager m_pUserManager;
	RL::Service::RLServiceUDP::RLServiceUDPNet      m_pNetDelegate;
};


void*  RLServiceUDPDelegateCreate(const char* remote_ip) {
	return new RLJanusWarperCPP(remote_ip, 0);
}

int RLServiceUDPDelegateRelease(void *p) {
	delete (RLJanusWarperCPP*)p;
	return true;
}

int RLServiceUDPDelegateInitial(void *p) {
	return ((RLJanusWarperCPP*)p)->Initialize();
}

int RLServiceUDPDelegateStart(void *p) {
	return ((RLJanusWarperCPP*)p)->Start();
}

int RLServiceUDPDelegateStop(void *p) {
	return ((RLJanusWarperCPP*)p)->Stop();
}

int RLServiceUDPDelegateStarted(void *p) {
	return ((RLJanusWarperCPP*)p)->Started();
}

int RLServiceUDPDelegateClear(void *p, RLUsertag addr) {
	return ((RLJanusWarperCPP*)p)->Clear(addr);
}

int RLServiceUDPDelegateSetHandler(void *p, RLHandlerType handler, void* param) {
	return ((RLJanusWarperCPP*)p)->SetHandler(*((RL::Service::RLServiceUDP::HandlerType*)&handler), param);
}

int RLServiceUDPDelegateSetMaxBitrate(void *p, RLUsertag addr, int maxbitrate) {
	return ((RLJanusWarperCPP*)p)->SetMaxBitrate(addr, maxbitrate);
}

int RLServiceUDPDelegateSetMinBitrate(void *p, RLUsertag addr, int minbitrate) {
	return ((RLJanusWarperCPP*)p)->SetMinBitrate(addr, minbitrate);
}

int RLServiceUDPDelegateDealWith(void *p, RLSTATE state, RLUsertag addr, int fps) {
	return ((RLJanusWarperCPP*)p)->DealWith(*((RL::Service::RLServiceUDP::STATE*)&state), addr, fps);
}

int RLServiceUDPDelegateStopUser(void *p, RLUsertag addr) {
	return ((RLJanusWarperCPP*)p)->StopUser(addr);
}