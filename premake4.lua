solution( "rss2rss" )
	configurations{ "debug", "release" }
	
	project( "Server" )
		kind( "ConsoleApp" )
		targetname( "rss2rss" )
		language( "C++" )
		location( "build" )
		files( { "./src/**.h", "./src/**.cpp" } )
		
		-- Enable C++11 support
		buildoptions{ "-std=c++11" }
		
		links( {
				"tidy"
			,	"sqlite3"
			
			-- Poco libraries and dependencies
			,	"PocoNetSSL"
			,	"PocoCrypto"
			,	"PocoNet"
			,	"PocoUtil"
			,	"PocoXML"
			,	"Ws2_32"
			,	"wsock32"
			,	"ssl"
			,	"crypto"
			,	"PocoFoundation"
			,	"iphlpapi"
			} )
		
		
		configuration( "debug" )
			build_dir = "debug"
			targetdir( "bin/" .. build_dir )
			defines( { "DEBUG" } )
			flags { "Symbols" }
		
		configuration( "release" )
			build_dir = "release"
			targetdir( "bin/" .. build_dir )
			defines( { "RELEASE" } )
			flags { "Optimize" }