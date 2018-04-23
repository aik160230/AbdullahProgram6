/*
 * Abdullah Khan
 * aik160230@utdallas.edu
 * CS3377.501
 * CDK File
 */

#include <iostream>
#include <stdlib.h>
#include "cdk.h"
#include "filereader.h"

#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;


int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"0", "a", "b", "c", "d", "e"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);
   FILE *fp=fopen("cs3377.bin","rb");
   char myBuffer[33];
   BinaryFileHeader head;
   BinaryFileRecord record;
   fread(&head, sizeof(struct BinaryFileHeader),1,fp);
   //printf("%x %d %d\n", head.magicNumber, head.versionNumber, head.numRecords);
   snprintf(myBuffer, sizeof(myBuffer), "Magic: %#x", head.magicNumber);
   setCDKMatrixCell(myMatrix, 1, 1, myBuffer);
   snprintf(myBuffer, sizeof(myBuffer), "Version: %d", head.versionNumber);
   setCDKMatrixCell(myMatrix, 1, 2, myBuffer);
   snprintf(myBuffer, sizeof(myBuffer), "NumRecords: %lld", (long long) head.numRecords);
   setCDKMatrixCell(myMatrix, 1, 3, myBuffer);
   fseek(fp, 16, SEEK_SET);
  /*
   * Dipslay a message
   */
  for(int i = 1; i<=4; i++)
  {
	fread(&record, sizeof(struct BinaryFileRecord),1,fp);
        //printf("%d %s\n", record.strLength, record.stringBuffer);
	snprintf(myBuffer, sizeof(myBuffer), "strlen: %d", record.strLength);
	setCDKMatrixCell(myMatrix, i+1, 1, myBuffer);
	snprintf(myBuffer, sizeof(myBuffer), "%s", record.stringBuffer);
	setCDKMatrixCell(myMatrix, i+1, 2, myBuffer);
  }
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
