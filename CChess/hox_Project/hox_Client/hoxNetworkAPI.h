/***************************************************************************
 *  Copyright 2007, 2008 Huy Phan  <huyphan@playxiangqi.com>               *
 *                                                                         * 
 *  This file is part of HOXChess.                                         *
 *                                                                         *
 *  HOXChess is free software: you can redistribute it and/or modify       *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  HOXChess is distributed in the hope that it will be useful,            *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with HOXChess.  If not, see <http://www.gnu.org/licenses/>.      *
 ***************************************************************************/

/////////////////////////////////////////////////////////////////////////////
// Name:            hoxNetworkAPI.h
// Created:         10/26/2007
//
// Description:     Containing network related APIs specific to this project.
/////////////////////////////////////////////////////////////////////////////

#ifndef __INCLUDED_HOX_NETWORK_API_H_
#define __INCLUDED_HOX_NETWORK_API_H_

#include <wx/wx.h>
#include <wx/socket.h>
#include "hoxEnums.h"
#include "hoxTypes.h"

namespace hoxNetworkAPI
{
    /**
     * Providing exlusive access to the socket input by disabling 
     * wxSOCKET_INPUT event and re-enabling it upon destruction.
     */
    class SocketInputLock
    {
    public:
        SocketInputLock( wxSocketBase* sock );
        ~SocketInputLock();
    private:
        wxSocketBase* m_sock;
    };


    hoxResult SendRequest( wxSocketBase*   sock, 
                           const wxString& request,
                           wxString&       response );

    hoxResult SendOutData( wxSocketBase*   sock, 
                           const wxString& contentStr );

    hoxResult ParseCommand( const wxString& commandStr, 
                            hoxCommand&     command );

    hoxResult ParseSimpleResponse( const wxString& responseStr,
                                   int&            returnCode,
                                   wxString&       returnMsg );

	hoxResult ParseConnectResponse( const wxString& responseStr,
                                    int&            returnCode,
                                    wxString&       returnMsg,
									wxString&       sessionId,
									int&            nScore );

    hoxResult ParseNetworkTables( const wxString&          responseStr,
                                  hoxNetworkTableInfoList& tableList );
    hoxResult ParseOneNetworkTable( const wxString&      tableStr,
                                    hoxNetworkTableInfo &tableInfo );

    hoxResult ParseNewNetworkTable( const wxString&  responseStr,
		                            hoxNetworkTableInfo &tableInfo );

    hoxResult ParseJoinNetworkTable( const wxString&      responseStr,
                                     hoxNetworkTableInfo& tableInfo );

    hoxResult ParseNetworkEvents( const wxString&      responseStr,
                                  int&                 returnCode,
                                  wxString&            returnMsg,
                                  hoxNetworkEventList& networkEvents );

    hoxResult ReadCommand( wxSocketBase* sock, 
                           hoxCommand&   command );

    hoxResult ReadLine( wxSocketBase* sock, 
                        wxString&     result );

    hoxResult WriteMsg( wxSocketBase*   sock,
                        const wxString& message );

    hoxResult ReadMsg( wxSocketBase* sock,
                       wxString&     response );


    /* PRIVATE */
    hoxResult _ParseNetworkEventString( const wxString&  eventStr,
                                        hoxNetworkEvent& networkEvent );

    /**
     * Convert a given socket-event to a (human-readable) string.
     */
    const wxString SocketEventToString( const wxSocketNotify socketEvent );

    /**
     * Convert a given socket-error to a (human-readable) string.
     */
    const wxString SocketErrorToString( const wxSocketError socketError );


} /* namespace hoxNetwork */

#endif /* __INCLUDED_HOX_NETWORK_API_H_ */