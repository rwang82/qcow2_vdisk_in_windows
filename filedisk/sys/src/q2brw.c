#include "q2brw.h"


#define BE2LE(x) beleSwap( &x, sizeof(x) );
static void beleSwap( void* pData, unsigned char ucSize );

//////////////////////////////////////////////////////////
BOOLEAN brwInitQcow2Header( HANDLE hFileQcow2, QCow2Header* pCow2Header )
{
	IO_STATUS_BLOCK ioStatus;
	NTSTATUS ntStatus;
	LARGE_INTEGER liOffset;
	
	if ( !hFileQcow2 || !pCow2Header )
		return FALSE;
	KdPrint( ("In brwInitQcow2Header!\n") );
	liOffset.QuadPart = 0;
	ntStatus = ZwReadFile( hFileQcow2,
    NULL,
    NULL,
    NULL, 
    &ioStatus,
    pCow2Header,
    sizeof( QCow2Header ),
    &liOffset,
    NULL
    );
  
  //big endian 2 litter endian
	BE2LE( pCow2Header->magic ); //if need?
	BE2LE( pCow2Header->version );
	BE2LE( pCow2Header->backing_file_offset );
	BE2LE( pCow2Header->backing_file_size );
	BE2LE( pCow2Header->cluster_bits );
	BE2LE( pCow2Header->size );
	BE2LE( pCow2Header->crypt_method );
	BE2LE( pCow2Header->l1_size );
	BE2LE( pCow2Header->l1_table_offset );
	BE2LE( pCow2Header->refcount_table_offset );
	BE2LE( pCow2Header->refcount_table_clusters );
	BE2LE( pCow2Header->nb_snapshots );
	BE2LE( pCow2Header->snapshots_offset );
  
  return NT_SUCCESS(ntStatus) ? TRUE : FALSE ; 
}

void beleSwap( void* pData, unsigned char ucSize )
{
	unsigned char ucTmp;
	unsigned char ucSwapCount;

	ucSwapCount = ucSize/2;
	while ( ucSwapCount )
	{
		ucTmp = ((unsigned char*)pData)[ ucSwapCount - 1 ];
		((unsigned char*)pData)[ ucSwapCount - 1 ] = ((unsigned char*)pData)[ ucSize - ucSwapCount ];
		((unsigned char*)pData)[ ucSize - ucSwapCount ] = ucTmp;
		--ucSwapCount;
	}
}