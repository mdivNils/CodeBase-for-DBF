/***********************************************************************\
*                                                                       *
*   APPEND.CPP       Copyright (C) 1999 Sequiter Software Inc.          *
*                                                                       *
\***********************************************************************/
/* See User's Manual, chapter 11 */

#include "d4all.hpp"

#ifdef __TURBOC__
   extern unsigned _stklen = 10000 ; // for all Borland compilers
#endif

void main()
{
   Code4 cb ;
   cb.optimize = OPT4ALL ;
   cb.optimizeWrite = OPT4ALL ;

   Data4 dataFrom( cb, "from_dbf"), dataTo( cb, "to_dbf" ) ;
   cb.exitTest( ) ;

   Field4 infoFrom( dataFrom, "NAME" ), infoTo( dataTo, "FNAME" ) ;
   cb.optStart( ) ;

   cb.lockAttempts = 1 ;
   int rc1 = dataFrom.lockAll( ) ;
   int rc2 = dataTo.lockAll( ) ;

   if( rc1 != 0 || rc2 != 0 )
   {
      cout << "Locking Failed" << endl ;
      cb.exit( ) ;
   }

   for( int rc = dataFrom.top( ); rc == 0; rc = dataFrom.skip( ) )
   {
      dataTo.appendStart( ) ;
      infoTo.assignField( infoFrom ) ;
      dataTo.append( ) ;
   }

   dataFrom.unlock( ) ;
   dataTo.unlock( ) ;

   cb.closeAll( ) ;
   cb.initUndo( ) ;
}
