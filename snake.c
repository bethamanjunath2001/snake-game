#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/select.h>
#include <time.h>

#define WIDTH 50
#define HEIGHT 20
#define LEFTGAP 50

typedef struct orderedpair{
	int x;
	int y;
}op;


// Function to set terminal to raw mode*************************************************************
void enableRawMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);  // Get current terminal attributes
    term.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &term);  // Apply the new settings
}

// Function to restore terminal to normal mode******************************************************
void disableRawMode() {                                                                             
    struct termios term;                                                                            
    tcgetattr(STDIN_FILENO, &term);                                                                 
    term.c_lflag |= (ICANON | ECHO);  // Re-enable canonical mode and echo                          
    tcsetattr(STDIN_FILENO, TCSANOW, &term);                                                        
}                                                                                                   
                                                                                                    
                                                                                                    
//Function to print an instant in the game**********************************************************
void snapshot(op coin, op* locus, int len, int dist, int score){

int update;

printf("\n");
for (int j=-LEFTGAP; j<0; j++){
	printf(" ");
}
for (int j=0; j<=WIDTH; j++){
	printf("_");
}
printf("\n");

for (int j=-LEFTGAP; j<0; j++){
	printf(" ");
}
printf("||                  SNAKE  XENIA                 ||\n");

for (int j=-LEFTGAP; j<0; j++){
	printf(" ");
}
for (int j=0; j<=WIDTH; j++){
	printf("\u203e");
}
printf("\n");
for (int j=-LEFTGAP; j<0; j++){
	printf(" ");
}
for (int j=0; j<=WIDTH; j++){
	printf("*");
}
printf("\n");
for (int j=-LEFTGAP; j<0; j++){
	printf(" ");
}
printf("DISTANCE: %5d                          SCORE: %3d\n", dist, score);

//printing the top boundary
for (int j=-LEFTGAP; j<0; j++){
	printf(" ");
}
for (int j=0; j<=WIDTH; j++){
	printf("_");
}
printf("\n");

//printing the space inbetween
for (int i=1; i<HEIGHT; i++){
	for (int j=-LEFTGAP; j<0; j++){
	printf(" ");
	}
	printf("|");
	for (int j=1; j<WIDTH; j++){
		if (locus[0].x == coin.x && locus[0].y == coin.y){
			if(i==locus[0].y && j==locus[0].x){
				printf("@");
			}else {
				update = 0;
				for (int k=len-1; k>0; k--){
					if (i==locus[k].y && j==locus[k].x){
						printf("O");
						update++;
						break;
					}
				}
				if (update==0){
					printf(" ");
				}
			}
		} else {
			if(i==locus[0].y && j==locus[0].x){
				printf("@");
			}else {
				update=0;
				for (int k=len-1; k>0; k--){
					if (i==locus[k].y && j==locus[k].x){
						printf("O");
						update++;
						break;
					}
					
				}
				if (update==0){
					if (i==coin.y && j==coin.x){
						printf("$");
					}else {
						printf(" ");
					}
				}
			}
		
		}
				
	}
	printf("|");
	printf("\n");
}

//printing the bottom boundary
for (int j=-LEFTGAP; j<0; j++){
	printf(" ");
}
for (int j=0; j<=WIDTH; j++){
	printf("\u203e");
}
printf("\n");

///////////////////////////////
for (int j=-LEFTGAP; j<(WIDTH/2)-2; j++){
	printf(" ");
}
printf("  ^\n");
for (int j=-LEFTGAP; j<(WIDTH/2)-2; j++){
	printf(" ");
}
printf("/_W_\\\n");
for (int j=-LEFTGAP; j<(WIDTH/2)-2; j++){
	printf(" ");
}
printf(" |_|\n\n");
///////////////////////////////
for (int j=-LEFTGAP; j<(WIDTH/3)-1; j++){
	printf(" ");
}
printf("  /|_   _|\u203e|_   _|\\\n");
for (int j=-LEFTGAP; j<(WIDTH/3)-1; j++){
	printf(" ");
}
printf("< A  |  \\ S /  |  D >\n");
for (int j=-LEFTGAP; j<(WIDTH/3)-1; j++){
	printf(" ");
}
printf("  \\|\u203e    \\ /    \u203e|/\n");
for (int j=-LEFTGAP; j<(WIDTH/3); j++){
	printf(" ");
}
printf("         V\n\n\n");
///////////////////////////////
for (int j=-LEFTGAP; j<(WIDTH/3); j++){
	printf(" ");
}
printf("  PRESS Q TO QUIT\n");

	
}



