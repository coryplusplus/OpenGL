# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <ctime>

using namespace std;

# include "bmp_io.h"

//
//  Set BMP_BYTE_SWAP to true if byte swapping is needed.
//

static bool bmp_byte_swap = true;

//****************************************************************************

bool bmp_byte_swap_get ( void )

//****************************************************************************
//
//  Purpose:
// 
//    BMP_BYTE_SWAP_GET returns the internal value of BMP_BYTE_SWAP.
// 
//  Modified:
// 
//    26 February 2003
//
//  Author:
// 
//    John Burkardt
//
//  Parameters:
//
//    Output, bool BMP_BYTE_SWAP_GET, the internal value of BMP_BYTE_SWAP.
//
{
  return bmp_byte_swap;
}
//****************************************************************************

void bmp_byte_swap_set ( bool value )

//****************************************************************************
//
//  Purpose:
// 
//    BMP_BYTE_SWAP_SET sets the internal value of BMP_BYTE_SWAP.
// 
//  Modified:
// 
//    26 February 2003
//
//  Author:
// 
//    John Burkardt
//
//  Parameters:
//
//    Input, bool VALUE, the new value of BMP_BYTE_SWAP.
//
{
  bmp_byte_swap = value;

  return;
}
//****************************************************************************

bool bmp_data_read ( ifstream &file_in, unsigned long int width, long int height, 
  unsigned char *rarray, unsigned char *garray, unsigned char *barray )

//****************************************************************************
//
//  Purpose:
//  
//    BMP_DATA_READ reads the image data of the BMP file.
// 
//  Discussion:
//
//    On output, the RGB information in the file has been copied into the
//    R, G and B arrays.
//
//    Thanks to Peter Kionga-Kamau for pointing out an error in the
//    previous implementation.
//
//    The standard ">>" operator cannot be used to transfer data, because
//    it will be deceived by characters that "look like" new lines.
//
//  Modified:
// 
//    03 March 2004
//
//  Author:
// 
//    John Burkardt
//
//  References:
//
//    David Kay and John Levine,
//    Graphics File Formats,
//    Second Edition,
//    McGraw Hill, 1995.
//
//    Microsoft Corporation,
//    Microsoft Windows Programmer's Reference,
//    Volume 5; Messages, Structures, and Macros,
//    Microsoft Press, 1993.
//
//    John Miano,
//    Compressed Image File Formats,
//    Addison Wesley, 1999.
//
//  Parameters:
//
//    Input, ifstream &FILE_IN, a reference to the input file.
//
//    Input, unsigned long int WIDTH, the X dimension of the image.
//
//    Input, long int HEIGHT, the Y dimension of the image.
//
//    Input, unsigned char *RARRAY, *GARRAY, *BARRAY, pointers to the 
//    red, green and blue color arrays.
//
//    Output, bool BMP_DATA_READ, is true if an error occurred.
//
{
  char c;
  bool error = false;
  int i;
  unsigned char *indexb;
  unsigned char *indexg;
  unsigned char *indexr;
  int j;
  int numbyte;

  indexr = rarray;
  indexg = garray;
  indexb = barray;
  numbyte = 0;

  for ( j = 0; j < abs ( height ); j++ ) 
  {
    for ( i = 0; i < width; i++ )
    {

      file_in.read ( &c, 1 );

      error = file_in.eof();

      if ( error )
      {
        cout << "\n";
        cout << "BMP_DATA_READ: Fatal error!\n";
        cout << "  Failed reading B for pixel (" << i << "," << j << ").\n";
        return error;
      }

      *indexb = ( unsigned char ) c;
      numbyte = numbyte + 1;
      indexb = indexb + 1;

      file_in.read ( &c, 1 );

      error = file_in.eof();

      if ( error ) 
      {
        cout << "\n";
        cout << "BMP_DATA_READ: Fatal error!\n";
        cout << "  Failed reading G for pixel (" << i << "," << j << ").\n";
        return error;
      }

      *indexg = ( unsigned char ) c;
      numbyte = numbyte + 1;
      indexg = indexg + 1;

      file_in.read ( &c, 1 );

      error = file_in.eof();

      if ( error ) 
      {
        cout << "\n";
        cout << "BMP_DATA_READ: Fatal error!\n";
        cout << "  Failed reading R for pixel (" << i << "," << j << ").\n";
        return error;
      }

      *indexr = ( unsigned char ) c;
      numbyte = numbyte + 1;
      indexr = indexr + 1;

    }

	// Changd by Zhang, Three
	while (numbyte%4!=0) {
	    file_in.read ( &c, 1 );
	    numbyte = numbyte + 1;
	}

  }

  return false;
}
//****************************************************************************

void bmp_data_write ( ofstream &file_out, unsigned long int width, 
  long int height, unsigned char *rarray, unsigned char *garray, 
  unsigned char *barray )

//****************************************************************************
//
//  Purpose:
//  
//    BMP_DATA_WRITE writes the image data to the BMP file.
// 
//  Modified:
// 
//    27 February 2003
//
//  Author:
// 
//    John Burkardt
//
//  References:
//
//    David Kay and John Levine,
//    Graphics File Formats,
//    Second Edition,
//    McGraw Hill, 1995.
//
//    Microsoft Corporation,
//    Microsoft Windows Programmer's Reference,
//    Volume 5; Messages, Structures, and Macros,
//    Microsoft Press, 1993.
//
//    John Miano,
//    Compressed Image File Formats,
//    Addison Wesley, 1999.
//
//  Parameters:
//
//    Input, ofstream &FILE_OUT, a reference to the output file.
//
//    Input, unsigned long int WIDTH, the X dimension of the image.
//
//    Input, long int HEIGHT, the Y dimension of the image.
//
//    Input, unsigned char* RARRAY, GARRAY, BARRAY, pointers to the red, green
//    and blue color arrays.
//
{
  int i;
  unsigned char *indexb;
  unsigned char *indexg;
  unsigned char *indexr;
  int j;

  indexr = rarray;
  indexg = garray;
  indexb = barray;

  for ( j = 0; j < abs ( height ); j++ )
  {
    for ( i = 0; i < width; i++ )
    {
      file_out << *indexb;
      file_out << *indexg;
      file_out << *indexr;

      indexb = indexb + 1;
      indexg = indexg + 1;
      indexr = indexr + 1;
    }
  }

  return;
}
//****************************************************************************

void bmp_header1_print ( unsigned short int filetype, 
  unsigned long int filesize, unsigned short int reserved1, 
  unsigned short int reserved2, unsigned long int bitmapoffset )

