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
    int GetNEntries() const { return static_cast<int>(mData.size()); }
    bool SetDataEntry(int row, const T& aEntry);

  private:
    std::vector<T> mData;
};

template <class T>
bool Property<T>::SetDataEntry(int row, const T& aEntry) {
  if (row < mData.size()) {
    mData[row] = aEntry;
    return true;
  }
  return false;
};

#endif
