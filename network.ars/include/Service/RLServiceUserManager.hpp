#ifndef RL_SERVICE_USER_MANAGER_HPP
#define RL_SERVICE_USER_MANAGER_HPP

#include "base/RLbase.h"
#include <stdlib.h>
#include <map>
#include <memory>
#include <stdio.h>
#include <string>

namespace RL {
namespace Service {
	template <typename _Usertag, class _StateManager>
	class RLServiceUserManager {
	public:
		RLServiceUserManager() = default;
		~RLServiceUserManager() = default;

		// We should find the user's state manager through the usertag
		// TODO: map only support type that support the < operator, 
		// and char[64] now is transformed to char[], so we need to
		// use std::string 
		virtual bool GetStateManager(_Usertag tag
			, _StateManager*& mgr) {
			RLTRY;
			std::string newtag(tag);
			if (FindUser(tag, mgr)) {
				return true;
			}
			return NewUser(tag, mgr);
			RLCATCH;
			return false;
		}

		// We should destroy the user's state manager through the usertag
		virtual bool DestroyStateManager(_Usertag tag) {
			RLTRY;
			std::string newtag(tag);
			return DeleteUser(newtag);
			RLCATCH;
			return false;
		}

	private:
		// TODO:the point*& should be replaced
		virtual bool FindUser(std::string tag, _StateManager*& mgr) {
			RLTRY;
			auto iter = m_map.find(tag);
			if (iter != m_map.end()) {
				mgr = iter->second.get();
				return true;
			}
			else {
				return false;
			}

			RLCATCH;
			return false;
		}
		// the shared_ptr will manage the memory of StateManager
		virtual bool NewUser(std::string tag, _StateManager*& mgr) {
			RLTRY;
			std::shared_ptr<_StateManager> mgr_ptr(new _StateManager());
			mgr = mgr_ptr.get();
			m_map.insert(std::pair<std::string, std::shared_ptr<_StateManager>>(tag, mgr_ptr));

			return true;
			RLCATCH;
			return false;
		}
		// erase will destroy the shared_ptr, and shared_ptr destroyed
		// leads to StateManager Deleted
		virtual bool DeleteUser(std::string tag) {
			RLTRY;
			auto iter = m_map.find(tag);
			if (iter != m_map.end()) {
				m_map.erase(iter);
			}
			return true;
			RLCATCH;
			return false;
		}

	private:
		std::map<std::string, std::shared_ptr<_StateManager>> m_map;
	};
}
}
#endif