//****************************************************************************
//
//  Purpose:
// 
//    BMP_HEADER1_PRINT prints the header information of a BMP file.
//
//  Discussion:
//
//    The header comprises 14 bytes:
//
//    2 bytes FILETYPE;        Magic number: "BM",
//    4 bytes FILESIZE;        Size of file in 32 byte integers,
//    2 bytes RESERVED1;       Always 0,
//    2 bytes RESERVED2;       Always 0,
//    4 bytes BITMAPOFFSET.    Starting position of image data, in bytes.
//
//  Modified:
// 
//    05 March 2004
// 
//  Author:
// 
//    John Burkardt
//
//  References:
//
//    David Kay and John Levine,
//    Graphics File Formats,
//    Second Edition,
//    McGraw Hill, 1995.
//
//    Microsoft Corporation,
//    Microsoft Windows Programmer's Reference,
//    Volume 5; Messages, Structures, and Macros,
//    Microsoft Press, 1993.
//
//    John Miano,
//    Compressed Image File Formats,
//    Addison Wesley, 1999.
//
//  Parameters:
//
//    Input, unsigned short int FILETYPE, the file type.
//
//    Input, unsigned long int FILESIZE, the file size.
//
//    Input, unsigned short int RESERVED1, a reserved value.
//
//    Input, unsigned short int RESERVED2, a reserved value.
//
//    Input, unsigned long int BITMAPOFFSET, the bitmap offset.
//
{
  cout << "\n";
  cout << "  Contents of BMP file header:\n";
  cout << "\n";
  cout << "    FILETYPE =     " << filetype     << "\n";
  cout << "    FILESIZE =     " << filesize     << "\n";
  cout << "    RESERVED1 =    " << reserved1    << "\n";
  cout << "    RESERVED2 =    " << reserved2    << "\n";
  cout << "    BITMAPOFFSET = " << bitmapoffset << "\n";

  return;
}
//****************************************************************************

bool bmp_header1_read ( ifstream &file_in, unsigned short int *filetype, 
  unsigned long int *filesize, unsigned short int *reserved1, 
  unsigned short int *reserved2, unsigned long int *bitmapoffset )

//****************************************************************************
//
//  Purpose:
// 
//    BMP_HEADER1_READ reads the header information of a BMP file.
//
//  Discussion:
//
//    The header comprises 14 bytes:
//
//    2 bytes FILETYPE;        Magic number: "BM",
//    4 bytes FILESIZE;        Size of file in 32 byte integers,
//    2 bytes RESERVED1;       Always 0,
//    2 bytes RESERVED2;       Always 0,
//    4 bytes BITMAPOFFSET.    Starting position of image data, in bytes.
//
//  Modified:
// 
//    05 March 2003
// 
//  Author:
// 
//    John Burkardt
//
//  References:
//
//    David Kay and John Levine,
//    Graphics File Formats,
//    Second Edition,
//    McGraw Hill, 1995.
//
//    Microsoft Corporation,
//    Microsoft Windows Programmer's Reference,
//    Volume 5; Messages, Structures, and Macros,
//    Microsoft Press, 1993.
//
//    John Miano,
//    Compressed Image File Formats,
//    Addison Wesley, 1999.
//
//  Parameters:
//
//    Input, ifstream &FILE_IN, a reference to the input file.
//
//    Output, unsigned short int *FILETYPE, the file type.
//
//    Output, unsigned long int *FILESIZE, the file size.
//
//    Output, unsigned short int *RESERVED1, a reserved value.
//
//    Output, unsigned short int *RESERVED2, a reserved value.
//
//    Output, unsigned long int *BITMAPOFFSET, the bitmap offset.
//
{
  bool error;
//
//  Read FILETYPE.
//
  error = u_short_int_read ( filetype, file_in );

  if ( error )
  {
    return error;
  }
//
//  Read FILESIZE.
//
  error = u_long_int_read ( filesize, file_in );
  if ( error ) 
  {
    return error;
  }
//
//  Read RESERVED1.
//
  error = u_short_int_read ( reserved1, file_in );
  if ( error )
  {
    return error;
  }
//
//  Read RESERVED2.
//
  error = u_short_int_read ( reserved2, file_in );
  if ( error )
  {
    return error;
  }
//
//  Read BITMAPOFFSET.
//
  error = u_long_int_read ( bitmapoffset, file_in );
  if ( error )
  {
    return error;
  }

  error = false;
  return error;
}
//****************************************************************************

void bmp_header1_write ( ofstream &file_out, unsigned short int filetype,
  unsigned long int filesize, unsigned short int reserved1, 
  unsigned short int reserved2, unsigned long int bitmapoffset )

//****************************************************************************
//
//  Purpose:
// 
//    BMP_HEADER1_WRITE writes the header information to a BMP file.
//
//  Discussion:
//
//    The header comprises 14 bytes:
//
//    2 bytes FILETYPE;        Magic number: "BM",
//    4 bytes FILESIZE;        Size of file in 32 byte integers,
//    2 bytes RESERVED1;       Always 0,
//    2 bytes RESERVED2;       Always 0,
//    4 bytes BITMAPOFFSET.    Starting position of image data, in bytes.
//
//  Modified:
// 
//    04 March 2004
// 
//  Author:
// 
//    John Burkardt
//
//  References:
//
//    David Kay and John Levine,
//    Graphics File Formats,
//    Second Edition,
//    McGraw Hill, 1995.
//
//    Microsoft Corporation,
//    Microsoft Windows Programmer's Reference,
//    Volume 5; Messages, Structures, and Macros,
//    Microsoft Press, 1993.
//
//    John Miano,
//    Compressed Image File Formats,
//    Addison Wesley, 1999.
//
//  Parameters:
//
//    Input, ofstream &FILE_OUT, a reference to the output file.
//
//    Input, unsigned short int FILETYPE, the file type.
//
//    Input, unsigned long int FILESIZE, the file size.
//
//    Input, unsigned short int RESERVED1, a reserved value.
//
//    Input, unsigned short int RESERVED2, a reserved value.
//
//    Input, unsigned long int BITMAPOFFSET, the bitmap offset.
//
{
  u_short_int_write ( filetype, file_out );
  u_long_int_write ( filesize, file_out );
  u_short_int_write ( reserved1, file_out );
  u_short_int_write ( reserved2, file_out );
  u_long_int_write ( bitmapoffset, file_out );

  return;
}
//****************************************************************************

void bmp_header2_print ( unsigned long int size, unsigned long int width, 
  long int height, 
  unsigned short int planes, unsigned short int bitsperpixel, 
  unsigned long int compression, unsigned long int sizeofbitmap,
  unsigned long int horzresolution, unsigned long int vertresolution,
  unsigned long int colorsused,  unsigned long int colorsimportant )

