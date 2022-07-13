//---------------------------------------------------------------------
//                      H A P T I C   M A S T E R
//
// Included functions.
// 
//---------------------------------------------------------------------
#ifndef _HAPTIC_MASTER_H_
#define _HAPTIC_MASTER_H_

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include "Vector3d.h"
#include "HapticAPI2.h"

#ifndef Pi
#define Pi 3.14159265358979
#endif

#ifndef Pi2
#define Pi2 6.28318530717958
#endif

#ifndef DegPerRad
#define DegPerRad 180/Pi
#endif

#ifndef RadPerDeg
#define RadPerDeg Pi/180
#endif



//---------------------------------------------------------------------
//          H A   S E N D   C O M M A N D   -   n o   p a r a m s
//
// Overloaded function to send a command to the HapticMASTER.
// This version excpect no extra parameters for the command.
//---------------------------------------------------------------------
int  haSendCommand ( long inDev, 
                     const char* inCommand, 
                     char* outCommand ) {

   if ( haDeviceSendString(inDev, inCommand, outCommand) ) {
      printf ( "--- ERROR: Command could not be sent to the Real-time\n" );
      return -1;
   }
   else {
      if ( strstr(outCommand, "--- ERROR") ) {
         return -1;
      }
      else {
         return 0;
      }
   }
}

//---------------------------------------------------------------------
//          H A   S E N D   C O M M A N D   -   1   d o u b l e
//
// Overloaded function to send a command to the HapticMASTER.
// This version excpect one double as a parameter for the command.
//---------------------------------------------------------------------
int  haSendCommand ( long inDev, 
                     const char* inCommand, 
                     double inDouble1,
                     char* outCommand ) {
   char tempString[100];
   sprintf(tempString, "%s %g", inCommand, inDouble1);
   if ( haDeviceSendString(inDev, tempString, outCommand) ) {
      printf ( "--- ERROR: Command could not be sent to the Real-time\n" );
      return -1;
   }
   else {
      if ( strstr(outCommand, "--- ERROR") ) {
         return -1;
      }
      else {
         return 0;
      }
   }
}

//---------------------------------------------------------------------
//         H A   S E N D   C O M M A N D   -   3   d o u b l e s
//
// Overloaded function to send a command to the HapticMASTER.
// This version excpect 3 doubles as parameters for the command.
//---------------------------------------------------------------------
int  haSendCommand ( long inDev, 
                     const char* inCommand, 
                     double inDouble1,
                     double inDouble2,
                     double inDouble3,
                     char* outCommand ) {
   char tempString[200];
   sprintf(tempString, "%s [%g,%g,%g]", inCommand, inDouble1, inDouble2, inDouble3);
   if ( haDeviceSendString(inDev, tempString, outCommand) ) {
      printf ( "--- ERROR: Command could not be sent to the Real-time\n" );
      return -1;
   }
   else {
      if ( strstr(outCommand, "--- ERROR") ) {
         return -1;
      }
      else {
         return 0;
      }
   }
}

//---------------------------------------------------------------------
//         H A   S E N D   C O M M A N D   -   4   d o u b l e s
//
// Overloaded function to send a command to the HapticMASTER.
// This version excpect 4 doubles as parameters for the command.
//---------------------------------------------------------------------
int  haSendCommand ( long inDev, 
                     const char* inCommand, 
                     double inDouble1,
                     double inDouble2,
                     double inDouble3,
                     double inDouble4,
                     char* outCommand ) {
   char tempString[200];
   sprintf(tempString, "%s [%g,%g,%g,%g]", inCommand, inDouble1, inDouble2, inDouble3, inDouble4);
   if ( haDeviceSendString(inDev, tempString, outCommand) ) {
      printf ( "--- ERROR: Command could not be sent to the Real-time\n" );
      return -1;
   }
   else {
      if ( strstr(outCommand, "--- ERROR") ) {
         return -1;
      }
      else {
         return 0;
      }
   }
}

