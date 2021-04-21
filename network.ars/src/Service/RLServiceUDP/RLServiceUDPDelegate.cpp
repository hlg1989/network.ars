#include "pch.h"
#include "Service/RLServiceUDP/RLServiceUDPDelegate.h"

using namespace RL::Service::RLServiceUDP;

RLServiceUDP::RLServiceUDP() {}

RLServiceUDP::~RLServiceUDP() { Stop(); }

bool RLServiceUDP::Initialize() {
	RLTRY;
	return m_pNetDelegate.Initialize();
	RLCATCH;
	return false;
}

bool RLServiceUDP::Start() {
	RLTRY;
	if (!m_pNetDelegate.Started()) {
		m_pNetDelegate.Start();
	}
	if (m_pNetDelegate.Started() && !m_started) {
		m_started = true;
		m_thread = std::thread(std::bind(&RLServiceUDP::task, this));
	}

	return Started();
	RLCATCH;
	return false;
}

bool RLServiceUDP::Stop() {
	RLTRY;
	if (m_started) {
		m_started = false;
		m_thread.join();
	}
	if (m_pNetDelegate.Started()) {
		m_pNetDelegate.Stop();
	}

	return !Started();
	RLCATCH;
	return false;
}

bool RLServiceUDP::Started() {
	RLTRY;
	return m_pNetDelegate.Started() && m_started;
	RLCATCH;
	return false;
}

bool RLServiceUDP::SetHandler(HandlerType handler, void *param) {
	RLTRY;
	return m_pNetDelegate.SetHandler(handler, param);
	RLCATCH;
	return false;
}

bool RLServiceUDP::Clear(Usertag addr) {
	RLTRY;
	RLServiceUDPStateManager *mgr = nullptr;
	if (m_pUserManager.GetStateManager(addr, mgr)) {
		return mgr->Clear();
	}
	return false;
	RLCATCH;
	return false;
}

bool RLServiceUDP::DealWith(STATE &state, Usertag tag) {
	RLTRY;
	RLServiceUDPStateManager *mgr = nullptr;
	if (m_pUserManager.GetStateManager(tag, mgr)) {
		SendType se = mgr->Pack(state);
		memcpy(&se.addr, &tag, ADDRLEN);
		//TODO: We need to send maxbitrate and min bitrate
		return m_pNetDelegate.Started() && m_pNetDelegate.DealWith(se);
	}
	return false;
	RLCATCH;
	return false;
}

bool RLServiceUDP::DealWith(STATE &state, Usertag tag, int fps) {
	RLTRY;
	RLServiceUDPStateManager *mgr = nullptr;
	if (m_pUserManager.GetStateManager(tag, mgr)) {
		SendType se = mgr->Pack(state);
		memcpy(&se.addr, &tag, ADDRLEN);
		//TODO: We need to send maxbitrate and min bitrate
		return m_pNetDelegate.Started() && m_pNetDelegate.DealWith(se, fps);
	}
	return false;
	RLCATCH;
	return false;
}