//****************************************************************************
//
//  Purpose:
// 
//    BMP_HEADER2_PRINT prints the bitmap header information of a BMP file.
//
//  Discussion:
//
//    The bitmap header is 40 bytes long:
//
//    4 bytes SIZE;                Size of this header ( = 40 bytes).
//    4 bytes WIDTH;               Image width, in pixels.   
//    4 bytes HEIGHT;              Image height, in pixels.  
//                                 (Pos/Neg, origin at bottom, top)
//    2 bytes PLANES;              Number of color planes (always 1).
//    2 bytes BITSPERPIXEL;        1 to 24.  1, 4, 8, 16, 24 or 32.
//    4 bytes COMPRESSION;         0, uncompressed; 1, 8 bit RLE; 
//                                 2, 4 bit RLE; 3, bitfields.
//    4 bytes SIZEOFBITMAP;        Size of bitmap in bytes. (0 if uncompressed).
//    4 bytes HORZRESOLUTION;      Pixels per meter. (Can be zero)
//    4 bytes VERTRESOLUTION;      Pixels per meter. (Can be zero)
//    4 bytes COLORSUSED;          Number of colors in palette.  (Can be zero).
//    4 bytes COLORSIMPORTANT.     Minimum number of important colors. (Can be zero).
//
//  Modified:
// 
//    06 March 2004
// 
//  Author:
// 
//    John Burkardt
//
//  References:
//
//    David Kay and John Levine,
//    Graphics File Formats,
//    Second Edition,
//    McGraw Hill, 1995.
//
//    Microsoft Corporation,
//    Microsoft Windows Programmer's Reference,
//    Volume 5; Messages, Structures, and Macros,
//    Microsoft Press, 1993.
//
//    John Miano,
//    Compressed Image File Formats,
//    Addison Wesley, 1999.
//
//  Parameters:
//
//    Input, unsigned short int SIZE, the size of this header in bytes.
//
//    Input, unsigned long int WIDTH, the X dimension of the image.
//
//    Input, long int HEIGHT, the Y dimension of the image.
//
//    Input, unsigned short int PLANES, the number of color planes.
//
//    Input, unsigned short int BITSPERPIXEL, color bits per pixel.
//
//    Input, unsigned long int COMPRESSION, the compression option.
//
//    Input, unsigned long int SIZEOFBITMAP, the size of the bitmap.
//
//    Input, unsigned long int HORZRESOLUTION, the horizontal resolution.
//
//    Input, unsigned long int VERTRESOLUTION, the vertical resolution.
//
//    Input, unsigned long int COLORSUSED, the number of colors in the palette.
//
//    Input, unsigned long int COLORSIMPORTANT, the minimum number of colors.
//
{
  cout << "\n";
  cout << "  Contents of BMP file bitmap header:\n";
  cout << "\n";
  cout << "    SIZE =            " << size            << "\n";
  cout << "    WIDTH =           " << width           << "\n";
  cout << "    HEIGHT =          " << height          << "\n";
  cout << "    PLANES =          " << planes          << "\n";
  cout << "    BITSPERPIXEL =    " << bitsperpixel    << "\n";
  cout << "    COMPRESSION =     " << compression     << "\n";
  cout << "    SIZEOFBITMAP =    " << sizeofbitmap    << "\n";
  cout << "    HORZRESOLUTION =  " << horzresolution  << "\n";
  cout << "    VERTRESOLUTION =  " << vertresolution  << "\n";
  cout << "    COLORSUSED =      " << colorsused      << "\n";
  cout << "    COLORSIMPORTANT = " << colorsimportant << "\n";

  return;
} 
//****************************************************************************

bool bmp_header2_read ( ifstream &file_in, unsigned long int *size,
  unsigned long int *width, long int *height, 
  unsigned short int *planes, unsigned short int *bitsperpixel,
  unsigned long int *compression, unsigned long int *sizeofbitmap,
  unsigned long int *horzresolution, unsigned long int *vertresolution,
  unsigned long int *colorsused, unsigned long int *colorsimportant )

//****************************************************************************
//
//  Purpose:
// 
//    BMP_HEADER2_READ reads the bitmap header information of a BMP file.
//
//  Discussion:
//
//    The bitmap header is 40 bytes long:
//
//    4 bytes SIZE;                Size of this header, in bytes.
//    4 bytes WIDTH;               Image width, in pixels.   
//    4 bytes HEIGHT;              Image height, in pixels.  
//                                 (Pos/Neg, origin at bottom, top)
//    2 bytes PLANES;              Number of color planes (always 1).
//    2 bytes BITSPERPIXEL;        1 to 24.  1, 4, 8, 16, 24 or 32.
//    4 bytes COMPRESSION;         0, uncompressed; 1, 8 bit RLE; 
//                                 2, 4 bit RLE; 3, bitfields.
//    4 bytes SIZEOFBITMAP;        Size of bitmap in bytes. (0 if uncompressed).
//    4 bytes HORZRESOLUTION;      Pixels per meter. (Can be zero)
//    4 bytes VERTRESOLUTION;      Pixels per meter. (Can be zero)
//    4 bytes COLORSUSED;          Number of colors in palette.  (Can be zero).
//    4 bytes COLORSIMPORTANT.     Minimum number of important colors. (Can be zero).
//
//  Modified:
// 
//    03 March 2004
// 
//  Author:
// 
//    John Burkardt
//
//  References:
//
//    David Kay and John Levine,
//    Graphics File Formats,
//    Second Edition,
//    McGraw Hill, 1995.
//
//    Microsoft Corporation,
//    Microsoft Windows Programmer's Reference,
//    Volume 5; Messages, Structures, and Macros,
//    Microsoft Press, 1993.
//
//    John Miano,
//    Compressed Image File Formats,
//    Addison Wesley, 1999.
//
//  Parameters:
//
//    Input, ifstream &FILE_IN, a reference to the input file.
//
//    Output, unsigned long int *SIZE, the size of this header in bytes.
//
//    Output, unsigned long int *WIDTH, the X dimension of the image.
//
//    Output, long int *HEIGHT, the Y dimension of the image.
//
//    Output, unsigned short int *PLANES, the number of color planes.
//
//    Output, unsigned short int *BITSPERPIXEL, color bits per pixel.
//
//    Output, unsigned long int *COMPRESSION, the compression option.
//
//    Output, unsigned long int *SIZEOFBITMAP, the size of the bitmap.
//
//    Output, unsigned long int *HORZRESOLUTION, the horizontal resolution.
//
//    Output, unsigned long int *VERTRESOLUTION, the vertical resolution.
//
//    Output, unsigned long int *COLORSUSED, the number of colors in the palette.
//
//    Output, unsigned long int *COLORSIMPORTANT, the minimum number of colors.
//
//    Output, bool BMP_HEADER2_READ, is true if an error occurred.
//
{
  unsigned char c1;
  unsigned char c2;
  bool error;
//
//  Read SIZE, the size of the header in bytes.
//
  error = u_long_int_read ( size, file_in );
  if ( error )
  {
    return error;
  }
//
//  Read WIDTH, the image width in pixels.
//
  error = u_long_int_read ( width, file_in );
  if ( error )
  {
    return error;
  }
//
//  Read HEIGHT, the image height in pixels.
//
  error = long_int_read ( height, file_in );
  if ( error )
  {
    return error;
  }
//
//  Read PLANES, the number of color planes.
//
  error = u_short_int_read ( planes, file_in ); 
  if ( error )
  {
    return error;
  }
//
//  Read BITSPERPIXEL.
//
  error = u_short_int_read ( bitsperpixel, file_in );
  if ( error )
  {
    return error;
  }
//
//  Read COMPRESSION.
//
  error = u_long_int_read ( compression, file_in );
  if ( error )
  {
    return error;
  }
//
//  Read SIZEOFBITMAP.
//
  error = u_long_int_read ( sizeofbitmap, file_in );
  if ( error )
  {
    return error;
  }
//
//  Read HORZRESOLUTION.
//
  error = u_long_int_read ( horzresolution, file_in );
  if ( error )
  {
    return error;
  }
//
//  Read VERTRESOLUTION.
//
  error = u_long_int_read ( vertresolution, file_in );
  if ( error )
  {
    return error;
  }
//
//  Read COLORSUSED.
//
  error = u_long_int_read ( colorsused, file_in );
  if ( error )
  {
    return error;
  }
//
//  Read COLORSIMPORTANT.
//
  error = u_long_int_read ( colorsimportant, file_in );
  if ( error )
  {
    return error;
  }

  error = false;
  return error;
}
//****************************************************************************

