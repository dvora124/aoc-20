#include <stdio.h>
#include <string.h>

/*-----------------------------------------------------------------------------------------------*/
/**
 * Determine, whether the password is valid.
 *
 * The password is valid iff there is at least *min* # of occurences and at most *max* # of
 * occurences of the character *c*.
 *
 * @param[in] pwd the password
 * @param[in] min min. # of occurences of *c*
 * @param[in] max max. # of occurences of *c*
 * @param[in] c   character we check for
 * @return 1 - password is valid, 0 - password is invalid
 */
int passwordOK ( const char * pwd, int min, int max, char c )
{
  int oc = 0;
  while ( *pwd )
  {
    if ( *pwd == c )
      oc ++;
    pwd ++;
  }
  return oc >= min && oc <= max;
}
/*-----------------------------------------------------------------------------------------------*/
int main ( int argc, char * argv [] )
{
  char  * str = NULL;
  size_t  capacity = 0, cnt = 0;

  while ( getline ( &str, &capacity, stdin ) != -1 )
  {
    int  min, max, nr;
    char c;
    if ( sscanf ( str, "%d-%d %c: %n", &min, &max, &c, &nr ) != 3
         || min < 0
         || min > max )
    {
      printf ( "Wrong policy format\n" );
      return 1;
    }
    if ( passwordOK ( str + nr, min, max, c ) )
      cnt ++;
  }
  if ( ! feof ( stdin ) )
  {
    printf ( "Wrong input\n" );
    return 1;
  }

  printf ( "# of valid passwords is %zd\n", cnt );
  return 0;
}
