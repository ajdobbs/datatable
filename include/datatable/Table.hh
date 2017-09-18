#ifndef TABLE_HH
#define TABLE_HH

#include <string>
#include <vector>

#include "datatable/Property.hh"

class Table {
  public:
    Table() {};
    virtual ~Table() {};

    bool AddEntry(const std::string& aName, const std::vector<std::string>& aStringProperties,
                  const std::vector<double>& aNumericProperties);
    void AddStringProperty(const Property<std::string>& aProperty);
    void AddNumericProperty(const Property<double>& aProperty);

    void PrintData();
    void PrintProperties();

  private:
    std::vector<std::string> mNames;
    std::vector<Property<std::string> > mStringProperties;
    std::vector<Property<double> > mNumericProperties;
};

#endif
