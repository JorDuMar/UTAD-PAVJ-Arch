#pragma once

class EntityManager
{
public:
  EntityManager();
  ~EntityManager();
  //Creates a Player entity with ID 1 and their corresponding components. 
  // If it has already been created, return Player ID.
  int CreatePlayer();

  //Gets Player ID
  int GetPlayer() const;
  //Gets the current number of enemies
  int GetCurrentNumEnemies() const;

  //Creates an Enemy entity with ID from 2 and their corresponding components. 
  //Add component position using coordinates x and y.
  void CreateEnemy(int x, int y);
  //Deletes all the enemies
  void ResetGame();

private:
  unsigned int currentEnemies = 0;
  unsigned int entities = 2;
  int m_iNone = 0, m_iPlayer = -1;
  const char* spriteMatrix[2][3] =
  {
    {"./data/VerySmallBlue.png", "./data/VerySmallGreen.png", "./data/VerySmallRed.png"},
    {"./data/SmallBlue.png", "./data/SmallGreen.png", "./data/SmallRed.png"}
  };

};