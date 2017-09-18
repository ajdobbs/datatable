#ifndef TABLE_HH
#define TABLE_HH

#include <string>
#include <vector>

#include "datatable/Property.hh"

class Table {
  public:
    Table() {};
    virtual ~Table() {};

    void AddStringProperty(Property<std::string>& aProperty);
    void AddNumericProperty(Property<double>& aProperty);

    void ListProperties();

  private:
    std::vector<std::string> mNames;
    std::vector<Property<std::string> > mStringProperties;
    std::vector<Property<double> > mNumericProperties;
};

#endif
