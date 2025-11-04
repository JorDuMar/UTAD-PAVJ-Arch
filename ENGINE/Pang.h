#pragma once


class EntityManager;
class Engine;

class Pang
{
public:
  Pang(Engine* engine);
  ~Pang();
  //Start Game screen. Waits until space is pressed.
  void StartGame();
  //The Pang game logic. Manages the timer, the collision between the player and enemy and the enemies spawn.
  void GameLogic();
  //Load the best time from a XML file
  bool LoadBestScore(const char* filename);
  //Save the best time in a XML file
  bool SaveBestScore(const char* filename) const;
  //Returns true if the game is paused (in Start Game screen)
  bool isPaused() const;

  EntityManager* m_pEntManager = nullptr;
  Engine* m_pEngine = nullptr;

  unsigned int gameMinutes = 0;
  unsigned int gameSeconds = 0;

  unsigned int bestMinutes = 0;
  unsigned int bestSeconds = 0;

private:
  int m_iPlayerEntity = -1;

  double totalTime = 0.;
  double gameSecs = 0.;
  double bestTime = 0.;
  bool paused = true;
  bool cooldown = false;


 
};