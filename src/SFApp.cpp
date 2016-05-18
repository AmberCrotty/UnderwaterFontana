#include "SFApp.h"

SFApp::SFApp(std::shared_ptr<SFWindow> window) : Score(0), fire(0), fire_down(false),up(false),down(false),left(false),right(false), is_running(true), sf_window(window) {
  int canvas_w, canvas_h;
  SDL_GetRendererOutputSize(sf_window->getRenderer(), &canvas_w, &canvas_h);

  app_box = make_shared<SFBoundingBox>(Vector2(canvas_w, canvas_h), canvas_w, canvas_h);
  player  = make_shared<SFAsset>(SFASSET_PLAYER, sf_window);
  auto player_pos = Point2(canvas_w/2, 22);
  player->SetPosition(player_pos);
  player->SetLives(5);
  

  cout<<"Number of Lives: "<<player->Lives()<<endl;


  const int number_of_aliens = 8;
  for(int i=0; i<number_of_aliens; i++) {
    // place an alien at width/number_of_aliens * i
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN, sf_window);
    auto pos   = Point2(rand()%600, rand()%700+ 500);
    alien->SetPosition(pos);
    alien->SetLives(1);
    aliens.push_back(alien);
   }


   const int number_of_secondaliens = 8;
   for(int i=0; i<number_of_secondaliens; i++) {
     //place an alien at width/number_of_secondaliens * i
    auto secondalien = make_shared<SFAsset>(SFASSET_SECONDALIEN, sf_window);
    auto poss   = Point2(rand()%600, rand()%700+500);
    secondalien->SetPosition(poss);
    secondalien->SetLives(2);
    secondaliens.push_back(secondalien);
   }

  
   const int number_of_thirdaliens = 8;
   for(int t=0; t<number_of_aliens; t++) {
    // place an alien at width/number_of_thirdaliens * t
    auto thirdalien = make_shared<SFAsset>(SFASSET_THIRDALIEN, sf_window);
    auto post   = Point2(rand()%600, rand()%800+600);
    thirdalien->SetPosition(post);
    thirdalien->SetLives(3);
    thirdaliens.push_back(thirdalien);
   }

    auto coin = make_shared<SFAsset>(SFASSET_COIN, sf_window);
    auto pos  = Point2((canvas_w/4), 100);
    coin->SetPosition(pos);
    coins.push_back(coin);

  const int number_of_walls = 3;
  for(int a=0; a <number_of_walls; a++) {
  auto wall = make_shared<SFAsset>(SFASSET_WALL, sf_window);
  auto posw = Point2((canvas_w/3)*a+90, 200);
  wall->SetPosition(posw);
  walls.push_back(wall);
    }

}

SFApp::~SFApp() {
}

/**
 * Handle all events that come from SDL.
 * These are timer or keyboard events.
 */
void SFApp::OnEvent(SFEvent& event) {
  SFEVENT the_event = event.GetCode();
  switch (the_event) {
  case SFEVENT_QUIT:
    is_running = false;
    break;
  case SFEVENT_UPDATE:
    OnUpdateWorld();
    OnRender();
    break;
  case SFEVENT_PLAYER_LEFT_KEYDOWN:
    left = true;
    
    break;
  case SFEVENT_PLAYER_RIGHT_KEYDOWN:
    right = true;
    break;
  case SFEVENT_PLAYER_UP_KEYDOWN:
    up = true;
    break;
  case SFEVENT_PLAYER_DOWN_KEYDOWN:
    down = true;
    break;
  case SFEVENT_FIRE_KEYDOWN:
    fire_down = true;
    break;
  case SFEVENT_PLAYER_LEFT_KEYUP:
    left = false;
    break;
  case SFEVENT_PLAYER_RIGHT_KEYUP:
    right = false;
    break;
  case SFEVENT_PLAYER_UP_KEYUP:
    up = false;
    break;
  case SFEVENT_PLAYER_DOWN_KEYUP:
    down = false;
    break;
  case SFEVENT_FIRE_KEYUP:
    fire_down = false;
    break;
  }
}

int SFApp::OnExecute() {
  // Execute the app
  SDL_Event event;
  while (SDL_WaitEvent(&event) && is_running) {
    // wrap an SDL_Event with our SFEvent
    SFEvent sfevent((const SDL_Event) event);
    // handle our SFEvent
    OnEvent(sfevent);
  }
}

