#pragma once
#include "Cell.h"


// WARNING
// MAKE SURE YOU FOLLOW THESE RULES IN YOUR CellRoles FUNCTIONS
//
// 1.	Do not mofidy cells vector in roles - all roles are called for elements of the vector. 
//		If you modify the vector during update procedure it will cause vector's memory realocation
//		and then SEGFAULT or other NullPtrException.
//		Use Environment::getInstance().addNewCell(..cell..) instead.
//
// 2.	For all value changes use deltaTime from CellSimApp.
//
// 3.	If you want kill cell use this->kill() [will be moved to dead cells vector],
//		if you want delete cell from cells vector use this->markAsDeleted() [will be removed from any vector].
//
//
// 4.	REGISTER ALL NEW ADDED ROLES IN CellRoles C-TOR
//		This is needed to properly save cell to file.

class CellRoles
{
public:
	using RolePtr = void(*)(Cell*);

	RolePtr getRoleById(int id);

	int getRoleId(RolePtr ptr);

	static CellRoles& getManager();


	static void moveForward(Cell* c);

	static void changeDirection(Cell* c);

	static void changeSpeed(Cell* c);

	static void eat(Cell* c);

	static void updateColor(Cell* c);

	static void beDead(Cell* c);

	static void simulateHunger(Cell * c);

	static void divideAndConquer(Cell * c);

	static void grow(Cell * c);

	static void getingHot(Cell * c);

	static void makeFood(Cell * c);

	static void fight(Cell * c);

	static void makeOlder(Cell * c);

	static void mutate(Cell * c);

	static void sniffForFood(Cell * c);

	static void checkCollisions(Cell * c);

	static void sniffForCell(Cell * c);

	/// \returns true if collision occured - otherwise false
	static bool checkEnvironmentBounds(Cell* c);
private:
	CellRoles();
	inline void registerRole(RolePtr ptr, int id, std::string roleName = "");

	std::map<int, RolePtr> idToRole;
	std::map<RolePtr, int> roleToId;
};

