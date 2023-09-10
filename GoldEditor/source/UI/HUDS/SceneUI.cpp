#pragma once
#include "../../Editor/GoldEditor.h"
#include "SceneUI.h"
#include "../UIManager.h"
#include <imguizmo/ImGuizmo.h>
#include <glm/glm.hpp>
#include <iostream>


using namespace ImGuizmo;
using namespace std;


ImGuizmo::MODE gizmoMode(ImGuizmo::LOCAL);
ImGuizmo::OPERATION gizmoOperation(ImGuizmo::TRANSLATE);

//Shader* pickingShader = nullptr;
GLuint pickingFramebuffer; // FBO para renderizar la textura de selección
GLuint pickingTexture;     // Textura de selección
GLuint pickingShaderProgram; // Programa de sombreado para la selección

void SceneUI::start() {
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



    glGenTextures(1, &colorAndDepthTexture);
    glBindTexture(GL_TEXTURE_2D, colorAndDepthTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, AppSettings::instance->ScreenWidth, AppSettings::instance->ScreenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Crear y configurar el renderbuffer de profundidad
    glGenRenderbuffers(1, &depthRenderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, AppSettings::instance->ScreenWidth, AppSettings::instance->ScreenHeight);


    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void SceneUI::draw() {
#pragma region DRAW TEXTURE SCENE

    ImVec2 windowSize = ImVec2(AppSettings::ScreenWidth, AppSettings::ScreenHeight);

    // Dibujamos la imagen en la ventana de ImGui
    ImGui::SetNextWindowSize(windowSize);
    ImGui::Begin("Scene", nullptr, ImGuiWindowFlags_NoTitleBar);
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
        float* matrix = (float*)glm::value_ptr(UIManager::instance->inspectorui->ObjectSelectToInspector->transform->GetMatrix());

        float* projection = (float*)glm::value_ptr(SceneManager::GetSceneManager()->OpenScene->worldCamera->GetProjectionMatrix());
        float* view = (float*)glm::value_ptr(SceneManager::GetSceneManager()->OpenScene->worldCamera->GetView());
        ImGuizmo::SetRect(p.x, p.y, imageSizeSCENE.x, imageSizeSCENE.y);

        const bool res = ImGuizmo::Manipulate(view, projection, gizmoOperation, gizmoMode, matrix);

        ignoreGui &= !ImGuizmo::IsOver();

        glm::vec3 matrixRotation;
        ImGuizmo::DecomposeMatrixToComponents(
            matrix,
            glm::value_ptr(UIManager::instance->inspectorui->ObjectSelectToInspector->transform->Position),
            glm::value_ptr(matrixRotation),
            glm::value_ptr(UIManager::instance->inspectorui->ObjectSelectToInspector->transform->Scale)
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

    WorldPoint = RenderSystem::RenderSystem::ScreenToViewPort(glm::vec2(imagePosition.x, imagePosition.y), glm::vec2(imageSizeSCENE.x, imageSizeSCENE.y));
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
                newOBJ->getComponent<SpriteComponent>().TexturePath = AComponent::RemoveDir(receivedString);
                newOBJ->getComponent<SpriteComponent>().LoadTexture();

                newOBJ->transform->Position = glm::vec3(WorldPoint.x, WorldPoint.y, 0);
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


    if (ImGui::IsMouseDown (0)/* && ImGui::IsWindowHovered()*/) {

        glm::vec3 ray_origin;
        glm::vec3 ray_direction;

        double x, y;
        glfwGetCursorPos(StartEngineGraphics::window, &x, &y);

        double xPos = x - imagePosition.x;
        double yPos = y - imagePosition.y;



        ScreenPosToWorldRay(
            xPos, yPos,
            imageSizeSCENE.x, imageSizeSCENE.y,
            SceneManager::GetSceneManager()->OpenScene->worldCamera->GetView(),
            SceneManager::GetSceneManager()->OpenScene->worldCamera->GetProjectionMatrix(),
            ray_origin,
            ray_direction
        );

        
        for (Entity* objs : SceneManager::GetSceneManager()->OpenScene->objectsInScene) {
            float intersection_distance; // Output of TestRayOBBIntersection()

            glm::vec3 ObjectScale = glm::vec3
            (
                (objs->transform->Scale.x),
                (objs->transform->Scale.y),
                (objs->transform->Scale.z)
            );

            glm::vec3 aabb_min(-ObjectScale.x,
                               -ObjectScale.y,
                               -ObjectScale.z);


            glm::vec3 aabb_max(ObjectScale.x,
                               ObjectScale.y,
                               ObjectScale.z);
            
            glm::mat4 RotationMatrix = glm::mat4_cast(glm::quat(1, 0, 0, 0));
            glm::mat4 TranslationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(objs->transform->Position.x, objs->transform->Position.y, objs->transform->Position.z));
            glm::mat4 ModelMatrix = objs->transform->GetMatrix()/*TranslationMatrix * RotationMatrix*/;


            if (TestRayOBBIntersection(
                ray_origin,
                ray_direction,
                aabb_min,
                aabb_max,
                ModelMatrix,
                intersection_distance)
                ) {
                UIManager::instance->inspectorui->ObjectSelectToInspector = objs;
                std::cout << "Object Found:  " << objs->ObjectName << " | DISTANCE: " << intersection_distance << std::endl;
            }
            else {
                //UIManager::instance->inspectorui->ObjectSelectToInspector = nullptr;
            }
        }
    }
    ImGui::End();

#pragma endregion
}

void SceneUI::ScreenPosToWorldRay(
    int mouseX, int mouseY,             // Mouse position, in pixels, from bottom-left corner of the window
    int screenWidth, int screenHeight,  // Window size, in pixels
    glm::mat4 ViewMatrix,               // Camera position and orientation
    glm::mat4 ProjectionMatrix,         // Camera parameters (ratio, field of view, near and far planes)
    glm::vec3& out_origin,              // Ouput : Origin of the ray. /!\ Starts at the near plane, so if you want the ray to start at the camera's position instead, ignore this.
    glm::vec3& out_direction            // Ouput : Direction, in world space, of the ray that goes "through" the mouse.
) {

    // The ray Start and End positions, in Normalized Device Coordinates (Have you read Tutorial 4 ?)
    glm::vec4 lRayStart_NDC(
        ((float)mouseX / (float)screenWidth - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
        ((float)(screenHeight - mouseY) / (float)screenHeight - 0.5f) * 2.0f, // [0, 768] -> [-1,1] (Invierte la coordenada Y)
        -1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
        1.0f
    );
    glm::vec4 lRayEnd_NDC(
        ((float)mouseX / (float)screenWidth - 0.5f) * 2.0f,
        ((float)(screenHeight - mouseY) / (float)screenHeight - 0.5f) * 2.0f, // Invierte la coordenada Y
        0.0,
        1.0f
    );



    // The Projection matrix goes from Camera Space to NDC.
    // So inverse(ProjectionMatrix) goes from NDC to Camera Space.
    glm::mat4 InverseProjectionMatrix = glm::inverse(ProjectionMatrix);

    // The View Matrix goes from World Space to Camera Space.
    // So inverse(ViewMatrix) goes from Camera Space to World Space.
    glm::mat4 InverseViewMatrix = glm::inverse(ViewMatrix);

    glm::vec4 lRayStart_camera = InverseProjectionMatrix * lRayStart_NDC;    lRayStart_camera /= lRayStart_camera.w;
    glm::vec4 lRayStart_world = InverseViewMatrix * lRayStart_camera; lRayStart_world /= lRayStart_world.w;
    glm::vec4 lRayEnd_camera = InverseProjectionMatrix * lRayEnd_NDC;      lRayEnd_camera /= lRayEnd_camera.w;
    glm::vec4 lRayEnd_world = InverseViewMatrix * lRayEnd_camera;   lRayEnd_world /= lRayEnd_world.w;


    // Faster way (just one inverse)
    //glm::mat4 M = glm::inverse(ProjectionMatrix * ViewMatrix);
    //glm::vec4 lRayStart_world = M * lRayStart_NDC; lRayStart_world/=lRayStart_world.w;
    //glm::vec4 lRayEnd_world   = M * lRayEnd_NDC  ; lRayEnd_world  /=lRayEnd_world.w;


    glm::vec3 lRayDir_world(lRayEnd_world - lRayStart_world);
    lRayDir_world = glm::normalize(lRayDir_world);


    out_origin = glm::vec3(lRayStart_world);
    out_direction = glm::normalize(lRayDir_world);
}


bool SceneUI::TestRayOBBIntersection(
    glm::vec3 ray_origin,        // Ray origin, in world space
    glm::vec3 ray_direction,     // Ray direction (NOT target position!), in world space. Must be normalize()'d.
    glm::vec3 aabb_min,          // Minimum X,Y,Z coords of the mesh when not transformed at all.
    glm::vec3 aabb_max,          // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh is centered, but it's not always the case.
    glm::mat4 ModelMatrix,       // Transformation applied to the mesh (which will thus be also applied to its bounding box)
    float& intersection_distance // Output : distance between ray_origin and the intersection with the OBB
) {

    // Intersection method from Real-Time Rendering and Essential Mathematics for Games

    float tMin = 0.0f;
    float tMax = 100000000.0f;

    glm::vec3 OBBposition_worldspace(ModelMatrix[3].x, ModelMatrix[3].y, ModelMatrix[3].z);

    glm::vec3 delta = OBBposition_worldspace - ray_origin;

    // Test intersection with the 2 planes perpendicular to the OBB's X axis
    {
        glm::vec3 xaxis(ModelMatrix[0].x, ModelMatrix[0].y, ModelMatrix[0].z);
        float e = glm::dot(xaxis, delta);
        float f = glm::dot(ray_direction, xaxis);

        if (fabs(f) > 0.001f) { // Standard case

            float t1 = (e + aabb_min.x) / f; // Intersection with the "left" plane
            float t2 = (e + aabb_max.x) / f; // Intersection with the "right" plane
            // t1 and t2 now contain distances betwen ray origin and ray-plane intersections

            // We want t1 to represent the nearest intersection, 
            // so if it's not the case, invert t1 and t2
            if (t1 > t2) {
                float w = t1; t1 = t2; t2 = w; // swap t1 and t2
            }

            // tMax is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
            if (t2 < tMax)
                tMax = t2;
            // tMin is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
            if (t1 > tMin)
                tMin = t1;

            // And here's the trick :
            // If "far" is closer than "near", then there is NO intersection.
            // See the images in the tutorials for the visual explanation.
            if (tMax < tMin)
                return false;

        }
        else { // Rare case : the ray is almost parallel to the planes, so they don't have any "intersection"
            if (-e + aabb_min.x > 0.0f || -e + aabb_max.x < 0.0f)
                return false;
        }
    }


    // Test intersection with the 2 planes perpendicular to the OBB's Y axis
    // Exactly the same thing than above.
    {
        glm::vec3 yaxis(ModelMatrix[1].x, ModelMatrix[1].y, ModelMatrix[1].z);
        float e = glm::dot(yaxis, delta);
        float f = glm::dot(ray_direction, yaxis);

        if (fabs(f) > 0.001f) {

            float t1 = (e + aabb_min.y) / f;
            float t2 = (e + aabb_max.y) / f;

            if (t1 > t2) { float w = t1; t1 = t2; t2 = w; }

            if (t2 < tMax)
                tMax = t2;
            if (t1 > tMin)
                tMin = t1;
            if (tMin > tMax)
                return false;

        }
        else {
            if (-e + aabb_min.y > 0.0f || -e + aabb_max.y < 0.0f)
                return false;
        }
    }


    // Test intersection with the 2 planes perpendicular to the OBB's Z axis
    // Exactly the same thing than above.
    {
        glm::vec3 zaxis(ModelMatrix[2].x, ModelMatrix[2].y, ModelMatrix[2].z);
        float e = glm::dot(zaxis, delta);
        float f = glm::dot(ray_direction, zaxis);

        if (fabs(f) > 0.001f) {

            float t1 = (e + aabb_min.z) / f;
            float t2 = (e + aabb_max.z) / f;

            if (t1 > t2) { float w = t1; t1 = t2; t2 = w; }

            if (t2 < tMax)
                tMax = t2;
            if (t1 > tMin)
                tMin = t1;
            if (tMin > tMax)
                return false;

        }
        else {
            if (-e + aabb_min.z > 0.0f || -e + aabb_max.z < 0.0f)
                return false;
        }
    }

    intersection_distance = tMin;
    return true;

}

glm::vec3 SceneUI::ScreenToWorldRay(float mouseX, float mouseY, int screenWidth, int screenHeight, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    // Normaliza las coordenadas del clic del mouse
    float x = (2.0f * mouseX) / screenWidth - 1.0f;
    float y = 1.0f - (2.0f * mouseY) / screenHeight;

    // Combina las matrices de vista y proyección para obtener la matriz de transformación inversa
    glm::mat4 inverseMatrix = glm::inverse(projectionMatrix * viewMatrix);

    // Punto de inicio del rayo en el espacio de proyección
    glm::vec4 rayStart(x, y, -1.0f, 1.0f);

    // Punto de fin del rayo en el espacio de proyección
    glm::vec4 rayEnd(x, y, 1.0f, 1.0f);

    // Desproyecta los puntos en el espacio 3D
    rayStart = inverseMatrix * rayStart;
    rayStart /= rayStart.w;

    rayEnd = inverseMatrix * rayEnd;
    rayEnd /= rayEnd.w;

    // Dirección del rayo en el espacio 3D
    glm::vec3 rayDirection = glm::normalize(glm::vec3(rayEnd - rayStart));

    return rayDirection;
}

bool SceneUI::RayIntersectsAABB(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, const glm::vec3& aabbMin, const glm::vec3& aabbMax) {
    // Calcula los valores t mínimos y t máximos para cada plano del AABB
    float tMin = (aabbMin.x - rayOrigin.x) / rayDirection.x;
    float tMax = (aabbMax.x - rayOrigin.x) / rayDirection.x;

    // Asegúrate de que tMin sea el valor más pequeño y tMax sea el valor más grande
    if (tMin > tMax) {
        std::swap(tMin, tMax);
    }

    // Calcula t para el plano Y
    float tYMin = (aabbMin.y - rayOrigin.y) / rayDirection.y;
    float tYMax = (aabbMax.y - rayOrigin.y) / rayDirection.y;

    // Asegúrate de que tYMin sea el valor más pequeño y tYMax sea el valor más grande
    if (tYMin > tYMax) {
        std::swap(tYMin, tYMax);
    }

    // Actualiza tMin y tMax para tener en cuenta la intersección en el plano Y
    if ((tMin > tYMax) || (tYMin > tMax)) {
        return false; // No hay intersección con el AABB
    }

    // Actualiza tMin y tMax para tener en cuenta la intersección en el plano Z
    float tZMin = (aabbMin.z - rayOrigin.z) / rayDirection.z;
    float tZMax = (aabbMax.z - rayOrigin.z) / rayDirection.z;

    // Asegúrate de que tZMin sea el valor más pequeño y tZMax sea el valor más grande
    if (tZMin > tZMax) {
        std::swap(tZMin, tZMax);
    }

    // Actualiza tMin y tMax para tener en cuenta la intersección en el plano Z
    if ((tMin > tZMax) || (tZMin > tMax)) {
        return false; // No hay intersección con el AABB
    }

    // Si llegamos a este punto, el rayo intersecta con el AABB
    return true;
}


void SceneUI::update() {

}

void SceneUI::lateupdate() {
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAndDepthTexture, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);
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