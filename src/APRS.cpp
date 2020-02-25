#include <APRS.h>

struct PathAddress addresses[] = {
  {(char *)D_CALLSIGN, D_CALLSIGN_ID},  // Destination callsign
  {(char *)S_CALLSIGN, S_CALLSIGN_ID},  // Source callsign
  {(char *)NULL, 0}, // Digi1 (first digi in the chain)
  {(char *)NULL, 0}  // Digi2 (second digi in the chain)
};

// setup() method runs once, when the sketch starts
void APRS_setup()
{
  // Set up the APRS module
  aprs_setup(50, // number of preamble flags to send
       0,
       0); // No VOX ton
}

// Function to broadcast your location
void APRS_broadcastLocation(double lati,double longui, const char *comment)
{
  
  // If above 5000 feet switch to a single hop path
  int nAddresses;
  // APRS recomendations for > 5000 feet is:
  // Path: WIDE2-1 is acceptable, but no path is preferred.
  nAddresses = 3;
  addresses[2].callsign = "WIDE2";
  addresses[2].ssid = 1;

  // Send the packet
  aprs_send(addresses,  //Path
            nAddresses, //nPath
            23, //Day of month
            6,  //Hour of day
            34, // Minute
            (float)lati,   //Degrees
            (float)longui, //Degrees
            0,// altitude in meters
            0,// heading in degrees
            0,// speed in knots
            SYMBOL_TABLE,
            SYMBOL_CHAR,
            comment);
    
}

bool APRS_not_busy(){
  return !aprs_busy();
}