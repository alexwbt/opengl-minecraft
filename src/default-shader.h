#pragma once

namespace shader
{
    class DefaultShader : public Shader
    {
    private:
        static constexpr const char* vertex =
        {
            "#version 460 core\n"
            "\n"
            "layout (location = 0) in vec3 pos;\n"
            "layout (location = 1) in vec3 normal;\n"
            "layout (location = 2) in vec2 uv;\n"
            "\n"
            "out vec3 Normal;\n"
            "out vec3 FragPos;\n"
            "out vec2 UV;\n"
            "\n"
            "uniform mat4 mvp;\n"
            "uniform mat4 model;\n"
            "\n"
            "void main()\n"
            "{\n"
            "    gl_Position = mvp * vec4(pos, 1.0);\n"
            "\n"
            "    FragPos = vec3(model * vec4(pos, 1.0));\n"
            "    Normal = normalize(mat3(transpose(inverse(model))) * normal);\n"
            "    UV = uv;\n"
            "}"
        };

        static constexpr const char* fragment =
        {
            "#version 460 core\n"
            "\n"
            "in vec3 Normal;\n"
            "in vec3 FragPos;\n"
            "in vec2 UV;\n"
            "\n"
            "out vec4 FragColor;\n"
            "\n"
            "uniform vec3 cameraPos;\n"
            "uniform sampler2D diffuseMap;\n"
            "uniform float specular;\n"
            "uniform float shininess;\n"
            "\n"
            "struct Light {\n"
            "    vec3 position;\n"
            "\n"
            "    vec3 ambient;\n"
            "    vec3 diffuse;\n"
            "    vec3 specular;\n"
            "\n"
            "    float constant;\n"
            "    float linear;\n"
            "    float quadratic;\n"
            "};\n"
            "uniform int lights_size;\n"
            "uniform Light lights[32];\n"
            "\n"
            "struct SunLight {\n"
            "\tvec3 direction;\n"
            "\n"
            "\tvec3 ambient;\n"
            "\tvec3 diffuse;\n"
            "\tvec3 specular;\n"
            "};\n"
            "uniform int sunLights_size;\n"
            "uniform SunLight sunLights[32];\n"
            "\n"
            "struct SpotLight {\n"
            "\tvec3 position;\n"
            "\tvec3 direction;\n"
            "\n"
            "\tvec3 ambient;\n"
            "\tvec3 diffuse;\n"
            "\tvec3 specular;\n"
            "\n"
            "    float constant;\n"
            "    float linear;\n"
            "    float quadratic;\n"
            "\n"
            "\tfloat cutOff;\n"
            "\tfloat outerCutOff;\n"
            "};\n"
            "uniform int spotLights_size;\n"
            "uniform SpotLight spotLights[32];\n"
            "\n"
            "vec3 calcSunLight(SunLight light, vec3 viewDir);\n"
            "vec3 calcPointLight(Light light, vec3 viewDir);\n"
            "vec3 calcSpotLight(SpotLight light, vec3 viewDir);\n"
            "\n"
            "void main()\n"
            "{\n"
            "    vec3 viewDir = normalize(cameraPos - FragPos);\n"
            "\n"
            "    vec3 result = vec3(0);\n"
            "\n"
            "    for (int i = 0; i < sunLights_size; i++)\n"
            "    {\n"
            "    \tresult += calcSunLight(sunLights[i], viewDir);\n"
            "    }\n"
            "\n"
            "    for (int i = 0; i < lights_size; i++)\n"
            "    {\n"
            "    \tresult += calcPointLight(lights[i], viewDir);\n"
            "    }\n"
            "\n"
            "    for (int i = 0; i < spotLights_size; i++)\n"
            "    {\n"
            "    \tresult += calcSpotLight(spotLights[i], viewDir);\n"
            "    }\n"
            "\n"
            "    FragColor = vec4(result * texture(diffuseMap, UV).rgb, 1.0);\n"
            "}\n"
            "\n"
            "\n"
            "vec3 calcSunLight(SunLight light, vec3 viewDir)\n"
            "{\n"
            "\tvec3 lightDir = normalize(-light.direction);\n"
            "    \n"
            "    // Diffuse\n"
            "\tvec3 diffuse = light.diffuse * max(dot(Normal, lightDir), 0.0);\n"
            "\t// Specular\n"
            "\tvec3 reflectDir = reflect(-lightDir, Normal);\n"
            "\tvec3 specular = light.specular * pow(max(dot(viewDir, reflectDir), 0.0f), shininess);\n"
            "\n"
            "\treturn light.ambient + diffuse + specular;\n"
            "}\n"
            "\n"
            "\n"
            "vec3 calcPointLight(Light light, vec3 viewDir)\n"
            "{\n"
            "    vec3 lightDir = normalize(light.position - FragPos);\n"
            "\n"
            "    // Diffuse\n"
            "    vec3 diffuse = light.diffuse * max(dot(Normal, lightDir), 0.0);\n"
            "\n"
            "    // Specular\n"
            "    vec3 reflectDir = reflect(-lightDir, Normal);\n"
            "    vec3 specular = light.specular * pow(max(dot(viewDir, reflectDir), 0.0), shininess);\n"
            "\n"
            "    // Attenuation\n"
            "    float dis = length(light.position - FragPos);\n"
            "    float attenuation = 1.0 / (light.constant + light.linear * dis + light.quadratic * (dis * dis));  \n"
            "\n"
            "    return (light.ambient + diffuse + specular) * attenuation;\n"
            "}\n"
            "\n"
            "\n"
            "vec3 calcSpotLight(SpotLight light, vec3 viewDir)\n"
            "{\n"
            "    vec3 lightDir = normalize(light.position - FragPos);\n"
            "\n"
            "    // Diffuse\n"
            "    vec3 diffuse = light.diffuse * max(dot(Normal, lightDir), 0.0);\n"
            "\n"
            "    // Specular\n"
            "    vec3 reflectDir = reflect(-lightDir, Normal);\n"
            "    vec3 specular = light.specular * pow(max(dot(viewDir, reflectDir), 0.0), shininess);\n"
            "\n"
            "\t// Attenuation\n"
            "\tfloat dis = length(light.position - FragPos);\n"
            "\tfloat attenuation = 1.0 / (light.constant + light.linear * dis + light.quadratic * (dis * dis));\n"
            "\n"
            "    // Cut Off\n"
            "    float theta = dot(lightDir, normalize(-light.direction));\n"
            "\tfloat epsilon = light.cutOff - light.outerCutOff;\n"
            "\tfloat intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);\n"
            "\n"
            "    return (light.ambient + (diffuse + specular) * intensity) * attenuation;\n"
            "}"
        };

    public:
        struct Uniforms
        {
            glm::vec3 camera_pos;
            int diffuce_map;
            float specular;
            float shininess;
            glm::mat4 mvp;
            glm::mat4 model;
        };

    private:
        std::function<Uniforms&()> get_uniforms_;

    public:
        DefaultShader(std::function<Uniforms&()> get_uniforms)
            : Shader(vertex, fragment), get_uniforms_(get_uniforms)
        {}

        void Use() override
        {
            UseProgram();

            auto& uniforms = get_uniforms_();

            SetVec3("cameraPos", uniforms.camera_pos);

            SetInt("diffuseMap", uniforms.diffuce_map);
            SetFloat("specular", uniforms.specular);
            SetFloat("shininess", uniforms.shininess);

            SetMat4("mvp", uniforms.mvp);
            SetMat4("model", uniforms.model);
        }
    };
}
