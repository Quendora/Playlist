#include "playable.h"
#include "exception.h"

#include <iostream>
#include <algorithm>
#include <regex>

Media::Media(const MetadataMap& metadata, const std::string& content)
  : content(content), metadata(metadata) {}

bool Media::checkForCycle(__attribute__((unused)) const Playable* const playable) const {
  return false;
}

Song::Song(const MetadataMap& metadata, const std::string& content)
  : Media(metadata, content) {
    if(this->metadata.find("title") == this->metadata.end() || this->metadata.find("artist") == this->metadata.end()) {
      throw InvalidMetadata();
    }
  }


Movie::Movie(const MetadataMap& metadata, const std::string& content)
  : Media(metadata, ROT13(content)) {
    if(this->metadata.find("title") == this->metadata.end() || this->metadata.find("year") == this->metadata.end()) {
      throw InvalidMetadata();
    }

    static std::regex regex("^-?[0-9]*$");
    std::smatch match;

    if (!std::regex_match(metadata.at("year"), match, regex))
    {
        throw YearNotANumber();
    }
  }

void Song::play() {
    std::cout << "Song [" + metadata["artist"] + ", " + metadata["title"] +
    "]: " + content << "\n";
}

void Movie::play() {
    std::cout << "Movie [" + metadata["title"] + ", " + metadata["year"] +
            "]: " + content << "\n";
}

std::string Movie::ROT13(const std::string& source) {
  std::string result;
  result.resize(source.length());

  std::transform(
    source.begin(), source.end(), result.begin(),
    [] (char c) -> char {
      if (!std::isalpha(c))
        return c;

      char const pivot = std::isupper(c) ? 'A' : 'a';
      return (c - pivot + 13) % 26 + pivot;
  });
  return result;
}