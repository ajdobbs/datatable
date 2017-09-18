#include "datatable/Table.hh"

#include <iostream>
#include <cmath>

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
  mEntryNames.push_back(aName);
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

std::string Table::GetStringProperty(int row, std::string& name) {
  std::string result = "";
  if (row >= static_cast<int>(mEntryNames.size()))
    return "";
  for (auto prop : mStringProperties) {
    if (name == prop.Name()) {
      result = prop.GetDataEntry(row);
    }
  }
  return result;
}

double Table::GetNumericProperty(int row, std::string& name) {
  double result = nan("");
  if (row >= static_cast<int>(mEntryNames.size()))
    return nan("");
  for (auto prop : mNumericProperties) {
    if (name == prop.Name()) {
      result = prop.GetDataEntry(row);
    }
  }
  return result;
}

void Table::PrintData() {
  PrintProperties();
  for (size_t iRow = 0; iRow < mEntryNames.size(); ++iRow) {
    std::cout << mEntryNames[iRow] << " ";
    for (size_t iStrCol = 0; iStrCol < mStringProperties.size(); ++iStrCol) {
      std::cout << " " << mStringProperties[iStrCol].GetDataEntry(iRow);
    }
    for (size_t iNumCol = 0; iNumCol < mNumericProperties.size(); ++iNumCol) {
      std::cout << " " << mNumericProperties[iNumCol].GetDataEntry(iRow);
    }
    std::cout << std::endl;
  }
}

std::vector<std::string> Table::GetStringPropertyNames() const {
  std::vector<std::string> names;
  for (auto prop : mStringProperties) {
    names.push_back(prop.Name());
  }
  return names;
}

std::vector<std::string> Table::GetNumericPropertyNames() const {
  std::vector<std::string> names;
  for (auto prop : mNumericProperties) {
    names.push_back(prop.Name());
  }
  return names;
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

Table Table::Union(const Table& aTable) {
  Table result;
  // Add properties from current table
  for (std::string prop : GetStringPropertyNames()) {
    result.AddStringProperty(Property<std::string>(prop));
  }
  for (std::string prop : GetNumericPropertyNames()) {
    result.AddNumericProperty(Property<double>(prop));
  }

  // Add any additional properties from argument table
  for (std::string prop : aTable.GetStringPropertyNames()) {
    bool existing_prop = false;
    for (std::string prop2 : result.GetStringPropertyNames()) {
      if (prop == prop2)
        existing_prop = true;
    }
    if (!existing_prop)
      result.AddStringProperty(Property<std::string>(prop));
  }
  for (std::string prop : aTable.GetNumericPropertyNames()) {
    bool existing_prop = false;
    for (std::string prop2 : result.GetNumericPropertyNames()) {
      if (prop == prop2) {
        existing_prop = true;
      }
    }
    if (!existing_prop)
      result.AddNumericProperty(Property<double>(prop));
  }

  // Add rows from the current table
  for (size_t iRow = 0; iRow < mEntryNames.size(); ++iRow) {
    // Add the row name
    result.mEntryNames.push_back(mEntryNames[iRow]);
    // Add string properties
    for (size_t iCol = 0; iCol < result.mStringProperties.size(); ++iCol) {
      bool prop_found = false;
      for (auto current_table_prop : mStringProperties) {
        if (result.mStringProperties[iCol].Name() == current_table_prop.Name()) {
          result.mStringProperties[iCol].AddDataEntry(current_table_prop.GetDataEntry(iRow));
          prop_found = true;
          break;
        }
      }
      if (!prop_found)
        result.mStringProperties[iCol].AddDataEntry("null");
    }
    // Add numeric properties
    for (size_t iCol = 0; iCol < result.mNumericProperties.size(); ++iCol) {
      bool prop_found = false;
      for (auto current_table_prop : mNumericProperties) {
        if (result.mNumericProperties[iCol].Name() == current_table_prop.Name()) {
          result.mNumericProperties[iCol].AddDataEntry(current_table_prop.GetDataEntry(iRow));
          prop_found = true;
          break;
        }
      }
      if (!prop_found)
        result.mNumericProperties[iCol].AddDataEntry(nan(""));
    }
  }
  result.PrintData();

  // Add rows from argument table
  for (size_t iRow = 0; iRow < aTable.mEntryNames.size(); ++iRow) {
    // Add the row name if not already in the table
    bool row_present = false;
    int result_row = 0;

    for (size_t iResultRow = 0; iResultRow < result.mEntryNames.size(); ++iResultRow) {
      if (result.mEntryNames[iResultRow] == aTable.mEntryNames[iRow]) {
        result_row = iResultRow;
        row_present = true;
        break;
      }
    }
    if (!row_present) {// That is, this is a new row for the result table
      result.mEntryNames.push_back(aTable.mEntryNames[iRow]);
      result_row = result.mEntryNames.size() - 1;
    }

    // Add string properties
    for (size_t iCol = 0; iCol < result.mStringProperties.size(); ++iCol) {
      bool matched_property = false;
      for (auto current_table_prop : aTable.mStringProperties) {
        if (result.mStringProperties[iCol].Name() == current_table_prop.Name()) {
          matched_property = true;
          if (!row_present) {
            result.mStringProperties[iCol].AddDataEntry(current_table_prop.GetDataEntry(iRow));
          } else {
            result.mStringProperties[iCol].SetDataEntry(result_row, current_table_prop.GetDataEntry(iRow));
          }
          break;
        }
      }
      // Check for new row and but argument table doesn't have this property, if so add null entry
      if (!matched_property && !row_present) {
        result.mStringProperties[iCol].AddDataEntry("null");
      }
    }
    // Add numeric properties
    for (size_t iCol = 0; iCol < result.mNumericProperties.size(); ++iCol) {
      bool matched_property = false;
      for (auto current_table_prop : aTable.mNumericProperties) {
        if (result.mNumericProperties[iCol].Name() == current_table_prop.Name()) {
          matched_property = true;

          if (!row_present) {
            result.mNumericProperties[iCol].AddDataEntry(current_table_prop.GetDataEntry(iRow));
          } else {
            result.mNumericProperties[iCol].SetDataEntry(result_row, current_table_prop.GetDataEntry(iRow));
          }
          break;
        }
      }
      // Check for new row and but argument table doesn't have this property, if so add null entry
      if (!matched_property && !row_present) {
        result.mNumericProperties[iCol].AddDataEntry(nan(""));
      }
    }
  }

  return result;
}
