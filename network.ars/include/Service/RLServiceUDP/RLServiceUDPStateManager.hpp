#ifndef RL_SERVICE_UDP_STATE_MANAGER_HPP
#define RL_SERVICE_UDP_STATE_MANAGER_HPP

#include "RLServiceUDPbase.h"
#include "base/RLStateManager.hpp"
#include <memory.h>
#include <malloc.h>

namespace RL {
namespace Service{
namespace RLServiceUDP {
	class RLServiceUDPStateManager :public RL::RLStateManager<STATE, SendType> {
	public:
		RLServiceUDPStateManager() {
			memset(m_state, 0, sizeof(m_state));
		}
		~RLServiceUDPStateManager() = default;
		SendType Pack(STATE state) override {
			SendType se;
			m_Cpings.Append(state.delay);
			state.delay -= m_Cpings.Min();
			int temp_offset = m_offset - 1;
			if (temp_offset == -1) {
				temp_offset = S_LEN - 1;
			}
			memcpy(m_state + m_offset, &state, sizeof(STATE));
			m_offset = (m_offset + 1) % S_LEN;
			isFirstchunk = false;
			memset(se.state, 0, sizeof(se.state));
			for (int i = 0; i < S_LEN; i++) {
				int offset = (m_offset + i) % S_LEN;
				memcpy(se.state + i, m_state + offset, sizeof(STATE));
			}
			se.maxbitrate = m_maxbitrate;
			se.minbitrate = m_minbitrate;
			return se;
		}
	};
}//namespace RLServiceUDP
}//namespace Service
}//namespace RL

#endif