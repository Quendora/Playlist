#include "playmode.h"

void SequenceMode::play_mode(const std::vector<std::shared_ptr<Playable>> &playables) {
  for (const std::shared_ptr<Playable>& playable: playables) {
    playable->play();
  }
}

ShuffleMode::ShuffleMode(int seed) : random_engine(seed) {}

void ShuffleMode::play_mode(const std::vector<std::shared_ptr<Playable>> &playables) {   
  std::vector<size_t> indexes(playables.size());
  std::iota(indexes.begin(), indexes.end(), 0);

  std::shuffle(indexes.begin(), indexes.end(), random_engine);
  for(const auto& i: indexes) {
    playables[i]->play();
  }
}

void OddEvenMode::play_mode(const std::vector<std::shared_ptr<Playable>> &playables) {
  for (unsigned long i = 1; i < playables.size(); i += 2) {
    playables[i]->play();
  }

  for (unsigned long i = 0; i < playables.size(); i += 2) {
    playables[i]->play();
  }
}

std::shared_ptr<PlayMode> createShuffleMode(int seed) {
  return std::make_shared<ShuffleMode>(seed);
}

std::shared_ptr<PlayMode> createOddEvenMode() {
  return std::make_shared<OddEvenMode>();
  //std::shared_ptr<PlayMode> oddEvenMode = std::make_shared<OddEvenMode>();
  //return oddEvenMode;
}

std::shared_ptr<PlayMode> createSequenceMode() {
  return std::make_shared<SequenceMode>();
  //std::shared_ptr<PlayMode> seqMode = std::make_shared<SequenceMode>();
  //return seqMode;
}