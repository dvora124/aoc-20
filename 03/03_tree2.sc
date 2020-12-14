import scala .annotation.tailrec
import java  .io.File
import scala .io.Source

class  CTreeGrid ( val Data : Seq[String] )
{
  def              CountTrees                              ( mr    : Int,
                                                             mc    : Int ) : Int =
  {
    @tailrec
    def            hilfe                                   ( r     : Int,
                                                             c     : Int,
                                                             accum : List[Char] ) : List[Char] =
    {
      if ( r >= Data . length )
        return accum
      else
        hilfe ( r + mr, (c + mc) % Data(r) . length, Data(r)(c) :: accum )
    }
    hilfe ( 0, 0, List . empty ) . foldLeft[Int] ( 0 ) ( (b, a) =>
                                                           {
                                                             if ( a == '#' )
                                                               b + 1
                                                             else
                                                               b
                                                           } )
  }
};

object CTreeGrid
{
  def apply ( file : File ) : CTreeGrid =
  {
    new CTreeGrid ( Source . fromFile ( file ) . getLines . toSeq )
  }
}

object Main
{
  def main ( args : Array[String] ) : Unit =
  {
    if ( args . length == 1 )
    {
      val g = CTreeGrid ( new File ( args(0) ) )
      println ( "The answer is " + List ( (1, 1), (1, 3), (1, 5), (1, 7), (2, 1) )
                                     . foldLeft[Long] ( 1 )
                                         ( (mul, puzzle) =>
                                             {
                                               mul * g . CountTrees ( puzzle . _1, puzzle . _2 )
                                             } ) )
    }
    else
      println ( "Wrong arguments" )
  }
};