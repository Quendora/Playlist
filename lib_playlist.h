#include <utility>
#include <vector>
#include <random>
#include <memory>
#include <algorithm>

//TODO (INFO) IMPLEMENTUJEMY ZAIMPLEMENTOWAC WZORZEC 'COMPOSITE'

class PlayerException : std::exception
{
public:
    //FIXME Jak zamiast override wpisze virtual to Clang krzyczy
    [[nodiscard]] const char *what() const noexcept override = 0;
};

class Composite
{
public:
    virtual void play() = 0;
};

class PlayMode
{
public:
    virtual void play(const std::vector<std::shared_ptr<Composite>> &composites) = 0;
};


class SequenceMode : public PlayMode
{
public:
    void play(const std::vector<std::shared_ptr<Composite>> &composites) override
    {
        for (const std::shared_ptr<Composite>& composite: composites)
        {
            composite->play();
        }
    }
};

class ShuffleMode : public PlayMode
{
public:
    ShuffleMode(int seed) : seed(seed) {}

    void play(const std::vector<std::shared_ptr<Composite>> &composites) override
    {   
        std::shuffle(composites.begin(), composites.end(), std::default_random_engine(seed));
        for(const auto& comp: composites) {
            comp->play();
        }
    }

private:
    int seed;
};

class OddEvenMode : public PlayMode
{
public:
    void play(const std::vector<std::shared_ptr<Composite>> &composites) override
    {
        for (unsigned long i = 1; i < composites.size(); i += 2)
        {
            composites[i]->play();
        }

        for (unsigned long i = 0; i < composites.size(); i += 2)
        {
            composites[i]->play();
        }
    }
};

class File : public Composite
{
    void
    play() override = 0; //TODO Clang krzyczy ze zamiast virtual ma byc override
};

class Song : public File
{
public:
    void play() override
    {

    }
};

class Movie : public File
{
public:
    void play() override
    {

    }
};

class Playlist : public Composite
{
public:

    explicit Playlist(std::string playListName)
    {
        // czy tutaj moze byc move
        this->name = std::move(playListName);
        this->mode = std::make_shared<SequenceMode>();
    }

    void add(const std::shared_ptr<Composite>& composite)
    {
        composites.push_back(composite);
    }

    void add(const std::shared_ptr<Composite>& composite, unsigned int position)
    {
        composites.insert(composites.begin() + position, composite);
    }

    void remove()
    {
        composites.pop_back();
    }

    void remove(unsigned int position)
    {
        composites.erase(composites.begin() + position);
    }

    void setMode(std::shared_ptr<PlayMode> playMode)
    {
        //czy tutaj moze byc move
        this->mode = std::move(playMode);
    }

    void play() override
    {
        mode->play(composites);
    }

private:
    std::string name;
    std::vector<std::shared_ptr<Composite>> composites;
    std::shared_ptr<PlayMode> mode;
};

class Player
{
public:
    File openFile(File file);

    std::shared_ptr<Playlist> createPlaylist(std::string name)
    {
        //tczy tutaj moze byc move
        return std::make_shared<Playlist>(Playlist(std::move(name)));
    }
};

std::shared_ptr<ShuffleMode> createShuffleMode(int seed)
{
    return std::make_shared<ShuffleMode>(seed);
}

std::shared_ptr<OddEvenMode> createOddEvenMode()
{
    return std::make_shared<OddEvenMode>();
}

std::shared_ptr<SequenceMode> createSequenceMode()
{
    return std::make_shared<SequenceMode>();
}