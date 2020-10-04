#pragma once

#include "GLCall.h"
#include <unordered_map>
#include <glm/glm.hpp>

namespace Shengine {

    struct ShaderSrc
    {
        std::string vertSrc;
        std::string fragSrc;

        ShaderSrc()
        {}
    };

    class Shader
    {
    public:
        Shader();
        ~Shader();

        void CreateFromFile(const std::string& path);
        void CreateFromMemory(const std::string& vertSrc, const std::string& fragSrc);

        void Use() const;

        void SetMat4(const std::string& name, const glm::mat4& value);
        void SetFloat1v(const std::string& name, uint32_t count, float* value);
        void SetInt1v(const std::string& name, uint32_t count, int* value);
        void SetFloat(const std::string& name, float value);
        void SetVec2(const std::string& name, const glm::vec2& value);
        void SetVec3(const std::string& name, const glm::vec3& value);

    private:
        void ReadShaderFromFile(const std::string& path, ShaderSrc& src);
        uint32_t GetUniformLocation(const std::string& name);

        std::unordered_map<std::string, uint32_t> m_UniformLocations;

        uint32_t m_ProgramID, m_VertexShaderID, m_FragmentShaderID;
    };
}