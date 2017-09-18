#include <string>

#include "datatable/PropertyBase.hh"
#include "datatable/Property.hh"
#include "datatable/Table.hh"

int main() {
  Property<std::string> string_prop1("string_prop1");
  Property<std::string> string_prop2("string_prop2");
  Property<std::string> string_prop3("string_prop3");
  Property<double> numeric_prop1("numeric_prop1");
  Property<double> numeric_prop2("numeric_prop2");

  Table table1;
  table1.AddStringProperty(string_prop1);
  table1.AddStringProperty(string_prop2);
  table1.AddNumericProperty(numeric_prop1);
  table1.AddEntry("drug1", {"sp11", "sp12"}, {11.0});
  table1.AddEntry("drug2", {"sp21", "sp22"}, {21.0});

  Table table2;
  table2.AddStringProperty(string_prop2);
  table2.AddStringProperty(string_prop3);
  table2.AddNumericProperty(numeric_prop2);
  table2.AddNumericProperty(numeric_prop1);
  table2.AddEntry("drug1", {"sp12", "sp13"}, {11.0, 12.0});
  table2.AddEntry("drug3", {"sp32", "sp33"}, {31.0, 32.0});
  table2.AddEntry("drug4", {"sp42", "sp43"}, {41.0, 42.0});

  Table table3 = table1.Union(table2);

  // table1.PrintData();
  // table2.PrintData();
  table3.PrintData();

  return 0;
};
