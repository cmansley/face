
// Include header files
#include "cv.h"
#include "highgui.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>

// Create a string that contains the exact cascade name
const char* cascade_name = "haarcascade_frontalface_alt.xml";

// Function prototype for detecting and drawing an object from an image
void detect( IplImage* image, char *filename, char *work );

// Main function, defines the entry point for the program.
int main( int argc, char** argv )
{

  // Create a sample image
  IplImage *img = cvLoadImage(argv[1],1);
  
  // Call the function to detect and draw the face positions
  detect(img, argv[2], argv[3]);
  
  // Release the image
  cvReleaseImage(&img);
    
  // return 0 to indicate successfull execution of the program
  return 0;
}

// Function to detect and draw any faces that is present in an image
void detect( IplImage* img, char *filename, char *work)
{

  // Create memory for calculations
  static CvMemStorage* storage = 0;

  // Create a new Haar classifier
  static CvHaarClassifierCascade* cascade = 0;

  CvRect* r;

  int scale = 1;

  FILE *out;

  out=fopen(filename,"a+");
  if(out == NULL) {
    fprintf( stderr, "ERROR: Could not open logfile\n" );
    return;
  }

  // Load the HaarClassifierCascade
  cascade = (CvHaarClassifierCascade*)cvLoad( cascade_name, 0, 0, 0 );
    
  // Check whether the cascade has loaded successfully. Else report and error and quit
  if( !cascade )
  {
    fprintf( stderr, "ERROR: Could not load classifier cascade\n" );
    return;
  }
    
  // Allocate the memory storage
  storage = cvCreateMemStorage(0);

  // Clear the memory storage which was used before
  cvClearMemStorage( storage );

  // Find whether the cascade is loaded, to find the faces. If yes, then:
  if( cascade )
  {

    // There can be more than one face in an image. So create a growable sequence of faces.
    // Detect the objects and store them in the sequence
    CvSeq* faces = cvHaarDetectObjects( img, cascade, storage,
                                        1.1, 2, CV_HAAR_DO_CANNY_PRUNING,
                                        cvSize(40, 40) );

    if(faces) {

      int i = 0;
      int area = 0;

      while(area < 7000 && i < faces->total) {

        // Create a new rectangle for drawing the face
        r = (CvRect*)cvGetSeqElem( faces, i );

        area = r->width*r->height;
	    
        i++;	    
      }

      fprintf(out,"%s %4d %4d %4d %4d\n",work,r->x, r->y, r->width, r->height);
	  
    }
	
  }
}
