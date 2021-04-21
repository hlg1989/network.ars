#ifndef RL_SERVICE_JANUS_C_INTERFACE_H
#define RL_SERVICE_JANUS_C_INTERFACE_H
#include "network_ars.h"
#ifdef __cplusplus
extern "C" {
#endif
	typedef char RLUsertag[64];

	typedef struct {
		float bitrate;
		float buffer_size;
		float recv_bitrate;
		float delay;
		float packet_loss_rate;
		float nack_sent_count;
	}RLSTATE;

	typedef struct {
		RLUsertag addr;
		int bitrate;
	}RLRecvType;

	typedef void(*RLHandlerType)(RLRecvType, void *);

	network_ars_API void* RLServiceUDPDelegateCreate(const char* remote_ip);
	network_ars_API int RLServiceUDPDelegateRelease(void *p);
	network_ars_API int RLServiceUDPDelegateInitial(void *p);
	network_ars_API int RLServiceUDPDelegateStart(void *p);
	network_ars_API int RLServiceUDPDelegateStop(void *p);
	network_ars_API int RLServiceUDPDelegateStarted(void *p);
	network_ars_API int RLServiceUDPDelegateClear(void *p, RLUsertag addr);
	network_ars_API int RLServiceUDPDelegateSetHandler(void *p, RLHandlerType handler, void* param);
	network_ars_API int RLServiceUDPDelegateSetMaxBitrate(void *p, RLUsertag addr, int maxbitrate);
	network_ars_API int RLServiceUDPDelegateSetMinBitrate(void *p, RLUsertag addr, int minbitrate);
	network_ars_API int RLServiceUDPDelegateDealWith(void *p, RLSTATE state, RLUsertag addr, int fps);
	network_ars_API int RLServiceUDPDelegateStopUser(void *p, RLUsertag addr);

#ifdef __cplusplus
}
#endif

#endif