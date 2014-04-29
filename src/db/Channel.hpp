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

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "Record.hpp"
#include "Statement.hpp"

#include <string>

class Channel: public Record{
	public:
		std::string name;
		std::string title;
		std::string address;
		int update_interval;
		int last_update;
		
	public:
		void load( Statement& stmt );
		
		static Statement all( Database &db ){
			return Statement( db, "SELECT * FROM channel" );
		}
};

#endif

