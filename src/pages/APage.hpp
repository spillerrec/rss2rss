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

#ifndef A_PAGE_H
#define A_PAGE_H

#include <vector>
#include <string>
#include <utility>

class APage{
	public:
		typedef std::pair<std::string,std::string> header;
		static header content_type( std::string mime="text/html" ){ return header( "Content-Type", mime ); }
		virtual std::string serve( std::vector<std::string> args, std::vector<header> &headers ) const = 0;
		virtual ~APage(){ }
		
		static std::string getFromUrl( std::string url,	std::vector<std::pair<std::string,std::string> > headers = std::vector<std::pair<std::string,std::string> >() );
};

#endif

