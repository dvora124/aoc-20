import java  .io.File
import scala .io.Source
import scala .util.control.Breaks._

class CGrid ( val Data : Seq[String] )
{
  def CountTrees ( ) : Int =
  {
    var c = 0;
    var cnt = 0;
    for ( line <- Data )
    {
      if ( c >= line . length () )
        c -= line . length
      if ( line(c) == '#' )
        cnt += 1
      c += 3
    }
    return cnt;
  }
};

object Puzzle
{
  def LoadGrid ( in : File ) : CGrid =
  {
    LoadGrid ( Source . fromFile ( in ) )
  }
  def LoadGrid ( in : Source ) : CGrid =
  {
    val seq = in . getLines () . toSeq
    new CGrid ( seq )
  }
};

object Main
{
  def main ( args : Array[String] ) : Unit =
  {
    if ( args . length != 1 )
    {
      println ( "Usage: prog <puzzle>" )
      sys . exit  ( 1 )
    }

    val g = Puzzle . LoadGrid ( new File ( args(0) ) )
    println ( s"There are ${g . CountTrees ()} trees" )
  }
};