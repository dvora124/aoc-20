import sys  # read lines

def parseRow ( code : str ) -> int :
  # the key observation here is that the code already corresponds to the binary number which
  # is the row number, we just need to replace B with 1 and F with 0
  def hilfe ( it, mask : int, accum : int ) :
    # terminating condition
    if mask == 0 :
      return accum
    if next ( it ) == 'B' :
      accum |= mask
    return hilfe ( it, mask >> 1, accum )
    pass
  return hilfe ( iter ( code ), 1 << 6, int ( 0 ) )
  pass

def parseCol ( code : str ) -> int :
  # we can also extract the information by mapping characters to their numeric counterparts and
  # then feeding the python's int(_,2) function
  return int ( '' . join ( list ( map ( lambda x : '1' if x == 'R' else '0', code ) ) ), 2 )
  pass

def parseSeat ( code : str ) -> int :
  r = parseRow ( code[0:7] )
  c = parseCol ( code[7:10] )
  print ( f"{code} -> R {r}, C {c}" )
  return r * 8 + c
  pass

maxID = 0
for line in sys . stdin :
  if line[-1] == "\n" :
    line = line[:-1]
  maxID = max ( parseSeat ( line ), maxID )

print ( f"Max = {maxID}" )