#ifndef RL_STATE_MANAMEGER_HPP
#define RL_STATE_MANAMEGER_HPP

#include "RLbase.h"
#include "ElemType/CircleDataSet.hpp"

namespace RL {
	template <typename STATE,typename SendType>
	class RLStateManager
	{
	public:
		RLStateManager() : m_Cpings(WINDOWSIZE) {}
		virtual SendType Pack(STATE state)   = 0;
		virtual bool Clear() {
			RLTRY;
			m_offset = 0;
			memset(m_state, 0, sizeof(m_state));
			isFirstchunk = true;
			return true;
			RLCATCH;
			return false;
		}
		virtual bool SetMaxBitrate(int kbps) {
			return m_maxbitrate = kbps;
		}
		virtual bool SetMinBitrate(int kbps) {
			return m_minbitrate = kbps;
		}
	protected:
		int   m_offset = 0;
		STATE m_state[S_LEN];
		int   m_maxbitrate = INIT_MAX_BITRATE;
		int   m_minbitrate = INIT_MIN_BITRATE;
		bool  isFirstchunk = false;
		ElemType::CircleDataSet<float> m_Cpings /*WINDOWSIZE*/;
	};
}

#endif
