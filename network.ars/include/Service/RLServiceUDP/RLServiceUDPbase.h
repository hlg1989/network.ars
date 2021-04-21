#ifndef RL_SERVICE_UDP_BASE_H
#define RL_SERVICE_UDP_BASE_H

#include <string.h>

#define ADDRLEN 64
#define S_LEN 8

namespace RL {
namespace Service {
namespace RLServiceUDP {
	typedef char Usertag[64];

	typedef struct {
		float bitrate;
		float buffer_size;
		float recv_bitrate;
		float delay;
		float packet_loss_rate;
		float nack_sent_count;
	}STATE;

	typedef struct {
		STATE state[S_LEN];
		Usertag addr;
		int maxbitrate;
		int minbitrate;
	}SendType;

	typedef struct {
		Usertag addr;
		int bitrate;
	}RecvType;

	typedef void(*HandlerType)(RecvType, void *);
}//namespace RLServiceUDP
}//namespace Service
}//namespace RL
#endif