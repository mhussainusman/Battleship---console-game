#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<ctime>
#include <windows.h>
using namespace std;

		void leaderboard();
		void instructions();
		void ShowGameMenu();
		void startnewgame(string &name,int &clr,int &mode);
		void clearScreen();
		void initializeboard(char board[10][10]);
		void printboard(char board[10][10],bool hideShips);
		void setRandomShips(char board[10][10]);
		void SettingShips(char board[10][10]);
		void vsPlayer(char player1board[10][10],char player2board[10][10]);
		void vsComputer();
		void playerAttack(char board[10][10], int &health,int &score);
		bool canPlaceHorizontal(char board[10][10], int r, int c, int size);
   		bool canPlaceVertical(char board[10][10], int r, int c, int size);
    	void placeHorizontal(char board[10][10], int r, int c, int size,int shipID);
   		void placeVertical(char board[10][10], int r, int c, int size,int shipID);
    	void askCoordinates(int &r, int &c);
		void placeShipsManually(char board[10][10]);
		void showResults(int p1Score, int p2Score);
		void setColor(int textColor, int bgColor);
		void printBoardsSideBySide(char left[10][10], char middle[10][10], char right[10][10]);
		void checkSunkShip(char board[10][10], int targetPlayer);
		
		//color codes to put in set colour functions
		const int BLACK  = 0, BLUE   = 1,GREEN  = 2,CYAN = 3,RED  = 4,MAGENTA= 5,YELLOW = 6,WHITE  = 7;
			


	void setColor(int textColor, int bgColor) {
    	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    	SetConsoleTextAttribute(hConsole, (bgColor << 4) | (textColor & 0x0F));
	}

		

		// 3D ship tracking system (player, shipID, block) to show which ships are sunk
		int shipR[2][5][5];
		int shipC[2][5][5];
		int shipLen[2][5];
		int shipHits[2][5];

		int shipSizes[5] = {5,4,3,3,2};

		int currentPlayer = 0;
		int targetPlayer = 0;

		
		void vsComputer(){cout<<"Chaudry saab :)\n";}
		
		
		
		void vsPlayer(char player1board[10][10],char player2board[10][10]){
			clearScreen();
			cout<<"-----------------------------------------\n";
			cout<<"             Multiplayer Mode            \n";
			cout<<"-----------------------------------------\n";
			cout<<"Enter name of Player 2: ";string name2;cin>>name2;
			cout<<"\nPlayer 1 place your ships:\n\n";
					
					currentPlayer = 0;

				SettingShips(player1board);
				cout<<"\nPerfect! Press any key(other than spacebar): ";char k2;cin>>k2;
				clearScreen();
				cout<<"\nPlayer 2 place your ships:\n\n";
				
				currentPlayer = 1;

				SettingShips(player2board);
				cout<<"\nLets Play! Press any key(other than spacebar): ";char k3;cin>>k3;cout<<endl;clearScreen();
			//starting gameplay
			
			int p1Health=17;int p2Health = 17;	int p1score=0;	int p2score=0;
		
   			int shotsPerTurn = 6;  
    
	while (true) {
    	
    	clearScreen();// important clear screen before changing turns
    	
        // Player 1 TURN
        cout << "\nPlayer 1's turn:\n";
        currentPlayer = 0;   
        targetPlayer = 1;

        
			printBoardsSideBySide(
    	player2board,
    	player2board,
    	player1board
		);

			
        for (int s = 0; s < shotsPerTurn; s++) {
            playerAttack(player2board, p2Health,p1score);
            
            if (p2Health == 0) {
            	
                
                 cout << "Player 1 destroyed all enemy ships!\n";
    			 showResults(p1score, p2score);
                
                return; }
                
                cout << "\nPress any key to continue: ";char k5; cin>> k5;

    
    			clearScreen();

    			printBoardsSideBySide(player2board,player2board,player1board);
	 
                
        }
        
				clearScreen();// important clear screen before changing turns
    
        // Player 2 TURN
        cout << "\nPlayer 2's turn:\n\n";
        currentPlayer = 1;
        targetPlayer = 0;

        
		printBoardsSideBySide(player1board,player1board,player2board);
			
        for (int s = 0; s < shotsPerTurn; s++) {
            playerAttack(player1board, p1Health,p2score);
            
            if (p1Health==0) {
            	
                cout << "Player 2 destroyed all enemy ships!\n";
    			showResults(p1score, p2score);
    
                return;}
                
            cout << "Press any key to continue: ";char k4; cin>>k4; clearScreen();

    		printBoardsSideBySide(player1board,player1board,player2board);

        }	
    }
    
    
			
		}
		
