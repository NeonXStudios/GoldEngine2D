#pragma once
#include "../../Editor/GoldEditor.h"
#include "SceneUI.h"
#include "../UIManager.h"
#include <imguizmo/ImGuizmo.h>
#include <glm/glm.hpp>
#include <iostream>

ImGuizmo::MODE gizmoMode(ImGuizmo::LOCAL);
ImGuizmo::OPERATION gizmoOperation(ImGuizmo::TRANSLATE);

using namespace ImGuizmo;
using namespace std;

    void SceneUI::start () {
        glGenFramebuffers(1, &framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, AppSettings::instance->ScreenWidth, AppSettings::instance->ScreenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer is not complete!" << std::endl;

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }


    void SceneUI::draw() {

#pragma region DRAW TEXTURE SCENE



        ImVec2 windowSize = ImVec2(AppSettings::ScreenWidth, AppSettings::ScreenHeight);

        // Dibujamos la imagen en la ventana de ImGui
        ImGui::SetNextWindowSize(windowSize);
        ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
        //RenderSizeWindow = ImGui::GetWindowSize();
        ImGuizmo::SetDrawlist();

        ImVec2 windowPos = ImGui::GetWindowPos();
        ImVec2 offset = ImGui::GetWindowContentRegionMin();
        ImVec2 size = ImGui::GetContentRegionAvail();
        ImVec2 p = ImGui::GetCursorScreenPos();

        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        // Obtenemos el tamaño de la ventana de ImGui después de que se apliquen las restricciones de tamaño
        ImVec2 actualWindowSize = ImGui::GetWindowSize();
        float scaleFactor = std::min(actualWindowSize.x / windowSize.x, actualWindowSize.y / windowSize.y);
        imageSizeSCENE = ImVec2(AppSettings::ScreenWidth * scaleFactor, AppSettings::ScreenHeight * scaleFactor);


        // Calculamos la posición para centrar la imagen en la ventana
        imagePosition = ImVec2((actualWindowSize.x - imageSizeSCENE.x) * 0.5f, (actualWindowSize.y - imageSizeSCENE.y) * 0.5f);

        ImGui::SetCursorPos(imagePosition);

        int WindowXSize = imageSizeSCENE.x;
        int WindowYSize = imageSizeSCENE.y;
        imageSizeSCENE.x = WindowXSize;
        imageSizeSCENE.y = WindowYSize;

        // Invertimos las coordenadas de textura en el eje Y antes de mostrar la imagen
        ImGui::Image((void*)(intptr_t)texture, ImVec2(WindowXSize, WindowYSize), ImVec2(ImVec2(0, 1)), ImVec2(ImVec2(1, 0)));
        GoldEditor::editor->activeMouse = ImGui::IsItemHovered();

#pragma region IMGUIZMO 


        if (UIManager::instance->inspectorui->ObjectSelectToInspector != nullptr) {
            bool ignoreGui = false;
            static ImGuizmo::MODE gizmoMode(ImGuizmo::LOCAL);
            static ImGuizmo::OPERATION gizmoOperation(ImGuizmo::TRANSLATE);
            float* matrix = (float*)glm::value_ptr(UIManager::instance->inspectorui->ObjectSelectToInspector->getComponent<SpriteComponent>().GetMatrix());

            float* projection = (float*)glm::value_ptr(SceneManager::GetSceneManager()->OpenScene->worldCamera->GetProjectionMatrix());
            float* view = (float*)glm::value_ptr(SceneManager::GetSceneManager()->OpenScene->worldCamera->GetView());
            ImGuizmo::SetRect(p.x, p.y, size.x, size.y);

            const bool res = ImGuizmo::Manipulate(view, projection, gizmoOperation, gizmoMode, matrix);

            ignoreGui &= !ImGuizmo::IsOver();

            glm::vec3 matrixRotation;
            ImGuizmo::DecomposeMatrixToComponents(
                matrix,
                glm::value_ptr(UIManager::instance->inspectorui->ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition),
                glm::value_ptr(matrixRotation),
                glm::value_ptr(UIManager::instance->inspectorui->ObjectSelectToInspector->getComponent<SpriteComponent>().Scale)
            );

            //std::cout << "GIZMO OVER: " << ignoreGui << std::endl;

            //UIManager::instance->inspectorui->ObjectSelectToInspector->getComponent<SpriteComponent>().rotation = glm::quat(glm::radians(matrixRotation));
        }
#pragma endregion

        if (!UIManager::instance->rightClickui->miniMenuOpen) {
            UIManager::instance->rightClickui->SceneHover = ImGui::IsWindowHovered();
        }

        //std::cout << "Nuevo tamaño de la textura: " << imageSizeSCENE.x << "x" << imageSizeSCENE.y << std::endl;

        // Después de obtener el nuevo tamaño de la textura, puedes usarlo como lo necesites

        imagePosition.x += ImGui::GetWindowPos().x;
        imagePosition.y += ImGui::GetWindowPos().y;

        glm::vec2 WorldPoint = RenderSystem::RenderSystem::ScreenToViewPort (glm::vec2 (imagePosition.x, imagePosition.y), glm::vec2 (imageSizeSCENE.x, imageSizeSCENE.y));
        glm::vec2 initialMousePos;  // Posición del mouse cuando comenzó el arrastre
        glm::vec2 initialObjectPos; // Posición inicial del objeto cuando comenzó el arrastre

        if (ImGui::BeginDragDropTarget())
        {
            ImGuiDragDropFlags target_flags = 0;
            target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;
            target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;


            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("TEXTUREDA_PATH", target_flags))
            {
                if (ImGui::IsMouseReleased(0)) {
                    const char* receivedString = static_cast<const char*>(payload->Data);

                    Entity* newOBJ = SceneManager::GetSceneManager()->NewEntity();
                    newOBJ->getComponent<SpriteComponent>().TexturePath = AComponent::RemoveDir (receivedString);
                    newOBJ->getComponent<SpriteComponent>().LoadTexture();

                    newOBJ->getComponent <SpriteComponent>().ObjectPosition = glm::vec3(WorldPoint.x, WorldPoint.y, 0);
                }
            }


            ImGui::EndDragDropTarget();
        }

        if (ImGui::IsWindowHovered() && !LockWithGizmos) {
            float maxZ = -std::numeric_limits<float>::max();

            //for (int i = 0; i < SceneManager::GetSceneManager()->OpenScene->objectsInScene.size(); i++) {
            //    Entity* objD = SceneManager::GetSceneManager()->OpenScene->objectsInScene[i];
            //    glm::vec3& obj = objD->getComponent<SpriteComponent>().ObjectPosition;
            //    float objWidth = objD->getComponent<SpriteComponent>().Scale.x * objD->getComponent<SpriteComponent>().GlobalScale;
            //    float objHeight = objD->getComponent<SpriteComponent>().Scale.y * objD->getComponent<SpriteComponent>().GlobalScale;

            //    // Obtén la rotación en radianes desde Box2D
            //    float radians = objD->getComponent<SpriteComponent>().rotationAngle * (b2_pi / 180.0f);

            //    // Aplica la rotación inversa al punto del mundo
            //    glm::vec2 localPoint = RotatePoint(glm::vec2 (WorldPoint.x, WorldPoint.y), obj, radians);

            //    // Calcula las coordenadas de la caja delimitadora del objeto rotado
            //    glm::vec2 rotatedBoxMin(obj.x - objWidth * 0.5f, obj.y - objHeight * 0.5f);
            //    glm::vec2 rotatedBoxMax(obj.x + objWidth * 0.5f, obj.y + objHeight * 0.5f);
            //    glm::vec2 dragOffset;


            //     //Comprueba si el punto rotado está dentro de la caja delimitadora rotada
            //    if (localPoint.x >= rotatedBoxMin.x && localPoint.x <= rotatedBoxMax.x &&
            //        localPoint.y >= rotatedBoxMin.y && localPoint.y <= rotatedBoxMax.y) {

            //        //std::cout << "Objects in this position" << objectsInAABB.size() << std::endl;
            //        if (std::find(objectsInAABB.begin(), objectsInAABB.end(), objD) == objectsInAABB.end()) {
            //            objectsInAABB.push_back(objD);
            //        }
            //        if (ImGui::IsMouseClicked(0)) {
            //            if (objectsInAABB.size() > 0) {
            //                SelectIndex++;
            //            }

            //            if (SelectIndex > objectsInAABB.size() - 1) {
            //                SelectIndex = 0;
            //            }
            //            if (UIManager::instance->inspectorui->ObjectSelectToInspector != objD) {
            //                UIManager::instance->inspectorui->SelectEntity(objectsInAABB[SelectIndex]);
            //            }

            //            /*if (UIManager::instance->inspectorui->ObjectSelectToInspector != nullptr && UIManager::instance->inspectorui->ObjectSelectToInspector != objD) {
            //                UIManager::instance->inspectorui->SelectEntity(objD);
            //            }
            //            else {
            //                if (UIManager::instance->inspectorui->ObjectSelectToInspector == nullptr) {
            //                    UIManager::instance->inspectorui->SelectEntity(objD);
            //                }
            //            }*/
            //            ObjectSelect = true;

            //            UIManager::instance->hierarhcyui->SelectInHierarchy = false;
            //            std::cout << "Clicked object" << std::endl;
            //            break;
            //        }
            //    }
            //    else {
            //        auto it = std::find(objectsInAABB.begin(), objectsInAABB.end(), objD);
            //        if (it != objectsInAABB.end()) {
            //            objectsInAABB.erase(it);
            //        }

            //        if (ImGui::IsMouseClicked (0) && !LockWithGizmos) {
            //            UIManager::instance->inspectorui->ObjectSelectToInspector = nullptr;
            //        }
            //    }

            //    
            //    if (ImGui::IsMouseDragging (0) && ImGui::IsMouseDown(0) && UIManager::instance->inspectorui->ObjectSelectToInspector != nullptr) {
            //            //UIManager::instance->inspectorui->ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition.x = WorldPoint.x;
            //            //UIManager::instance->inspectorui->ObjectSelectToInspector->getComponent<SpriteComponent>().ObjectPosition.y = WorldPoint.y;
            //        isdragging = true;
            //    }

            //    if (!ImGui::IsMouseDragging (0)) {
            //        isdragging = false;
            //    }
            //}
        }        
        ImGui::End();
#pragma endregion
    }


    void SceneUI::update() {

    }

    void SceneUI::lateupdate() {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    }


    void SceneUI::fixupdate() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Copiar el contenido del framebuffer en la textura
        glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
        glBindTexture(GL_TEXTURE_2D, texture);
        glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, AppSettings::instance->ScreenWidth, AppSettings::instance->ScreenHeight, 0);
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    }


    glm::vec2 SceneUI::RotatePoint(const glm::vec2& point, const glm::vec2& center, float angle) {
        glm::vec2 rotatedPoint;
        float cosTheta = cos(angle);
        float sinTheta = sin(angle);

        rotatedPoint.x = center.x + (point.x - center.x) * cosTheta - (point.y - center.y) * sinTheta;
        rotatedPoint.y = center.y + (point.x - center.x) * sinTheta + (point.y - center.y) * cosTheta;

        return rotatedPoint;
    }
