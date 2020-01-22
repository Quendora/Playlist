#include "file.h"
#include "exception.h"

File::File(const std::string &fileString) {
  extractData(fileString);
}

std::string File::getType() const {
  return fileType;
}

MetadataMap File::getMetadata() const {
  return metadata;
}

std::string File::getContent() const {
  return content;
}

void File::extractData(const std::string& fileString) {
  static std::regex regex("^([^\\|]+)\\|(([^\\|]+:[^\\|]*\\|)*)([^\\|]*)$");
  static size_t typeGroup = 1, metadataGroup = 2, contentGroup = 4;
  std::smatch match;

  if(!std::regex_match(fileString, match, regex)) {
    throw CorruptedFile();
  }

  extractFileType(match.str(typeGroup));
  extractMetadata(match.str(metadataGroup));
  extractContent(match.str(contentGroup));
}

void File::extractFileType(const std::string& typeString) {
  fileType = typeString;
}

void File::extractMetadata(const std::string& metadataString) {
  static std::regex regex("([^\\|]+):([^\\|]*)");

  for(auto it = std::sregex_iterator(metadataString.begin(), metadataString.end(), regex);
   it != std::sregex_iterator(); it++) {
     std::smatch match = *it;
     std::string name = match.str(1);
     std::string value = match.str(2);

     metadata.insert_or_assign(name, value);
  }
}

void File::extractContent(const std::string& contentString) {
  static std::regex regex("^[a-zA-Z0-9\\s,.!':;\?\\-]*$");
  if(!std::regex_match(contentString, regex)) {
    throw CorruptedContent();
  }

  content = contentString;
}