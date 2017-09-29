/**
 * Challenge #333 [Easy] Packet Assembler
 * 
 * https://www.reddit.com/r/dailyprogrammer/comments/72ivih/20170926_challenge_333_easy_packet_assembler/
 * 
 * Start 9:50 PM
 * Stop xx:xx xx 
 */

#include <fstream>
#include <iostream>
#include <sstream>

#include <map>
#include <set>
#include <string>
#include <vector>

std::ifstream inf("input.txt");
std::ofstream ouf("output.txt");

#define cout ouf // Uncomment this line to echo state to stdout

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
void readPackets(MessageToPackets& packets);

/**
 * MAIN
 */
using namespace std;
int main(void) {
    // The primary packet container stores first by message, and then packet ID
    MessageToPackets packets;
    
    // Read the lines of input (simulating stdin)
    string line = "";
    while(getline(inf, line))
    {   
        // Generate and store the packet element onto container
        PacketElement packetElement = generatePacketElement(line);        
        storePacketElementIntoSortedContainer(packetElement, packets);
    }
    
    // The entire contents of the container echoed at the end for completeness
    // Note that the contents may be queried anytime, such as whithin the loop
    readPackets(packets);
    
    return 0;
}

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
    stringstream ss(line);

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
        set<PacketElement> elements;
        packets.insert(PacketIdToPacket(packetElement.messageId, elements));
    }
    
    // Extract the packet elements container to store the new input
    set<PacketElement>& elements = packets.find(packetElement.messageId)->second;
    elements.insert(packetElement);
    
    return;
}

void readPackets(MessageToPackets& packets)
{
    // Primary loop is over all message ID's
    MessageToPackets::iterator messageBlock = packets.begin();
    MessageToPackets::iterator messageEnd = packets.end();
    for (; messageBlock != messageEnd; ++messageBlock)
    {
        // Secondary loop is over all packet ID's
        set<PacketElement>& elements = messageBlock->second;
        set<PacketElement>::iterator it = elements.begin();
        set<PacketElement>::iterator et = elements.end();
        for (; it != et; ++it)
        {
            cout << it->line << endl;
        }    
    }
    
    return;
}
