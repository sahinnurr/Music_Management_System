#include "song.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>


int main()
{
    struct Song *songs=NULL;
    int numSongs = 0;
    int user_year;
    int operation=-1;

    readFile("spotify2023.csv", &songs, &numSongs);


    printf("Please choose an operation (to stop making operations press 0):\n");
    while(operation!=0){
        printf("\n-To show the song with the highest streams in the year you give press 1\n");
        printf("-To show the song with the lowest streams in the year you give press 2\n"); 
        printf("-To add songs press 3\n");
        printf("-To remove songs press 4\n");
        printf("-To search by released year press 5\n");
        printf("-To search by artist press 6\n");
        printf("-To search by name press 7\n");
        printf("-To get a suggested song 8\n");
        printf("-To create a playlist press 9\nOperation:");

        scanf("%d",&operation);

        if(operation==1){
            printf("Enter the year to find the most streamed song: ");
            scanf("%d", &user_year);
            findMostStreamedSong(songs, numSongs, user_year);
        }else if(operation==2){
            printf("Enter the year to find the least streamed song: ");
            scanf("%d", &user_year);
            findLeastStreamedSong(songs, numSongs, user_year);
        }else if(operation==3){
            addSong(&songs, &numSongs);
        }else if(operation==4){
            removeSongs(&songs, &numSongs);

        }else if(operation==5){
            printf("Enter a year to find the songs that relased in the year: ");
             scanf("%d", &user_year);
            findSongsByYear(songs, numSongs, user_year);
        }else if (operation == 6) {
              char artistName[100];
              printf("Enter the artist name to find songs: ");
              // Consume the newline character left in the buffer
              getchar();
              // Use fgets to read the whole line (including spaces) for the artist's name
              fgets(artistName, sizeof(artistName), stdin);

              // Remove the newline character from the end
              artistName[strcspn(artistName, "\n")] = '\0';
              findSongsByArtist(songs, numSongs, artistName);
        }else if(operation==7){
            char user_name_input[100];
            printf("Enter the track name to search: ");

            getchar();

            fgets(user_name_input, sizeof(user_name_input), stdin);
            user_name_input[strcspn(user_name_input, "\n")] = '\0';
            findSongByName(songs, numSongs, user_name_input);
        }else if(operation==8){
            int user_choice;
                // Prompt the user to choose a feature
            printf("What kind of song do you want to listen?\n");
            printf("0 - Danceable\n");
            printf("1 - Energetic\n");
            printf("2 - Acoustic\n");
            printf("3 - Instrumental\n");
            printf("4 - Live\n");
            printf("5 - Speechfull\n");
            printf("Your choice: ");
            scanf("%d", &user_choice);
            findTopSong(songs, numSongs, user_choice);
        }else if (operation == 9) {
            char playlist_name[100];
            printf("playlist name:");
            scanf("%s",playlist_name);
            create_playlist(songs,numSongs, playlist_name);

        }else if(operation ==0){
            printf("Operations done\n");
        }else{
            printf("Invalid operation number\n");

        }
    }
        freesong(&songs);
        return 0;

}