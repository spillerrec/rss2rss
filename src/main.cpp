//#include <iostream>
//#include <sqlite3.h>

#include "Server.hpp"
#include "db/Database.hpp"
//using namespace std;

int main( int argc, char* argv[] ){
	Database db( "test.sqlite" );
	
	return Server().run( argc, argv );
	/*
	sqlite3 *db;
	if( sqlite3_open( argv[1], &db ) ){
		cout << "Can't open database :\\" << endl;
		return -1;
	}
	
	sqlite3_stmt* ppStmt;
	if( sqlite3_prepare_v2( db, "SELECT * FROM channel", -1, &ppStmt, NULL ) != SQLITE_OK ){
		cout << "Prepare failed: " << sqlite3_errmsg( db ) << endl; //TODO: correct?
		return -2;
	}
	
	while( sqlite3_step( ppStmt ) != SQLITE_DONE ){
		for( int i=0; i<sqlite3_column_count( ppStmt ); i++ ){
			switch( sqlite3_column_type( ppStmt, i ) ){
				case SQLITE_INTEGER: cout << sqlite3_column_int64( ppStmt, i ) << endl; break;
				case SQLITE_FLOAT: cout << sqlite3_column_double( ppStmt, i ) << endl; break;
				case SQLITE_TEXT: cout << sqlite3_column_text( ppStmt, i ) << endl; break;
				case SQLITE_BLOB: cout << "BLOB" << endl; break;
				case SQLITE_NULL: cout << "NULL" << endl; break;
			}
		}
		
		cout << endl;
	}
	
	sqlite3_close( db );
	return 0;
	*/
}
