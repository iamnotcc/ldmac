//
// Generated file, do not edit! Created by nedtool 5.0 from inet/linklayer/tdma/ApAllocationPkOfTDMA.msg.
//

#ifndef __INET_APALLOCATIONPKOFTDMA_M_H
#define __INET_APALLOCATIONPKOFTDMA_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0500
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif


namespace inet {

/**
 * Class generated from <tt>inet/linklayer/tdma/ApAllocationPkOfTDMA.msg:18</tt> by nedtool.
 * <pre>
 * packet ApAllocationPkOfTDMA
 * {
 *     int nIndex;
 *     int nSlotNum;
 * }
 * </pre>
 */
class ApAllocationPkOfTDMA : public ::omnetpp::cPacket
{
  protected:
    int nIndex;
    int nSlotNum;

  private:
    void copy(const ApAllocationPkOfTDMA& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ApAllocationPkOfTDMA&);

  public:
    ApAllocationPkOfTDMA(const char *name=nullptr, int kind=0);
    ApAllocationPkOfTDMA(const ApAllocationPkOfTDMA& other);
    virtual ~ApAllocationPkOfTDMA();
    ApAllocationPkOfTDMA& operator=(const ApAllocationPkOfTDMA& other);
    virtual ApAllocationPkOfTDMA *dup() const {return new ApAllocationPkOfTDMA(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b);

    // field getter/setter methods
    virtual int getNIndex() const;
    virtual void setNIndex(int nIndex);
    virtual int getNSlotNum() const;
    virtual void setNSlotNum(int nSlotNum);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ApAllocationPkOfTDMA& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ApAllocationPkOfTDMA& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_APALLOCATIONPKOFTDMA_M_H
