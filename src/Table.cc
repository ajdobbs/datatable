#include "datatable/Table.hh"

#include <iostream>

bool Table::AddEntry(const std::string& aName, const std::vector<std::string>& aStringProperties,
                     const std::vector<double>& aNumericProperties) {
  // Check input format is correct
  if (aStringProperties.size() != mStringProperties.size() &&
      aNumericProperties.size() != mNumericProperties.size()) {
    std::cerr << "Failed to add entry, require " << mStringProperties.size()
              << "string entries and " << mNumericProperties.size() << " numeric entries\n";
    return false;
  }

  // Add the data
  mNames.push_back(aName);
  for (size_t i = 0; i < mStringProperties.size(); ++i) {
    mStringProperties[i].AddDataEntry(aStringProperties[i]);
  }
  for (size_t i = 0; i < mNumericProperties.size(); ++i) {
    mNumericProperties[i].AddDataEntry(aNumericProperties[i]);
  }

  return true;
}

void Table::AddStringProperty(const Property<std::string>& aProperty) {
  mStringProperties.push_back(aProperty);
}

void Table::AddNumericProperty(const Property<double>& aProperty) {
  mNumericProperties.push_back(aProperty);
}

void Table::PrintData() {
  PrintProperties();
  for (size_t iRow = 0; iRow < mNames.size(); ++iRow) {
    std::cout << mNames[iRow] << " ";
    for (size_t iStrCol = 0; iStrCol < mStringProperties.size(); ++iStrCol) {
      std::cout << " " << mStringProperties[iStrCol].GetDataEntry(iRow);
    }
    for (size_t iNumCol = 0; iNumCol < mNumericProperties.size(); ++iNumCol) {
      std::cout << " " << mNumericProperties[iNumCol].GetDataEntry(iRow);
    }
    std::cout << std::endl;
  }
}

void Table::PrintProperties() {
  std::cout << "name(string)";
  for (auto& prop : mStringProperties) {
    std::cout << " " << prop.Name() << "(string)";
  }
  for (auto& prop : mNumericProperties) {
    std::cout << " " << prop.Name() << "(double)";
  }
  std::cout << std::endl;
}
