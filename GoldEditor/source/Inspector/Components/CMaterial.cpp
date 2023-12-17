#include "CMaterial.h"

float z[2] = 
{
    0,
    0
};

void CMaterial::start() {

}

void CMaterial::draw(Entity* owner) {
    ImGui::Button("Material", ImVec2(ImGui::GetContentRegionAvail().x, 20));
    ImGui::Spacing();

    owner->getComponent<MaterialComponent>().VertexPath = EditorGUI::InputText("Vertex Shader", owner->getComponent<MaterialComponent>().VertexPath);
    if (ImGui::BeginDragDropTarget())
    {
        ImGuiDragDropFlags target_flags = 0;
        target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;
        target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;


        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SHADER_PATH", target_flags))
        {
            const char* receivedString = static_cast<const char*>(payload->Data);

            if (ImGui::IsMouseReleased(0)) {
                std::string convertedPath = AComponent::RemoveDir(receivedString);
                owner->getComponent<MaterialComponent>().VertexPath = convertedPath;

                std::cout << "Convertido: " << convertedPath << std::endl;
                owner->getComponent<MaterialComponent>().RecompileShader();
            }
        }


        ImGui::EndDragDropTarget();
    }

    owner->getComponent<MaterialComponent>().FragmentPath = EditorGUI::InputText("Fragment Shader", owner->getComponent<MaterialComponent>().FragmentPath);
    if (ImGui::BeginDragDropTarget())
    {
        ImGuiDragDropFlags target_flags = 0;
        target_flags |= ImGuiDragDropFlags_AcceptBeforeDelivery;
        target_flags |= ImGuiDragDropFlags_AcceptNoDrawDefaultRect;


        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("SHADER_PATH", target_flags))
        {
            const char* receivedString = static_cast<const char*>(payload->Data);

            if (ImGui::IsMouseReleased(0)) {
                std::string convertedPath = AComponent::RemoveDir(receivedString);
                owner->getComponent<MaterialComponent>().FragmentPath = convertedPath;



                std::cout << "Convertido: " << convertedPath << std::endl;
                owner->getComponent<MaterialComponent>().RecompileShader();
            }
        }


        ImGui::EndDragDropTarget();
    }

    ImGui::Separator();

    ImGui::Text("Material Properties");



    owner->getComponent<MaterialComponent>().ourShader->use();

    GLuint program = owner->getComponent<MaterialComponent>().ourShader->ID;

    GLint numUniforms;
    glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &numUniforms);

    const GLsizei bufSize = 256;
    GLchar name[bufSize];

    for (int i = 0; i < numUniforms; ++i) {
        GLint size;
        GLenum type;
        glGetActiveUniform(program, GLuint(i), bufSize, nullptr, &size, &type, name);

        GLint iddata = glGetUniformLocation(program, name);

        //std::cout << "Uniform #" << i << " Nombre: " << name << ", Tipo: " << type << ", Tamaño: " << size << std::endl;

        switch (type)
        {
        case GL_SAMPLER_2D: {
            GLint intDataShader;
            GLint iddata = glGetUniformLocation(program, name);
            glGetUniformiv(owner->getComponent<MaterialComponent>().ourShader->ID, iddata, &intDataShader);
            int NameData = EditorGUI::Int(name, intDataShader);
            owner->getComponent<MaterialComponent>().setInt(name, NameData);
            ImGui::Image ((void*)(intptr_t)owner->getComponent<SpriteComponent>().texture, ImVec2(128, 128));
            break;
        }


        case GL_FLOAT: {
            GLfloat floatDataShader;
            GLint iddata = glGetUniformLocation(program, name);
            glGetUniformfv(owner->getComponent<MaterialComponent>().ourShader->ID, iddata, &floatDataShader);
            float NameData = EditorGUI::Float(name, floatDataShader);
            owner->getComponent<MaterialComponent>().setFloat(name, NameData);
            break;
        }

        case GL_FLOAT_VEC2: {
            GLfloat vector2Values[2];
            GLint iddata = glGetUniformLocation(program, name);
            glGetUniformfv(owner->getComponent<MaterialComponent>().ourShader->ID, iddata, vector2Values);
            glm::vec2 NameData = EditorGUI::Vector2(name, glm::vec2(vector2Values[0], vector2Values[1]));
            owner->getComponent<MaterialComponent>().setVec2(name, NameData);
            break;
        }

        case GL_FLOAT_VEC3: {
            GLfloat vector2Values[3];
            GLint iddata = glGetUniformLocation(program, name);
            glGetUniformfv(owner->getComponent<MaterialComponent>().ourShader->ID, iddata, vector2Values);
            glm::vec3 NameData = EditorGUI::Vector3(name, glm::vec3(vector2Values[0], vector2Values[1], vector2Values[2]));
            owner->getComponent<MaterialComponent>().setVec3(name, NameData);
            break;
        }

        case GL_FLOAT_VEC4: {
            GLfloat vector2Values[4];
            GLint iddata = glGetUniformLocation(program, name);
            glGetUniformfv(owner->getComponent<MaterialComponent>().ourShader->ID, iddata, vector2Values);
            glm::vec4 NameData = EditorGUI::Vector4(name, glm::vec4(vector2Values[0], vector2Values[1], vector2Values[2], vector2Values[3]));
            owner->getComponent<MaterialComponent>().setVec4(name, NameData);
            break;
        }

        case GL_BOOL: {
            GLint vector2Values;
            GLint iddata = glGetUniformLocation(program, name);
            glGetUniformiv(owner->getComponent<MaterialComponent>().ourShader->ID, iddata, &vector2Values);
            bool NameData = EditorGUI::Toggle(name, vector2Values);
            owner->getComponent<MaterialComponent>().setBool(name, NameData);
            break;
        }
        }
    }
}