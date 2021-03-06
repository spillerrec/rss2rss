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

#include "PageHandler.hpp"

#include "ChannelPage.hpp"
#include "FilePage.hpp"
#include "HomePage.hpp"
#include "UpdatePage.hpp"
#include "RssPage.hpp"

using namespace std;

PageHandler::PageHandler()
		:	page_root( new HomePage() )
		,	page_404( new HomePage() )
	{
	add( "rss", new RssPage() );
	add( "update", new UpdatePage() );
	add( "files", new FilePage() );
	add( "channel", new ChannelPage() );
}


PageHandler::~PageHandler(){
	
}


PageHandler::APage_ptr PageHandler::get( std::string page ){
	auto got = pages.find( page );
	if( got != pages.end() )
		return got->second;
	else
		return page_404;
}

