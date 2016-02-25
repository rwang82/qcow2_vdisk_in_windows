#ifndef __Q2BRW_H__
#define __Q2BRW_H__

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus
#include <NTDDK.h>
#ifdef __cplusplus
}
#endif //__cplusplus

typedef struct QCow2Header {
    __int32 magic;
    __int32 version;
    __int64 backing_file_offset;
    __int32 backing_file_size;
    __int32 cluster_bits;
    __int64 size; /* in bytes */
    __int32 crypt_method;
    __int32 l1_size; /* XXX: save number of clusters instead ? */
    __int64 l1_table_offset;
    __int64 refcount_table_offset;
    __int32 refcount_table_clusters;
    __int32 nb_snapshots;
    __int64 snapshots_offset;
} QCow2Header;

struct DEVICE_EXTENSION;
BOOLEAN brwInitQcow2Header( HANDLE hFileQcow2, QCow2Header* pCow2Header );



#endif //__Q2BRW_H__