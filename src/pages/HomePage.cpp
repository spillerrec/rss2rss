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

#include "HomePage.hpp"

#include "../db/Database.hpp"
#include "../db/Channel.hpp"

using namespace std;

string HomePage::serve( vector<string> args, vector<header> &headers ) const{
	Database db( "test.sqlite" );
	Statement stmt = Channel::all( db );
	
	string html_begin = "<html><head><title>test</title><head><body>";
	string html_end = "</body></html>";
	
	string content;
	while( stmt.next() ){
		Channel ch;
		ch.load( stmt );
		content += "<p>" + ch.title + "</p>";
	}
	
	return html_begin + content + html_end;
}

