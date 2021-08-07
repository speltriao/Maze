#define indicator1 '('
#define indicator2 ')'
#define RED     "\x1b[31m"
#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
#define BOLD "\e[1;37m"
#define UNDER "\e[4;37m"

class Maze{
    protected:    
        char m[13][20]={//m[y][x]   
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
            for (int i = 0; i < 13; i++){
                for (int j = 0; j < 20; j++){
                    if (m[i][j]==indicator1 || m[i][j]==indicator2) std::cout<<BOLD<<RED<< m[i][j]<<RESET;
                    else std::cout<<CYAN<<m[i][j]<<RESET;
                }
                std::cout<<"\n";
            }
            std::cout<<"\n";
        }
};

class Move : public Maze{
    private:
        char in;
        bool msg = false, gameover=false;
        const char wall[4]={'.','|',':','-'};
        static int count,currentX, currentY;
        static const int  defaultY = 1, defaultX = 17;
    public:
        Move(){//Constructor
            if (count == 0) {
                currentX=defaultX;
                currentY=defaultY;
            }

            updateLocation();
            count++; //count moves
        }

        void input(){
            do{
                in=getch(); 
            }while((in!='w')&&(in!='a')&&(in!='s')&&(in!='d'));
        }

        void movement(){
            do {
                if((currentY==9)&&(currentX==0)){
                    printMaze();
                    gameover=true;
                    return;
                } 
                printMaze();
                input();
                system("clear");
            } while(!isValidMove());
            
        }

        bool isValidMove(){
            switch (in) {
                case 'w': 
                    if(moveW()) return true;
                    return false;
                case 'a':
                    if(moveA()) return true;
                    return false;
                case 's':
                    if(moveS()) return true;
                    return false;
                case 'd':
                    if(moveD()) return true;
                    return false;
            }
        }

        bool moveW(){
            if((isWall(m[currentY-1][currentX]))||(isWall(m[currentY-1][currentX+1]))) return false;   
            currentY--;                 
            return true;
        }
        
        bool moveA(){
            if(isWall(m[currentY][currentX-1])) return false;   
            currentX--;                  
            return true;
        }
        bool moveS(){
            if((isWall(m[currentY+1][currentX]))||(isWall(m[currentY+1][currentX+1]))) return false;         
            currentY++;                 
            return true;
        }

        bool moveD(){
            if(isWall(m[currentY][currentX+2])) return false;   //2 because the player is a double parenteses ()    
            currentX+=1;                  
            return true;
        }

        void updateLocation(){
            m[currentY][currentX]=indicator1;
            m[currentY][currentX+1]=indicator2;
        }
        bool isWall(char c){
            for (int i = 0; i < 4; i++) if(wall[i]==c)return true;
            return false;
        }
 
        bool endGame(){return gameover;}
        int getCount(){return count;}

        char getch(){//ignores Enter to input
            system("stty -echo"); // supress echo
            system("stty cbreak"); // go to RAW mode
            in=getchar();
            system ("stty echo"); // Make echo work
            system("stty -cbreak");// go to COOKED mode
            return in;
        }
};
int Move::count=-1;
int Move::currentX=Move::defaultX;
int Move::currentY=Move::defaultY;


