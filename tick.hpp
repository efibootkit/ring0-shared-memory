bool SendSharedMemTick( )
{
	bool Return = FALSE;

	if ( SharedMem->Operation != EOperation::Complete )
	{
		switch ( SharedMem->Operation )
		{
		case EOperation::Ping:
			Return = SendPing( );
			break;
		}

		SharedMem->Operation = EOperation::Complete;
	}
	else
	{
		Return = TRUE;
	}

	return Return;
}