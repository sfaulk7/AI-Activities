#include "Engine.h"
#include "raylib.h"
#include "Transform2D.h"
#include "SteeringBehaviorsScene.h"
#include "FiniteStateMachineScene.h"
#include "DijkstrasSearchScene.h"

bool Engine::m_applicationShouldClose = false;
Scene** Engine::m_scenes = new Scene*;
//Engine::m_actorsToDelete = ActorArray();
DynamicArray<Actor*> Engine::m_actorsToDelete;
int Engine::m_sceneCount = 0;
int Engine::m_currentSceneIndex = 0;


Engine::Engine()
{
	m_applicationShouldClose = false;
	m_scenes = new Scene*;
	m_camera = new Camera2D();
	m_currentSceneIndex = 0;
	m_sceneCount = 0;
}

void Engine::start()
{
	//Initialize window
	int screenWidth = 1400;
	int screenHeight = 1000;
	InitWindow(screenWidth, screenHeight, "Intro To C++");
	SetTargetFPS(0);

	//Add the scenes
	
	addScene(new SteeringBehaviorsScene()); //scene index 0
	addScene(new FiniteStateMachineScene()); //scene index 1
	addScene(new DijkstrasSearchScene()); //scene index 2

	//Start the scenes
	m_currentSceneIndex = 2;
	m_scenes[m_currentSceneIndex]->start();
	m_currentSceneIndex = 1;
	m_scenes[m_currentSceneIndex]->start();
	m_currentSceneIndex = 0;
	m_scenes[m_currentSceneIndex]->start();
}

void Engine::update(float deltaTime)
{
	//Show scene control
	DrawText("ENTER to swap between scenes", 10, 950, 10, YELLOW);
	switch (m_currentSceneIndex)
	{
		case 0: // current scene is SteeringBehaviors
		{
			DrawText("Current Scene: SteeringBehaviors", 10, 960, 10, YELLOW);
			break;
		}

		case 1: // current scene is FiniteStateMachine
		{
			DrawText("Current Scene: FiniteStateMachine", 10, 960, 10, YELLOW);
			break;
		}
	}

	//Clean up actors marked for destruction
	destroyActorsInList();

	//Update scene
	m_scenes[m_currentSceneIndex]->update(deltaTime);
	m_scenes[m_currentSceneIndex]->updateUI(deltaTime);

	//Change scene to finite state machine
	if (IsKeyPressed(KEY_ENTER))
	{
		m_currentSceneIndex++;

		if (m_currentSceneIndex >= 3)
		{
			m_currentSceneIndex = 0;
		}
	}
}

void Engine::draw()
{
	BeginDrawing();

	ClearBackground(BLACK);

	m_scenes[m_currentSceneIndex]->draw();
	m_scenes[m_currentSceneIndex]->drawUI();

	EndDrawing();
}

void Engine::end()
{
	m_scenes[m_currentSceneIndex]->end();
	CloseWindow();
}

void Engine::run()
{
	//Create window and start scene
	start();

	//Loop while the application shouldn't end
	while (!m_applicationShouldClose && !RAYLIB_H::WindowShouldClose())
	{
		//Calculate deltatime
		float deltaTime = RAYLIB_H::GetFrameTime();

		//Update scene
		update(deltaTime);

		//Draw current scene
		draw();
	}

	end();
}

Scene* Engine::getScene(int index)
{
	//Return nullptr if the scene is out of bounds
	if (index < 0 || index >= m_sceneCount)
		return nullptr;

	return m_scenes[index];
}

Scene* Engine::getCurrentScene()
{
	return m_scenes[m_currentSceneIndex];
}

int Engine::getCurrentSceneIndex()
{
	return m_currentSceneIndex;
}

int Engine::addScene(Scene* scene)
{
	///If the scene is null then return before running any other logic
	if (!scene)
		return -1;

	//Create a new temporary array that one size larger than the original
	Scene** tempArray = new Scene * [m_sceneCount + 1];

	//Copy values from old array into new array
	for (int i = 0; i < m_sceneCount; i++)
	{
		tempArray[i] = m_scenes[i];
	}

	//Store the current index
	int index = m_sceneCount;

	//Sets the scene at the new index to be the scene passed in
	tempArray[index] = scene;

	delete m_scenes;

	//Set the old array to the tmeporary array
	m_scenes = tempArray;
	m_sceneCount++;

	return index;
}

void Engine::addActorToDeletionList(Actor* actor)
{
	//return if the actor is already going to be deleted
	if (m_actorsToDelete.Contains(actor))
		return;

	//Add actor to deletion list
	m_actorsToDelete.Add(actor);

	//Add all the actors children to the deletion list
	for (int i = 0; i < actor->getTransform()->getChildCount(); i++)
	{
		m_actorsToDelete.Add(actor->getTransform()->getChildren()[i]->getOwner());
	}
}

bool Engine::removeScene(Scene* scene)
{
	//If the scene is null then return before running any other logic
	if (!scene)
		return false;

	bool sceneRemoved = false;

	//Create a new temporary array that is one less than our original array
	Scene** tempArray = new Scene * [m_sceneCount - 1];

	//Copy all scenes except the scene we don't want into the new array
	int j = 0;
	for (int i = 0; i < m_sceneCount; i++)
	{
		if (tempArray[i] != scene)
		{
			tempArray[j] = m_scenes[i];
			j++;
		}
		else
		{
			sceneRemoved = true;
		}
	}

	//If the scene was successfully removed set the old array to be the new array
	if (sceneRemoved)
	{
		m_scenes = tempArray;
		m_sceneCount--;
	}


	return sceneRemoved;
}

void Engine::setCurrentScene(int index)
{
	//If the index is not within the range of the the array return
	if (index < 0 || index >= m_sceneCount)
		return;

	//Call end for the previous scene before changing to the new one
	if (m_scenes[m_currentSceneIndex]->getStarted())
		m_scenes[m_currentSceneIndex]->end();

	//Update the current scene index
	m_currentSceneIndex = index;
}

bool Engine::getKeyDown(int key)
{
	return RAYLIB_H::IsKeyDown((KeyboardKey)key);
}

bool Engine::getKeyPressed(int key)
{
	return RAYLIB_H::IsKeyPressed((KeyboardKey)key);
}

void Engine::destroy(Actor* actor)
{
	addActorToDeletionList(actor);
}

void Engine::destroyActorsInList()
{
	//Iterate through deletion list
	for (int i = 0; i < m_actorsToDelete.Length(); i++)
	{
		//Remove actor from the scene
		Actor* actorToDelete = m_actorsToDelete[i];
		if (!getCurrentScene()->removeActor(actorToDelete))
			getCurrentScene()->removeUIElement(actorToDelete);

		//Call actors clean up functions
		actorToDelete->end();
		actorToDelete->onDestroy();

		//Delete the actor
		delete actorToDelete;
	}

	//Clear the array
	m_actorsToDelete.Clear();
}

void Engine::CloseApplication()
{
	Engine::m_applicationShouldClose = true;
}