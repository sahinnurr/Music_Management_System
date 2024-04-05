#include "song.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

void readFile(char *filename, struct Song **songs, int *numSongs)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }
    const int initialCapacity = 300;
    *songs = (struct Song *)malloc(initialCapacity * sizeof(struct Song)); 

    if (*songs == NULL) {
        printf("Memory allocation error.\n");
        exit(1);
    }

    char line[1000];
    int index = 0;

    fgets(line, sizeof(line), file); // Read and ignore the header line

    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, ";");
        while (token != NULL) {
            //seperate each string and assign it to xorrect index of songs array 
            strcpy((*songs)[index].track_name, token);
            token = strtok(NULL, ";");  //get to the next token
            strcpy((*songs)[index].artist_name, token);
            token = strtok(NULL, ";");
            (*songs)[index].artist_count = atoi(token);
            token = strtok(NULL, ";");
            (*songs)[index].released_year = atoi(token);
            token = strtok(NULL, ";");
            (*songs)[index].streams = atol(token);
            token = strtok(NULL, ";");
            (*songs)[index].danceability = atoi(token);
            token = strtok(NULL, ";");
            (*songs)[index].energy = atoi(token);
            token = strtok(NULL, ";");
            (*songs)[index].acousticness = atoi(token);
            token = strtok(NULL, ";");
            (*songs)[index].instrumentalness = atoi(token);
            token = strtok(NULL, ";");
            (*songs)[index].liveness = atoi(token);
            token = strtok(NULL, ";");
            (*songs)[index].speechiness = atoi(token);

            index++; //increment index when each line is seperated
            token = strtok(NULL, ";");
        }
    }

    *numSongs = index;
    fclose(file);
}
void freesong(struct Song **songs)
{

    free(*songs);
}

//a method to show the song with the highest streams in the year given by user
void findMostStreamedSong(struct Song *songs, int numSongs, int year){

long int max_stream = 0;
int max_index = -1;

for(int i = 0; i<numSongs; i++ ){
    if(songs[i].released_year == year && songs[i].streams>max_stream) {
        max_stream = songs[i].streams;
        max_index = i;        
    }
}

if(max_index != -1){ //check if a value found in that specified index
    printf("Song with the highest streams in %d is %s by %s\n", year,songs[max_index].track_name, songs[max_index].artist_name  );
    printf("The stream of the song: %ld\n", songs[max_index].streams );
}else{ //if there is not  a match
    printf("It is not a valid year or exists in table\n");
}
}

//a method to show the song with the lowest streams in the year given by user
void findLeastStreamedSong(struct Song *songs, int numSongs, int year){

long int min_stream = LONG_MAX;
int min_index = -1;

for(int i = 0; i<numSongs; i++ ){
    if(songs[i].released_year == year && songs[i].streams<min_stream ) {
        min_stream = songs[i].streams;
        min_index = i;        
    }
}

if(min_index != -1){
    printf("Song with the lowest streams in %d is %s by %s\n", year,songs[min_index].track_name, songs[min_index].artist_name  );
    printf("The stream of the song: %ld\n", songs[min_index].streams );
}else{
    printf("It is not a valid year or exists in table\n");
}
}


//This method finds the song according to the song name received from the user and shows it to the user with all its features
void findSongByName(struct Song *songs, int numSongs, const char *user_name_input) {

    bool match_found;

    for (int i = 0; i < numSongs; i++) {
        if (strcasecmp(songs[i].track_name, user_name_input) == 0) {
            //strcasecmp is case insensitive string comparator 
            match_found=true; //if there are a match
            printf("Song found at index %d\n", i);
            printf("Track: %s, Artist: %s, Streams: %ld, Danceability percentage: %d, Energy percentage: %d, Acousticness percentage: %d, Instrumentalness percentage: %d, Liveness percentage: %d,Speechiness percentage: %d\n", songs[i].track_name, songs[i].artist_name, songs[i].streams, songs[i].danceability,songs[i].energy, songs[i].acousticness,songs[i].instrumentalness,songs[i].liveness,songs[i].speechiness);
            printf("\n");
        }
    }
            if(match_found==false){ //if there is not a match
            printf("Sorry, the song not found\n");
            }
            printf("\n");
    
    
}

void findSongsByYear(struct Song *songs, int numSongs, int year) {
    printf("Songs released in %d:\n", year);
    int found = 0;
    int song_num=0;
    for (int i = 0; i < numSongs; i++) {
        if (songs[i].released_year == year) {
            printf("Track: %s, Artist: %s, Streams: %ld\n", songs[i].track_name, songs[i].artist_name, songs[i].streams);
            found = 1;
            song_num++;
        }
    }
    printf("The total number of songs with the same released year: %d \n",song_num);
    if (!found) {
        printf("No songs found for the year %d\n", year);
    }
}

void findSongsByArtist(struct Song *songs, int numSongs, const char *artistName) {
    printf("Songs by %s:\n", artistName);
    int found = 0;
    int song_num = 0;

    char *token = strtok((char *)artistName, ",");
    while (token != NULL) {
        char trimmedToken[100];
        sscanf(token, " %99[^\n]", trimmedToken);
// tokenizes the input artist name by commas because in some songs there are multiple artists
        for (int i = 0; i < numSongs; i++) {
            // Split the song's artist names using strtok
            char songArtist[100];
            strcpy(songArtist, songs[i].artist_name);
            char *songToken = strtok(songArtist, ",");
            while (songToken != NULL) { // trims leading and trailing whitespaces from each token
                char trimmedSongToken[100];
                sscanf(songToken, " %99[^\n]", trimmedSongToken);

                if (strcasecmp(trimmedSongToken, trimmedToken) == 0) {
                    printf("Track: %s, Released Year: %d, Streams: %ld\n", songs[i].track_name, songs[i].released_year, songs[i].streams);
                    found = 1;
                    song_num++;
                    break;  // No need to continue checking once a match is found for the current token
                }

                songToken = strtok(NULL, ",");
            }
        }

        token = strtok(NULL, ",");
    }

    printf("Total number of songs by %s: %d\n", artistName, song_num);
    if (!found) {
        printf("No songs found for the artist %s\n", artistName);
    }
}

