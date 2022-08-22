void welMsg(){                     
   std::cout<<"  /\\/\\    __ _  ____  ___"<<"\n";
    std::cout<<" /    \\  / _` ||_  / / _ \\"<<"\n";
    std::cout<<"/ /\\/\\ \\| (_| | / / |  __/"<<"\n";
    std::cout<<"\\/    \\/ \\__,_|/___| \\___|"<<"\n";
    std::cout<<UNDER<<"\n\nplay with WASD keys\n\n"<<RESET;                              
}

int runGame(){
    welMsg();
    Movement mv;
    while(!mv.isGameOver()) {
        mv.doMove();
    } 
    return mv.getCountMoves();
}