#pragma once
#include <iostream>
#include <string>
#include "Components/CAudio.h"
#include "Components/CSprite.h"
#include "Components/CScript.h"
#include "Components/CRigidBody.h"
//#include "Components/CRigidBody3D.h"
//#include "Components/CBoxCollider3D.h"

class InspectorComponents
{
public:

	void update (Entity* ownerActor);
};