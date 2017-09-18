#ifndef PROPERTYBASE_HH
#define PROPERTYBASE_HH

#include <string>

class PropertyBase {
  public:
    PropertyBase(const std::string& aName) : mName{aName} {};
    virtual ~PropertyBase() {};

    std::string Name() const { return mName; }

  private:
    std::string mName;
};

#endif
