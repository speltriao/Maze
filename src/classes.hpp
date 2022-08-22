//Define the characters that will be used to display the player's current position
#define leftIndicator '('
#define rightIndicator ')'

//Colors and fonts
#define RED     "\x1b[31m"
#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define BOLD "\e[1;37m"
#define UNDER "\e[4;37m"

//Define the Maze Matrix size
#define lenY 13
#define lenX 20 

class Maze{
    protected:    
        char maze[lenY][lenX]={ //m[y][x]   
            {' ','.','-','-','.','-','-','.','-','-','.','-','-','.','-','-','.','-','-','.'},
            {' ','|',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ','|'},
            {' ',':',' ',' ',':','-','-',':',' ',' ',':',' ',' ',':',' ',' ',':',' ',' ',':'},
            {' ','|',' ',' ','|',' ',' ',' ',' ',' ','|',' ',' ','|',' ',' ',' ',' ',' ','|'},
            {' ',':',' ',' ',':',' ',' ',':',' ',' ',':','-','-',':','-','-',':','-','-',':'},
            {' ','|',' ',' ','|',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|'},
            {' ',':',' ',' ',':',' ',' ',':','-','-',':','-','-',':','-','-',':',' ',' ',':'},
            {' ','|',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ','|',' ',' ','|'},
            {' ',':',' ',' ',':','-','-',':','-','-',':',' ',' ',':',' ',' ',':',' ',' ',':'},
            {' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ','|',' ',' ','|',' ',' ','|'},
            {' ',':','-','-',':',' ',' ',':',' ',' ',':','-','-',':',' ',' ',':',' ',' ',':'},
            {' ','|',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ','|'},
            {' ',':','-','-',':','-','-',':','-','-',':','-','-',':','-','-',':','-','-',':'},
       };
    public:
        void printMaze(){ 
            for (int i = 0; i < lenY; i++){
                for (int j = 0; j < lenX; j++){
                    if (maze[i][j] == leftIndicator || maze[i][j] == rightIndicator){
                        std::cout << BOLD << RED << maze[i][j] <<RESET;
                    }
                    else {
                        std::cout << CYAN << maze[i][j] <<RESET;
                    }
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }
};

class Movement : public Maze{
    private:
        const char wall[4] = {'.' , '|' , ':' , '-'}; //Characters that compose the Maze Wall
        int currentX, currentY, countMoves;
        const int defaultY = 1, defaultX = 17, gameOverY = 9, gameOverX = 0; //Game special positions

    public:
        Movement(){ //Defaults
            countMoves = 0;
            currentX = defaultX;
            currentY = defaultY;
        }

        int getCountMoves(){return countMoves;}

        bool isGameOver(){
            if ((currentY == gameOverY) && (currentX == gameOverX)){
                return true;
            }
            return false; 
        }

        bool isWall(char ch){
            for (int i = 0; i < 4; i++){
                if (wall[i] == ch) {
                    return true;
                }
            }
            return false;
        }

        void resetLastLocation(){ 
            maze[currentY][currentX] = ' ';
            maze[currentY][currentX+1] = ' ';
        }

        void updatePlayerLocation(){
            maze[currentY][currentX] = leftIndicator;
            maze[currentY][currentX+1] = rightIndicator;
        }

        bool moveUp(){ 
            if ((isWall(maze[currentY-1][currentX])) || (isWall(maze[currentY-1][currentX+1]))){
                return false;
            }
            resetLastLocation();
            currentY--;                 
            return true;
        }
        
        bool moveLeft(){
            if (isWall(maze[currentY][currentX-1])){
                return false;
            }
            resetLastLocation();
            currentX--;                  
            return true;
        }

        bool moveDown(){
            if ((isWall(maze[currentY+1][currentX])) || (isWall(maze[currentY+1][currentX+1]))){
                return false;
            }
            resetLastLocation();
            currentY++;
            return true;
        }

        bool moveRight(){
            if(isWall(maze[currentY][currentX+2])){   
                return false;
            }
            resetLastLocation();
            currentX++;                  
            return true;
        }

        char inputWithoutEnter(){ //Hack to skip [Enter] key press on input
            system("stty -echo"); 
            system("stty cbreak"); 
            char input = getchar();
            system ("stty echo"); 
            system("stty -cbreak");
            return input;
        }

        bool isValidMove(char input){
            switch (input) {
                case 'w': 
                    return (moveUp()); 
                case 'a':
                    return (moveLeft()); 
                case 's':
                    return (moveDown()); 
                case 'd':
                    return (moveRight()); 
                default:
                    return false;
            }
        }

        void userInput(){
            char input;
            do{
                input = inputWithoutEnter();
            } while (!isValidMove(input));
        }

        void doMove(){
            do{
                updatePlayerLocation();
                printMaze();
                userInput();
                countMoves++;
                system("clear"); //Clear the terminal
            }while(!isGameOver());
        }
};
