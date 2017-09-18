#ifndef PROPERTY_HH
#define PROPERTY_HH

#include <string>
#include <vector>

#include "datatable/PropertyBase.hh"

template <class T>
class Property : public PropertyBase {
  public:
    Property(const std::string& aName) : PropertyBase{aName} {};
    virtual ~Property() {};

    void AddDataEntry(const T& aEntry) { mData.push_back(aEntry); }
    T GetDataEntry(int i) { return mData[i]; }

  private:
    std::vector<T> mData;
};

#endif
