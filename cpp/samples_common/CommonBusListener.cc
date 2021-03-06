/******************************************************************************
 * Copyright (c) 2013 - 2014, AllSeen Alliance. All rights reserved.
 *
 *    Permission to use, copy, modify, and/or distribute this software for any
 *    purpose with or without fee is hereby granted, provided that the above
 *    copyright notice and this permission notice appear in all copies.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *    WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *    MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *    ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *    WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *    ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *    OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 ******************************************************************************/

#include "CommonBusListener.h"
#include <iostream>
#include <algorithm>

using namespace ajn;

CommonBusListener::CommonBusListener(ajn::BusAttachment* bus) :
    BusListener(), SessionPortListener(), m_SessionPort(0), m_Bus(bus)
{
}

CommonBusListener::~CommonBusListener()
{
}

void CommonBusListener::setSessionPort(ajn::SessionPort sessionPort)
{
    m_SessionPort = sessionPort;
}

SessionPort CommonBusListener::getSessionPort()
{
    return m_SessionPort;
}

bool CommonBusListener::AcceptSessionJoiner(ajn::SessionPort sessionPort, const char* joiner, const ajn::SessionOpts& opts)
{
    if (sessionPort != m_SessionPort) {
        return false;
    }

    std::cout << "Accepting JoinSessionRequest" << std::endl;
    return true;
}

void CommonBusListener::SessionJoined(SessionPort sessionPort, SessionId id, const char* joiner)
{
    std::cout << "Session has been joined successfully" << std::endl;
    if (m_Bus) {
        m_Bus->SetSessionListener(id, this);
    }
    m_SessionIds.push_back(id);
}

void CommonBusListener::SessionLost(SessionId sessionId, SessionLostReason reason)
{
    std::cout << "Session has been lost" << std::endl;
    std::vector<SessionId>::iterator it = std::find(m_SessionIds.begin(), m_SessionIds.end(), sessionId);
    if (it != m_SessionIds.end()) {
        m_SessionIds.erase(it);
    }
}

const std::vector<SessionId>& CommonBusListener::getSessionIds() const
{
    return m_SessionIds;
}
