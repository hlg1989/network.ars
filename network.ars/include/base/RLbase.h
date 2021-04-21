#ifndef RL_BASE_H
#define RL_BASE_H

#include <stdio.h>
#include <memory.h>

#define RLTRY try{


#define RLCATCH_BEGIN(x) }catch(x){printf("%s RL Module Compiled on %s!Error in FILE:%s Line:%d",\
							__TIME__,__DATE__,__FILE__,__LINE__);

#define RLCATCH_END }

#define RLCATCH RLCATCH_BEGIN(...) RLCATCH_END

#define RLLOCALPORTBASE 44748

#define RLREMOTEPORTBASE 48484

#define RLREMOTEPORT30 48484

#define RLREMOTEPORT60 48485

#define INIT_MAX_BITRATE 10000

#define INIT_MIN_BITRATE 1000

#define RLLOCALHOST "127.0.0.1"

#define RLANYADDR "0.0.0.0"

#define RLCHECKPORT(val1,val2) RL##val1##PORT##val2

#define RL_SAFE_FREE(val) if(val){ free(val); val = nullptr;}

#define WINDOWSIZE 300




#endif
