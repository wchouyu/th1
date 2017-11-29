#include <gtest/gtest.h>
// #include "utScanner.h"
#include "utParser.h"
#include "atom.h"
#include "atom.cpp"
#include "list.h"
#include "list.cpp"
int main( int argc , char **argv )
{
    testing :: InitGoogleTest( &argc , argv ) ;
    return RUN_ALL_TESTS( ) ;
}
