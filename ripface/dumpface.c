
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

#define LVL 8

// Function prototype for detecting and drawing an object from an image
void detect_and_save( IplImage* img, char *filename, int x, int y, int width, int height, int num);

struct stuff {
  int num;
  int x;
  int y;
  int winx;
  int winy;
};

int compare(const void * a, const void * b)
{
  struct stuff *item1 = (struct stuff*)a;
  struct stuff *item2 = (struct stuff*)b;

  return ( item1->num - item2->num );
}

// Main function, defines the entry point for the program.
int main( int argc, char** argv )
{
  
  struct stuff imgs[200];
  struct stuff n_imgs[200];

  char logfile[200];
  char filename[200];
  int i,j,k;

  FILE *in;  

  sprintf(logfile,"%s/%s",argv[1],argv[3]);

  // Open log file
  in = fopen(logfile, "r");
  if(in == NULL) {
    fprintf(stderr, "Error: Log file failed to open\n");
    return -1;
  }

  // Parse 
  i = 0;
  while(fscanf(in,"%d %d %d %d %d",
               &(imgs[i].num), 
               &(imgs[i].x), 
               &(imgs[i].y), 
               &(imgs[i].winx), 
               &(imgs[i].winy))!=EOF) {
    i++;
  }

  // sort by frame num
  qsort(imgs, i, sizeof(struct stuff), compare);

  // do filtering
  int off = 8;
  int temp_x, temp_y;

  for(j=off; j<i-off; j++){
    temp_x = 0;
    temp_y = 0;

    for(k=-off; k<=off; k++) {
      temp_x += imgs[j+k].x;
      temp_y += imgs[j+k].y;
    }

    n_imgs[j].x = floor(temp_x/17.0+0.5);
    n_imgs[j].y = floor(temp_y/17.0+0.5);
  }

  // filename
  sprintf(filename,"%s/%03d.jpg",argv[1],imgs[0].num);
  
  // Create a sample image
  IplImage *img = cvLoadImage(filename,1);
  
  // Call the function to detect and draw the face positions
  detect_and_save(img, argv[2], imgs[0].x, imgs[0].y, imgs[0].winx, imgs[0].winy, imgs[0].num);
  
  // Releaseq the image
  cvReleaseImage(&img);
  /*
  // loop over images
  for(j=off; j<i-off; j++) {
    
    // filename
    sprintf(filename,"%s/%03d.jpg",argv[1],imgs[j].num);

    // Create a sample image
    IplImage *img = cvLoadImage(filename,1);
  
    // Call the function to detect and draw the face positions
    detect_and_save(img, argv[2], n_imgs[j].x, n_imgs[j].y, imgs[0].winx, imgs[0].winy, imgs[j].num);
  
    // Releaseq the image
    cvReleaseImage(&img);
  }
  */
  // return 0 to indicate successfull execution of the program
  return 0;
}

// Function to detect and draw any faces that is present in an image
void detect_and_save( IplImage* img, char *dirname, int x, int y, int width, int height, int num)
{
  double kern[LVL] = {0, 5.0, 7.0, 9.0, 11.0, 13.0, 15.0, 17.0};

  char outfile[200];

  IplImage *faceimg;
  IplImage *faceimgcolor;
  IplImage *smoothimg;

  CvRect r;

  int i;

  //
  // Grab face from image and resize
  //
  
  // get rect
  r.x = x;
  r.y = y;
  r.width = width;
  r.height = height;

  // set area in orginal images
  cvSetImageROI(img, r);
  
  // create new images
  faceimgcolor = cvCreateImage(cvSize(256,256),
                               img->depth,
                               img->nChannels);
  
  // create new bw images
  faceimg = cvCreateImage(cvSize(256,256),
                          img->depth,
                          1);

  // create new filt images
  smoothimg = cvCreateImage(cvSize(256,256),
                          img->depth,
                          1);  

  cvResize(img, faceimgcolor, CV_INTER_CUBIC);
  
  // copy subimage 
  cvCvtColor(faceimgcolor, faceimg, CV_RGB2GRAY);
  
  // always reset the Region of Interest
  cvResetImageROI(img);

  //
  // Create blurred images
  //

  // no blur image
  sprintf(outfile,"%s/%03d_%03d_head.jpg", dirname, num, 0);
  cvSaveImage(outfile, faceimg);

  // do loop to fillout blurring
  for(i=1; i<LVL; i++) {

    // gaussian blur with default kernal (Buggy documentation)
    cvSmooth(faceimg, smoothimg, CV_GAUSSIAN, 0, 0, kern[i], kern[i]);
    
    // blur image name 
    sprintf(outfile,"%s/%03d_%03d_head.jpg", dirname, num, i);

    // save blurred image
    cvSaveImage(outfile, smoothimg);
  }


  //
  // Cleanup!
  //

  // Release smooth image
  cvReleaseImage( &smoothimg );

  // Release face image
  cvReleaseImage( &faceimg );

  // Release face image
  cvReleaseImage( &faceimgcolor );
}
