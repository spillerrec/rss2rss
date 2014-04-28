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

#include "RssPage.hpp"

#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <iostream>

#include "../parsing/Rss.hpp"

using namespace std;

string RssPage::serve( vector<string> args, vector<header> &headers ) const{
	
	Rss rss;
	rss.title.value = "Test";
	rss.link.value = "http://www.google.com/";
	
	
	headers.push_back( header( "Content-Type", "application/rss+xml" ) );
	return rss.save();
}

