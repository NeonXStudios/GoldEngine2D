#pragma once
#include "../UI/UIManager.h"

class MoveGizmos
{
public:
	//Entity* parent;
	Entity* left;
	Entity* top;
	Entity* dragEntity;
	bool dragging;
	bool usingTop, usingLeft;
	string getPathProject;

	void start() {
		setup();
		left = new Entity();
		top = new Entity();
		//parent = new Entity();

		left->addComponent <SpriteComponent>();
		top->addComponent  <SpriteComponent>();
		//parent->addComponent  <SpriteComponent>();

		left->getComponent <SpriteComponent>().TexturePath = "Editor/engine/GIZMOS/LeftPos.png";
		top->getComponent  <SpriteComponent>().TexturePath = "Editor/engine/GIZMOS/TopPos.png";

		left->getComponent <SpriteComponent>().LoadTexture();
		top->getComponent  <SpriteComponent>().LoadTexture();

		top->getComponent <SpriteComponent>().rotationAngle = 90;

		left->getComponent <SpriteComponent>().GlobalScale *= 2;
		top->getComponent <SpriteComponent>().GlobalScale *= 2; 
	}

	void setup();

	void draw() {
		glm::vec2 WorldPoint = RenderSystem::RenderSystem::ScreenToViewPort(glm::vec2(UIManager::instance->sceneui->imagePosition.x, UIManager::instance->sceneui->imagePosition.y), glm::vec2(UIManager::instance->sceneui->imageSizeSCENE.x, UIManager::instance->sceneui->imageSizeSCENE.y));


		if (UIManager::instance->inspectorui->ObjectSelectToInspector != nullptr) {
			//parent->getComponent<SpriteComponent>().ObjectPosition = UIManager::instance->inspectorui->ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition;

			if (!dragging) {
				left->getComponent <SpriteComponent>().ObjectPosition = UIManager::instance->inspectorui->ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition + glm::vec3(-100, 0, 0);
				top->getComponent <SpriteComponent>().ObjectPosition = UIManager::instance->inspectorui->ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition + glm::vec3(0, 100, 0);
			}

			left->entity = left;
			top->entity = top;

			left->update();
			top->update();

			glm::vec3& obj = left->getComponent<SpriteComponent>().ObjectPosition;
			float objWidth = left->getComponent<SpriteComponent>().Scale.x * left->getComponent<SpriteComponent>().GlobalScale;
			float objHeight = left->getComponent<SpriteComponent>().Scale.y * left->getComponent<SpriteComponent>().GlobalScale;
			float radians = left->getComponent<SpriteComponent>().rotationAngle * (b2_pi / 180.0f);

			glm::vec2 localPoint = RotatePoint(glm::vec2 (-WorldPoint.x, WorldPoint.y), obj, radians);
			glm::vec2 rotatedBoxMin(obj.x - objWidth * 0.5f, obj.y - objHeight * 0.5f);
			glm::vec2 rotatedBoxMax(obj.x + objWidth * 0.5f, obj.y + objHeight * 0.5f);

			if (localPoint.x >= rotatedBoxMin.x && localPoint.x <= rotatedBoxMax.x &&
				localPoint.y >= rotatedBoxMin.y && localPoint.y <= rotatedBoxMax.y) {
				UIManager::instance->sceneui->LockWithGizmos = true;
				usingLeft = true;

				if (ImGui::IsMouseClicked(0)) {
					std::cout << "Draw gizmos" << std::endl;
					dragEntity = left;
				}
			}
			else {
				usingLeft = false;
				if (!usingTop)
				UIManager::instance->sceneui->LockWithGizmos = false;

				if (dragEntity == left) {
					dragEntity == nullptr;
				}

				if (ImGui::IsMouseClicked(0)) {

				}
			}

			


			glm::vec3& objTop = top->getComponent<SpriteComponent>().ObjectPosition;
			float objWidthTop = top->getComponent<SpriteComponent>().Scale.x * top->getComponent<SpriteComponent>().GlobalScale;
			float objHeightTop = top->getComponent<SpriteComponent>().Scale.y * top->getComponent<SpriteComponent>().GlobalScale;
			float radiansTop = top->getComponent<SpriteComponent>().rotationAngle * (b2_pi / 180.0f);

			glm::vec2 localPointTop = RotatePoint(glm::vec2 (-WorldPoint.x, WorldPoint.y), objTop, radiansTop);
			glm::vec2 rotatedBoxMinTop(objTop.x - objWidth * 0.5f, objTop.y - objHeight * 0.5f);
			glm::vec2 rotatedBoxMaxTop(objTop.x + objWidth * 0.5f, objTop.y + objHeight * 0.5f);



			if (localPointTop.x >= rotatedBoxMinTop.x && localPointTop.x <= rotatedBoxMaxTop.x &&
				localPointTop.y >= rotatedBoxMinTop.y && localPointTop.y <= rotatedBoxMaxTop.y) {
				UIManager::instance->sceneui->LockWithGizmos = true;
				usingTop = true;

				if (ImGui::IsMouseClicked(0)) {
					std::cout << "Draw gizmos" << std::endl;
					dragEntity = top;
				}
			}
			else {
				usingTop = false;

				if (dragEntity == top) {
					dragEntity == nullptr;
				}

				if (!usingLeft)
				UIManager::instance->sceneui->LockWithGizmos = false;
			}
		}


		if (dragEntity != nullptr && dragEntity == left) {
			if (dragging) {


				SpriteComponent* sprite = &left->getComponent<SpriteComponent>();
				SpriteComponent* parentSprite = &UIManager::instance->inspectorui->ObjectSelectToInspector->getComponent<SpriteComponent>();
				float getDistance = glm::distance (glm::vec3 (-WorldPoint.x, WorldPoint.y, 0), sprite->ObjectPosition);

				float distanceOffset = glm::distance(sprite->ObjectPosition, parentSprite->ObjectPosition);

				left->getComponent<SpriteComponent>().ObjectPosition.x = -WorldPoint.x;
				parentSprite->ObjectPosition.x = left->getComponent<SpriteComponent>().ObjectPosition.x + distanceOffset;
				top->getComponent <SpriteComponent>().ObjectPosition.y = UIManager::instance->inspectorui->ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition.y + 100;
				top->getComponent <SpriteComponent>().ObjectPosition.x = UIManager::instance->inspectorui->ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition.x;
			}
		}

		if (dragEntity != nullptr && dragEntity == top) {
			if (dragging) {
				SpriteComponent* sprite = &top->getComponent<SpriteComponent>();
				SpriteComponent* parentSprite = &UIManager::instance->inspectorui->ObjectSelectToInspector->getComponent<SpriteComponent>();

				float distanceOffset = glm::distance(sprite->ObjectPosition, parentSprite->ObjectPosition);

				top->getComponent<SpriteComponent>().ObjectPosition.y = WorldPoint.y;
				parentSprite->ObjectPosition.y = top->getComponent<SpriteComponent>().ObjectPosition.y - distanceOffset;
				left->getComponent <SpriteComponent>().ObjectPosition.y = UIManager::instance->inspectorui->ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition.y;
			}
		}


		if (ImGui::IsMouseReleased(0)) {
			dragEntity = nullptr;
		}

		dragging = ImGui::IsMouseDragging(0);

	}

	glm::vec2 RotatePoint(const glm::vec2& point, const glm::vec2& center, float angle) {
		glm::vec2 rotatedPoint;
		float cosTheta = cos(angle);
		float sinTheta = sin(angle);

		rotatedPoint.x = center.x + (point.x - center.x) * cosTheta - (point.y - center.y) * sinTheta;
		rotatedPoint.y = center.y + (point.x - center.x) * sinTheta + (point.y - center.y) * cosTheta;

		return rotatedPoint;
	}
};