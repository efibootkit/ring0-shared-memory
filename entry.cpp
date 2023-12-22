#include "Core.hpp"

VOID ThreadEntry( PVOID Ctx )
{
	KAPC_STATE Apc;
	KeStackAttachProcess( _Client , &Apc );

	PHYSICAL_ADDRESS PhysShared = MmGetPhysicalAddress( reinterpret_cast< PVOID >( _SharedMemAddr ) );

	if ( PhysShared.QuadPart )
	{
		SharedMem = reinterpret_cast< c_SharedMem* >( MmMapIoSpace( PhysShared , sizeof( SharedMem ) , MmNonCached ) );
	}

	KeUnstackDetachProcess( &Apc );

	if ( SharedMem )
	{
		while ( TRUE )
		{
			if ( !SendSharedMemTick( ) )
				break;
		}
	}

	ObDereferenceObject( _Client );
}

NTSTATUS ReroutedEntry( std::uint64_t SharedMemAddr , std::uint32_t ClientPID )
{
	_SharedMemAddr = SharedMemAddr;
	_ClientPID = ClientPID;

	if ( !NT_SUCCESS( PsLookupProcessByProcessId( HANDLE( ClientPID ) , &_Client ) ) )
		return STATUS_UNSUCCESSFUL;

	HANDLE SystemThreadHdl;
	PsCreateSystemThread( &SystemThreadHdl , THREAD_ALL_ACCESS , NULL , NULL , NULL , ThreadEntry , NULL );

	return ZwClose( SystemThreadHdl );
}