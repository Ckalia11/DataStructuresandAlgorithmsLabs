// Group Members:
//Chetan Kalia 20771400
//Sasi Priya 
// 2020/01/16


#include <iostream>
#include <vector>
#include <algorithm>
#include<time.h>
#include <cstdlib>  

using namespace std;

class Music {
private:
    string artist_name, music_id;
    unsigned int made_year;

public:
    Music()
    {
        made_year = 0;
    }
    Music(string art_name, unsigned int year, string id)
    {
        artist_name = art_name;
        made_year = year;
        music_id = id;
    }

    string get_artist() {
        return artist_name;
    }

    void operator==(const Music &other_music) {
        artist_name = other_music.artist_name;
        made_year = other_music.made_year;
        music_id = other_music.music_id;
    }
};

class Song : public Music {
private:
    string genre;
    string name;
    unsigned int length;

public:
    Song() {
        length = 0;
    }

    string get_name() {
        return name;
    }

    Song(string incoming_genre, string incoming_name, unsigned int incoming_length, string incoming_artist_name, unsigned int incoming_madeYear, string incoming_musicId): Music(incoming_artist_name, incoming_madeYear, incoming_musicId) {
        genre = incoming_genre;
        name = incoming_name;
        length = incoming_length;
    }

    bool operator==(const Song& other_song) {
            if (genre == other_song.genre &&
                name == other_song.name &&
                length == other_song.length) {
                return true;
            }
            else {
                return false;
            }
        }
};

class Playlist {
public:
    vector<Song> songs;

    friend Playlist operator+(const Playlist& play1, const Playlist& play2);
    
    bool insert_song(Song& song_info) {
        bool flag = true;
        int counter = 0;

        for (auto song : songs) {
            // checking if two song objects are the same
            bool is_equal = song_info == song;
            if (is_equal) {
                return false;
            }

            if (song.get_artist() == song_info.get_artist()) {
                counter++;
            }

            if (counter >= 3) {
                return false;
            }
        }

            if (flag) {
                songs.push_back(song_info);
            }

        return flag;
    }

    Playlist shuffle_songs() {

        Playlist shuffle;

        for (unsigned int i = 0; i < this->songs.size(); ++i) {
            shuffle.songs.push_back(this->songs[i]);
        }

        for (unsigned int i = 0; i < shuffle.songs.size(); ++i) {
            int random = rand() % shuffle.songs.size();
            Song s1 = shuffle.songs[i];
            shuffle.songs[i] = shuffle.songs[random];
            shuffle.songs[random] = s1;

        }

        return shuffle;
    }
};

//non-member friend overloaded operator
Playlist operator+(const Playlist& play1, const Playlist& play2) {
    Playlist sum;

    for (unsigned int i = 0; i < play1.songs.size(); ++i) {
        sum.songs.push_back(play1.songs[i]);
    }

    for (unsigned int i = 0; i < play2.songs.size(); ++i) {
        sum.songs.push_back(play2.songs[i]);
    }

    return sum;
}

// Test functions
class Test {

public: 
    // should not be able to insert two same song instances
    void test_insert_same_song() {
        Song song1("pop", "beggin", 20, "Ralph", 2017, "beg");
        Song song2("pop", "beggin", 20, "Ralph", 2017, "beg");
        Song song3("rock", "window", 35, "Lauren", 2019, "wind");
        Playlist play1;
        play1.insert_song(song1);
        bool is_insert = play1.insert_song(song2);
        cout << "was able to add duplicate song : " << is_insert << endl;
        is_insert = play1.insert_song(song3);
        cout << "was able to add different song : " << is_insert << endl;
        
    }


    // same artist name, non-identical song objects
    void test_insert_same_artist() {
        Song song1("a", "song", 1, "aritst_name", 10, "music_id");
        Song song2("b", "song", 1, "aritst_name", 10, "music_id");
        Song song3("c", "song", 1, "aritst_name", 10, "music_id");
        Song song4("d", "song", 1, "aritst_name", 10, "music_id");
        Playlist play1;
        bool is_insert = play1.insert_song(song1);
        cout << "song with same artist added to vector : " << is_insert << endl;
        is_insert = play1.insert_song(song2);
        cout << "song with same artist added to vector : " << is_insert << endl;
        is_insert = play1.insert_song(song3);
        cout << "song with same artist added to vector : " << is_insert << endl;
        is_insert = play1.insert_song(song4);
        cout << "song with same artist added to vector : " << is_insert << endl;
    }
    // 4 different artist names and no duplicates
    void test_shuffle_song() {
        Song song1("a", "song_1", 1, "a", 10, "music_id");
        Song song2("b", "song_2", 1, "b", 10, "music_id");
        Song song3("c", "song_3", 1, "c", 10, "music_id");
        Song song4("d", "song_4", 1, "d", 10, "music_id");
        Playlist play1;
        bool is_insert = true;
        is_insert = play1.insert_song(song1);
        is_insert = play1.insert_song(song2);
        is_insert = play1.insert_song(song3);
        is_insert = play1.insert_song(song4);
        
        cout << "the original vector of song instances is : " << endl;
        for (unsigned int i = 0; i < play1.songs.size(); ++i) {
            cout << play1.songs[i].get_name() << endl;
        }
        cout << "the shuffled playlist is : " << endl;
        Playlist shuffled = play1.shuffle_songs();
        for (unsigned int i = 0; i < shuffled.songs.size(); ++i) {
            cout << shuffled.songs[i].get_name() << endl;
        }

     }
};

int main(){
   
    Test t1;
    t1.test_insert_same_song();
    t1.test_insert_same_artist();
    srand(time(0));
    t1.test_shuffle_song();
}
