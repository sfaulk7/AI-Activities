#include "AStarPathfinding.h"
#include <algorithm>
#include <vector> 
#include <chrono>
#include <iostream>



namespace AStarpathfinding
{
	//Use this function to sort nodes using their fScore value
	bool NodeSort(Node* i, Node* j)
	{
		return (i->fScore < j->fScore);
	}

	void Node::ConnectTo(Node* other, float cost)
	{
		connections.push_back(Edge(other, cost));
	}

	std::vector<Node*> AStarSearch(Node* startNode, Node* endNode)
	{
		auto start = std::chrono::high_resolution_clock::now();


		//Validate the input
		if (startNode == nullptr || endNode == nullptr)
		{
			return std::vector<Node*>();
		}

		if (startNode == endNode)
		{
			std::vector<Node*> singleNodePath;
			singleNodePath.push_back(startNode);
			return singleNodePath;
		}

		//Initialize the starting node
		startNode->gScore = 0;
		startNode->hScore = 0;
		startNode->fScore = 0;
		startNode->previous = nullptr;

		//Create our temporary lists for storing nodes
		std::vector<Node*> openList;
		std::vector<Node*> closedList;

		//Add the starting node to openList
		openList.push_back(startNode);


		while (!openList.empty())
		{
			//Sort openList based on fScore using the function created above
			std::sort(openList.begin(), openList.end(), NodeSort);

			//Set the current node to the first node in the openList
			Node* currentNode = openList.front();
			//Remove currentNode from openList
			openList.erase(openList.begin());
			//Add currentNode to closedList
			closedList.push_back(currentNode);

			//If the destination node was added to the closed list,
			//the shortest path has been found
			if (currentNode == endNode)
			{
				break;
			}

			//For each Edge e in currentNode's connections
			for (Edge e : currentNode->connections)
			{
				//If the target node is in the closedList, ignore it
				if (std::find(closedList.begin(), closedList.end(), e.target) != closedList.end()) 
				{
					continue;
				}
				//If the target node is not in the openList, update it
				if (std::find(openList.begin(), openList.end(), e.target) == openList.end()) 
				{
					//Calculate the target node's G, H, and F Scores
					e.target->gScore = currentNode->gScore + e.cost; //Cost so far
					//e.target->hScore = abs((endNode->position.x - currentNode->position.x)) +
					//	abs((endNode->position.y - currentNode->position.y)); //Cost remaining
					float hvalue = sqrt(
						((endNode->position.x - currentNode->position.x) * (endNode->position.x - currentNode->position.x))
						+
						((endNode->position.y - currentNode->position.y) * (endNode->position.y - currentNode->position.y))); //Cost remaining
					e.target->hScore = hvalue / 32;

					e.target->fScore = e.target->gScore + e.target->hScore; // G + H

					//Set the target node's previous to currentNode
					e.target->previous = currentNode;
					//Find the earliest point we should insert the node
					//to the list to keep it sorted
					auto insertionPos = openList.end();
					for (auto i = openList.begin(); i != openList.end(); i++) 
					{
						if (e.target->fScore < (*i)->fScore) 
						{
							insertionPos = i;
							break;
						}
					}
					//Insert the node at the appropriate position
					openList.insert(insertionPos, e.target);
				}
				//Otherwise the target node IS in the open list
				else 
				{
					//Compare the new F Score to the old one before updating
					if (currentNode->fScore + e.cost < e.target->fScore) 
					{
						//Calculate the target node's G, H, and F Scores
						e.target->gScore = currentNode->gScore + e.cost; //Cost so far
						//e.target->hScore = abs((endNode->position.x - currentNode->position.x)) +
						//	abs((endNode->position.y - currentNode->position.y)); //Cost remaining

						e.target->hScore = sqrt(
							((endNode->position.x - currentNode->position.x) * (endNode->position.x - currentNode->position.x))
							+
							((endNode->position.y - currentNode->position.y) * (endNode->position.y - currentNode->position.y))); //Cost remaining

						e.target->fScore = e.target->gScore + e.target->hScore; // G + H

						//Set the target node's previous to currentNode
						e.target->previous = currentNode;
					}
				}
			}
		}

		//Create path in reverse from endNode to startNode
		std::vector<Node*> path;
		Node* currentNode = endNode;

		while (currentNode != nullptr)
		{
			//Add the current node to the beginning of the path
			path.insert(path.begin(), currentNode);
			//Go to the previous node
			currentNode = currentNode->previous;
		}

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = end - start;
		auto durationAsValue = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
		std::cout << "AStar Chrono" << std::endl;
		std::cout << durationAsValue << std::endl;

		return path;
	}

	void DrawPath(std::vector<Node*>& path, Color lineColor)
	{
		for (int i = 1; i < path.size(); i++)
			DrawLine(path[i - 1]->position.x, path[i - 1]->position.y, path[i]->position.x, path[i]->position.y, lineColor);
	}

	void DrawNode(Node* node, bool selected)
	{
		static char bufferg[10];
		static char bufferh[10];
		static char bufferf[10];
		sprintf_s(bufferg, "%.0f", node->gScore);
		sprintf_s(bufferh, "%.0f", node->hScore);
		sprintf_s(bufferf, "%.0f", node->fScore);

		//Draw the circle for the outline
		DrawCircle(node->position.x, node->position.y, 25, YELLOW);
		//Draw the inner circle
		if (selected)
		{
			DrawCircle(node->position.x, node->position.y, 22, BROWN);
		}
		else
		{
			DrawCircle(node->position.x, node->position.y, 22, BLACK);
		}
		//Draw the text
		DrawText(bufferg, node->position.x - 10, node->position.y - 10, 15, WHITE);
		DrawText(bufferh, node->position.x + 10, node->position.y - 10, 15, WHITE);
		DrawText(bufferf, node->position.x, node->position.y - 15, 15, WHITE);
	}

	void DrawGraph(Node* node, std::vector<Node*>* drawnList)
	{
		DrawNode(node);
		drawnList->push_back(node);

		//For each Edge in this node's connections
		for (Edge e : node->connections)
		{
			//Draw the Edge
			DrawLine(node->position.x, node->position.y, e.target->position.x, e.target->position.y, WHITE);
			//Draw the cost
			Vector2 costPos = { (node->position.x + e.target->position.x) / 2, (node->position.y + e.target->position.y) / 2 };
			static char buffer[10];
			sprintf_s(buffer, "%.0f", e.cost);
			DrawText(buffer, costPos.x, costPos.y, 15, WHITE);
			//Draw the target node
			if (std::find(drawnList->begin(), drawnList->end(), e.target) == drawnList->end())
			{
				DrawGraph(e.target, drawnList);
			}
		}
	}
}