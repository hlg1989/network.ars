#ifndef RL_SERVICE_UDP_NET_HPP
#define RL_SERVICE_UDP_NET_HPP

#include "base/RLNetDelegate.hpp"
#include "RLServiceUDPbase.h"

namespace RL {
namespace Service {
namespace RLServiceUDP {
	class RLServiceUDPNet :public RLNetDelegate<SendType, RecvType, HandlerType> {
	public:
		RLServiceUDPNet(const std::string& remote_address = "127.0.0.1", unsigned int local_port = 0)
			:RLNetDelegate<SendType, RecvType, HandlerType>(remote_address, local_port) {}
		~RLServiceUDPNet() = default;
	};
}
}
}
#endif