//---------------------------------------------------------------------
//         H A   S E N D   C O M M A N D   -   V E C T O R 3 D
//
// Overloaded function to send a command to the HapticMASTER.
// This version excpect 1 Vector3d object as a parameter for the command.
//---------------------------------------------------------------------
int  haSendCommand ( long inDev, 
                     const char* inCommand, 
                     Vector3d inVector,
                     char* outCommand ) {
   char tempString[200];
   sprintf(tempString, "%s [%g,%g,%g]", inCommand, inVector.x, inVector.y, inVector.z);
   if ( haDeviceSendString(inDev, tempString, outCommand) ) {
      printf ( "--- ERROR: Command could not be sent to the Real-time\n" );
      return -1;
   }
   else {
      if ( strstr(outCommand, "--- ERROR") ) {
         return -1;
      }
      else {
         return 0;
      }
   }
}

//---------------------------------------------------------------------
//               I N I T I A L I Z E   D E V I C E
//
// This function initializes the HapticMASTER device.
// It first searches for the end positions. When all ends are found,
// the HapticMASTER is set to the force_sensitive state.
//---------------------------------------------------------------------
void InitializeDevice( long dev ) 
{
	char outputString[200] = "";

   haSendCommand( dev, "remove all", outputString);
   printf("remove all ==> %s\n", outputString);

	// set the inertia to the default value
   haSendCommand( dev, "set inertia 3.0", outputString);
   printf("set inertia ==> %s\n", outputString);
   
   char isCalibratedStr[10] = "";

   haSendCommand (dev, "get position_calibrated", outputString);
   printf("get position_calibrated ==> %s\n", outputString);
   strcpy_s(isCalibratedStr, outputString);

   if ( !strcmp(isCalibratedStr, "\"false\"") ) {
   	haDeviceSendString ( dev, "set state init", outputString);
      printf("set state init ==> %s\n", outputString);
      if (!strstr(outputString, "--- ERROR:") ) {
         printf( "Initializing the HapticMASTER. Please wait...\n" );
      }
	
	   haDeviceSendString ( dev, "get state", outputString );

	   while( strcmp(outputString, "\"stop\"") ) {
		   haDeviceSendString ( dev, "get state", outputString );
	   }
   }

	printf("Setting to state Force\n");
	haDeviceSendString ( dev, "set state force", outputString);
   printf("set state force ==> %s\n", outputString);
}


int createSpring(const long dev, const char *springName, const double pos[3], const double dir[3],  const double springConst, const double dampFactor, const double maxForce)
{
    char tempString[100] = "";
    char response[300];
    
    // Create the spring 
    sprintf(tempString, "create spring %s", *springName);
    if(haSendCommand(dev, tempString, response))
        return -1;
    
    // Set spring location
    sprintf(tempString, "set mySpringX pos [%g,%g,%g]", pos[0], pos[1], pos[2]);
    if(haSendCommand(dev, tempString, response))
        return -1;
    
    // Set spring stiffness
    sprintf(tempString, "set mySpringX stiffness %g", springConst);
    if(haSendCommand(dev, tempString, response))
        return -1;
    
    // Set spring direction
    sprintf(tempString, "set mySpringX direction [%g,%g,%g]", dir[0], dir[1], dir[2]);
    if(haSendCommand(dev, tempString, response))
        return -1;
    
    // Set damping factor
    sprintf(tempString, "set mySpringX dampfactor %g", dampFactor);
    if(haSendCommand(dev, tempString, response))
        return -1;
    
    // Set maximum spring force
    sprintf(tempString, "set mySpringX maxforce %g", maxForce);
    if(haSendCommand(dev, tempString, response))
        return -1;
    
    // Enable the spring
    sprintf(tempString, "create spring %s", *springName);
    if(haSendCommand(dev, tempString, response))
        return -1;
    
    return 0;
}


#endif