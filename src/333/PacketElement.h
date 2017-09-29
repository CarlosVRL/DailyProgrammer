#ifndef PACKETELEMENT_H
#define PACKETELEMENT_H

/**
 * Contains the packet element data structures and simple accessors
 */

#include <iostream>
#include <sstream>

#include <map>
#include <set>
#include <string>

/**
 * Packet element holds sorting information in addition to the primary message
 */
struct PacketElement {
    int messageId;    //!< The message ID is the highest group level
    int packetId;     //!< zero-indexed location of the message
    int packetCount;  //!< Total number of packets in the message
    std::string line; //!< The entire package input line
    
    // Constructor maps the sorting information onto semantic variables
    PacketElement(int messageId, int packetId, int packetCount, std::string line)
    {
        this->messageId = messageId;
        this->packetId  = packetId;
        this->packetCount = packetCount;
        this->line = line;
    }
    
    // Elements are sorted on @packetId to return correct relative ordering
    bool operator< (const PacketElement& rhs) const {
        return packetId < rhs.packetId;
    }
};

/**
 * The packet container stores packet collections based on message ID
 */
typedef std::pair<int, std::set<PacketElement> > PacketIdToPacket;
typedef std::map<int, std::set<PacketElement> > MessageToPackets;

/**
 * Prototypes
 */
PacketElement generatePacketElement(const std::string& line);
void storePacketElementIntoSortedContainer(const PacketElement packetElement, MessageToPackets& packets);
std::string readPackets(MessageToPackets& packets);

/**
 * Parses the input packet message to extract sorting information
 * 
 * @param line
 *      raw HTML input message
 * @return 
 *      PacketElement containing the parsed location information
 */
PacketElement generatePacketElement(const std::string& line)
{
    // Read line into a string stream based on " "
    std::stringstream ss(line);

    // Read the first three integers X Y Z into string array
    int x,y,z;
    ss >> x;
    ss >> y;
    ss >> z;
    
    return PacketElement(x,y,z,line);
}

/**
 * Stores packet elements onto the passed container
 * 
 * @param packetElement
 *      copy of the packet element that will be stored
 * @param packets
 *      packet container
 */
void storePacketElementIntoSortedContainer(const PacketElement packetElement, MessageToPackets& packets)
{
    // Check if packet sub-container exists
    if(packets.find(packetElement.messageId) == packets.end())
    {
        std::set<PacketElement> elements;
        packets.insert(PacketIdToPacket(packetElement.messageId, elements));
    }
    
    // Extract the packet elements container to store the new input
    std::set<PacketElement>& elements = packets.find(packetElement.messageId)->second;
    elements.insert(packetElement);
    
    return;
}

std::string readPackets(MessageToPackets& packets)
{
    std::string res;
    
    // Primary loop is over all message ID's
    MessageToPackets::iterator messageBlock = packets.begin();
    MessageToPackets::iterator messageEnd = packets.end();
    for (; messageBlock != messageEnd; ++messageBlock)
    {
        // Secondary loop is over all packet ID's
        std::set<PacketElement>& elements = messageBlock->second;
        std::set<PacketElement>::iterator it = elements.begin();
        std::set<PacketElement>::iterator et = elements.end();
        for (; it != et; ++it)
        {
            res += it->line + "\n";
        }    
    }
    
    return res;
}

#endif /* PACKETELEMENT_H */