int main(){
	
srand(time(0));
	ShowGameMenu();
	clearScreen();
	
	string name;int mode,clr;
	startnewgame(name,clr,mode);
	char player1board[10][10], player2board[10][10];
	if (mode==2){vsPlayer(player1board,player2board);}
	else {vsComputer();}
	
return 0;
}

void ShowGameMenu(){
		cout<<"=========================================\n\n";
		
		cout<<"       WELCOME TO BATTLESHIP GAME        \n\n";
		
		cout<<"=========================================\n\n";
		
		int choice;
		while(true){
		
		cout<<"               MAIN MENU                 \n\n";
			
		cout<<"-----------------------------------------\n\n";
		
		cout<<"1. Start New game\n";
		cout<<"2. Instructions\n";
		cout<<"3. View Leaderboard\n";
		cout<<"4. Exit\n\n";
		
		cout<<"-----------------------------------------\n\n";
		
		cout<<"Enter your choice (1-4): ";	
		cin>>choice;
		
		if (choice==1){return;}
		else if (choice==2)instructions();	
		else if (choice==3)leaderboard();
		else if (choice==4){cout<<"\nGame Exited\n";exit(0);}
		else cout<<"Invalid input\n";

	
		}
	}
	
void instructions(){
		 	char ak;	
		cout<<"-----------------------------------------\n\n";
		cout<<"              INSTRUCTIONS               \n\n";
		cout<<"-----------------------------------------\n\n";
		cout<<"1. Place your ships on the board.\n";
		cout<<"2. You and Computer/Player 2 take turns firing shots.\n";
		cout<<"3. 'O' means MISS, 'X' means HIT.\n";
		cout<<"4. Sink all enenmy ships to win!\n";
		cout<<"5. Your score is based on accuracy and speed.\n\n";
		cout<<"-----------------------------------------\n\n";
		cout<<"(Press any key(other than space bar) to return to Main Menu...)\n";
		cin>>ak;
		}
	
	
void leaderboard(){
	char ik;
		cout<<"-----------------------------------------\n";
		cout<<"              LEADERBOARD                \n";
		cout<<"-----------------------------------------\n";
		cout<<"1. Hussian	90\n";
		cout<<"2. Rehman	80\n";
		cout<<"3. Saeed 	70\n";
		cout<<endl;
		cout<<"-----------------------------------------\n\n";
		cout<<"(Press any key(other than space bar) to return to Main Menu...)\n";
		cin>>ik;
}

void startnewgame(string &name,int &clr,int &mode){
	
		
		cout<<"-----------------------------------------\n";
		cout<<"             START NEW GAME              \n";
		cout<<"-----------------------------------------\n";
		
		cout<<"Enter Player's name: ";
		cin>>name;
		
		cout<<"\nThese are the available colours to represent your Ships:\n";
		cout<<"1. Yellow\n";
		cout<<"2. Cyan\n";
		cout<<"3. Green\n";
		
		cout<<"\nEnter your choice: ";
		cin>>clr;
		
		cout<<"\nAvailable modes:\n";
		cout<<"1. Player vs computer\n";
		cout<<"2. Player vs player\n";
		
		cout<<"\nEnter your choice: ";
		cin>>mode;while(mode!=1&&mode!=2){cout<<"Invalid input. Choose again: ";cin>>mode;}
		
		
}

