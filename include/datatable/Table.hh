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

    // An alternative to these two functions would be one template function
    std::string GetStringProperty(int row, std::string& name);
    double GetNumericProperty(int row, std::string& name);

    std::vector<std::string> GetEntryNames() { return mEntryNames; }
    std::vector<std::string> GetStringPropertyNames() const;
    std::vector<std::string> GetNumericPropertyNames() const;

    // Do not like returning refs to members, but will do for now
    std::vector<Property<std::string> >& GetStringProperties() { return mStringProperties; }
    std::vector<Property<double> >& GetNumericProperties() { return mNumericProperties; }

    void PrintData();
    void PrintProperties();

    Table Union(const Table& aTable);

  private:
    std::vector<std::string> mEntryNames;
    std::vector<Property<std::string> > mStringProperties;
    std::vector<Property<double> > mNumericProperties;
};

#endif
