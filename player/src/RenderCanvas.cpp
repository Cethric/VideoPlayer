//
// Created by rogan on 6/01/2018.
//

#include <ext.hpp>
#include "RenderCanvas.hpp"

VP::RenderCanvas::RenderCanvas(wxWindow *parent) : wxGLCanvas(parent, glGetCanvasAttributes(), wxID_ANY,
                                                              wxDefaultPosition, wxDefaultSize) {

}

void VP::RenderCanvas::RenderView(VP::VideoDecoder *decoder) {
    wxClientDC dc(this);
    GLLoaderStats stats = glLoader(this);
    if (!stats.loaded) {
        GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
        const GLchar *vertexSource = "#version 330 core\n"
                "struct RectangleParameters {\n"
                "    vec2 position;\n"
                "    vec2 size;\n"
                "    vec2 offset;\n"
                "    vec4 rotation;\n"
                "    int layer;\n"
                "};\n"
                "uniform mat4 MVP;\n"
                "uniform RectangleParameters parameters;\n"
                "out vec2 vertexUV;\n"
                "const vec4 verts[4] = vec4[] (\n"
                "    vec4(0, 1, 0, 0),\n"
                "    vec4(0, 0, 0, 1),\n"
                "    vec4(1, 1, 1, 0),\n"
                "    vec4(1, 0, 1, 1)\n"
                ");\n"
                "vec2 getUV() {\n"
                "    return vec2(verts[gl_VertexID].zw);\n"
                "}\n"
                "vec4 getQuatFromAxisAngle(vec3 axis, float angle) {\n"
                "    float half_angle = (angle * 0.5) * 3.14159 / 180.0;\n"
                "    return vec4(\n"
                "        axis.x * sin(half_angle),\n"
                "        axis.y * sin(half_angle),\n"
                "        axis.z * sin(half_angle),\n"
                "        cos(half_angle)\n"
                "    );\n"
                "}\n"
                "vec3 rotateVertex(vec3 v, vec4 q) {\n"
                "   return v*(q.w*q.w - dot(q.xyz,q.xyz)) + 2.0*q.xyz*dot(q.xyz,v) + 2.0*q.w*cross(q.xyz,v);\n"
                "}\n"
                "vec4 getVertex() {\n"
                "    vec3 v = (vec3(0, 0, parameters.layer) + vec3(parameters.size * verts[gl_VertexID].xy, 0)) - vec3(parameters.offset, 0);\n"
                "    vec4 q = getQuatFromAxisAngle(parameters.rotation.xyz, parameters.rotation.w);\n"
                "    vec3 r = rotateVertex(v, q);\n"
                "    vec3 o = vec3(parameters.position, 0);\n"
                "    return vec4(o + r , 1.0);\n"
                "}\n"
                "void main() {\n"
                "   gl_Position = MVP * getVertex();\n"
                "   vertexUV = getUV();\n"
                "}\n";
        glShaderSource(vertex, 1, &vertexSource, nullptr);
        glCompileShader(vertex);

        GLint status = GL_FALSE;
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            wxPrintf("Error with shader:\n");
            int logLength;
            glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &logLength);
            if (logLength > 0) {
                std::vector<char> errorMessage(static_cast<unsigned long long int>(logLength + 1));
                glGetShaderInfoLog(vertex, logLength, nullptr, &errorMessage[0]);
                wxLogFatalError("Shader Compile Error: %s\n", &errorMessage[0]);
                wxTheApp->Exit();
            }
        }

        glCheckError();

        GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
        const GLchar *fragmentSource = "#version 330 core\n"
                "in vec2 vertexUV;\n"
                "out vec4 fragmentColour;\n"
                "uniform sampler2D textureRGB;\n"
                "uniform vec4 colour;\n"
                "vec4 GetRGBTexture() {\n"
                "    return vec4(texture(textureRGB, vec2(0.0 + vertexUV.x, 1.0 - vertexUV.y)).rgb, 1);\n"
                "}\n"
                "void main() {\n"
                "    fragmentColour = GetRGBTexture() * colour;\n"
                "}\n";
        glShaderSource(fragment, 1, &fragmentSource, nullptr);
        glCompileShader(fragment);

        status = GL_FALSE;
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &status);
        if (status == GL_FALSE) {
            wxPrintf("Error with shader:\n");
            int logLength;
            glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &logLength);
            if (logLength > 0) {
                std::vector<char> errorMessage(static_cast<unsigned long long int>(logLength + 1));
                glGetShaderInfoLog(fragment, logLength, nullptr, &errorMessage[0]);
                wxLogFatalError("Shader Compile Error: %s\n", &errorMessage[0]);
                wxTheApp->Exit();
            }
        }

        glCheckError();

        shaderProgram = glCreateProgram();

        glCheckError();

