////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2009 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Network/IPAddress.hpp>
#include <SFML/Network/Http.hpp>
#include <SFML/Network/SocketHelper.hpp>
#include <string.h>


namespace sf
{
////////////////////////////////////////////////////////////
/// Static member data
////////////////////////////////////////////////////////////
const IPAddress IPAddress::LocalHost("127.0.0.1");


////////////////////////////////////////////////////////////
/// Default constructor
////////////////////////////////////////////////////////////
IPAddress::IPAddress() :
myAddress(INADDR_NONE)
{

}


////////////////////////////////////////////////////////////
/// Construct the address from a string
////////////////////////////////////////////////////////////
IPAddress::IPAddress(const std::string& address)
{
    // First try to convert it as a byte representation ("xxx.xxx.xxx.xxx")
    myAddress = inet_addr(address.c_str());

    // If not successful, try to convert it as a host name
    if (!IsValid())
    {
        hostent* host = gethostbyname(address.c_str());
        if (host)
        {
            // Host found, extract its IP address
            myAddress = reinterpret_cast<in_addr*>(host->h_addr)->s_addr;
        }
        else
        {
            // Host name not found on the network
            myAddress = INADDR_NONE;
        }
    }
}


////////////////////////////////////////////////////////////
/// Construct the address from a C-style string ;
/// Needed for implicit conversions from literal strings to IPAddress to work
////////////////////////////////////////////////////////////
IPAddress::IPAddress(const char* address)
{
    // First try to convert it as a byte representation ("xxx.xxx.xxx.xxx")
    myAddress = inet_addr(address);

    // If not successful, try to convert it as a host name
    if (!IsValid())
    {
        hostent* host = gethostbyname(address);
        if (host)
        {
            // Host found, extract its IP address
            myAddress = reinterpret_cast<in_addr*>(host->h_addr)->s_addr;
        }
        else
        {
            // Host name not found on the network
            myAddress = INADDR_NONE;
        }
    }
}


////////////////////////////////////////////////////////////
/// Construct the address from 4 bytes
////////////////////////////////////////////////////////////
IPAddress::IPAddress(Uint8 byte0, Uint8 byte1, Uint8 byte2, Uint8 byte3)
{
    myAddress = htonl((byte0 << 24) | (byte1 << 16) | (byte2 << 8) | byte3);
}


////////////////////////////////////////////////////////////
/// Construct the address from a 32-bits integer
////////////////////////////////////////////////////////////
IPAddress::IPAddress(Uint32 address)
{
    myAddress = htonl(address);
}


////////////////////////////////////////////////////////////
/// Tell if the address is a valid one
////////////////////////////////////////////////////////////
bool IPAddress::IsValid() const
{
    return myAddress != INADDR_NONE;
}


////////////////////////////////////////////////////////////
/// Get a string representation of the address
////////////////////////////////////////////////////////////
std::string IPAddress::ToString() const
{
    in_addr address;
    address.s_addr = myAddress;

    return inet_ntoa(address);
}


////////////////////////////////////////////////////////////
/// Get an integer representation of the address
////////////////////////////////////////////////////////////
Uint32 IPAddress::ToInteger() const
{
    return ntohl(myAddress);
}


////////////////////////////////////////////////////////////
/// Get the computer's local IP address (from the LAN point of view)
////////////////////////////////////////////////////////////
IPAddress IPAddress::GetLocalAddress()
{
    // The method here is to connect a UDP socket to anyone (here to localhost),
    // and get the local socket address with the getsockname function.
    // UDP connection will not send anything to the network, so this function won't cause any overhead.

    IPAddress localAddress;

    // Create the socket
    SocketHelper::SocketType sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == SocketHelper::InvalidSocket())
        return localAddress;

    // Build the host address (use a random port)
    sockaddr_in sockAddr;
    memset(sockAddr.sin_zero, 0, sizeof(sockAddr.sin_zero));
    sockAddr.sin_addr.s_addr = INADDR_LOOPBACK;
    sockAddr.sin_family      = AF_INET;
    sockAddr.sin_port        = htons(4567);

    // Connect the socket
    if (connect(sock, reinterpret_cast<sockaddr*>(&sockAddr), sizeof(sockAddr)) == -1)
    {
        SocketHelper::Close(sock);
        return localAddress;
    }
 
    // Get the local address of the socket connection
    SocketHelper::LengthType size = sizeof(sockAddr);
    if (getsockname(sock, reinterpret_cast<sockaddr*>(&sockAddr), &size) == -1)
    {
        SocketHelper::Close(sock);
        return localAddress;
    }

    // Close the socket
    SocketHelper::Close(sock);

    // Finally build the IP address
    localAddress.myAddress = sockAddr.sin_addr.s_addr;

    return localAddress;
}


////////////////////////////////////////////////////////////
/// Get the computer's public IP address (from the web point of view)
////////////////////////////////////////////////////////////
IPAddress IPAddress::GetPublicAddress(float timeout)
{
    // The trick here is more complicated, because the only way
    // to get our public IP address is to get it from a distant computer.
    // Here we get the web page from http://www.sfml-dev.org/ip-provider.php
    // and parse the result to extract our IP address
    // (not very hard : the web page contains only our IP address).

    Http server("www.sfml-dev.org");
    Http::Request request(Http::Request::Get, "/ip-provider.php");
    Http::Response page = server.SendRequest(request, timeout);
    if (page.GetStatus() == Http::Response::Ok)
        return IPAddress(page.GetBody());

    // Something failed: return an invalid address
    return IPAddress();
}


////////////////////////////////////////////////////////////
/// Comparison operator ==
////////////////////////////////////////////////////////////
bool IPAddress::operator ==(const IPAddress& other) const
{
    return myAddress == other.myAddress;
}


////////////////////////////////////////////////////////////
/// Comparison operator !=
////////////////////////////////////////////////////////////
bool IPAddress::operator !=(const IPAddress& other) const
{
    return myAddress != other.myAddress;
}


////////////////////////////////////////////////////////////
/// Comparison operator <
////////////////////////////////////////////////////////////
bool IPAddress::operator <(const IPAddress& other) const
{
    return myAddress < other.myAddress;
}


////////////////////////////////////////////////////////////
/// Comparison operator >
////////////////////////////////////////////////////////////
bool IPAddress::operator >(const IPAddress& other) const
{
    return myAddress > other.myAddress;
}


////////////////////////////////////////////////////////////
/// Comparison operator <=
////////////////////////////////////////////////////////////
bool IPAddress::operator <=(const IPAddress& other) const
{
    return myAddress <= other.myAddress;
}


////////////////////////////////////////////////////////////
/// Comparison operator >=
////////////////////////////////////////////////////////////
bool IPAddress::operator >=(const IPAddress& other) const
{
    return myAddress >= other.myAddress;
}


////////////////////////////////////////////////////////////
/// Operator >> overload to extract an address from an input stream
////////////////////////////////////////////////////////////
std::istream& operator >>(std::istream& stream, IPAddress& address)
{
    std::string str;
    stream >> str;
    address = IPAddress(str);

    return stream;
}


////////////////////////////////////////////////////////////
/// Operator << overload to print an address to an output stream
////////////////////////////////////////////////////////////
std::ostream& operator <<(std::ostream& stream, const IPAddress& address)
{
    return stream << address.ToString();
}

} // namespace sf
