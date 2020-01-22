#include "exception.h"

const char* UnsupportedMediaType::what() const throw() {
  return "unsupported type";
}

const char* InvalidMetadata::what() const throw() {
  return "invalid metadata";
}

const char* CorruptedFile::what() const throw() {
  return "corrupt file";
}

const char* CycleFound::what() const throw() {
  return "cycle found";
}

const char* PlaylistOutOfRange::what() const throw() {
  return "position out of range";
}

const char* CorruptedContent::what() const throw() {
  return "corrupt content";
}

const char* YearNotANumber::what() const throw() {
    return "year is not a number";
}