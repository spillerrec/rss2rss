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

#include "ChannelItem.hpp"

void ChannelItem::load( Statement& stmt ){
	title = stmt.text( 0 );
	link = stmt.text( 1 );
	description = stmt.text( 2 );
	author = stmt.text( 3 );
	category = stmt.text( 4 );
	guid = stmt.text( 5 );
	pubDate = stmt.text( 6 );
	source = stmt.text( 7 );
	media_thumb_url = stmt.text( 8 );
	media_content_url = stmt.text( 9 );
	channel = stmt.text( 10 );
}

ChannelItem::ItemStatement ChannelItem::saveAll( Database &db ){
	return ItemStatement( db
		,	"SELECT * FROM item WHERE guid = ?1"
		,	"INSERT INTO item VALUES( ?1, ?2, ?3, ?4, ?5, ?6, ?7, ?8, ?9, ?10, ?11 )"
		);
}

void ChannelItem::save( ChannelItem::ItemStatement &stmt ){
	stmt.load.reset();
	stmt.load.bind( guid, 1 );
	if( stmt.load.next() ){
		//TODO: do a better check, as guid might be unavailable IIRC
		//TODO: update contents if different
		return;
	}
	
	stmt.save.reset();
	stmt.save.bind( title, 1 );
	stmt.save.bind( link, 2 );
	stmt.save.bind( description, 3 );
	stmt.save.bind( author, 4 );
	stmt.save.bind( category, 5 );
	stmt.save.bind( guid, 6 );
	stmt.save.bind( pubDate, 7 );
	stmt.save.bind( source, 8 );
	stmt.save.bind( media_thumb_url, 9 );
	stmt.save.bind( media_content_url, 10 );
	stmt.save.bind( channel, 11 );
	stmt.save.next();
}
