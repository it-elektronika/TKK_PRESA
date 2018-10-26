#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "kunbus.h"

void piControlOpen(void)
{
    /* open handle if needed */
    if (PiControlHandle_g < 0)
    {
        PiControlHandle_g = open(PICONTROL_DEVICE, O_RDWR);
    }
}

int piControlGetVariableInfo(SPIVariable *pSpiVariable)
{
    piControlOpen();

    if (PiControlHandle_g < 0)
        return -1;

    return ioctl(PiControlHandle_g, KB_FIND_VARIABLE, pSpiVariable);
}

int piControlGetBitValue(SPIValue *pSpiValue)
{
    piControlOpen();

    if (PiControlHandle_g < 0)
        return -1;

    return ioctl(PiControlHandle_g, KB_GET_VALUE, pSpiValue);
}

int piControlSetBitValue(SPIValue *pSpiValue)
{
    piControlOpen();

    if (PiControlHandle_g < 0)
	return -ENODEV;

    if (ioctl(PiControlHandle_g, KB_SET_VALUE, pSpiValue) < 0)
	return errno;

    return 0;
}


int piControlRead(uint32_t Offset, uint32_t Length, uint8_t *pData)
{
    int BytesRead = 0;

    piControlOpen();

    if (PiControlHandle_g < 0)
        return -1;

    /* seek */
    if (lseek(PiControlHandle_g, Offset, SEEK_SET) < 0)
    {
        return -2;
    }

    /* read */
    BytesRead = read(PiControlHandle_g, pData, Length);
    if (BytesRead < 0)
    {
        return -3;
    }

    return BytesRead;
}


uint16_t readVariableValue(const char *pszVariableName)
{


    int rc;
    SPIVariable sPiVariable;
    SPIValue sPIValue;
    uint8_t i8uValue;
    uint16_t i16uValue;
    uint32_t i32uValue;
    sPiVariable.i16uLength = 0;
    sPiVariable.i8uBit = 0;
    sPiVariable.i16uAddress = 0;
    
    sPIValue.i16uAddress = 0;
    sPIValue.i8uBit = 0;
    sPIValue.i8uValue = 0;

    i8uValue = 0;
    i16uValue = 0;
    i32uValue = 0;

    strncpy(sPiVariable.strVarName, pszVariableName, sizeof(sPiVariable.strVarName));
    rc = piControlGetVariableInfo(&sPiVariable);
    if (rc < 0)
    {
        printf("Cannot find variable '%s'\n", pszVariableName);
        return 0;
    }
    if (sPiVariable.i16uLength == 1)
    {
        sPIValue.i16uAddress = sPiVariable.i16uAddress;
        sPIValue.i8uBit = sPiVariable.i8uBit;
        
        rc = piControlGetBitValue(&sPIValue);
        if (rc < 0)
	{        
          /*printf("Get bit error\n");*/
        }
        else
        {
          ;
        }
        
    }
    else if (sPiVariable.i16uLength == 8)
    {
      while (1)
      {
        rc = piControlRead(sPiVariable.i16uAddress, 1, (uint8_t*)&i8uValue);
        if (rc < 0)
        {
          printf("Read error\n");
        }    
        else
        {
          ;
        }          
      }
    }
    else if (sPiVariable.i16uLength == 16)
    {
      while (1)
      {
        rc = piControlRead(sPiVariable.i16uAddress, 2, (uint8_t*)&i16uValue);
        if (rc < 0)
        {
          printf("Read error\n");
        }
        else
        {
          break;
        }   
             
      }
    }
    else if (sPiVariable.i16uLength == 32)
    {
      while (1)
      {
        rc = piControlRead(sPiVariable.i16uAddress, 4, (uint8_t*)&i32uValue);
        if (rc < 0)
        {
          printf("Read error\n");
        }     
        else
        {
          ; 
        }   
      }
    }
    else
    {
      printf("Could not read variable %s. Internal Error\n", pszVariableName);
    } 
    if(sPiVariable.i16uLength==1)
    {
      return sPIValue.i8uValue;
    }    
    else if(sPiVariable.i16uLength==8)
    {
      return i8uValue;
    }
    else if(sPiVariable.i16uLength==16)
    {
      return i16uValue; 
    }
    else if(sPiVariable.i16uLength==32)
    {
      return i8uValue;
    }
    else
    {
      return 0;
    }
}


