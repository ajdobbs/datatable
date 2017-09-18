#include <string>

#include "datatable/PropertyBase.hh"
#include "datatable/Property.hh"
#include "datatable/Table.hh"

int main() {
  Property<std::string> string_prop1("string_prop1");
  Property<std::string> string_prop2("string_prop2");
  Property<double> numeric_prop1("numeric_prop1");
  Property<double> numeric_prop2("numeric_prop2");
  Table table1;
  table1.AddStringProperty(string_prop1);
  table1.AddStringProperty(string_prop2);
  table1.AddNumericProperty(numeric_prop1);
  table1.AddNumericProperty(numeric_prop2);

  std::vector<std::string> str_row1 {"sp11", "sp12"};
  std::vector<std::string> str_row2 {"sp21", "sp22"};
  std::vector<std::string> str_row3 {"sp31", "sp32"};
  std::vector<double> num_row1 {11.0, 12.0};
  std::vector<double> num_row2 {21.0, 22.0};
  std::vector<double> num_row3 {31.0, 32.0};

  table1.AddEntry("drug1", str_row1, num_row1);
  table1.AddEntry("drug2", str_row2, num_row2);
  table1.AddEntry("drug3", str_row3, num_row3);

  table1.PrintData();

  return 0;
};