void bmp_header2_write ( ofstream &file_out, unsigned long int size,
  unsigned long int width, long int height, 
  unsigned short int planes, unsigned short int bitsperpixel,
  unsigned long int compression, unsigned long int sizeofbitmap,
  unsigned long int horzresolution, unsigned long int vertresolution,
  unsigned long int colorsused, unsigned long int colorsimportant )

//****************************************************************************
//
//  Purpose:
// 
//    BMP_HEADER2_WRITE writes the bitmap header information to a BMP file.
//
//  Discussion:
//
//    Thanks to Mark Cave-Ayland, mca198@ecs.soton.ac.uk, for pointing out an 
//    error which caused the code to write one too many long ints, 19 May 2001.
//
//    The bitmap header is 40 bytes long:
//
//    4 bytes SIZE;                Size of this header, in bytes.
//    4 bytes WIDTH;               Image width, in pixels.   
//    4 bytes HEIGHT;              Image height, in pixels.  
//                                 (Pos/Neg, origin at bottom, top)
//    2 bytes PLANES;              Number of color planes (always 1).
//    2 bytes BITSPERPIXEL;        1 to 24.  1, 4, 8, 16, 24 or 32.
//    4 bytes COMPRESSION;         0, uncompressed; 1, 8 bit RLE; 
//                                 2, 4 bit RLE; 3, bitfields.
//    4 bytes SIZEOFBITMAP;        Size of bitmap in bytes. (0 if uncompressed).
//    4 bytes HORZRESOLUTION;      Pixels per meter. (Can be zero)
//    4 bytes VERTRESOLUTION;      Pixels per meter. (Can be zero)
//    4 bytes COLORSUSED;          Number of colors in palette.  (Can be zero).
//    4 bytes COLORSIMPORTANT.     Minimum number of important colors. (Can be zero).
//
//  Modified:
// 
//    03 March 2004
// 
//  Author:
// 
//    John Burkardt
//
//  References:
//
//    David Kay and John Levine,
//    Graphics File Formats,
//    Second Edition,
//    McGraw Hill, 1995.
//
//    Microsoft Corporation,
//    Microsoft Windows Programmer's Reference,
//    Volume 5; Messages, Structures, and Macros,
//    Microsoft Press, 1993.
//
//    John Miano,
//    Compressed Image File Formats,
//    Addison Wesley, 1999.
//
//  Parameters:
//
//    Input, ofstream &FILE_OUT, a reference to the output file.
//
//    Input, unsigned long int SIZE, the size of this header in bytes.
//
//    Input, unsigned long int WIDTH, the X dimensions of the image.
//
//    Input, long int HEIGHT, the Y dimensions of the image.
//
//    Input, unsigned short int PLANES, the number of color planes.
//
//    Input, unsigned short int BITSPERPIXEL, color bits per pixel.
//
//    Input, unsigned long int COMPRESSION, the compression option.
//
//    Input, unsigned long int SIZEOFBITMAP, the size of the bitmap.
//
//    Input, unsigned long int HORZRESOLUTION, the horizontal resolution.
//
//    Input, unsigned long int VERTRESOLUTION, the vertical resolution.
//
//    Input, unsigned long int COLORSUSED, the number of colors in the palette.
//
//    Input, unsigned long int COLORSIMPORTANT, the minimum number of colors.
//
{
  u_long_int_write ( size, file_out );
  u_long_int_write ( width, file_out );
  long_int_write ( height, file_out );
  u_short_int_write ( planes, file_out ); 
  u_short_int_write ( bitsperpixel, file_out );
  u_long_int_write ( compression, file_out );
  u_long_int_write ( sizeofbitmap, file_out );
  u_long_int_write ( horzresolution, file_out );
  u_long_int_write ( vertresolution, file_out );
  u_long_int_write ( colorsused, file_out );
  u_long_int_write ( colorsimportant, file_out );

  return;
}
//****************************************************************************

void bmp_palette_print ( unsigned long int colorsused, 
  unsigned char *rparray, unsigned char *gparray, unsigned char *bparray,
  unsigned char *aparray )

//****************************************************************************
//
//  Purpose:
//  
//    BMP_PALETTE_PRINT prints the palette data in a BMP file.
// 
//  Modified:
// 
//    05 March 2004
//
//  Author:
// 
//    John Burkardt
//
//  References:
//
//    David Kay and John Levine,
//    Graphics File Formats,
//    Second Edition,
//    McGraw Hill, 1995.
//
//    Microsoft Corporation,
//    Microsoft Windows Programmer's Reference,
//    Volume 5; Messages, Structures, and Macros,
//    Microsoft Press, 1993.
//
//    John Miano,
//    Compressed Image File Formats,
//    Addison Wesley, 1999.
//
//  Parameters:
//
//    Input, unsigned long int COLORSUSED, the number of colors in the palette.
//
//    Input, unsigned char *RPARRAY, *GPARRAY, *BPARRAY, *APARRAY, pointers to the 
//    red, green and blue palette arrays.
//
{
  int i;
  unsigned char *indexa;
  unsigned char *indexb;
  unsigned char *indexg;
  unsigned char *indexr;

  cout << "\n";
  cout << "  Palette information from BMP file:\n";
  cout << "\n";

  if ( colorsused < 1 )
  {
    cout << "    There are NO colors defined for the palette.\n";
    return;
  }

  indexr = rparray;
  indexg = gparray;
  indexb = bparray;
  indexa = aparray;

  cout << "\n";
  cout << " Color    Blue   Green     Red   Trans\n";
  cout << "\n";

  for ( i = 0; i < colorsused; i++ )
  {
    cout << setw(6) << i       << "  "
         << setw(6) << *indexb << "  "
         << setw(6) << *indexg << "  "
         << setw(6) << *indexr << "  "
         << setw(6) << *indexa << "\n";

    indexb = indexb + 1;
    indexg = indexg + 1;
    indexr = indexr + 1;
    indexa = indexa + 1;

  }

  return;
}
//****************************************************************************

bool bmp_palette_read ( ifstream &file_in, unsigned long int colorsused,
  unsigned char *rparray, unsigned char *gparray, unsigned char *bparray, 
  unsigned char *aparray )