int piControlWrite(uint32_t Offset, uint32_t Length, uint8_t *pData)
{
    int BytesWritten = 0;

    piControlOpen();

    if (PiControlHandle_g < 0)
	return -ENODEV;

    /* seek */
    if (lseek(PiControlHandle_g, Offset, SEEK_SET) < 0)
    {
	return errno;
    }

    /* Write */
    BytesWritten = write(PiControlHandle_g, pData, Length);
    if (BytesWritten < 0)
    {
	return errno;
    }

    return BytesWritten;
}


void writeVariableValue(const char *pszVariableName, uint32_t i32uValue)
{
    int rc;
    SPIVariable sPiVariable;
    SPIValue sPIValue;
    uint8_t i8uValue;
    uint16_t i16uValue;
    sPiVariable.i16uLength = 0;
    sPiVariable.i8uBit = 0;
    sPiVariable.i16uAddress = 0;
    
    sPIValue.i16uAddress = 0;
    sPIValue.i8uBit = 0;
    sPIValue.i8uValue = 0;

    i8uValue = 0;
    i16uValue = 0;
    i32uValue = 0;
    strncpy(sPiVariable.strVarName, pszVariableName, sizeof(sPiVariable.strVarName));
    rc = piControlGetVariableInfo(&sPiVariable);
    if (rc < 0) {
	printf("Cannot find variable '%s'\n", pszVariableName);
	return;
    }
    
    if (sPiVariable.i16uLength == 1) 
    {
	sPIValue.i16uAddress = sPiVariable.i16uAddress;
	sPIValue.i8uBit = sPiVariable.i8uBit;
	sPIValue.i8uValue = i32uValue;
	rc = piControlSetBitValue(&sPIValue);
	
        
        if (rc < 0)
	   printf("Set bit error:");  /*%s\n", getWriteError(rc));*/
	else
        {
          ;
        }
	   /* printf("Set bit %d on byte at offset %d. Value %d\n", sPIValue.i8uBit, sPIValue.i16uAddress, sPIValue.i8uValue);*/
    } 
    
    else if (sPiVariable.i16uLength == 8) 
    {
	i8uValue = i32uValue;
	rc = piControlWrite(sPiVariable.i16uAddress, 1, (uint8_t *) & i8uValue);
	if (rc < 0)
	    printf("Write error:"); /* %s\n", getWriteError(rc)); */
	else
	{ printf("8-Write value %d dez (=%02x hex) to offset %d.\n", i8uValue, i8uValue,
	   	   sPiVariable.i16uAddress);
          
        }
    } else if (sPiVariable.i16uLength == 16) {
	i16uValue = i32uValue;
        printf("I32:%d\n", i32uValue);
        printf("I16:%d\n", i16uValue);
        

	rc = piControlWrite(sPiVariable.i16uAddress, 2, (uint8_t *) & i16uValue);
	if (rc < 0)
	    printf("Write error:"); /* %s\n", getWriteError(rc)); */
	else
	{    printf("16-Write value %d dez (=%04x hex) to offset %d.\n", i16uValue, i16uValue,sPiVariable.i16uAddress);
        }
    } else if (sPiVariable.i16uLength == 32) {
	rc = piControlWrite(sPiVariable.i16uAddress, 4, (uint8_t *) & i32uValue);
	if (rc < 0)
	    printf("Write error:"); /* %s\n", getWriteError(rc)); */
	else
        {
          ;
        }
	    printf("32-Write value %d dez (=%08x hex) to offset %d.\n", i32uValue, i32uValue,
		   sPiVariable.i16uAddress);
    }
}






