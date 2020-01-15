#include <vector>
#include <random>

//TODO CHCEMY ZAIMPLEMENTOWAC WZORZEC 'COMPOSITE'

//TODO JAK TO ZROBIC ZEBY DO DO PLAYLISTY ODWOLYWALO SIE PRZEZ ->


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
    virtual void play(const std::vector<Composite> &composites) = 0;
};


class SequenceMode : public PlayMode
{
    void play(const std::vector<Composite> &composites)
    {
        for (Composite composite: composites)
        {
            composite.play();
        }
    }
};

class ShuffleMode : public PlayMode
{
public:
    ShuffleMode(int seed);

    void play(const std::vector<Composite> &composites);

private:
    std::default_random_engine e;
};

class OddEvenMode : public PlayMode
{
    void play(const std::vector<Composite> &composites);
};

class File : public Composite
{
    void
    play() override = 0; //TODO Clang krzyczy ze zamiast virtual ma byc override
};

class Song : public File
{
public:
    void play();
};

class Movie : public File
{
public:
    void play();
};

class Playlist : public Composite
{
public:

    Playlist(std::string name)
    {
        this->name = name;
        this->mode = SequenceMode();
    }

    void add(Composite composite)
    {
        composites.push_back(composite);
    }

    void add(const Composite composite, unsigned int position)
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

    void setMode(PlayMode mode)
    {
        this->mode = mode;
    }

    void play();

private:
    std::string name;
    std::vector<Composite> composites;
    PlayMode mode;
};

class Player
{
public:
    File openFile(File file);

    Playlist createPlaylist(std::string name)
    {
        return Playlist(name);
    }
};

ShuffleMode createShuffleMode(
        int seed) //TODO Nwm czy to powinno tak latać w przestrzeni, pewnie nie :v
{
    return ShuffleMode(seed);
}

OddEvenMode createOddEvenMode() //TODO Nwm czy to powinno tak latać w przestrzeni, pewnie nie :v
{
    return OddEvenMode();
}

SequenceMode createSequenceMode() //TODO Nwm czy to powinno tak latać w przestrzeni, pewnie nie :v
{
    return SequenceMode();
}