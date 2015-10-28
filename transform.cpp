#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include "mobius.hpp"

 using namespace cv;

 /// Global variables
 Mat src, dst;
 Mat map_x, map_y;
 char* remap_window = "Remap demo";
 int ind = 0;

 /// Function Headers
 void update_map( void );

 /**
 * @function main
 */
 int main( int argc, char** argv )
 {
  /// Load the image
   src = imread( argv[1], 1 );

  /// Create dst with the same size as src:
  dst.create( src.size(), src.type() );
  
  
  Mobius transformation;

  complex<float> v = complex<float>(10.0f, 5.0f);
  
  transformation.dilate(0.0001f);
  transformation.invert();

  map_x = transformation.map_x(src);
  map_y = transformation.map_y(src);

  /// Create window
  namedWindow( remap_window, CV_WINDOW_AUTOSIZE );

  remap( src, dst, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0,0, 0) );
  /// Display results
  imshow( remap_window, dst );

  waitKey(0);

  return 0;
 }
