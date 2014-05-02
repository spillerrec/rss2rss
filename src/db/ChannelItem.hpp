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

#ifndef CHANNEL_ITEM_HPP
#define CHANNEL_ITEM_HPP

#include "Record.hpp"
#include "../parsing/rss.hpp"

#include <cstdint>

class ChannelItem: public Record{
	public:
		std::string channel;
		std::string title;
		std::string link;
		std::string description;
		std::string content;
		std::string author;
		std::string category;
		std::string guid;
		int64_t pubDate;
		std::string source;
		std::string media_thumb_url;
		std::string media_content_url;
		
	public:
		ChannelItem(){ }
		ChannelItem( std::string channel, Rss::Item item )
			:	channel( channel )
			,	 title( item.title.value )
			,	 link( item.link.value )
			,	 description( item.description.value )
			,	 content( item.content.value )
			,	 author( item.author.value )
			,	 category( item.category.value )
			,	 guid( item.guid.value )
			,	 source( item.source.url.value ) //TODO: name?
			,	 media_thumb_url( item.media_thumbnail.url.value )
			,	 media_content_url( item.media_content.url.value )
			{ fromRssDate( item.pubDate.value ); }
		
		void fromRssDate( std::string date );
		
		struct ItemStatement{
			Statement load;
			Statement save;
			ItemStatement( Database &db, const char* q1, const char* q2 )
				:	load( db, q1 ), save( db, q2 ) { }
		};
		void load( Statement& stmt );
		void save( ItemStatement &stmt );
		
		static Statement all( Database &db ){
			return Statement( db, "SELECT * FROM item" );
		}
		
		static ItemStatement saveAll( Database &db );
};

#endif

