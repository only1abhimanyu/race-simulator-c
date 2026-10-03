#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h> // experimental

// Structures section
typedef struct Race {
  int numberOfLaps;
  int currentLap;
  char* firstPlaceDriverName;
  char* firstPlaceRaceCarColor;
  } Race;
typedef struct RaceCar {
  char* driverName;
  char* raceCarColor;
  int totalLapTime;
} RaceCar;

// Cross-platform (Windows) console clear using WinAPI for reliability
void clearConsole() {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hConsole != INVALID_HANDLE_VALUE) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
      DWORD cellCount = (DWORD)(csbi.dwSize.X * csbi.dwSize.Y);
      COORD homeCoords = {0, 0};
      DWORD count;
      FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);
      FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);
      SetConsoleCursorPosition(hConsole, homeCoords);
      return;
    } else {
      /* If we're not attached to a traditional console (for example the
         VS Code integrated terminal uses a pseudo-tty), GetConsoleScreenBufferInfo
         may fail. Try enabling virtual terminal processing so ANSI escapes work,
         then fall back to printing an ANSI clear sequence below. */
      DWORD mode = 0;
      if (GetConsoleMode(hConsole, &mode)) {
        SetConsoleMode(hConsole, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
      }
    }
  }

  /* Fallback: print ANSI clear screen + cursor-home. This works in many
     terminals (including VS Code integrated terminal) once VT processing is enabled. */
  printf("\x1b[2J\x1b[H");
  fflush(stdout);
}


// Print functions section
void printIntro(){
  printf("Welcome to our main event digital race fans!\nI hope everybody has their snacks because we are about to begin!\n");
	Sleep(2000);
}
//experimental (using windows header file for first time)
void printCountDown(){
  printf("\nRacers Ready! In...\n");
  /* Make clearing the console more reliable than system("cls") and ensure
     visible output by flushing stdout before sleeps. */
  Sleep(1000); // Pauses for 1000 milliseconds (1 second)
  // clear and show numbers with flushes so they appear in terminals
  // We'll replace system("cls") with clearConsole() implemented below.

  clearConsole();
  printf("5\n"); fflush(stdout);
  Sleep(1000);
  clearConsole();
  printf("4\n"); fflush(stdout);
  Sleep(1000);
  clearConsole();
  printf("3\n"); fflush(stdout);
  Sleep(1000);
  clearConsole();
  printf("2\n"); fflush(stdout);
  Sleep(1000);
  clearConsole();
  printf("1\n"); fflush(stdout);
  Sleep(1000);
  clearConsole();
  printf("\nRace!\n"); fflush(stdout);
}
//conventional code
void printFirstPlaceAfterLap(struct Race* race){
  printf("\nAfter lap number %d\nFirst Place Is: %s in the %s race car!\n", race->currentLap, race->firstPlaceDriverName, race->firstPlaceRaceCarColor);
}
void printCongratulation(struct Race* race){
  printf("\nLet's all congratulate %s in the %s race car for an amazing performance.\nIt truly was a great race and everybody have a goodnight!\n", race->firstPlaceDriverName, race->firstPlaceRaceCarColor);
}


// Logic functions section
int calculateTimeToCompleteLap(){
  /* Return a more varied lap time (1-10) so races diverge more often.
     Lower value = faster (better). */
  int lapTime = (rand() % 10) + 1; // 1..10
  return lapTime;
}
void updateRaceCar(struct RaceCar* raceCar){
  raceCar-> totalLapTime = raceCar -> totalLapTime + calculateTimeToCompleteLap();
}
void updateFirstPlace(struct Race* race, struct RaceCar* raceCar1, struct RaceCar* raceCar2){
  if(raceCar1->totalLapTime <= raceCar2->totalLapTime){
    race->firstPlaceDriverName = raceCar1->driverName;
    race->firstPlaceRaceCarColor = raceCar1->raceCarColor;
  } else {
    race->firstPlaceDriverName = raceCar2->driverName;
    race->firstPlaceRaceCarColor = raceCar2->raceCarColor;
  }
}
void startRace(struct RaceCar* raceCar1, struct RaceCar* raceCar2){
  struct Race race = {5, 1, NULL, NULL};
  for (int i = 0; i < race.numberOfLaps; i++){
    updateRaceCar(raceCar1);
    updateRaceCar(raceCar2);
    updateFirstPlace(&race, raceCar1, raceCar2);
    race.currentLap = i+1;
    printFirstPlaceAfterLap(&race);
  }
  printCongratulation(&race);
}


// Main function
int main() {
	srand(time(0));
  	printIntro();
  	printCountDown();
  	struct RaceCar racer1 = {"Racer 1", "Blue", 0};
  	struct RaceCar racer2 = {"Racer 2", "Red", 0};
  	startRace(&racer1, &racer2);
	return 0;
}