//****************************************************************************
//
//  Purpose:
// 
//    BMP_PALETTE_READ reads the palette information of a BMP file.
//
//  Discussion:
// 
//    There are COLORSUSED colors listed.  For each color, the values of
//    (B,G,R,A) are listed, where A is a quantity reserved for future use.
//
//  Modified:
// 
//    05 March 2003
// 
//  Author:
// 
//    John Burkardt
//
//  References:
//
//    David Kay and John Levine,
//    Graphics File Formats,
//    Second Edition,
//    McGraw Hill, 1995.
//
//    Microsoft Corporation,
//    Microsoft Windows Programmer's Reference,
//    Volume 5; Messages, Structures, and Macros,
//    Microsoft Press, 1993.
//
//    John Miano,
//    Compressed Image File Formats,
//    Addison Wesley, 1999.
//
//  Parameters:
//
//    Input, ifstream &FILE_IN, a reference to the input file.
//
//    Input, unsigned long int COLORSUSED, the number of colors in the palette.
//
//    Input, unsigned char *RPARRAY, *GPARRAY, *BPARRAY, *APARRAY pointers to the 
//    red, green, blue and transparency palette arrays.
//
//    Output, bool BMP_PALETTE_READ, is true if an error occurred.
//
{
  char c;
  bool error;
  int i;
  unsigned char *indexa;
  unsigned char *indexb;
  unsigned char *indexg;
  unsigned char *indexr;

  indexr = rparray;
  indexg = gparray;
  indexb = bparray;
  indexa = aparray;

  for ( i = 0; i < colorsused; i++ )
  {

    file_in.read ( &c, 1 );

    error = file_in.eof();

    if ( error )
    {
      cout << "\n";
      cout << "BMP_PALETTE_READ: Fatal error!\n";
      cout << "  Failed reading B for palette color " << i << ".\n";
      return error;
    }

    *indexb = ( unsigned char ) c;
    indexb = indexb + 1;

    file_in.read ( &c, 1 );

    error = file_in.eof();

    if ( error )
    {
      cout << "\n";
      cout << "BMP_PALETTE_READ: Fatal error!\n";
      cout << "  Failed reading G for palette color " << i << ".\n";
      return error;
    }

    *indexg = ( unsigned char ) c;
    indexg = indexg + 1;

    file_in.read ( &c, 1 );

    error = file_in.eof();

    if ( error )
    {
      cout << "\n";
      cout << "BMP_PALETTE_READ: Fatal error!\n";
      cout << "  Failed reading R for palette color " << i << ".\n";
      return error;
    }

    *indexr = ( unsigned char ) c;
    indexr = indexr + 1;

    file_in.read ( &c, 1 );

    error = file_in.eof();

    if ( error )
    {
      cout << "\n";
      cout << "BMP_PALETTE_READ: Fatal error!\n";
      cout << "  Failed reading A for palette color " << i << ".\n";
      return error;
    }

    *indexa = ( unsigned char ) c;
    indexa = indexa + 1;
  }

  error = false;
  return error;
}
//****************************************************************************

void bmp_palette_write ( ofstream &file_out, unsigned long int colorsused, 
  unsigned char *rparray, unsigned char *gparray, unsigned char *bparray,
  unsigned char *aparray )

//****************************************************************************
//
//  Purpose:
//  
//    BMP_PALETTE_WRITE writes the palette data to the BMP file.
// 
//  Modified:
// 
//    04 March 2004
//
//  Author:
// 
//    John Burkardt
//
//  References:
//
//    David Kay and John Levine,
//    Graphics File Formats,
//    Second Edition,
//    McGraw Hill, 1995.
//
//    Microsoft Corporation,
//    Microsoft Windows Programmer's Reference,
//    Volume 5; Messages, Structures, and Macros,
//    Microsoft Press, 1993.
//
//    John Miano,
//    Compressed Image File Formats,
//    Addison Wesley, 1999.
//
//  Parameters:
//
//    Input, ofstream &FILE_OUT, a reference to the output file.
//
//    Input, unsigned long int COLORSUSED, the number of colors in the palette.
//
//    Input, unsigned char *RPARRAY, *GPARRAY, *BPARRAY, *APARRAY, pointers to the 
//    red, green, blue and transparency palette arrays.
//
{
  int i;
  unsigned char *indexa;
  unsigned char *indexb;
  unsigned char *indexg;
  unsigned char *indexr;

  indexr = rparray;
  indexg = gparray;
  indexb = bparray;
  indexa = aparray;

  for ( i = 0; i < colorsused; i++ )
  {
    file_out << *indexb;
    file_out << *indexg;
    file_out << *indexr;
    file_out << *indexa;

    indexb = indexb + 1;
    indexg = indexg + 1;
    indexr = indexr + 1;
    indexa = indexa + 1;
  }

  return;
}
//****************************************************************************

bool bmp_print_test ( char *file_in_name )

//****************************************************************************
//
//  Purpose:
//
//    BMP_PRINT_TEST tests the BMP print routines.
//
//  Modified:
//
//    05 March 2003
//
//  Author:
//
//    John Burkardt
//
//  References:
//
//    David Kay and John Levine,
//    Graphics File Formats,
//    Second Edition,
//    McGraw Hill, 1995.
//
//    Microsoft Corporation,
//    Microsoft Windows Programmer's Reference,
//    Volume 5; Messages, Structures, and Macros,
//    Microsoft Press, 1993.
//
//    John Miano,
//    Compressed Image File Formats,
//    Addison Wesley, 1999.
//
//  Parameters:
//
//    Input, char* FILE_IN_NAME, the name of the input file.
//
//    Output, bool BMP_PRINT_TEST, is true if an error occurred.
//
{
# define VERBOSE false

  unsigned char *aparray;
  unsigned char *barray;
  unsigned char *bparray;
  unsigned long int bitmapoffset;
  unsigned short int bitsperpixel;
  unsigned long int colorsimportant;
  unsigned long int colorsused;
  unsigned long int compression;
  bool error;
  ifstream file_in;
  unsigned long int filesize;
  unsigned short int filetype;
  unsigned char *garray;
  unsigned char *gparray;
  long int height;
  unsigned long int horzresolution;
  unsigned short int magic;
  int numbytes;
  unsigned short int planes;
  unsigned char *rarray;
  unsigned char *rparray;
  unsigned short int reserved1;
  unsigned short int reserved2;
  unsigned long int size;
  unsigned long int sizeofbitmap;
  unsigned long int vertresolution;
  unsigned long int width;
//
//  Open the input file.
//
  file_in.open ( file_in_name );

  if ( !file_in ) 
  {
    error = true;
    cout << "\n";
    cout << "BMP_PRINT_TEST - Fatal error!\n";
    cout << "  Could not open the input file.\n";
    return error;
  }
  cout << "\n";
  cout << "BMP_PRINT_TEST:\n";
  cout << "  Contents of BMP file \"" << file_in_name << "\"\n";
//
//  Read header 1.
//
  error = bmp_header1_read ( file_in, &filetype, &filesize, &reserved1, 
    &reserved2, &bitmapoffset );

  if ( error ) 
  {
    cout << "\n";
    cout << "BMP_PRINT_TEST: Fatal error!\n";
    cout << "  BMP_HEADER1_READ failed.\n";
    return error;
  }

  bmp_header1_print ( filetype, filesize, reserved1, reserved2, bitmapoffset );
//
//  Read header 2.
//
  error = bmp_header2_read ( file_in, &size, &width, &height, &planes,
    &bitsperpixel, &compression, &sizeofbitmap, &horzresolution,
    &vertresolution, &colorsused, &colorsimportant );

  if ( error ) 
  {
    cout << "\n";
    cout << "BMP_PRINT_TEST: Fatal error!\n";
    cout << "  BMP_HEADER2_READ failed.\n";
    return error;
  }

  bmp_header2_print ( size, width, height, planes, bitsperpixel,
    compression, sizeofbitmap, horzresolution, vertresolution, 
    colorsused, colorsimportant );
//
//  Read the palette.
//
//if ( 0 < colorsused )
//{
    rparray = new unsigned char[colorsused];
    gparray = new unsigned char[colorsused];
    bparray = new unsigned char[colorsused];
    aparray = new unsigned char[colorsused];

    error = bmp_palette_read ( file_in, colorsused, rparray, gparray,
      bparray, aparray );

    if ( error ) 
    {
      cout << "\n";
      cout << "BMP_PRINT_TEST: Fatal error!\n";
      cout << "  BMP_PALETTE_READ failed.\n";
      return error;
    }

    bmp_palette_print ( colorsused, rparray, gparray, bparray, aparray );

    delete [] rparray;
    delete [] gparray;
    delete [] bparray;
    delete [] aparray;
//}
//
//  Allocate storage.
//
  numbytes = width * abs ( height ) * sizeof ( unsigned char );

  rarray = new unsigned char[numbytes];
  garray = new unsigned char[numbytes];
  barray = new unsigned char[numbytes];
//
//  Read the data.
//
  error = bmp_data_read ( file_in, width, height, rarray, garray, 
    barray );

  if ( error ) 
  {
    cout << "\n";
    cout << "BMP_PRINT_TEST: Fatal error!\n";
    cout << "  BMP_DATA_READ failed.\n";
    return error;
  }

  delete [] rarray;
  delete [] garray;
  delete [] barray;
//
//  Close the file.
//
  file_in.close ( );

  return error;
# undef VERBOSE
}
//****************************************************************************

