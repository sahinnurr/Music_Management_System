#ifndef SONG_H
#define SONG_H

struct Song {
    char track_name[100];
    char artist_name[100];
    int artist_count;
    int released_year;
    long int streams;
    int danceability;
    int energy;
    int acousticness;
    int instrumentalness;
    int liveness;
    int speechiness;
};

void readFile(char *filename, struct Song **songs, int *numSongs);
void freesong(struct Song **songs);
void findMostStreamedSong(struct Song *songs, int numSongs, int year);
void findLeastStreamedSong(struct Song *songs, int numSongs, int year);
void findSongsByYear(struct Song *songs, int numSongs, int year);
void findSongsByArtist(struct Song *songs, int numSongs, const char *artistName);
void addSong(struct Song **songs, int *numSongs);
void removeSongs(struct Song **songs, int *numSongs);
void findSongByName(struct Song *songs, int numSongs, const char *user_name_input);
void findTopSong(struct Song *songs, int numSongs, int feature);
void create_playlist(struct Song *songs, int numSongs, const char *outputFileName);

#endif  // SONG_H