//        for (auto attrib : attributes) {
//            glBindAttribLocation(programID, attrib.index, attrib.name);
//            glCheckError();
//        }


        glAttachShader(shaderProgram, vertex);
        glCheckError();
        glAttachShader(shaderProgram, fragment);
        glCheckError();

        glLinkProgram(shaderProgram);
        glCheckError();

        status = GL_FALSE;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
        glCheckError();

        if (status == GL_FALSE) {
            int logLength;
            glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &logLength);
            glCheckError();
            if (logLength > 0) {
                std::vector<char> errorMessage(static_cast<unsigned long long int>(logLength + 1));
                glGetProgramInfoLog(shaderProgram, logLength, nullptr, &errorMessage[0]);
                glCheckError();
                wxLogFatalError("Program Link Error: %s\n", &errorMessage[0]);
                wxTheApp->Exit();
            }
        }
        glDetachShader(shaderProgram, vertex);
        glCheckError();
        glDeleteShader(vertex);
        glCheckError();
        glDetachShader(shaderProgram, fragment);
        glCheckError();
        glDeleteShader(fragment);
        glCheckError();


        glUseProgram(shaderProgram);
        glCheckError();
        textureLocation = glGetUniformLocation(shaderProgram, "textureRGB");
        paramaterPositionLocation = glGetUniformLocation(shaderProgram, "parameters.position");
        paramaterOffsetLocation = glGetUniformLocation(shaderProgram, "parameters.offset");
        paramaterSizeLocation = glGetUniformLocation(shaderProgram, "parameters.size");
        paramaterRotationLocation = glGetUniformLocation(shaderProgram, "parameters.rotation");
        paramaterLayerLocation = glGetUniformLocation(shaderProgram, "parameters.layer");
        colourLocation = glGetUniformLocation(shaderProgram, "colour");
        MVPLocation = glGetUniformLocation(shaderProgram, "MVP");

        glGenVertexArrays(1, &vertexArrayObject);
        glCheckError();

        wxLogInfo("Prepared Render Canvas");
    }

    glClearColor(0, 1, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    glViewport(0, 0, GetSize().GetWidth(), GetSize().GetHeight());


    if (decoder != nullptr) {
        if (decoder->HasFrame()) {
            decoder->NextFrame(&videoTexture);
        }

        glUseProgram(shaderProgram);
        glCheckError();

        glBindVertexArray(this->vertexArrayObject);

        glBindTexture(GL_TEXTURE_2D, videoTexture);
        glActiveTexture(GL_TEXTURE0 + 0);
        glUniform1i(textureLocation, 0);
        glUniform1i(paramaterLayerLocation, 0);
        glUniform2f(paramaterPositionLocation, 0, 0);
        glUniform2f(paramaterOffsetLocation, 0, 0);
        glUniform2f(paramaterSizeLocation, 1920, 1080);
        glUniform4f(paramaterRotationLocation, 0, 0, 0, 0);
        glUniform4f(colourLocation, 1, 1, 1, 1);
        glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, &glm::ortho(0.0f, 1920.f, 1080.f, 0.f, -10.f, 10.0f)[0][0]);
        glCheckError();

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
        glUseProgram(0);
    }

    glFlush();
    SwapBuffers();
}