void clearScreen() {
	system("CLS"); }
	
void initializeboard(char board[10][10]){
	for (int i=0;i<10;i++){
		for (int j=0;j<10;j++){board[i][j]='~';}
	}	
}

void printboard(char board[10][10],bool hideShips){
	
	cout<<setw(3);
	for (int i=0;i<10;i++){
	cout<<i<<" ";}cout<<endl;
	
    for (int r=0; r<10;r++) {
        cout<< r<<setw(2);
        for (int c=0; c<10;c++) 
		{
			char cell=board[r][c];

            if (hideShips) {
                
                if (cell=='S') {cout<<"~ ";}	// Hide ships unless they are hit
                
                else {cout<<cell<<" ";}
                
            } 
            else {cout<<cell<<" ";} //shows everything 
        }
		cout << endl;
    }
}
	


void setRandomShips(char board[10][10]){

	for(int s=0;s<5;s++){
        int size=shipSizes[s];
        bool placed=false;

        while(!placed){
            int orientation=rand()%2;
            int r=rand()%10;
            int c=rand()%10;
            bool ok=true;

            if(orientation==0){
               ok=canPlaceHorizontal(board,r,c,size);
            }
			else{
                ok=canPlaceVertical(board,r,c,size);
            }

            if(ok){
                if(orientation==0){placeHorizontal(board,r,c,size,s);}
                else{placeVertical(board,r,c,size,s);}
                   
                placed=true;
            }
        }
    }
 }

	


void SettingShips(char board[10][10]){
		 initializeboard(board);
		
		int p = currentPlayer;   

	for(int i=0;i<5;i++){
    	shipHits[p][i] = 0;
    	shipLen[p][i] = shipSizes[i];

    	for(int j=0;j<5;j++){
        	shipR[p][i][j] = -1;
        	shipC[p][i][j] = -1;
    	}
}
			cout<<"Grid:\n";
		printboard(board,false);
	
		cout<<"\nYou have the following ships to place:\n";
	cout<<"1. Aircraft Carrier (takes 5 blocks)\n";
	cout<<"2. Battleship (takes 4 blocks)\n";
	cout<<"3. Destroyer (takes 3 blocks)\n";
	cout<<"4. Submarine (takes 3 blocks)\n";
	cout<<"5. Patrol Boat (takes 2 blocks)\n\n";
	
	
	cout<<"Chose placement option: 1= Manual, 2= Random: ";
	int plop;
	cin>>plop;while(plop!=1&&plop!=2){cout<<"Invalid input. Choose again: ";cin>>plop;}
	clearScreen();
		

	
	if(plop==2){
	 setRandomShips(board);
   		clearScreen();
		cout<<"\nUpdated board:\n\n";
		printboard(board,false);
	}
    
    else placeShipsManually(board);
 
}// settingShips function ends



void playerAttack(char board[10][10], int &health,int &score) {
    int r, c;

    while (true) {
        cout << "\nEnter attack coordinates: ";
       	askCoordinates(r,c);
		
        
        if (board[r][c] == 'X' || board[r][c] == 'O') {
            cout << "\nAlready fired here. Try again.\n";
            continue;
        }

        break;
    }

    // Hit
    if (board[r][c] == 'S') {

        cout << "\nHIT!\n";
        board[r][c] = 'X';
        health--;
        score+=10;
        checkSunkShip(board,targetPlayer);
    }
    else { // Miss
        cout << "\nMISS.\n";
        board[r][c] = 'O';
        score--;
    }
}

// Helper functions for placements of ships
bool canPlaceHorizontal(char board[10][10], int r, int c, int size){
    if(c+size-1>9) return false;
    for(int i=0;i<size;i++)
        if(board[r][c+i]!='~') return false;
    return true;
}

