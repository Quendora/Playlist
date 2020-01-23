#pragma once

#include <unordered_map>

using MetadataMap = std::unordered_map<std::string, std::string>;

class Playable {
public:
  virtual ~Playable() = default;

  virtual void play() = 0;

  virtual bool checkForCycle(const Playable* const playable) const = 0;
};

class Media : public Playable {
public:
  Media(const MetadataMap& metadata, const std::string& content);
  virtual ~Media() = default;

  virtual void play() = 0;

protected:
  bool checkForCycle(const Playable* const playable) const override;

  std::string content;
  MetadataMap metadata;
};

class Song : public Media {
public:
  Song(const MetadataMap& metadata, const std::string& content);

  void play() override;
};

class Movie : public Media {
public:
  Movie(const MetadataMap& metadata, const std::string& content);

  void play() override;

private:
  std::string ROT13(const std::string& source);
};