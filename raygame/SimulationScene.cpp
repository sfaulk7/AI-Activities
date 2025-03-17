#include "SimulationScene.h"
#include "Pathfinding/AStarPathfinding.h"
#include "Pathfinding/DijkstrasPathfinding.h"

/// <summary>
/// Simulation functioning
/// Four entities: Traders, Civilians, Knights, Kobolds
/// 
/// (PURPLE)
/// Traders slowly navigate the town with AStar
///		Will trade with nearby civilians
///		Can be attacked
/// 
/// (WHITE)
/// Civilians Wander to explore the town
///		Will stop to trade with traders
///		Can be attacked
/// 
/// (YELLOW)
/// Knights wander around the town until a trader or civilian gets attacked, 
/// in which they will use Dijkstras to go directly to them to help
///		Can not be attacked
/// 
/// (RED)
/// Kobolds will wander around the town quickly actively avoiding Knights but chasing traders and civilians
///		When withing a vicinity of a trader or civilian the kobold will use pursue to chase them
///		When a knight is nearby the kobold will stop pursuing and immediatly begin evading
/// </summary>

void SimulationScene::start()
{

}

void SimulationScene::update(float deltaTime)
{

}

void SimulationScene::end()
{

}