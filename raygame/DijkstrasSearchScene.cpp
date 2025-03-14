#include "DijkstrasSearchScene.h"
#include "Pathfinding/DijkstrasPathfinding.h"

void DijkstrasSearchScene::start()
{
	// create a map of nodes from some grid-based ASCII art
	m_nodeMap.cellSize = 32;
	std::vector<std::string> asciiMap;
	/*asciiMap.push_back("0000000000000000000000000");
	asciiMap.push_back("0101110111001010111011100");
	asciiMap.push_back("0101011101101010101110110");
	asciiMap.push_back("0101000000101010100000010");
	asciiMap.push_back("0111111111111111111111110");
	asciiMap.push_back("0100000010001010000001000");
	asciiMap.push_back("0111111111101011111111110");
	asciiMap.push_back("0000000000001000000000000");

	asciiMap.push_back("0000000000001000000000000");
	asciiMap.push_back("0101110111001010111011100");
	asciiMap.push_back("0101011101101010101110110");
	asciiMap.push_back("0101000000101010100000010");
	asciiMap.push_back("0111111111111111111111110");
	asciiMap.push_back("0000000000000000000000000");*/

	/*asciiMap.push_back("00000000000000000000000000000000000000000000");
	asciiMap.push_back("01111111111111111111111111111111111111111110");
	asciiMap.push_back("01111111111111111111111111111111111111111110");
	asciiMap.push_back("01111111111111111111111111111111111111111110");
	asciiMap.push_back("01111111111111111111111111111111111111111110");
	asciiMap.push_back("00000000000000000000000000000000000000011110");
	asciiMap.push_back("01111111111111111111111111111111111111111110");
	asciiMap.push_back("01111111111111111111111111111111111111111110");
	asciiMap.push_back("01111000000000000000000000000000000000000000");
	asciiMap.push_back("01111111111111111111101110111011101110111010");
	asciiMap.push_back("00000000000000000010101010101010101010101010");
	asciiMap.push_back("01111111111111111110101010101010101010101010");
	asciiMap.push_back("01000000000000000000101010101010101010101010");
	asciiMap.push_back("01111111111111111110101010101010101010101010");
	asciiMap.push_back("00000000000000000010101010101010101010101010");
	asciiMap.push_back("01111111111111111110111011101110111011101110");
	asciiMap.push_back("01000000000000000000000000000000000000000010");
	asciiMap.push_back("01111111111111111111111111111111111111111110");
	asciiMap.push_back("01111111111111111111111111111111111111111110");
	asciiMap.push_back("01111111111111111111111111111111111111111110");
	asciiMap.push_back("01111111111111111111111111111111111111111110");
	asciiMap.push_back("00000000000000000000000000000000000000000000");*/

	asciiMap.push_back("00000000000000000000000000000000000000000000");
	asciiMap.push_back("01111111111111111111111011111111111111111110");
	asciiMap.push_back("01111111111111111111111011111111111111111110");
	asciiMap.push_back("01111111111111111111111011111111111111111110");
	asciiMap.push_back("01111111111111111111111011111111111111111110");
	asciiMap.push_back("01111111111111111111111011111111111111111110");
	asciiMap.push_back("01111111111111111111111011111111111111111110");
	asciiMap.push_back("01111111111111111111111011111111111111111110");
	asciiMap.push_back("01111111111111111111111011111111111111111110");
	asciiMap.push_back("01111111111111111111111011111111111111111110");
	asciiMap.push_back("01111111111111111111111011111111111111111110");
	asciiMap.push_back("01111111111111111111111011111111111111111110");
	asciiMap.push_back("01111111111111111110001010001111111111111110");
	asciiMap.push_back("01111111111111111110111011101111111111111110");
	asciiMap.push_back("01111111111111111110000000001111111111111110");
	asciiMap.push_back("01111111111111111111111111111111111111111110");
	asciiMap.push_back("00000000000000000000000000000000000000000000");

	m_nodeMap.Initialise(asciiMap);

	m_pathAgent = new pathfinding::PathAgent;
	m_pathAgent->SetNode(m_nodeMap.GetNode(1, 1));
	m_pathAgent->speed = 500;
}

void DijkstrasSearchScene::update(float deltaTime)
{
	Color lineColor = { 255, 255, 255, 255 };
	bool drawNodeMap = true;

	m_nodeMap.Draw(true);
	pathfinding::DrawPath(m_pathAgent->path, lineColor);

	// read mouseclicks, left for start node, end for right node
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		Vector2 mousePos = GetMousePosition();
		pathfinding::Node* end = m_nodeMap.GetClosestNode(mousePos);
		m_pathAgent->GoToNode(end);
	}

	// Changes a node to be enable or disabled when right clicked
	/*if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
	{
		Vector2 mousePos = GetMousePosition();
		pathfinding::Node* end = m_nodeMap.GetClosestNode(mousePos);
	}*/

	m_pathAgent->Update(deltaTime);
	m_pathAgent->Draw();




	////Pathfinding::Node a(GetRandomValue(50, 1350), GetRandomValue(50, 950));
	////Pathfinding::Node b(GetRandomValue(50, 1350), GetRandomValue(50, 950));
	////Pathfinding::Node c(GetRandomValue(50, 1350), GetRandomValue(50, 950));

	//Pathfinding::Node a(150, 250);
	//Pathfinding::Node b(350, 250);
	//Pathfinding::Node c(550, 250);

	//Pathfinding::Node d(150, 450);
	//Pathfinding::Node e(350, 450);
	//Pathfinding::Node f(550, 450);

	//Pathfinding::Node g(150, 650);
	//Pathfinding::Node h(350, 650);
	//Pathfinding::Node i(550, 650);

	//Pathfinding::Node j(350, 850);

	////1st row
	//a.ConnectTo(&b, 7);
	//a.ConnectTo(&d, 3);

	////
	//b.ConnectTo(&c, 4);
	////
	//b.ConnectTo(&d, 8);
	//b.ConnectTo(&f, 8);

	////
	//c.ConnectTo(&f, 2);

	////2nd row
	//d.ConnectTo(&e, 6);
	//d.ConnectTo(&g, 4);

	////
	//e.ConnectTo(&i, 5);
	////
	//e.ConnectTo(&g, 8);
	//e.ConnectTo(&i, 8);

	////
	//f.ConnectTo(&e, 4);
	//f.ConnectTo(&i, 3);

	////3rd row
	//g.ConnectTo(&h, 6);
	//g.ConnectTo(&j, 8);

	////
	//h.ConnectTo(&j, 1);

	////
	//i.ConnectTo(&h, 3);
	//i.ConnectTo(&j, 7);



	//List<Pathfinding::Node*> list;
	//Pathfinding::DrawGraph(&a, &list);

	//List<Pathfinding::Node*> path = { &a, &b, &c };
	//Pathfinding::DrawPath(path, WHITE);

	//Pathfinding::DrawNode(&a, false);
	//Pathfinding::DrawNode(&b, false);
	//Pathfinding::DrawNode(&c, false);
	//Pathfinding::DrawNode(&d, false);
	//Pathfinding::DrawNode(&e, false);
	//Pathfinding::DrawNode(&f, false);
	//Pathfinding::DrawNode(&g, false);
	//Pathfinding::DrawNode(&h, false);
	//Pathfinding::DrawNode(&i, false);
	//Pathfinding::DrawNode(&j, true);

	////Pathfinding::DijkstrasSearch(&a, &c);

}

void DijkstrasSearchScene::end()
{
	delete m_pathAgent;
}