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

#include "ChannelPage.hpp"

#include "../db/Database.hpp"
#include "../db/Channel.hpp"
#include "../db/ChannelItem.hpp"

using namespace std;

string addChannelList( Database& db ){
	string content = "<div id=\"sidebar\">";
	
	content += "<ul>";
	Statement stmt = Channel::all( db );
	while( stmt.next() ){
		Channel ch;
		ch.load( stmt );
		content += "<li><a href=\"/channel/" + ch.name + "/\">" + ch.name + "</a></li>";
	}
	content += "</ul>";
	
	return content + "</div>";
}

string addItem( ChannelItem& item ){
	string content = "<article>";
	
	content += "<h3>" + item.title + "</h3>";
	
	//TODO: investigate sandboxed iframe?
	content += "<div>";
	content += item.content.empty() ? item.description : item.content;
	content += "</div></article>";
	
	return content;
}

string ChannelPage::serve( vector<string> args, vector<header> &headers ) const{
	Database db( "test.sqlite" ); //TODO: no manual connection here!
	Statement stmt = ChannelItem::all( db );
	//TODO: do the filtering in SQL
	if( args.size() != 2 )
		return "Invalid parameters";
	string channel = args[1];
	
	headers.emplace_back( "Content-Type", "text/html; charset=utf-8" );
	
	string start = "<html><head><title>" + channel + "</title><link rel=\"stylesheet\" href=\"/files/main.css\"/></head><body>";
	string end = "</body></html>";
	string content;
	
	
	content += "<div id=\"content\">";
	while( stmt.next() ){
		ChannelItem item;
		item.load( stmt );
		
		if( item.channel == channel ){
			content += addItem( item );
		}
	}
	content += "</div>";
	
	content += addChannelList( db );
	
	return start + content + end;
}