//Function to print the end of the game screen "GAME OVER"******************************************
void gameoversnapshot(int dist, int score){

system("clear");
printf("\n\n\n\n\n");

//printing the top boundary
for (int j=-LEFTGAP; j<0; j++){
	printf(" ");
}
for (int j=0; j<=WIDTH; j++){
	printf("_");
}
printf("\n");

//printing the space inbetween
for (int i=1; i<HEIGHT; i++){
	for (int j=-LEFTGAP; j<0; j++){
		printf(" ");
	}
	printf("|");
	
	if(i==5){
		for (int j=1; j<(WIDTH/2)-9; j++){
			printf(" ");
		}
		for (int j=(WIDTH/2)-9; j<(WIDTH/2)+11; j++){
			printf("*");
		}
		for (int j=(WIDTH/2)+11; j<WIDTH; j++){
			printf(" ");
		}
	}else if (i==6){
		for (int j=1; j<(WIDTH/2)-4; j++){
			printf(" ");
		}
		printf("GAME  OVER");
		for (int j=(WIDTH/2)+6; j<WIDTH; j++){
			printf(" ");
		}
	}else if(i==7){
		for (int j=1; j<(WIDTH/2)-9; j++){
			printf(" ");
		}
		for (int j=(WIDTH/2)-9; j<(WIDTH/2)+11; j++){
			printf("*");
		}
		for (int j=(WIDTH/2)+11; j<WIDTH; j++){
			printf(" ");
		}
	}else if(i==8){
		for (int j=1; j<(WIDTH/2)-4; j++){
				printf(" ");
		}
		printf("DIST: %4d", dist);
		for (int j=(WIDTH/2)+6; j<WIDTH; j++){
				printf(" ");
		}
	}else if(i==9){
		for (int j=1; j<(WIDTH/2)-4; j++){
				printf(" ");
		}
		printf("SCORE:%4d", score);
		for (int j=(WIDTH/2)+6; j<WIDTH; j++){
				printf(" ");
		}
	} else{
		for (int j=1; j<WIDTH; j++){
				printf(" ");
		}
	}
		printf("|");
		printf("\n");
}

//printing the bottom boundary
for (int j=-LEFTGAP; j<0; j++){
	printf(" ");
}
for (int j=0; j<=WIDTH; j++){
	printf("\u203e");
}
printf("\n");

printf("\n\n\n\n\n");
	
}


//MAIN FUNCTION************************************************************************************

int main(){

enableRawMode();

srand(time(NULL));

fd_set read_fds;
struct timeval timeout;
timeout.tv_sec = 1;
timeout.tv_usec = 0;
int key, key_na, key_prev;
int distance = 0;
int score = 0;
int length = 1;


op location, coinlocus;
location.y = 1;
location.x = 1;
op* locilist = (op*)calloc(1000, sizeof(op));
locilist[0].y = location.y;
locilist[0].x = location.x;


coinlocus.y = 0;
coinlocus.x = 0;


system("clear");
snapshot(coinlocus, locilist, length, distance, score);

while(location.y>0 && location.y<HEIGHT && location.x>0 && location.x<WIDTH){
	FD_ZERO(&read_fds);
	FD_SET(STDIN_FILENO, &read_fds);
	
	if (key=='w'){
		key_na = 's';
	}else if (key=='s'){
		key_na = 'w';
	}else if (key=='a'){
		key_na = 'd';
	}else if (key=='d'){
		key_na = 'a';
	}
	key_prev = key;
	
	while (distance%15==0 ){
		coinlocus.x = (rand()%(WIDTH/2))*2 +1 ;
		coinlocus.y = rand()%(HEIGHT-2);
		int check=0;
		for (int k=length-1; k>=0; k--){
			if (coinlocus.y==locilist[k].y && coinlocus.x==locilist[k].x){
				check++;
				break;
			}
		}
		if (check==0){
			break;
		}
	}
	
	int activity=0;
	if (distance!=0){
		activity = select(STDIN_FILENO + 1, &read_fds, NULL, NULL, &timeout);
	}else {
		activity = select(STDIN_FILENO + 1, &read_fds, NULL, NULL, NULL);
	}
	
	if (activity>0 && FD_ISSET(STDIN_FILENO, &read_fds)){
		key = getchar();
	}
	
	
	if (key!=key_na){
		if (key=='w'){
			(location.y)--;
		}else if (key=='s'){
			(location.y)++;
		}else if (key=='a'){
			(location.x)-= 2;
		}else if (key=='d'){
			(location.x)+= 2;
		}else if (key=='q'){
			break;
		}else {
			key=key_prev;
			if (key=='w'){
				(location.y)--;
			}else if (key=='s'){
				(location.y)++;
			}else if (key=='a'){
				(location.x)-= 2;
			}else if (key=='d'){
				(location.x)+= 2;
			}
		}
	}else {
		key = key_prev;
		if (key=='w'){
			(location.y)--;
		}else if (key=='s'){
			(location.y)++;
		}else if (key=='a'){
			(location.x)-= 2;
		}else if (key=='d'){
			(location.x)+= 2;
		}	
	}
	
	if (location.x==coinlocus.x && location.y ==coinlocus.y){
		score++;
		length++;
		coinlocus.y = 0;
		coinlocus.x = 0;
	}
	
	distance++;
	
	for (int k=length-1; k>0; k--){
		locilist[k].y = locilist[k-1].y;
		locilist[k].x = locilist[k-1].x;
	}
	locilist[0].y = location.y;
	locilist[0].x = location.x;
 	system("clear");
	snapshot(coinlocus, locilist, length, distance, score);
	int bite = 0;
	for (int k=length-1; k>0; k--){
		if (locilist[k].y==locilist[0].y && locilist[k].x==locilist[0].x){
			bite++;
			break;
		}
	}
	if (bite>0){
		break;
	}
	
	
	usleep(500000);
	

}

gameoversnapshot(distance-1, score);
free(locilist);

disableRawMode();

return 0;	
}


