#include <stdio.h>
#include <string.h>

/*-----------------------------------------------------------------------------------------------*/
/**
 * Determine, whether the password is valid.
 *
 * The password is valid iff exactly one of the two positions (pos1, pos2) contain the letter *c*.
 *
 * @param[in] pwd  the password
 * @param[in] pos1 position is *pwd*, 0-based
 * @param[in] pos2 position is *pwd*, 0-based
 * @param[in] c    character we check for
 * @return 1 - password is valid, 0 - password is invalid
 */
int passwordOK ( const char * pwd, int pos1, int pos2, char c )
{
  int a, b, len = strlen ( pwd );
  a = pos1 < len && pwd[pos1] == c;
  b = pos2 < len && pwd[pos2] == c;
  return a ^ b;
}
/*-----------------------------------------------------------------------------------------------*/
int main ( int argc, char * argv [] )
{
  char  * str = NULL;
  size_t  capacity = 0, cnt = 0;

  while ( getline ( &str, &capacity, stdin ) != -1 )
  {
    int  pos1, pos2, nr;
    char c;
    if ( sscanf ( str, "%d-%d %c: %n", &pos1, &pos2, &c, &nr ) != 3
         || pos1 < 1
         || pos2 < 1 )
    {
      printf ( "Wrong policy format\n" );
      return 1;
    }
    if ( passwordOK ( str + nr, pos1 - 1, pos2 - 1, c ) )
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
