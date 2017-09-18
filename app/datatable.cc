#include <string>

#include "datatable/PropertyBase.hh"
#include "datatable/Property.hh"
#include "datatable/Table.hh"

int main() {
  Property<std::string> string_prop1("string_prop");
  Property<double> numeric_prop1("solubility");
  Table table1;
  table1.AddStringProperty(string_prop1);
  table1.AddNumericProperty(numeric_prop1);
  table1.ListProperties();

  return 0;
};
