bool SendPing( )
{
	SharedMem->PhysMem.TargetBuffer = 0x1337;
	return TRUE;
}