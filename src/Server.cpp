/*	This file is part of BooruSurfer2.

	BooruSurfer2 is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	BooruSurfer2 is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with BooruSurfer2.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/HTTPServer.h>

#include "Server.hpp"
#include "pages/PageHandler.hpp"

#include <boost/algorithm/string.hpp>

#include <iostream>

using namespace Poco::Net;
using namespace std;

//TODO: find a proper implementation
void unencode_str( string& input ){
	int pos = 0;
	do{
		pos = input.find_first_of( '%', pos );
		if( pos - 2 >= input.size() )
			break;
		
		try{
			int value = stoi( input.substr( pos+1, 2 ), nullptr, 16 );
			input.replace( pos, 3, 1, (char)value );
		}
		catch( ... ){
			cout << "Error while processing: " << input << "\n";
			break;
		}
	}while( true );
}

class RequestHandler : public HTTPRequestHandler {
	public:
		virtual void handleRequest( HTTPServerRequest& req, HTTPServerResponse& response ) override {
			PageHandler pages;
			
			//Split on '/' and remove empty parts
			vector<string> args;
			boost::split( args, req.getURI(), boost::is_any_of( "/" ) ); //TODO: avoid is_any_of() ?
			args.erase( remove_if( args.begin(), args.end(), [](string arg){ return arg.empty(); } ), args.end() );
			
			for( auto& arg : args )
				unencode_str( arg );
			
			//Create content
			string contents;
			vector<APage::header> headers;
			if( args.size() == 0 )
				contents = pages.get_root()->serve( args, headers );
			else
				contents = pages.get( args[0] )->serve( args, headers );
			
			//Add headers
			response.setStatus( HTTPResponse::HTTP_OK );
			for( APage::header h : headers )
				response.add( h.first, h.second );
			
			//Send content
			response.sendBuffer( contents.c_str(), contents.size() );
		}
};

class RequestHandlerFactory : public HTTPRequestHandlerFactory {
	public:
		virtual HTTPRequestHandler* createRequestHandler( const HTTPServerRequest& request ) override{
			return new RequestHandler;
		}
};


int Server::main( const vector<string>& unknown ){
	HTTPServer s( new RequestHandlerFactory, ServerSocket( 9000 ), new HTTPServerParams );
	
	s.start();
	waitForTerminationRequest();
	s.stop();
	
	return Application::EXIT_OK;
}




