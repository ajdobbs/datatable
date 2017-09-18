#include "datatable/Table.hh"

#include <iostream>

void Table::AddStringProperty(Property<std::string>& aProperty) {
  mStringProperties.push_back(aProperty);
}

void Table::AddNumericProperty(Property<double>& aProperty) {
  mNumericProperties.push_back(aProperty);
}

void Table::ListProperties() {
  std::cout << "Table Properties: " << std::endl;
  std::cout << "  name (string)" << std::endl;
  for (auto& prop : mStringProperties) {
    std::cout << "  " << prop.Name() << " (string)" << std::endl;
  }
  for (auto& prop : mNumericProperties) {
    std::cout << "  " << prop.Name() << " (double)" << std::endl;
  }
}
