
#pragma once
#ifndef GOLDENGINELIB_H
#define GOLDENGINELIB_H

//LIBRARYS FOR THE MOTOR FUNCTIONS
#include "EngineBehaviour.h"
#include "../Graphics/StartEngineGraphics.h"
#include "../Graphics/RunEngine.h"
#include "../Graphics/AppSettings.h"

//EXTRA LIBS
#include "nlohmann/json.hpp"

//ENGINE COMPONENTS
#include "../Components/AudioSource/AudioManager.h"
#include "../Components/AudioSource/AudioSource.h"
#include "../Components/Camera/Camera2D.h"
#include "../Components/ECS/ECS.h"
#include "../Components/SceneManager/SceneManager.h"
#include "../Components/SceneManager/Scene.h"
#include "../Components/UI/UIImplement.h"
#include "../Components/Debug/DrawBox.h"
#include "../Components/Sprite/SpriteComponent.h"
#include "../Components/Systems/SystemsEvents.h"
#include "../Components/Systems/PickingTexture.h"
#include "../Components/Script/ScriptCompiler.h"
#include "../Components/Physics/RigidBody.h"
#include "../Components/Physics/ObjectCaster.h"
#include "../Components/Animator/Animator2D.h"
#include "../Components/Skybox/Skybox.h"
#include "../Components/SaveSystem/SaveSystem.h"
#include "../Components/Light/Light.h"
#include "../Components/Physics/LayerMaskSystem.h"
#include "../Components/TileMap/TileMapComponent.h"

//PHYSICS 3D IMPLEMENTATION 
//#include "../Components/Physics3D/Rigidbody3D.h"
//#include "../Components/Physics3D/BoxCollider.h"
//#include "../Components/Physics3D/Cast3D.h"

//#include "../Components/Shadercompiler/Material.h"

//#define MESHCLASS_H
//#include "../Components/Models/Mesh.h"


//#define MODELCLASS_H
//#include "../Components/Models/Model.h"
#endif