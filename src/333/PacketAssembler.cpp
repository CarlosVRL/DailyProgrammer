/**
 * Challenge #333 [Easy] Packet Assembler
 * 
 * https://www.reddit.com/r/dailyprogrammer/comments/72ivih/20170926_challenge_333_easy_packet_assembler/
 * 
 * Start 9:50 PM
 * Stop 12:30 AM
 */

#include <fstream>
#include <iostream>

#include <string>

#include "PacketElement.h"

std::ifstream inf("input.txt");
std::ofstream ouf("output.txt");

const int echoContents = 1; // Set to 1 to echo packet contents to stdout

/**
 * MAIN
 */
using namespace std;
int main(void) {
    // The primary packet container stores by message ID, and then by packet ID
    MessageToPackets packets;
    
    // Read the lines of input (simulating stdin)
    string line = "";
    while(getline(inf, line))
    {   
        // Generate and store the packet element onto container
        PacketElement packetElement = generatePacketElement(line);        
        storePacketElementIntoSortedContainer(packetElement, packets);
    }
    
    // Query the container for any stored elements and write to file
    string contents = readPackets(packets);
    ouf << contents;
    
    // Optional print to stdout
    if (echoContents) cout << contents;
    
    return 0;
}
