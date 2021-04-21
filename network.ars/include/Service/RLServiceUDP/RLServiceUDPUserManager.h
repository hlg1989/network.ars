#ifndef RL_SERVICE_UDP_USER_MANAGER_H
#define RL_SERVICE_UDP_USER_MANAGER_H

#include "Service/RLServiceUserManager.hpp"
#include "RLServiceUDPStateManager.hpp"


namespace RL {
namespace Service{
namespace RLServiceUDP {
	class RLServiceUserManager
		:public RL::Service::RLServiceUserManager<Usertag, RLServiceUDPStateManager>{
	public:
		RLServiceUserManager() = default;
		~RLServiceUserManager() = default;
	};
}
}
}

#endif