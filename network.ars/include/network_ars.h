#pragma once
#ifdef __cplusplus
namespace gwecom {
	namespace network_ars {
#endif



#if defined _WIN32 || defined __CYGWIN__ || defined __MINGW32__
#ifdef network_ars_SHARED
#ifdef __GNUC__
#define network_ars_API __attribute__ ((dllexport))
#else
#define network_ars_API __declspec(dllexport)
#endif
#elif defined network_ars_STATIC || defined _LIB
#define network_ars_API 
#else
#ifdef __GNUC__
#define network_ars_API __attribute__ ((dllimport))
#else
#define network_ars_API __declspec(dllimport)
#endif
#endif
#else
#if __GNUC__ >= 4
#define network_ars_API __attribute__ ((visibility ("default")))
#else
#define network_ars_API
#endif
#endif


#ifdef __cplusplus
	}
}
#endif
