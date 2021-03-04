void welMsg(){
                            
   std::cout<<"  /\\/\\    __ _  ____  ___"<<"\n";
    std::cout<<" /    \\  / _` ||_  / / _ \\"<<"\n";
    std::cout<<"/ /\\/\\ \\| (_| | / / |  __/"<<"\n";
    std::cout<<"\\/    \\/ \\__,_|/___| \\___|"<<"\n";
    std::cout<<UNDER<<"\n\nplay with WASD keys\n\n"<<RESET;                              
}

int run(){
    welMsg();
    while (1){
        Move mv; //each movement is an instance of the Move class
        mv.movement();
        if (mv.endGame()) return mv.getCount();
    }
}