bool canPlaceVertical(char board[10][10], int r, int c, int size){
    if(r+size-1>9) return false;
    for(int i=0;i<size;i++)
        if(board[r+i][c]!='~') return false;
    return true;
}

void placeHorizontal(char board[10][10], int r, int c, int size,int shipID){
    for(int i=0;i<size;i++){
        board[r][c+i]='S';
       shipR[currentPlayer][shipID][i] = r;
	shipC[currentPlayer][shipID][i] = c+i;
	shipLen[currentPlayer][shipID] = size;

    }
}

void placeVertical(char board[10][10], int r, int c, int size,int shipID){
    for(int i=0;i<size;i++){
        board[r+i][c]='S';
        	shipR[currentPlayer][shipID][i] = r+i;
			shipC[currentPlayer][shipID][i] = c;
		shipLen[currentPlayer][shipID] = size;

	}
}
// end of helpers for placement

void askCoordinates(int &r, int &c) {
    cout << "Enter row (0-9): ";
    cin >> r;
    while (r < 0 || r > 9) {
        cout << "Invalid row. Enter again: ";
        cin >> r;
    }

    cout << "Enter column (0-9): ";
    cin >> c;
    while (c < 0 || c > 9) {
        cout << "Invalid column. Enter again: ";
        cin >> c;
    }
}


void placeShipsManually(char board[10][10]){
int countships=0; int r,c;
    		int x=0,y=0,z=0,h=0,u=0;
			
    	
while(countships<5){
	clearScreen();
	cout<<"\nYou have the following ships to place:\n";
	if(x==0)cout<<"1. Aircraft Carrier (takes 5 blocks)\n";
	if(y==0)cout<<"2. Battleship (takes 4 blocks)\n";
	if(z==0)cout<<"3. Destroyer (takes 3 blocks)\n";
	if(h==0)cout<<"4. Submarine (takes 3 blocks)\n";
	if(u==0)cout<<"5. Patrol Boat (takes 2 blocks)\n\n";
	cout<<"Enter what you want to place: ";
	int ship;cin>>ship;
	
	int sz=0;
	
		if(ship==1){
			if(x==1){cout<<"The ship is alreasy placed. Chose another.\n";continue;}
			sz=5;}
		else if (ship==2){
			if(y==1){cout<<"The ship is alreasy placed. Chose another.\n";continue;}
			sz=4;}
		else if (ship==3){
			if(z==1){cout<<"The ship is alreasy placed. Chose another.\n";continue;}
			sz=3;}
	 	else if (ship==4){
	 		if(h==1){cout<<"The ship is alreasy placed. Chose another.\n";continue;}
		 	sz=3;}
		else if (ship==5){
			if(u==1){cout<<"The ship is alreasy placed. Chose another.\n";continue;}
			sz=2;}
		else {  cout << "Invalid ship number.\n";continue;}

	
	while(true){
	cout<<"Your grid:\n";	               
    printboard(board,false);    
    
	askCoordinates(r,c);

	
	//placements
	if(canPlaceHorizontal(board,r,c,sz)){placeHorizontal(board, r, c, sz,ship-1);
				clearScreen();
		cout<<"\nUpdated board:\n";
			printboard(board,false);break;}
	
		else{
				clearScreen();
		cout<<"Invalid placement. Try again.\n";continue;}
	}
		
	
		
		 cout<<"Do you want to rotate it vertically? (1 = Yes, 2 = No): ";int rot; cin>>rot;
		while(rot!=1&&rot!=2){cout<<"Invalid input. Choose again: ";cin>>rot;}
		
		 if(rot == 1){
        
        for(int i=0;i<sz;i++) board[r][c+i] = '~';

        
       
        if(canPlaceVertical(board,r,c,sz)){
            placeVertical(board,r,c,sz,ship-1);
            	clearScreen();
		cout<<"\nUpdated board:\n";
			printboard(board,false);
		
        }
        else {
            cout<<"Vertical placement failed. Enter new coordinates.\n";
            

           
            	while(true){
            	
            	  		cout<<"Your grid:\n";            
    					printboard(board,false);    
    	
            			askCoordinates(r,c);
                 
        			if(canPlaceVertical(board,r,c,sz)){placeVertical(board,r,c,sz,ship-1);clearScreen();
						cout<<"\nUpdated board:\n";
						printboard(board,false); break;}
        				else{
							clearScreen();
							cout<<"Invalid placement. Try again.\n";continue;}
            	}
            
            
            
       		}
		}
        
		countships++;
		
			 if(ship==1) x=1;else if(ship==2) y=1;else if(ship==3) z=1;else if(ship==4) h=1;else if(ship==5) u=1;
	}
 
}
 