void addSong(struct Song **songs, int *numSongs)
{

    FILE *file = fopen("spotify2023.csv", "a");
    *songs = realloc(*songs, (*numSongs + 1) * sizeof(struct Song)); 
    printf("Enter the details of the new song (track_name;artist_name; artist_count;released_year;streams;danceability;energy;acousticness;instrumentalness;liveness;speechiness):\n");

     // Parse the input and assign values to the new song
    scanf( "%99[^;];%99[^;];%d;%d;%ld;%d;%d;%d;%d;%d;%d",
           (*songs)[*numSongs].track_name,
           (*songs)[*numSongs].artist_name,
           &(*songs)[*numSongs].artist_count,
           &(*songs)[*numSongs].released_year,
           &(*songs)[*numSongs].streams,
           &(*songs)[*numSongs].danceability,
           &(*songs)[*numSongs].energy,
           &(*songs)[*numSongs].acousticness,
           &(*songs)[*numSongs].instrumentalness,
           &(*songs)[*numSongs].liveness,
           &(*songs)[*numSongs].speechiness);

     fprintf(file, "%s;%s;%d;%d;%ld;%d;%d;%d;%d;%d;%d\n",
            (*songs)[*numSongs].track_name,
            (*songs)[*numSongs].artist_name,
            (*songs)[*numSongs].artist_count,
            (*songs)[*numSongs].released_year,
            (*songs)[*numSongs].streams,
            (*songs)[*numSongs].danceability,
            (*songs)[*numSongs].energy,
            (*songs)[*numSongs].acousticness,
            (*songs)[*numSongs].instrumentalness,
            (*songs)[*numSongs].liveness,
            (*songs)[*numSongs].speechiness);

    (*numSongs)++;
    printf("Song added successfully!\n");
    fclose(file);
}
void removeSongs(struct Song **songs, int *numSongs) {
    char trackToRemove[100];

    printf("Enter the track name of the song to remove: ");
    scanf("%99s", trackToRemove);

    int foundIndex = -1;

    // Find the index of the song to remove
    for (int i = 0; i < *numSongs; i++) {
        if (strcasecmp((*songs)[i].track_name, trackToRemove) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        // Shift elements to fill the gap
        for (int i = foundIndex; i < *numSongs - 1; i++) {
            (*songs)[i] = (*songs)[i + 1];
        }

        (*numSongs)--;

        // Reallocate memory to adjust the size
        *songs = realloc(*songs, *numSongs * sizeof(struct Song));
        if (*songs == NULL) {
            printf("Memory reallocation error.\n");
            exit(1);
        }

        printf("Song removed successfully!\n");
    } else {
        printf("Song not found.\n");
    }
}


void findTopSong(struct Song *songs, int numSongs, int feature) {
    if (feature < 0 || feature > 6) {
        printf("Invalid feature selection.\n");
        return;
    }

    int max_index = -1;
    int max_value = INT_MIN;

    for (int i = 0; i < numSongs; i++) {
        int current_value = 0;
        switch (feature) {
            case 0:
                current_value = songs[i].danceability;
                break;
            case 1:
                current_value = songs[i].energy;
                break;
            case 2:
                current_value = songs[i].acousticness;
                break;
            case 3:
                current_value = songs[i].instrumentalness;
                break;
            case 4:
                current_value = songs[i].liveness;
                break;
            case 5:
                current_value = songs[i].speechiness;
                break;
        }

        if (current_value > max_value) {
            max_value = current_value;
            max_index = i;
        }
    }

    if (max_index != -1) {
        printf("Recommended song is: ");
        printf(": %s by %s\n", songs[max_index].track_name, songs[max_index].artist_name);
        printf("Feature value: %d\n", max_value);
    } else {
        printf("No songs found.\n");
    }
}


void create_playlist(struct Song *songs,int numSongs, const char *outputFileName)
{
    FILE *outputFile = fopen(outputFileName, "w");
    char user_song[100];
     int c;
        while ((c = getchar()) != '\n' && c != EOF);
    printf("Write the track name of the song you want to add in your playlist\nPress -1 to save and exit\n");
    

    while(1){
    fgets(user_song, sizeof(user_song), stdin);
    user_song[strcspn(user_song, "\n")] = '\0';

     if (strcmp(user_song, "-1") == 0) {
            break; 
        }
    bool match_found;

    for (int i = 0; i < numSongs; i++) {
        if (strcasecmp(songs[i].track_name, user_song) == 0) {
            match_found = true;
            fprintf(outputFile, "Track: %s, Artist: %s, Streams: %ld, Danceability percentage: %d, Energy percentage: %d, Acousticness percentage: %d, Instrumentalness percentage: %d, Liveness percentage: %d,Speechiness percentage: %d\n", songs[i].track_name, songs[i].artist_name, songs[i].streams, songs[i].danceability, songs[i].energy, songs[i].acousticness, songs[i].instrumentalness, songs[i].liveness, songs[i].speechiness);
            fprintf(outputFile, "\n");
            break;
            
        } else {
            match_found=false;
        }
    }

    if (match_found==false) {
        printf("Sorry, the song not found\n");
    }

    }

    fclose(outputFile);
}