bool bmp_read ( char *file_in_name, unsigned long int *width, long int *height, 
  unsigned char **rarray, unsigned char **garray, unsigned char **barray )

//****************************************************************************
//
//  Purpose:
// 
//    BMP_READ reads the header and data of a BMP file.
// 
//  Modified:
// 
//    14 November 2004
//
//  Author:
// 
//    John Burkardt
//
//  References:
//
//    David Kay and John Levine,
//    Graphics File Formats,
//    Second Edition,
//    McGraw Hill, 1995.
//
//    Microsoft Corporation,
//    Microsoft Windows Programmer's Reference,
//    Volume 5; Messages, Structures, and Macros,
//    Microsoft Press, 1993.
//
//    John Miano,
//    Compressed Image File Formats,
//    Addison Wesley, 1999.
//
//  Parameters:
//
//    Input, char *FILE_IN_NAME, the name of the input file.
//
//    Output, unsigned long int *WIDTH, the X dimension of the image.
//
//    Output, long int *HEIGHT, the Y dimension of the image.
//
//    Output, unsigned char **RARRAY, **GARRAY, **BARRAY, pointers to the red, green
//    and blue color arrays.
//
//    Output, bool BMP_READ, is true if an error occurred.
//
{
  unsigned char *aparray;
  unsigned long int bitmapoffset;
  unsigned short int bitsperpixel;
  unsigned char *bparray;
  unsigned long int colorsimportant;
  unsigned long int colorsused;
  unsigned long int compression;
  bool error;
  ifstream file_in;
  unsigned long int filesize;
  unsigned short int filetype;
  unsigned char *gparray;
  unsigned long int horzresolution;
  unsigned short int magic;
  int numbytes;
  unsigned short int planes;
  unsigned short int reserved1;
  unsigned short int reserved2;
  unsigned char *rparray;
  unsigned long int size;
  unsigned long int sizeofbitmap;
  unsigned long int vertresolution;
//
//  Open the input file.
//
  // Changed by Zhang, One
  // file_in.open ( file_in_name ); 
  file_in.open ( file_in_name, ios::in|ios::binary);

  if ( !file_in ) 
  {
    error = true;
    cout << "\n";
    cout << "BMP_READ - Fatal error!\n";
    cout << "  Could not open the input file.\n";
    return error;
  }
//
//  Read header 1.
//
  error = bmp_header1_read ( file_in, &filetype, &filesize, &reserved1, 
    &reserved2, &bitmapoffset );

  if ( error ) 
  {
    cout << "\n";
    cout << "BMP_READ: Fatal error!\n";
    cout << "  BMP_HEADER1_READ failed.\n";
    return error;
  }
//
//  Make sure the filetype is 'BM'.
//

  // Changd by Zhang, Two
  if (bmp_byte_swap)
	  magic = 'M' * 256 + 'B';
  else
	  magic = 'B' * 256 + 'M';

  if ( filetype != magic )
  {
    cout << "\n";
    cout << "BMP_READ: Fatal error!\n";
    cout << "  The file's internal magic number is not \"BM\".\n";
    cout << "  with the numeric value " << magic << "\n";
    cout << "\n";
    cout << "  Instead, it is \"" 
         << ( char ) ( filetype / 256 ) 
         << ( char ) ( filetype % 256 )
         << "\".\n";
    cout << "  with the numeric value " << filetype << "\n";
    cout << "\n";
    cout << "  (Perhaps you need to reverse the byte swapping option!)\n";
    return 1;
  }

//
//  Read header 2.
//
  error = bmp_header2_read ( file_in, &size, width, height, &planes,
    &bitsperpixel, &compression, &sizeofbitmap, &horzresolution,
    &vertresolution, &colorsused, &colorsimportant );

  if ( error ) 
  {
    cout << "\n";
    cout << "BMP_READ: Fatal error!\n";
    cout << "  BMP_HEADER2_READ failed.\n";
    return error;
  }
//
//  Read the palette.
//
  if ( 0 < colorsused )
  {
    rparray = new unsigned char[colorsused];
    gparray = new unsigned char[colorsused];
    bparray = new unsigned char[colorsused];
    aparray = new unsigned char[colorsused];

    error = bmp_palette_read ( file_in, colorsused, rparray, gparray,
      bparray, aparray );

    if ( error ) 
    {
      cout << "\n";
      cout << "BMP_READ: Fatal error!\n";
      cout << "  BMP_PALETTE_READ failed.\n";
      return error;
    }
    delete [] rparray;
    delete [] gparray;
    delete [] bparray;
    delete [] aparray;
  }
//
//  Allocate storage.
//
  numbytes = ( *width ) * ( abs ( *height ) ) * sizeof ( unsigned char );

  *rarray = new unsigned char[numbytes];
  *garray = new unsigned char[numbytes];
  *barray = new unsigned char[numbytes];
//
//  Read the data.
//
  error = bmp_data_read ( file_in, *width, *height, *rarray, *garray, 
    *barray );

  if ( error ) 
  {
    cout << "\n";
    cout << "BMP_READ: Fatal error!\n";
    cout << "  BMP_DATA_READ failed.\n";
    return error;
  }
//
//  Close the file.
//
  file_in.close ( );

  error = false;
  return error;
}
//****************************************************************************

bool bmp_read_test ( char *file_in_name )

