/**********************************************************************
  ga_bitstring.c
 **********************************************************************

  ga_bitstring - GAUL's low-level bitstring routines.
  Copyright �2001, Stewart Adcock <stewart@bellatrix.pcl.ox.ac.uk>

  The latest version of this program should be available at:
  http://www.stewart-adcock.co.uk/

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.  Alternatively, if your project
  is incompatible with the GPL, I will probably agree to requests
  for permission to use the terms of any other license.

  This program is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY WHATSOEVER.

  A full copy of the GNU General Public License should be in the file
  "COPYING" provided with this distribution; if not, see:
  http://www.gnu.org/

 **********************************************************************

  Synopsis:     Low-level bitstring handling functions.

		Note that there is a lack of sanity checking in here
		for efficiency reasons.  Parameter safety should be
		confirmed in the wrapper functions.

  To do:	Mappings.

 **********************************************************************/

#include "ga_bitstring.h"

/**********************************************************************
  ga_bit_new()
  synopsis:	Create a new bitstring.
  parameters:	int	length	Number of bits.
  return:	byte	*ptr	Newly allocated bitstring.
  last updated:	30/06/01
 **********************************************************************/

byte *ga_bit_new( int length )
  {
  byte *ptr;

  if ( !(ptr = (byte *) s_malloc( ga_bit_sizeof( length ) )) )
    die("Unable to allocate bitstring.");

  return ptr;
  }


/**********************************************************************
  ga_bit_free()
  synopsis:	Deallocates a bitstring.
  parameters:	byte	*bstr	Bitstring to deallocate.
  return:	none
  last updated:	30/06/01
 **********************************************************************/

void ga_bit_free( byte *bstr )
  {
  s_free( bstr );

  return;
  }


/**********************************************************************
  ga_bit_set()
  synopsis:	Sets a single bit in a bitstring.
  parameters:	byte	*bstr	Bitstring.
		int	n	Bit index.
  return:	none
  last updated:	30/06/01
 **********************************************************************/

void ga_bit_set( byte *bstr, int n )
  {
  bstr[n/BYTEBITS] |= 1 << ( (BYTEBITS-1)-n%BYTEBITS );

  return;
  }


/**********************************************************************
  ga_bit_clear()
  synopsis:	Unsets a single bit in a bitstring.
  parameters:	byte	*bstr	Bitstring.
		int	n	Bit index.
  return:	none
  last updated:	30/06/01
 **********************************************************************/

void ga_bit_clear( byte *bstr, int n )
  {
  bstr[n/BYTEBITS] &= ~(1 << ((BYTEBITS-1)-n%BYTEBITS));

  return;
  }


/**********************************************************************
  ga_bit_invert()
  synopsis:	Toggles a single bit in a bitstring.
  parameters:	byte	*bstr	Bitstring.
		int	n	Bit index.
  return:	none
  last updated:	30/06/01
 **********************************************************************/

void ga_bit_invert( byte *bstr, int n )
  {
/*
 * FIXME: If I spent longer thinking about the logic, I am sure
 * that I could remove the use of the 'if' statement.
 */
  if ( ga_bit_get( bstr, n ) )
    {
    ga_bit_clear( bstr, n );
    }
  else
    {
    ga_bit_set( bstr, n );
    }

  return;
  }


/**********************************************************************
  ga_bit_get()
  synopsis:	Returns the state of a single bit in a bitstring.
  parameters:	byte	*bstr	Bitstring.
		int	n	Bit index.
  return:	boolean	val	The bit's state.
  last updated:	30/06/01
 **********************************************************************/

boolean ga_bit_get( byte *bstr, int n )
  {
  return (( bstr[n/BYTEBITS] >> ((BYTEBITS-1)-n%BYTEBITS) ) & 1);
  }


/**********************************************************************
  ga_bit_randomize()
  synopsis:	Randomly sets the state of a single bit in a bitstring.
  parameters:	byte	*bstr	Bitstring.
		int	n	Bit index.
  return:	none
  last updated:	30/06/01
 **********************************************************************/

void ga_bit_randomize( byte *bstr, int n )
  {
  if ( random_boolean() )
    ga_bit_set( bstr, n );
  else
    ga_bit_clear( bstr, n );

  return;
  }


/**********************************************************************
  ga_bit_copy()
  synopsis:	Copies a set of bits in a bitstring.
  parameters:	byte	*dest	Destination bitstring.
		byte	*src	Source bitstring
		int	ndest	Initial bit index of destination bits.
		int	nsrc	Initial bit index of source bits.
		int	length	Number of bits to copy.
  return:	none
  last updated:	30/06/01
 **********************************************************************/

void ga_bit_copy( byte *dest, byte *src, int ndest, int nsrc, int length )
  {
/*
 * FIXME: Should use memcpy, when appropriate.
 */ 
  int i;

  for ( i=0; i < length; ++i )
    {
    if ( ga_bit_get(dest, ndest+i) )
      ga_bit_set( src, nsrc+i );
    else
      ga_bit_clear( src, nsrc+i );
    }

  return;
  }


/**********************************************************************
  ga_bit_sizeof()
  synopsis:	Return the size required for the given number of
		bits, rounded up if needed.
  parameters:	int	length	Number of bits.
  return:	none
  last updated:	30/06/01
 **********************************************************************/

