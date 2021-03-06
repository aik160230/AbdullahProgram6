/*
 * Abdullah Khan
 * aik160230@utdallas.edu
 * CS3377.501
 * included header file
 */


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const int maxRecordStringLength = 25;

struct BinaryFileHeader
{
     uint32_t magicNumber;
     uint32_t versionNumber;
     uint64_t numRecords;
};

struct BinaryFileRecord
{
     uint8_t strLength;
     char   stringBuffer[maxRecordStringLength];

};
