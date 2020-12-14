#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

#define BIT(n) (1lu << n)

//=================================================================================================
struct CFieldData
{
  const char               * m_K;
  uint8_t                    m_V;
};
//-------------------------------------------------------------------------------------------------
initializer_list<CFieldData> g_FieldData =
{
  { "byr", BIT ( 0 ) },
  { "iyr", BIT ( 1 ) },
  { "eyr", BIT ( 2 ) },
  { "hgt", BIT ( 3 ) },
  { "hcl", BIT ( 4 ) },
  { "ecl", BIT ( 5 ) },
  { "pid", BIT ( 6 ) },
  { "cid", BIT ( 7 ) }
};
//=================================================================================================
/**
 * Return the bitmask for a given key.
 * @param[in] k    key
 * @return the corresponding bitmask
 */
uint8_t getMask ( const string & k )
{
  for ( auto & x : g_FieldData )
    if ( k == x . m_K )
      return x . m_V;
  return 0x00;
}
//-------------------------------------------------------------------------------------------------
/**
 * Validate mask. The mask is valid all bits are in-place or only cid bit is missing.
 * @param[in] mask to be validate
 * @return true - valid, false - invalid
 */
bool    maskOK ( uint8_t mask )
{
  return mask == 0xff || mask == ( 0xff & ~ getMask ( "cid" ) );
}
//-------------------------------------------------------------------------------------------------
/**
 * Validate passport.
 *
 * The passport is valid if all required fields are present (or - a little shady - the CID is optionally
 * missing, which is very convenient for myself
 *
 * @param[in] x    passport string, whitespace separated list of fields
 * @return true - valid, false - invalid
 */
bool    passportOK ( const string & x )
{
  istringstream iss ( x );
  uint8_t       mask = 0;
  char          dummy1;
  string        key, dummy2;

  while ( iss >> setw ( 3 ) >> key >> dummy1 >> dummy2 )
    if ( dummy1 != ':' )
      return false;
    else
      mask |= getMask ( key );

  return maskOK ( mask );
}
//-------------------------------------------------------------------------------------------------
int main ( int argc, char * argv [] )
{
  int cnt = 0;
  while ( 1 )
  {
    string x, res;

    while ( getline ( cin, x ) && ! x . empty () )
      res += x + " ";
    if ( cin . eof () )
      break;

    if ( passportOK ( res ) ) cnt ++;
  }
  cout << "There are " << cnt << " valid passports" << endl;
  return 0;
}