void showResults(int p1Score, int p2Score) {
    clearScreen();
    cout << "\n=====================================\n";
    cout << "            GAME RESULTS             \n";
    cout << "=====================================\n";

    cout << "\nFinal Scores:\n";
    cout << "Player 1 Score: " << p1Score << endl;
    cout << "Player 2 Score: " << p2Score << endl;

    cout << "\nWinner (based on score): ";

    if (p1Score > p2Score)
        cout << "Player 1\n";
    else if (p2Score > p1Score)
        cout << "Player 2\n";
    else 
        cout << "It's a Draw !\n";

    cout << "\n=====================================\n";
}




void printBoardsSideBySide (char left[10][10], char middle[10][10], char right[10][10])
{
    cout << "\n      ENEMY BOARD" << setw(48) << "Opponent" << setw(52) << "PLAYER BOARD\n\n";


	cout<<"   ";
	for (int i=0;i<10;i++){cout<<i<<" ";}
	
    cout<<"           ";
    
	cout <<"0"<<setw(6)<<"1"<<setw(6)<<"2"<<setw(6)
	<<"3"<<setw(6)<<"4"<<setw(6)<<"5"<<setw(6)<<"6"<<setw(6)<<"7"<<setw(6)<<"8"<<setw(6)<<"9";

   
  	cout<<"            ";
  
    
	for (int i=0;i<10;i++){cout<<i<<" ";}
    
    cout << endl;
    
    

    for (int r= 0;r< 10; r++)
    {
        // left most enemy grid
        cout << r << "  ";
        for (int c = 0; c < 10; c++)
        {
            char cell = left[r][c];
            if (cell == 'S') cout << "~ ";
            else cout << cell << " ";
        }

        cout << setw(7);

        // coloured grid in the middle
        cout << r << " ¦";
        for (int c = 0; c < 10; c++)
        {
            char cell = middle[r][c];
            char show = (cell == 'S' ? '~' : cell);

            if (show=='~') setColor(7,1);
            else if (show=='X') setColor(15,12);
            else if (show=='O') setColor(0,8);
			else if (show=='P') setColor(15,5);    // sunken ship 

            cout<<"  "<<show<<"  ";
            setColor(7,0);
            cout<<"¦";
        }

        cout << setw(7);

        // player board display 
        cout << r << "  ";
        for (int c = 0; c < 10; c++)
            cout << right[r][c] << " ";

        cout << endl;
    }
}

void checkSunkShip(char board[10][10], int targetPlayer) {
    for(int id=0;id<5;id++){
        int len=shipLen[targetPlayer][id];
        int hits=0;

        for(int i=0;i<len;i++){
            int r=shipR[targetPlayer][id][i];
            int c=shipC[targetPlayer][id][i];

            if (r==-1)break;

            if(board[r][c]=='X') hits++;
        }

        if(hits==len){
            for(int i=0;i<len;i++){
                int r=shipR[targetPlayer][id][i];
                int c=shipC[targetPlayer][id][i];
                board[r][c]='P';
            }
        }
    }
}


