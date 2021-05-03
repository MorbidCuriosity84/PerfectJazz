﻿#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "../PerfectJazz/components/cmp_text.h"
#include "ecm.h"
#include <future>
#include <maths.h>
#include <mutex>
#include <string>

class Scene {
public:
	Scene() = default;
	virtual ~Scene();
	virtual void Load() = 0;
	virtual void LoadAsync();
	virtual void UnLoad();
	virtual void Update(const double& dt);
	void GameOver();
	virtual void Render();
	bool isLoaded() const;
	void levelOver();
	static int deadEnemies;
	std::shared_ptr<Entity> makeEntity();
	EntityManager ents;	

protected:
	void setLoaded(bool);
private:
	mutable bool _loaded;
	mutable std::future<void> _loaded_future;
	mutable std::mutex _loaded_mtx;
};

class Engine {
public:
	Engine() = delete;
	static void Start(unsigned int width, unsigned int height,
	const std::string& gameName, Scene* scn);
	static void ChangeScene(Scene*);
	static sf::RenderWindow& GetWindow();
	static sf::Vector2u getWindowSize();
	static void setVsync(bool b);
	static bool isGamePaused;
	static bool isMenu;
	static bool isPausedMenu;
	static bool isLevelComplete;
	static bool isLoading;
	static bool isLevelFinished;
	static Scene* _lastScene;
	static Scene* _activeScene;
	static int currentPlayerLevel;
	static double FPS;


private:
	static std::string _gameName;
	static void Update();
	static void Render(sf::RenderWindow& window);
	static void updateViewsSize();
};

namespace timing {
	// Return time since Epoc
	long long now();
	// Return time since last() was last called.
	long long last();
} // namespace timing