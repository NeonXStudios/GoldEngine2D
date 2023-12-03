#pragma once
#include "../../RequireLibs.h"
#include "../SaveSystem/CheckVar.h"
#include "../Physics/LayerMaskSystem.h"
#include "../FileSystem/FileSystem.h"
#include "../ShaderCompiler/Shader.h"
#include "ECS.h"

class MaterialComponent : public Component
{
public:
	string VertexPath = "shaders/vert.glsl";
	string FragmentPath = "shaders/frag.glsl";
	Shader* ourShader;

	void init() override;
	void update() override;
	void draw() override;
	void clean() override;

    void setBool(const std::string& name, bool value) const
    {
        ourShader->setBool(name, value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string& name, int value) const
    {
        ourShader->setInt(name, value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string& name, float value) const
    {
        ourShader->setFloat(name, value);
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string& name, const glm::vec2& value) const
    {
        ourShader->setVec2(name, value);
    }
    /*void setVec2(const std::string& name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }*/
    // ------------------------------------------------------------------------
    void setVec3(const std::string& name, const glm::vec3& value) const
    {
        ourShader->setVec3(name, value);
    }
    /*void setVec3(const std::string& name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }*/
    // ------------------------------------------------------------------------
    void setVec4(const std::string& name, const glm::vec4& value) const
    {
        ourShader->setVec4(name, value);
    }

    /* void setVec4(const std::string& name, float x, float y, float z, float w)
     {
         glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
     }*/
     // ------------------------------------------------------------------------
    void setMat2(const std::string& name, const glm::mat2& mat) const
    {
        ourShader->setMat2(name, mat);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string& name, const glm::mat3& mat) const
    {
        ourShader->setMat3(name, mat);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string& name, const glm::mat4& mat) const
    {
        ourShader->setMat4(name, mat);
    }

	string serialize() override;
	void deserialize(std::string g, std::string path = "") override;
	void RecompileShader();
};