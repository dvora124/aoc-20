#include <stdio.h>

#define DATA_MAX 200

/*-----------------------------------------------------------------------------------------------*/
/**
 * Find two numbers which add up to *val* and return their product. If there are multiple such
 * pairs, the first one is returned.
 * @param[in]  data    list of numbers
 * @param[in]  nr      length
 * @param[in]  val     value the pair ought to add up to
 * @param[out] mulRes  product of the pair
 * @return 0 - not found, 1 - found and inscribed to *mulRes*
 */
int findNum ( int data[], int nr, int val, int * mulRes )
{
  int i, j, seek, isFound;

  for ( i = 0; i < nr - 1; i ++ )
  {
    seek = val - data[i];

    isFound = 0;
    for ( j = i + 1; j < nr; j ++ )
      if ( data[j] == seek )
      {
        isFound = 1;
        break;
      }

    if ( isFound )
    {
     *mulRes = seek * data[i];
      return 1;
    }
  }
  return 0;
}
/*-----------------------------------------------------------------------------------------------*/
int main ( int argc, char * argv [] )
{
  int i, data[DATA_MAX], mulRes;

  printf ( "Enter values (200):\n" );
  for ( i = 0; i < DATA_MAX; i ++ )
    if ( scanf ( "%d", data + i ) != 1 )
    {
      printf ( "Invalid input.\n" );
      return 1;
    }

  if ( ! findNum ( data, DATA_MAX, 2020, &mulRes ) )
  {
    printf ( "No such pair of numbers found\n" );
    return 0;
  }
  printf ( "The product is: %d\n", mulRes );
  return 0;
}
