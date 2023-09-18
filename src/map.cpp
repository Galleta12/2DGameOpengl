#include "Map.h"

#include "SDWINDOW.h"
#include "Floor.h"
#include "Platforms.h"
#include "Box.h"
#include "Enemy.h"
#include "Player.h"
#include <memory>


void Map::Level1(std::shared_ptr<Player> player)
{

    //floor
    SDWINDOW::transformList.push_back(std::make_unique<Floor>(-10.0f, *SDWINDOW::WindowHeight /10));
    
     //platforms
     SDWINDOW::transformList.push_back(std::make_unique<Platforms>(300.0f,600.0f, 500.0f, 600.0f));
     SDWINDOW::transformList.push_back(std::make_unique<Platforms>(1166.0f, 558.0f, 949.0f, 434.0f));
     SDWINDOW::transformList.push_back(std::make_unique<Platforms>(295.0f, 500.0f, 295.0f, 394.0f));



    SDWINDOW::transformList.push_back(std::make_unique<Platforms>(800.0f,600.0f, 1000.0f, 600.0f));
    SDWINDOW::transformList.push_back(std::make_unique<Platforms>(900.0f, 500.0f, 700.0f, 394.0f));
    
    SDWINDOW::transformList.push_back(std::make_unique<Platforms>(2000.0f, 500.0f, 1900.0f, 394.0f));
    SDWINDOW::transformList.push_back(std::make_unique<Platforms>(1800.0f, 500.0f, 1700.0f, 394.0f));
     
     
     
     SDWINDOW::transformList.push_back(std::make_unique<Platforms>(-200.0f, 800.0f, 2500.0f, 800.0f));
     SDWINDOW::transformList.push_back(std::make_unique<Platforms>(-200.0f, 780.0f, -10.0f, -10.0f));
     SDWINDOW::transformList.push_back(std::make_unique<Platforms>(2450.0f, 780.0f, 2450.0f, -10.0f));
    

    //boxes
    SDWINDOW::transformList.push_back(std::make_unique<Box>(600.0f,250.0f,true));
    SDWINDOW::transformList.push_back(std::make_unique<Box>(100.0f,250.0f,true));
    SDWINDOW::transformList.push_back(std::make_unique<Box>( -157.945f,100.0f,true));
    SDWINDOW::transformList.push_back(std::make_unique<Box>( -100.945f,100.0f,true));
    SDWINDOW::transformList.push_back(std::make_unique<Box>( 220.945f,100.0f,true));
    SDWINDOW::transformList.push_back(std::make_unique<Box>( 800.945f,100.0f,true));


    SDWINDOW::transformList.push_back(std::make_unique<Box>( 1000.0f,100.0f,true));
    SDWINDOW::transformList.push_back(std::make_unique<Box>( 2000.945f,800.0f,true));
    SDWINDOW::transformList.push_back(std::make_unique<Box>( 1000.945f,200.0f,true));
    SDWINDOW::transformList.push_back(std::make_unique<Box>( 2000.945f,100.0f,true));

    //enemy   
    SDWINDOW::transformList.push_back(std::make_unique<Enemy>(1200.0f,200.0f,player));

}



void Map::Level2(std::shared_ptr<Player> player)
{
     //floor
    SDWINDOW::transformList.push_back(std::make_unique<Floor>(-10.0f, *SDWINDOW::WindowHeight /10));
    
     //platforms
     SDWINDOW::transformList.push_back(std::make_unique<Platforms>(300.0f,600.0f, 500.0f, 600.0f));
     SDWINDOW::transformList.push_back(std::make_unique<Platforms>(1166.0f, 558.0f, 949.0f, 434.0f));
     SDWINDOW::transformList.push_back(std::make_unique<Platforms>(295.0f, 500.0f, 295.0f, 394.0f));



     
     
     
     SDWINDOW::transformList.push_back(std::make_unique<Platforms>(-200.0f, 800.0f, 2500.0f, 800.0f));
     SDWINDOW::transformList.push_back(std::make_unique<Platforms>(-200.0f, 780.0f, -10.0f, -10.0f));
     SDWINDOW::transformList.push_back(std::make_unique<Platforms>(2450.0f, 780.0f, 2450.0f, -10.0f));
    

    //boxes
    SDWINDOW::transformList.push_back(std::make_unique<Box>(600.0f,250.0f,true));
    SDWINDOW::transformList.push_back(std::make_unique<Box>(100.0f,250.0f,true));
    SDWINDOW::transformList.push_back(std::make_unique<Box>( -157.945f,100.0f,true));
    SDWINDOW::transformList.push_back(std::make_unique<Box>( -100.945f,100.0f,true));
    SDWINDOW::transformList.push_back(std::make_unique<Box>( 220.945f,100.0f,true));
    SDWINDOW::transformList.push_back(std::make_unique<Box>( 800.945f,100.0f,true));
    
    
    SDWINDOW::transformList.push_back(std::make_unique<Box>( 800.945f,100.0f,true));
    SDWINDOW::transformList.push_back(std::make_unique<Box>( 2000.945f,100.0f,true));
    SDWINDOW::transformList.push_back(std::make_unique<Box>( 1800.945f,100.0f,true));


    SDWINDOW::transformList.push_back(std::make_unique<Box>( 1000.0f,100.0f,true));
    SDWINDOW::transformList.push_back(std::make_unique<Box>( 2000.945f,800.0f,true));
    SDWINDOW::transformList.push_back(std::make_unique<Box>( 1000.945f,200.0f,true));
    SDWINDOW::transformList.push_back(std::make_unique<Box>( 2000.945f,100.0f,true));
    
    
    SDWINDOW::transformList.push_back(std::make_unique<Box>( 2500.945f,700.0f,false));
    //SDWINDOW::transformList.push_back(std::make_unique<Box>( 2500.945f,000.0f,false));

    //enemy   
    SDWINDOW::transformList.push_back(std::make_unique<Enemy>(1200.0f,200.0f,player));
    SDWINDOW::transformList.push_back(std::make_unique<Enemy>(2200.0f,500.0f,player));
    SDWINDOW::transformList.push_back(std::make_unique<Enemy>(2200.04f,215.392f,player));
    // SDWINDOW::transformList.push_back(std::make_unique<Enemy>(1200.0f,500.0f,player));


}




