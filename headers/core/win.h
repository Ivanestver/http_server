#pragma once
#ifdef WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <winerror.h>

// Common names for struct which are specific for every OS
using socket_t = SOCKET;
using sockaddr_t = SOCKADDR;
using sockaddr_in_t = SOCKADDR_IN;
using port_t = u_short;

// Replacements for raw enumerations
enum class AddressFamily
{
	UNSPEC,  // unspecified
	UNIX,    // local to host (pipes, portals)
	INET,    // internetwork: UDP, TCP, etc.
	IMPLINK,	// arpanet imp addresses
	PUP,	// pup protocols: e.g. BSP
	CHAOS,	// mit CHAOS protocols
	NS,	// XEROX NS protocols
	IPX,	// IPX protocols: IPX, SPX, etc.
	ISO,	// ISO protocols
	OSI,	// OSI is ISO
	ECMA,	// european computer manufacturers
	DATAKIT,	// datakit protocols
	CCITT,	// CCITT protocols, X.25 etc
	SNA,	// IBM SNA
	DECnet,	// DECnet
	DLI,	// Direct data link interface
	LAT,	// LAT
	HYLINK,	// NSC Hyperchannel
	APPLETALK,	// AppleTalk
	NETBIOS,	// NetBios-style addresses
	VOICEVIEW,	// VoiceView
	FIREFOX,	// Protocols from Firefox
	UNKNOWN1,	// Somebody is using this!
	BAN,	// Banyan
	ATM,	// Native ATM Services
	INET6,	// Internetwork Version 6
	CLUSTER,	// Microsoft Wolfpack
	_12844,	// IEEE 1284.4 WG AF
	IRDA,	// IrDA
	NETDES,	// Network Designers OSI & gateway
};

enum class SockType
{
	UNSPEC = 0, // unspecified socket
	STREAM = 1, // stream socket
	DGRAM,		// datagram socket
	RAW,		// raw-protocol interface
	RDM,		// reliably-delivered message
	SEQPACKET	// sequenced packet stream
};

enum class InAddr : unsigned long
{
	ANY = INADDR_ANY,
	LOOPBACK = INADDR_LOOPBACK,
	BROADCAST = INADDR_BROADCAST,
	NONE = INADDR_NONE
};

enum class IPProtocol
{
	UNSPEC = 0,		// Unspecified protocol
	ICMP = 1,		// ICMP protocol
	IGMP = 2,		// IGMP protocol
	RFCOMM = 3,		// Bluetooth
	TCP = 6,		// TCP protocol
	UDP = 17,		// UDP protocol
	ICMPV6 = 58,	// ICMPv6 protocol
	RM = 113		// PGM protocol
};

#pragma comment (lib, "Ws2_32.lib")
#endif