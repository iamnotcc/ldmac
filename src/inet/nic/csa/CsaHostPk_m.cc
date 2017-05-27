//
// Generated file, do not edit! Created by nedtool 5.0 from inet/nic/csa/CsaHostPk.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "CsaHostPk_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: no doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: no doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace inet {

// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

Register_Class(CsaHostPk);

CsaHostPk::CsaHostPk(const char *name, int kind) : ::omnetpp::cPacket(name,kind)
{
    this->PkId = 0;
    this->HostId = 0;
    this->SlotIndex = 0;
    this->NumOfRepetions = 0;
    this->IsRecovery = false;
}

CsaHostPk::CsaHostPk(const CsaHostPk& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

CsaHostPk::~CsaHostPk()
{
}

CsaHostPk& CsaHostPk::operator=(const CsaHostPk& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void CsaHostPk::copy(const CsaHostPk& other)
{
    this->PkId = other.PkId;
    this->HostId = other.HostId;
    this->HostPath = other.HostPath;
    this->SlotIndex = other.SlotIndex;
    this->NumOfRepetions = other.NumOfRepetions;
    this->point = other.point;
    this->IsRecovery = other.IsRecovery;
}

void CsaHostPk::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->PkId);
    doParsimPacking(b,this->HostId);
    doParsimPacking(b,this->HostPath);
    doParsimPacking(b,this->SlotIndex);
    doParsimPacking(b,this->NumOfRepetions);
    doParsimPacking(b,this->point);
    doParsimPacking(b,this->IsRecovery);
}

void CsaHostPk::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->PkId);
    doParsimUnpacking(b,this->HostId);
    doParsimUnpacking(b,this->HostPath);
    doParsimUnpacking(b,this->SlotIndex);
    doParsimUnpacking(b,this->NumOfRepetions);
    doParsimUnpacking(b,this->point);
    doParsimUnpacking(b,this->IsRecovery);
}

long CsaHostPk::getPkId() const
{
    return this->PkId;
}

void CsaHostPk::setPkId(long PkId)
{
    this->PkId = PkId;
}

int CsaHostPk::getHostId() const
{
    return this->HostId;
}

void CsaHostPk::setHostId(int HostId)
{
    this->HostId = HostId;
}

const char * CsaHostPk::getHostPath() const
{
    return this->HostPath.c_str();
}

void CsaHostPk::setHostPath(const char * HostPath)
{
    this->HostPath = HostPath;
}

int CsaHostPk::getSlotIndex() const
{
    return this->SlotIndex;
}

void CsaHostPk::setSlotIndex(int SlotIndex)
{
    this->SlotIndex = SlotIndex;
}

int CsaHostPk::getNumOfRepetions() const
{
    return this->NumOfRepetions;
}

void CsaHostPk::setNumOfRepetions(int NumOfRepetions)
{
    this->NumOfRepetions = NumOfRepetions;
}

RepetionPoint& CsaHostPk::getPoint()
{
    return this->point;
}

void CsaHostPk::setPoint(const RepetionPoint& point)
{
    this->point = point;
}

bool CsaHostPk::getIsRecovery() const
{
    return this->IsRecovery;
}

void CsaHostPk::setIsRecovery(bool IsRecovery)
{
    this->IsRecovery = IsRecovery;
}

class CsaHostPkDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    CsaHostPkDescriptor();
    virtual ~CsaHostPkDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(CsaHostPkDescriptor);

CsaHostPkDescriptor::CsaHostPkDescriptor() : omnetpp::cClassDescriptor("inet::CsaHostPk", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

CsaHostPkDescriptor::~CsaHostPkDescriptor()
{
    delete[] propertynames;
}

bool CsaHostPkDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CsaHostPk *>(obj)!=nullptr;
}

const char **CsaHostPkDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *CsaHostPkDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int CsaHostPkDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount() : 7;
}

unsigned int CsaHostPkDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISCOMPOUND,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *CsaHostPkDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "PkId",
        "HostId",
        "HostPath",
        "SlotIndex",
        "NumOfRepetions",
        "point",
        "IsRecovery",
    };
    return (field>=0 && field<7) ? fieldNames[field] : nullptr;
}

int CsaHostPkDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='P' && strcmp(fieldName, "PkId")==0) return base+0;
    if (fieldName[0]=='H' && strcmp(fieldName, "HostId")==0) return base+1;
    if (fieldName[0]=='H' && strcmp(fieldName, "HostPath")==0) return base+2;
    if (fieldName[0]=='S' && strcmp(fieldName, "SlotIndex")==0) return base+3;
    if (fieldName[0]=='N' && strcmp(fieldName, "NumOfRepetions")==0) return base+4;
    if (fieldName[0]=='p' && strcmp(fieldName, "point")==0) return base+5;
    if (fieldName[0]=='I' && strcmp(fieldName, "IsRecovery")==0) return base+6;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *CsaHostPkDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "long",
        "int",
        "string",
        "int",
        "int",
        "RepetionPoint",
        "bool",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : nullptr;
}

const char **CsaHostPkDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *CsaHostPkDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int CsaHostPkDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    CsaHostPk *pp = (CsaHostPk *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CsaHostPkDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    CsaHostPk *pp = (CsaHostPk *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getPkId());
        case 1: return long2string(pp->getHostId());
        case 2: return oppstring2string(pp->getHostPath());
        case 3: return long2string(pp->getSlotIndex());
        case 4: return long2string(pp->getNumOfRepetions());
        case 5: {std::stringstream out; out << pp->getPoint(); return out.str();}
        case 6: return bool2string(pp->getIsRecovery());
        default: return "";
    }
}

bool CsaHostPkDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    CsaHostPk *pp = (CsaHostPk *)object; (void)pp;
    switch (field) {
        case 0: pp->setPkId(string2long(value)); return true;
        case 1: pp->setHostId(string2long(value)); return true;
        case 2: pp->setHostPath((value)); return true;
        case 3: pp->setSlotIndex(string2long(value)); return true;
        case 4: pp->setNumOfRepetions(string2long(value)); return true;
        case 6: pp->setIsRecovery(string2bool(value)); return true;
        default: return false;
    }
}

const char *CsaHostPkDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 5: return omnetpp::opp_typename(typeid(RepetionPoint));
        default: return nullptr;
    };
}

void *CsaHostPkDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    CsaHostPk *pp = (CsaHostPk *)object; (void)pp;
    switch (field) {
        case 5: return (void *)(&pp->getPoint()); break;
        default: return nullptr;
    }
}

} // namespace inet