void SFApp::OnUpdateWorld() {
  //Player Movement 
  
  if (up) player->GoNorth();
  for (auto w : walls)
    {
      if(player->CollidesWith(w))
      {
        player->GoSouth();
      }
   }
  if (down) player->GoSouth();
  for (auto w : walls)
    {
      if(player->CollidesWith(w))
      {
        player->GoNorth();
      }
   }
  if (right) player->GoEast();
  for (auto w : walls)
    {
      if(player->CollidesWith(w))
      {
        player->GoWest();
      }
   }
  if (left) player->GoWest();
  for (auto w : walls)
    {
      if(player->CollidesWith(w))
      {
        player->GoEast();
      }
   }


  timer++;
  if(timer > 40){
  if (fire_down){
  fire ++;
  FireProjectile();
  timer=0;
   }
 }

  
  // Update projectile positions
  for(auto p: projectiles) {
    p->GoNorth();
  }

  for(auto c: coins) {
    c->GoNorth();
  }

 
  // Update enemy positions
  for(auto a : aliens)
  for(auto s : secondaliens)
  for(auto t : thirdaliens)
    for(auto w : walls) {
     a->Movespeed();
     s->Movespeed();
     t->Movespeed();
      if(a->CollidesWith(w)){
         a->HandleCollision();
         }
      if(s->CollidesWith(w)){
         s->HandleCollision();
         }
      if(t->CollidesWith(w)){
         t->HandleCollision();
         }
     
     }


 //Detect enemy/player collision

    for(auto a : aliens)
    for(auto s : secondaliens)
    for(auto t : thirdaliens){

      if(player->CollidesWith(a)){
            a->HandleCollision();
            player->SetLives(player->Lives() -1);
             cout<<"Lives left: "<<player->Lives()<<endl;
            }
      if(player->CollidesWith(s)){
            s->HandleCollision();
            player->SetLives(player->Lives() -1);
             cout<<"Lives left: "<<player->Lives()<<endl;
            }
      if(player->CollidesWith(t)){
           t->HandleCollision();
            player->SetLives(player->Lives() -1);
             cout<<"Lives left: "<<player->Lives()<<endl;
            }
             
         }


  // Detect collisions
  for(auto p : projectiles) {
    for(auto a : aliens) {
      if(p->CollidesWith(a)) {
                        
            addScore(10);
             cout<<"Score plus 10!"<<endl;
        p->HandleCollision();
        a->HandleCollision();
      }
    }
  }

   //Detect Second Alien collision
   for(auto p : projectiles) {
    for (auto s : secondaliens) {
     if(p->CollidesWith(s)) {

             s->EnemyLives(15);
             addScore(20);
             cout<<"Score plus 20!"<<endl;
          p->HandleCollision();
        

        
       }
     }
   }

  //Detect Third Alien collision
   for(auto p : projectiles) {
    for (auto t : thirdaliens) {
     if(p->CollidesWith(t)) {

            t->EnemyLives(10);
            addScore(30);
             cout<<"Score plus 30!"<<endl;
         p->HandleCollision();
        
       }
     }
   }

// Destroy Projectile at wall
  for(auto p : projectiles) {
    for(auto w : walls) {
      if(p->CollidesWith(w)) {
        p->HandleCollision();
      }
    }
  }

  // remove dead aliens (the long way)
  list<shared_ptr<SFAsset>> tmp;
  for(auto a : aliens) {
    if(a->IsAlive()) {
      tmp.push_back(a);
    }
  }
  aliens.clear();
  aliens = list<shared_ptr<SFAsset>>(tmp);

  //removes second aliens
  list<shared_ptr<SFAsset>> tmp_sec;
  for(auto s : secondaliens) {
    if(s->IsAlive()) {
      tmp_sec.push_back(s);
    }
  }
  secondaliens.clear();
  secondaliens = list<shared_ptr<SFAsset>>(tmp_sec);

  //removes third aliens
  list<shared_ptr<SFAsset>> tmp_third;
  for(auto t : thirdaliens) {
    if(t->IsAlive()) {
      tmp_third.push_back(t);
    }
  }
  thirdaliens.clear();
  thirdaliens = list<shared_ptr<SFAsset>>(tmp_third);



   //remove projectile
   list<shared_ptr<SFAsset>> tmp_proj;
    for (auto p : projectiles) {
     if(p->IsAlive()) {
      tmp_proj.push_back(p);
    }
  }
  projectiles.clear();
  projectiles = list<shared_ptr<SFAsset>>(tmp_proj);
}




   

void SFApp::OnRender() {
  SDL_RenderClear(sf_window->getRenderer());

  // draw the player
  player->OnRender();

  for(auto p: projectiles) {
    if(p->IsAlive()) {p->OnRender();}
  }

  for(auto a: aliens) {
    if(a->IsAlive()) {a->OnRender();}
  }

  for(auto s: secondaliens) {
    if(s->IsAlive()) {s->OnRender();}
  }
 
  for(auto t: thirdaliens) {
    if(t->IsAlive()) {t->OnRender();}
  }

  for(auto w: walls) {
    w->OnRender();
  }
  // Switch the off-screen buffer to be on-screen
  SDL_RenderPresent(sf_window->getRenderer());
}

void SFApp::FireProjectile() {
  auto pb = make_shared<SFAsset>(SFASSET_PROJECTILE, sf_window);
  auto v  = player->GetPosition();
  pb->SetPosition(v);
  projectiles.push_back(pb);
}


void SFApp::addScore(int s) {

       Score+= s;

       //End Game
       if(Score == 100) {
         cout<<"Congratulations! You Scored: "<<Score<<endl;
         is_running = false;
         
      }
     
   } 

