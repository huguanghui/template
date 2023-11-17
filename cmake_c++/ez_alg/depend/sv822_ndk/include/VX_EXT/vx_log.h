#ifndef __VX_LOG_H__
#define __VX_LOG_H__

#include <stdarg.h>
#include <VX/vx.h>

#ifdef ALOG_PRINT
#include <log/log.h>
#define VX_LOG(...)  ALOGE(__VA_ARGS__)
#else
#define VX_LOG(...)  printf(__VA_ARGS__)
#endif

#define ERROR_CHECK_STATUS( status ) { \
        vx_status status_ = (status); \
        if(status_ != VX_SUCCESS) { \
            VX_LOG("ERROR: failed with status = (%d) at " __FILE__ "#%d\n", status_, __LINE__); \
            exit(1); \
        } \
    }

#define ERROR_CHECK_OBJECT( obj ) { \
        vx_status status_ = vxGetStatus((vx_reference)(obj)); \
        if(status_ != VX_SUCCESS) { \
            VX_LOG("ERROR: failed with status = (%d) at " __FILE__ "#%d\n", status_, __LINE__); \
            exit(1); \
        } \
    }

#endif
