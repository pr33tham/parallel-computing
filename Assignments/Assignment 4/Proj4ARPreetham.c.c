#include <stdlib.h>
/* PROGRAM Histogram */
/* Number of lines in <image>.pgm header */
#define header_lines 4;
/* "Hard coding" image header values into sizing and values to be written out.
    Change this to match the values in your image */
/* Note: Image Type P2 will be written directly in cout */
#define image_columns 120
#define image_rows 118
#define  MaxGrayComponentValue 255;
#define carriage_return '\n'

int image[image_rows + 1][image_columns + 1];
int hist[MaxGrayComponentValue + 2];
int intensity;
spinlock L[MaxGrayComponentValue + 1];

/* End of Global variables Shared Memory*/

void read_image_header() {
    /* this procedure reads the four header lines and throw them away*/
    char buffer[header_lines+1][80]; /* buffer for storing input line */
    char c;
    int m;
    for (m = 1; m <= header_lines; ++m)
    do
    {
      cin >> c;  /* input next character */
    } while (c != carriage_return);
 }

void read_image_values() {/* read image into array */
    int i, j;
    for(i = 1; i <= image_rows; i++){
        for( j = 1; j <= image_columns; j++){
            cin >> image[i][j];
        }
    }
}

/*
void write_image_to_file()
 {
    int output_row_width = 10;
    int OUTPUT_ROW_COUNTER = 1;
    for(i = 1; i <= image_rows; i++)
    {
      for ( j = 1; j <= image_columns; j++)
      {
        if (OUTPUT_ROW_COUNTER == output_row_width)
        {
          cout << ENDL;
          OUTPUT_ROW_COUNTER = 1;
        }
        cout << image_out[i][j] << " ";
        OUTPUT_ROW_COUNTER = OUTPUT_ROW_COUNTER + 1;
      }
    }
  }
*/

main( ) {
    read_image_header();
    read_image_values();
    int i, j;
    /*Input the image array*/
    for (i = 0; i <= MaxGrayComponentValue + 1; i++)
        hist[i] = 0;
    forall i = 1 to image_rows do {
        int j, intensity;
        for (j = 1; j <= image_columns; j++) {
            intensity = image[i][j];
            Lock(L[intensity]);
                hist[intensity] = hist[intensity] + 1;
            Unlock(L[intensity]);
        }
    }
    for (i = 1; i < MaxGrayComponentValue + 1; i++) {
        cout << hist[i] << endl;
    }
}