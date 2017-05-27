//
// Generated file, do not edit! Created by nedtool 5.0 from inet/nic/csa/CsaHostPk.msg.
//

#ifndef __INET_CSAHOSTPK_M_H
#define __INET_CSAHOSTPK_M_H

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0500
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif

// cplusplus {{
	#include <vector>
// }}


namespace inet {

// cplusplus {{
	typedef std::vector<int> RepetionPoint;
// }}

/**
 * Class generated from <tt>inet/nic/csa/CsaHostPk.msg:28</tt> by nedtool.
 * <pre>
 * packet CsaHostPk
 * {
 *     long PkId;
 *     int HostId;
 *     string HostPath;
 *     int SlotIndex;
 *     int NumOfRepetions;
 *     RepetionPoint point;
 *     bool IsRecovery;
 * }
 * </pre>
 */
class CsaHostPk : public ::omnetpp::cPacket
{
  protected:
    long PkId;
    int HostId;
    ::omnetpp::opp_string HostPath;
    int SlotIndex;
    int NumOfRepetions;
    RepetionPoint point;
    bool IsRecovery;

  private:
    void copy(const CsaHostPk& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const CsaHostPk&);

  public:
    CsaHostPk(const char *name=nullptr, int kind=0);
    CsaHostPk(const CsaHostPk& other);
    virtual ~CsaHostPk();
    CsaHostPk& operator=(const CsaHostPk& other);
    virtual CsaHostPk *dup() const {return new CsaHostPk(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b);

    // field getter/setter methods
    virtual long getPkId() const;
    virtual void setPkId(long PkId);
    virtual int getHostId() const;
    virtual void setHostId(int HostId);
    virtual const char * getHostPath() const;
    virtual void setHostPath(const char * HostPath);
    virtual int getSlotIndex() const;
    virtual void setSlotIndex(int SlotIndex);
    virtual int getNumOfRepetions() const;
    virtual void setNumOfRepetions(int NumOfRepetions);
    virtual RepetionPoint& getPoint();
    virtual const RepetionPoint& getPoint() const {return const_cast<CsaHostPk*>(this)->getPoint();}
    virtual void setPoint(const RepetionPoint& point);
    virtual bool getIsRecovery() const;
    virtual void setIsRecovery(bool IsRecovery);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const CsaHostPk& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, CsaHostPk& obj) {obj.parsimUnpack(b);}

} // namespace inet

#endif // ifndef __INET_CSAHOSTPK_M_H
