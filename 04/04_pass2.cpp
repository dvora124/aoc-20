#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <sstream>
using namespace std;

#define BIT(n) (1lu << (n))

//=================================================================================================
class ValidatorException : public std::exception
{
  public:
    //---------------------------------------------------------------------------------------------
                             ValidatorException            ( const char      * errDesc )
                             : m_ErrDesc ( errDesc )
    {
    }
    //---------------------------------------------------------------------------------------------
    virtual const char     * what                          ( void ) const noexcept override
    {
      return m_ErrDesc;
    }
    //---------------------------------------------------------------------------------------------
  private:
    const char * m_ErrDesc;
};
//=================================================================================================
class CValidator
{
  public:
    //---------------------------------------------------------------------------------------------
    static bool          ( * GetValidator ( const string    & val ) ) ( const string & )
    {
      for ( int i = 0; i < DATA_MAX; i ++ )
        if ( c_Data[i] . m_Identifier == val )
          return c_Data[i] . m_Meth;
      throw ValidatorException ( "function not found" );
    }
    //---------------------------------------------------------------------------------------------
  private:
    struct CHilfeData
    {
      const char           * m_Identifier;
      bool               ( * m_Meth ) ( const string & );
    };
  private:
    static const int         DATA_MAX                      = 8;
    static CHilfeData        c_Data[DATA_MAX];
  private:
    static bool              validateBYR                   ( const string    & val );
    static bool              validateIYR                   ( const string    & val );
    static bool              validateEYR                   ( const string    & val );
    static bool              validateHGT                   ( const string    & val );
    static bool              validateHCL                   ( const string    & val );
    static bool              validateECL                   ( const string    & val );
    static bool              validatePID                   ( const string    & val );
    static bool              validateCID                   ( const string    & val );
    static bool              validateYear                  ( const string    & val,
                                                             int               min,
                                                             int               max );
};
//-------------------------------------------------------------------------------------------------
CValidator::CHilfeData  CValidator::c_Data[CValidator::DATA_MAX] =
 {
   { "byr", validateBYR },
   { "iyr", validateIYR },
   { "eyr", validateEYR },
   { "hgt", validateHGT },
   { "hcl", validateHCL },
   { "ecl", validateECL },
   { "pid", validatePID },
   { "cid", validateCID },
 };
//-------------------------------------------------------------------------------------------------
bool               CValidator::validateBYR                 ( const string    & val )
{
  return validateYear ( val, 1920, 2002 );
}
//-------------------------------------------------------------------------------------------------
bool               CValidator::validateIYR                 ( const string    & val )
{
  return validateYear ( val, 2010, 2020 );
}
//-------------------------------------------------------------------------------------------------
bool               CValidator::validateEYR                 ( const string    & val )
{
  return validateYear ( val, 2020, 2030 );
}
//-------------------------------------------------------------------------------------------------
bool               CValidator::validateHGT                 ( const string    & val )
{
  int     height;
  string  unit;

  return istringstream ( val ) >> height >> unit
         && ( ( unit == "cm"
                 && height >= 150
                 && height <= 193 )
           || ( unit == "in"
                 && height >= 59
                 && height <= 76 ) );
}
//-------------------------------------------------------------------------------------------------
bool               CValidator::validateHCL                 ( const string    & val )
{
  if ( val . length () != 7 || val[0] != '#' )
    return false;
  for ( int i = 1; i < 7; i ++ )
    if ( ! isxdigit ( val[i] ) )
      return false;
  return true;
}
//-------------------------------------------------------------------------------------------------
bool               CValidator::validateECL                 ( const string    & val )
{
  initializer_list<string> ec =
   {
     "amb", "blu", "brn", "gry", "grn", "hzl", "oth"
   };
  for ( const auto & x : ec )
    if ( val == x )
      return true;
  return false;
}
//-------------------------------------------------------------------------------------------------
bool               CValidator::validatePID                 ( const string    & val )
{
  if ( val . length () != 9 )
    return false;
  for ( int i = 0; i < 9; i ++ )
    if ( ! isdigit ( val[i] ) )
      return false;
  return true;
}
//-------------------------------------------------------------------------------------------------
bool               CValidator::validateCID                 ( const string    & val )
{
  return true;
}
//-------------------------------------------------------------------------------------------------
bool               CValidator::validateYear                ( const string    & val,
                                                             int               min,
                                                             int               max )
{
  int year;
  if ( ! ( istringstream ( val ) >> year )
           || year < min
           || year > max )
    return false;
  else
    return true;
}
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
 * missing, which is very convenient for myself) and are in a valid format.
 *
 * @param[in] x    passport string, whitespace separated list of fields
 * @return true - valid, false - invalid
 */
bool passportOK ( const string & passport )
{
  istringstream  iss ( passport );
  string         k, v;
  char           dummy1;
  uint8_t        mask = 0;

  while ( ( iss >> setw ( 3 ) >> k >> dummy1 >> v ) && dummy1 == ':' )
  {
    auto val = CValidator::GetValidator ( k );
    if ( ! val ( v ) )
      return false;
    mask |= getMask ( k );
  }
  if ( ! iss . eof () )
    return false;

  return maskOK ( mask );
}
//-------------------------------------------------------------------------------------------------
int main ( int argc, char * argv [] )
{
  int validCnt = 0;
  while ( true )
  {
    string  x, res;
    bool    isFirst = true;

    while ( getline ( cin, x ) && ! x . empty () )
    {
      if ( ! isFirst )
        res += " ";
      res += x;
      isFirst = false;
    }
    if ( cin . eof () )
      break;

    if ( passportOK ( res ) )
      validCnt ++;
  }
  cout << "There are " << validCnt << " valid passports" << endl;
  return 0;
}