size_t ga_bit_sizeof( int length )
  {
/* Note that sizeof(byte) should always be 1. */
  return sizeof(byte) * (length+BYTEBITS-1) / BYTEBITS;
  }


/**********************************************************************
  ga_bit_clone()
  synopsis:	Copies a complete bitstring.
  parameters:	byte	*dest	Destination bitstring.
		byte	*src	Source bitstring
		int	length	Number of bits in bitstrings.
  return:	none
  last updated:	30/06/01
 **********************************************************************/

byte *ga_bit_clone( byte *dest, byte *src, int length )
  {
  if (!dest) dest=ga_bit_new( length );

  memcpy( dest, src, ga_bit_sizeof( length ) );

  return dest;
  }


unsigned int ga_bit_decode_binary_uint( byte *bstr, int n, int length )
  {
  int		i;
  unsigned int	value=0;	/* Decoded value. */

  for ( i=n; i < n+length; i++ )
    {
    value <<= 1;
    value |= ga_bit_get(bstr, i);
    }

  return value;
  }


void ga_bit_encode_binary_uint( byte *bstr, int n, int length, unsigned int value )
  {
  int i;

  /* Set bits in _reverse_ order. */
  for ( i = n+length-1; i >= n; i-- )
    {
    if ( value & 1 )
      ga_bit_set( bstr, i );
    else
      ga_bit_clear( bstr, i );

    value >>= 1;
    }

  return;
  }


int ga_bit_decode_binary_int( byte *bstr, int n, int length )
  {
  if ( ga_bit_get( bstr, n ) )
    return (int) -ga_bit_decode_binary_uint( bstr, n+1, length-1 );
  else
    return (int) ga_bit_decode_binary_uint( bstr, n+1, length-1 );
  }


void ga_bit_encode_binary_int( byte *bstr, int n, int length, int value )
  {
  if ( value < 0 )
    {
    ga_bit_set( bstr, n );
    value = -value;
    }
  else
    {
    ga_bit_clear( bstr, n );
    }

  ga_bit_encode_binary_uint( bstr, n+1, length-1, value );

  return;
  }


static void gray_to_binary( byte *gray_bstr, int n, byte *int_bstr, int length )
  {
  boolean	bit;
  int		i;

  bit = ga_bit_get( gray_bstr, n );
  if (bit)
    ga_bit_set( int_bstr, 0 );
  else
    ga_bit_clear( int_bstr, 0 );

  for ( i=1; i<length; i++ )
    {
    if (bit)
      bit = !ga_bit_get( gray_bstr, n+i );
    else
      bit = ga_bit_get( gray_bstr, n+i );

    if (bit)
      ga_bit_set( int_bstr, i );
    else
      ga_bit_clear( int_bstr, i );
    }  

  return;
  }


static void binary_to_gray( byte *gray_bstr, int n, byte *int_bstr, int length )
  {
  boolean	bit;
  int		i;

  bit = ga_bit_get( int_bstr, 0 );
  if (bit)
    ga_bit_set( gray_bstr, n );
  else
    ga_bit_clear( gray_bstr, n );

  for ( i=1; i < length; i++ )
    {
    if (bit)
      {
      bit = ga_bit_get( int_bstr, i );
      if (bit)
        ga_bit_clear( gray_bstr, n+i );
      else
        ga_bit_set( gray_bstr, n+i );
      }
    else
      {
      bit = ga_bit_get( int_bstr, i );
      if (bit)
        ga_bit_set( gray_bstr, n+i );
      else
        ga_bit_clear( gray_bstr, n+i );
      }
    }

  return;
  }


int ga_bit_decode_gray_int( byte *bstr, int n, int length )
  {
  byte	int_bstr[SIZEOF_INT];

  gray_to_binary( bstr, n, int_bstr, length );

  return ( ga_bit_decode_binary_int( int_bstr, 0, length ) );
  }


int ga_bit_decode_gray_uint( byte *bstr, int n, int length )
  {
  byte	int_bstr[SIZEOF_INT];

  gray_to_binary( bstr, n, int_bstr, length );

  return ( ga_bit_decode_binary_uint( int_bstr, 0, length ) );
  }


void ga_bit_encode_gray_uint( byte *bstr, int n, int length, int value )
  {
  byte	int_bstr[SIZEOF_INT];

  ga_bit_encode_binary_uint( int_bstr, 0, length, value );
  binary_to_gray( bstr, n, int_bstr, length );

  return;
  }


double ga_bit_decode_real( byte *bstr, int n, int mantissa, int exponent )
  {
  double	value;
  int		int_mantissa, int_exponent;

  int_mantissa = ga_bit_decode_binary_int( bstr, n, mantissa );
  int_exponent = ga_bit_decode_binary_int( bstr, n+mantissa, exponent );

  value = ((double)int_mantissa) / ((double)(1<<(mantissa-1)))
          * pow( 2.0, int_exponent );

  return value;        
  }


void ga_bit_encode_real( byte *bstr, int n, int mantissa, int exponent, double value )
  {
  int int_mantissa, int_exponent;

  int_mantissa = frexp( value, &int_exponent ) * (double)(1<<(mantissa-1));
  ga_bit_encode_binary_int( bstr, n, mantissa, int_mantissa );
  ga_bit_encode_binary_int( bstr, n+mantissa, exponent, int_exponent );

  return;
  }

