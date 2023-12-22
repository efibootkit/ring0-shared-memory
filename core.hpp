#include <ntddk.h>
#include <ntifs.h>
#include <cstdint>
#include "Tick.hpp"
#include "Handler.hpp"

std::uint64_t _SharedMemAddr;
std::uint32_t _ClientPID;
PEPROCESS _Client;

enum EOperation
{
	Complete ,
	Read ,
	Write ,
	ImageBase ,
	Ping
};

struct c_PhysMem
{
	std::uint32_t SourcePID;
	std::uint64_t SourceAddr;
	std::uint64_t TargetBuffer;
	size_t BufferSize;
};

struct c_SharedMem
{
	std::uint32_t Operation;
	c_PhysMem PhysMem;
};

c_SharedMem* SharedMem;