#include "playable.h"

#include <iostream>
#include <algorithm>

Media::Media(const MetadataMap& metadata, const std::string& content)
  : content(content), metadata(metadata) {}

bool Media::checkForCycle(__attribute__((unused)) const Playable* const playable) const {
  return false;
}

Song::Song(const MetadataMap& metadata, const std::string& content)
  : Media(metadata, content) {
    if(this->metadata.find("title") == this->metadata.end() || this->metadata.find("year") == this->metadata.end()) {
      //throw exception
    }
  }


Movie::Movie(const MetadataMap& metadata, const std::string& content)
  : Media(metadata, ROT13(content)) {
    if(this->metadata.find("title") == this->metadata.end() || this->metadata.find("year") == this->metadata.end()) {
      //throw exception
    }
  }

void Song::play() {
  std::cout << "testing song: " << metadata["title"] << std::endl << content << std::endl;
}

void Movie::play() {
  std::cout << "testing movie: " << metadata["title"] << std::endl << content << std::endl;
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