//****************************************************************************
//
//  Purpose:
//
//    BMP_READ_TEST tests the BMP read routines.
//
//  Modified:
//
//    05 March 2003
//
//  Author:
//
//    John Burkardt
//
//  References:
//
//    David Kay and John Levine,
//    Graphics File Formats,
//    Second Edition,
//    McGraw Hill, 1995.
//
//    Microsoft Corporation,
//    Microsoft Windows Programmer's Reference,
//    Volume 5; Messages, Structures, and Macros,
//    Microsoft Press, 1993.
//
//    John Miano,
//    Compressed Image File Formats,
//    Addison Wesley, 1999.
//
//  Parameters:
//
//    Input, char* FILE_IN_NAME, the name of the input file.
//
//    Output, bool BMP_READ_TEST, is true if an error occurred.
//
{
# define VERBOSE false

  unsigned char *barray;
  bool error;
  unsigned char *garray;
  long int height;
  unsigned char *rarray;
  unsigned long int width;

  rarray = NULL;
  garray = NULL;
  barray = NULL;
//
//  Read the data from file.
//
  error = bmp_read ( file_in_name, &width, &height, &rarray, &garray, 
    &barray );
//
//  Free the memory.
//
  delete [] rarray;
  delete [] garray;
  delete [] barray;

  if ( VERBOSE )
  {
    if ( error )
    {
      cout << "\n";
      cout << "BMP_READ_TEST - Fatal error!\n";
      cout << "  The test failed.\n";
    }
    else
    {
      cout << "\n";
      cout << "BMP_READ_TEST:\n";
      cout << "  WIDTH =  " << width  << ".\n";
      cout << "  HEIGHT = " << height << ".\n";
      cout << "\n";
      cout << "BMP_READ_TEST:\n";
      cout << "  The test was successful.\n";
    }
  }

  return error;
# undef VERBOSE
}
//****************************************************************************

bool bmp_write ( char *file_out_name, unsigned long int width, long int height, 
  unsigned char *rarray, unsigned char *garray, unsigned char *barray )

//****************************************************************************
//
//  Purpose:
// 
//    BMP_WRITE writes the header and data for a BMP file.
//
//  Discussion
//
//    Thanks to Keefe Roedersheimer for pointing out that I was creating
//    a filetype of 'MB' instead of 'BM'.
//
//  Modified:
// 
//    22 March 2004
//
//  Author:
// 
//    John Burkardt
//
//  References:
//
//    David Kay and John Levine,
//    Graphics File Formats,
//    Second Edition,
//    McGraw Hill, 1995.
//
//    Microsoft Corporation,
//    Microsoft Windows Programmer's Reference,
//    Volume 5; Messages, Structures, and Macros,
//    Microsoft Press, 1993.
//
//    John Miano,
//    Compressed Image File Formats,
//    Addison Wesley, 1999.
//
//  Parameters:
//
//    Input, char *FILE_OUT_NAME, the name of the output file.
//
//    Input, unsigned long int WIDTH, the X dimension of the image.
//
//    Input, long int HEIGHT, the Y dimension of the image.
//
//    Input, unsigned char *RARRAY, *GARRAY, *BARRAY, pointers to the red, green
//    and blue color arrays.
//
//    Output, bool BMP_WRITE, is true if an error occurred.
//
{
  unsigned char *aparray = NULL;
  unsigned long int bitmapoffset;
  unsigned short int bitsperpixel;
  unsigned char *bparray = NULL;
  unsigned long int colorsimportant;
  unsigned long int colorsused;
  unsigned long int compression;
  bool error;
  ofstream file_out;
  unsigned long int filesize;
  unsigned short int filetype;
  unsigned char *gparray = NULL;
  unsigned long int horzresolution;
  unsigned short int planes;
  unsigned short int reserved1 = 0;
  unsigned short int reserved2 = 0;
  unsigned char *rparray = NULL;
  unsigned long int size = 40;
  unsigned long int sizeofbitmap;
  unsigned long int vertresolution;
//
//  Open the output file.
//
  file_out.open ( file_out_name );

  error = !file_out;

  if ( error )
  {
    cout << "\n";
    cout << "BMP_WRITE - Fatal error!\n";
    cout << "  Could not open the output file.\n";
    return error;
  }
//
//  Write header 1.
//
  filetype = 'M' * 256 + 'B';
  filesize = 54 + 3 * width * abs ( height );
  bitmapoffset = 54;

  bmp_header1_write ( file_out, filetype, filesize, reserved1, 
    reserved2, bitmapoffset );
//
//  Write header 2.
//
  planes = 1;
  bitsperpixel = 24;
  compression = 0;
  sizeofbitmap = 0;
  horzresolution = 0;
  vertresolution = 0;
  colorsused = 0;
  colorsimportant = 0;

  bmp_header2_write ( file_out, size, width, height, planes, bitsperpixel, 
    compression, sizeofbitmap, horzresolution, vertresolution,
    colorsused, colorsimportant );
//
//  Write the palette.
//
  bmp_palette_write ( file_out, colorsused, rparray, gparray, bparray, 
    aparray );
//
//  Write the data.
//
  bmp_data_write ( file_out, width, height, rarray, garray, barray );
//
//  Close the file.
//
  file_out.close ( );

  error = false;
  return error;
}
//****************************************************************************

bool bmp_write_test ( char *file_out_name )

//****************************************************************************
//
//  Purpose:
//
//    BMP_WRITE_TEST tests the BMP write routines.
//
//  Modified:
//
//    05 March 2003
//
//  Author:
//
//    John Burkardt
//
//  References:
//
//    David Kay and John Levine,
//    Graphics File Formats,
//    Second Edition,
//    McGraw Hill, 1995.
//
//    Microsoft Corporation,
//    Microsoft Windows Programmer's Reference,
//    Volume 5; Messages, Structures, and Macros,
//    Microsoft Press, 1993.
//
//    John Miano,
//    Compressed Image File Formats,
//    Addison Wesley, 1999.
//
//  Parameters:
//
//    Input, char* FILE_OUT_NAME, the name of the output file.
//
//    Output, bool BMP_WRITE_TEST, is true if an error occurred.
//
{
# define VERBOSE false

  unsigned char *barray;
  bool error;
  unsigned char *garray;
  long int height;
  int i;
  unsigned char *indexb;
  unsigned char *indexg;
  unsigned char *indexr;
  int j;
  int j2;
  int numbytes;
  unsigned char *rarray;
  int result;
  unsigned long int width;

  width = 200;
  height = 200;
//
//  Allocate the memory.
//
  rarray = NULL;
  garray = NULL;
  barray = NULL;
  numbytes = width * abs ( height ) * sizeof ( unsigned char );  

  rarray = new unsigned char[numbytes];
  garray = new unsigned char[numbytes];
  barray = new unsigned char[numbytes];
//
//  Set the data.
//  Note that BMP files go from "bottom" up, so we'll reverse the
//  sense of "J" here to get what we want.
//
  indexr = rarray;
  indexg = garray;
  indexb = barray;

  for ( j2 = 0; j2 < abs ( height ); j2++ )
  {
    j = abs ( height ) - j2;
    for ( i = 0; i < width; i++ )
    {
      if ( i <= j )
      {
        *indexr = 255;
        *indexg = 0;
        *indexb = 0;
      }
      else if ( ( width - 1 ) * j + ( abs ( height ) - 1 ) * i <= 
        ( width - 1 ) * ( abs ( height ) - 1 ) )
      {
        *indexr = 0;
        *indexg = 255;
        *indexb = 0;
      }
      else
      {
        *indexr = 0;
        *indexg = 0;
        *indexb = 255;
      }
      indexr = indexr + 1;
      indexg = indexg + 1;
      indexb = indexb + 1;
    }
  }
//
//  Write the data to a file.
//
  error = bmp_write ( file_out_name, width, height, rarray, garray, barray );

  if ( error )
  {
    cout << "\n";
    cout << "BMP_WRITE_TEST - Fatal error!\n";
    cout << "  The test failed.\n";
    return error;
  }
//
//  Free the memory.
//
  delete [] rarray;
  delete [] garray;
  delete [] barray;

  if ( VERBOSE )
  {
    cout << "\n";
    cout << "BMP_WRITE_TEST:\n";
    cout << "  The test was successful.\n";
  }

  error = false;
  return error;
# undef VERBOSE
}
//****************************************************************************

