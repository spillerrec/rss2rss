/*	This file is part of rss2rss.

	rss2rss is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	rss2rss is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with rss2rss.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "UpdatePage.hpp"

#include "../db/Database.hpp"
#include "../db/Channel.hpp"
#include "../db/ChannelItem.hpp"

#include <iostream>

using namespace std;
using namespace pugi;

string UpdatePage::serve( vector<string> args, vector<header> &headers ) const{
	Database db( "test.sqlite" ); //TODO: no manual connection here!
	Statement stmt = Channel::all( db );
	
	while( stmt.next() ){
		Channel ch;
		ch.load( stmt );
		
		//Fetch and parse RSS
		string str = getFromUrl( ch.address );
		xml_document doc;
		doc.load_buffer( str.c_str(), str.size() );
		Rss rss( doc );
		
		//Insert all rows into DB
		for( auto item : rss.items ){
			ChannelItem ch_item( ch.name, item );
			ch_item.save( db );
		}
	}
	
	return "Updated!";
}

