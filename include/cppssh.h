/*
    cppssh - C++ ssh library
    Copyright (C) 2015  Chris Desjardins
    http://blog.chrisd.info cjd@chrisd.info

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _CPPSSH_Hxx
#define _CPPSSH_Hxx

#include "export.h"
#include <cstdlib>
#include <memory>
#include <string>

class CppsshImpl;
class CppsshMessage;
class CppsshLogger;
class CppsshConstPacket;

class Cppssh
{
public:
    CPPSSH_EXPORT static void create();
    CPPSSH_EXPORT static void destroy();
    CPPSSH_EXPORT static bool connectWithPassword(int* channelId, const char* host, const short port, const char* username, const char* password, unsigned int timeout = 1, bool shell = true);
    CPPSSH_EXPORT static bool connectWithKey(int* channelId, const char* host, const short port, const char* username, const char* privKeyFileName, unsigned int timeout = 1, bool shell = true);
    CPPSSH_EXPORT static bool isConnected(const int channelId);
    CPPSSH_EXPORT static bool send(const int channelId, const char* data, size_t bytes);
    CPPSSH_EXPORT static bool read(const int channelId, CppsshMessage* data);
    CPPSSH_EXPORT static bool close(const int channelId);
    CPPSSH_EXPORT static void setOptions(const char* prefCipher, const char* prefHmac);
    CPPSSH_EXPORT static bool generateKeyPair(const char* type, const char* fqdn, const char* privKeyFileName, const char* pubKeyFileName, short keySize = 0);
    CPPSSH_EXPORT static bool getLogMessage(const int channelId, CppsshMessage* message);

private:
    static std::shared_ptr<CppsshImpl> s_cppsshInst;
    Cppssh();
    Cppssh(const Cppssh&);
    Cppssh& operator=(const Cppssh&);
};

class CppsshMessage
{
public:
    CppsshMessage& operator=(const CppsshMessage&);
    CppsshMessage();
    ~CppsshMessage();
    CPPSSH_EXPORT const char* const message() const;
    friend class CppsshLogger;
    friend class CppsshConstPacket;
private:
    std::shared_ptr<char> _message;
};

#endif