bool long_int_read ( long int *long_int_val, ifstream &file_in )

//****************************************************************************
//
//  Purpose:
// 
//    LONG_INT_READ reads a long int from a file.
//
//  Modified:
//
//    06 March 2004
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Output, long int* LONG_INT_VAL, the value that was read.
//
//    Input, ifstream &FILE_IN, a reference to the input file.
//
//    Output, bool LONG_INT_READ, is true if an error occurred.
//
{
  bool error;
  unsigned short int u_short_int_val_hi;
  unsigned short int u_short_int_val_lo;

  if ( bmp_byte_swap )
  {
    error = u_short_int_read ( &u_short_int_val_lo, file_in );
    if ( error )
    {
      return error;
    }
    error = u_short_int_read ( &u_short_int_val_hi, file_in );
    if ( error )
    {
      return error;
    }
  }
  else
  {
    error = u_short_int_read ( &u_short_int_val_hi, file_in );
    if ( error )
    {
      return error;
    }
    error = u_short_int_read ( &u_short_int_val_lo, file_in );
    if ( error )
    {
      return error;
    }
  }

  *long_int_val = ( long int ) 
    ( u_short_int_val_hi << 16 ) | u_short_int_val_lo;

  return false;
}
//****************************************************************************

void long_int_write ( long int long_int_val, ofstream &file_out )

//****************************************************************************
//
//  Purpose:
// 
//    LONG_INT_WRITE writes a long int to a file.
//
//  Modified:
//
//    06 March 2004
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, long int* LONG_INT_VAL, the value to be written.
//
//    Input, ofstream &FILE_OUT, a reference to the output file.
//
{
  long int temp;
  unsigned short int u_short_int_val_hi;
  unsigned short int u_short_int_val_lo;

  temp = long_int_val / 65536;
  if ( temp < 0 )
  {
    temp = temp + 65536;
  }
  u_short_int_val_hi = ( unsigned short ) temp;

  temp = long_int_val % 65536;
  if ( temp < 0 )
  {
    temp = temp + 65536;
  }
  u_short_int_val_lo = ( unsigned short ) temp;

  if ( bmp_byte_swap )
  {
    u_short_int_write ( u_short_int_val_lo, file_out );
    u_short_int_write ( u_short_int_val_hi, file_out );
  }
  else
  {
    u_short_int_write ( u_short_int_val_hi, file_out );
    u_short_int_write ( u_short_int_val_lo, file_out );
  }

  return;
}
//****************************************************************************

bool u_long_int_read ( unsigned long int *u_long_int_val, 
  ifstream &file_in )

//****************************************************************************
//
//  Purpose:
// 
//    U_LONG_INT_READ reads an unsigned long int from a file.
//
//  Modified:
//
//    05 March 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Output, unsigned long int* U_LONG_INT_VAL, the value that was read.
//
//    Input, ifstream &FILE_IN, a reference to the input file.
//
//    Output, bool U_LONG_INT_READ, is true if an error occurred.
//
{
  bool error;
  unsigned short int u_short_int_val_hi;
  unsigned short int u_short_int_val_lo;

  if ( bmp_byte_swap )
  {
    error = u_short_int_read ( &u_short_int_val_lo, file_in );
    if ( error )
    {
      return error;
    }
    error = u_short_int_read ( &u_short_int_val_hi, file_in );
    if ( error )
    {
      return error;
    }
  }
  else
  {
    error = u_short_int_read ( &u_short_int_val_hi, file_in );
    if ( error )
    {
      return error;
    }
    error = u_short_int_read ( &u_short_int_val_lo, file_in );
    if ( error )
    {
      return error;
    }
  }
//
//  Acknowledgement:
//
//    A correction to the following line was supplied by
//    Peter Kionga-Kamau, 20 May 2000.
//

  *u_long_int_val = ( u_short_int_val_hi << 16 ) | u_short_int_val_lo;

  return false;
}
//****************************************************************************

void u_long_int_write ( unsigned long int u_long_int_val, 
  ofstream &file_out )

//****************************************************************************
//
//  Purpose:
// 
//    U_LONG_INT_WRITE writes an unsigned long int to a file.
//
//  Modified:
//
//    05 March 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, unsigned long int* U_LONG_INT_VAL, the value to be written.
//
//    Input, ofstream &FILE_OUT, a reference to the output file.
//
{
  unsigned short int u_short_int_val_hi;
  unsigned short int u_short_int_val_lo;

  u_short_int_val_hi = ( unsigned short ) ( u_long_int_val / 65536 );
  u_short_int_val_lo = ( unsigned short ) ( u_long_int_val % 65536 );

  if ( bmp_byte_swap )
  {
    u_short_int_write ( u_short_int_val_lo, file_out );
    u_short_int_write ( u_short_int_val_hi, file_out );
  }
  else
  {
    u_short_int_write ( u_short_int_val_hi, file_out );
    u_short_int_write ( u_short_int_val_lo, file_out );
  }

  return;
}
//****************************************************************************

bool u_short_int_read ( unsigned short int *u_short_int_val, 
  ifstream &file_in )

//****************************************************************************
//
//  Purpose:
// 
//    U_SHORT_INT_READ reads an unsigned short int from a file.
//
//  Modified:
//
//    05 March 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Output, unsigned short int* U_SHORT_INT_VAL, the value that was read.
//
//    Input, ifstream &FILE_IN, a reference to the input file.
//
//    Output, bool U_SHORT_INT_READ, is true if an error occurred.
//
{
  unsigned char chi;
  unsigned char clo;

  if ( bmp_byte_swap )
    {
    file_in >> clo;
    if ( file_in.eof() )
    {
      return true;
    }
    file_in >> chi;
    if ( file_in.eof() )
    {
      return true;
    }
  }
  else
  {
    file_in >> chi;
    if ( file_in.eof() )
    {
      return true;
    }
    file_in >> clo;
    if ( file_in.eof() )
    {
      return true;
    }
  }

  *u_short_int_val = ( chi << 8 ) | clo;

  return false;
}
//****************************************************************************

void u_short_int_write ( unsigned short int u_short_int_val, 
  ofstream &file_out )

//****************************************************************************
//
//  Purpose:
// 
//    U_SHORT_INT_WRITE writes an unsigned short int to a file.
//
//  Modified:
//
//    26 February 2003
//
//  Author:
//
//    John Burkardt
//
//  Parameters:
//
//    Input, unsigned short int* U_SHORT_INT_VAL, the value to be written.
//
//    Input, ofstream &FILE_OUT, a reference to the output file.
//
{
  unsigned char chi;
  unsigned char clo;

  chi = ( unsigned char ) ( u_short_int_val / 256 );
  clo = ( unsigned char ) ( u_short_int_val % 256 );

  if ( bmp_byte_swap )
  {
    file_out << clo << chi;
  }
  else
  {
    file_out << chi << clo;
  }

  return;
}

