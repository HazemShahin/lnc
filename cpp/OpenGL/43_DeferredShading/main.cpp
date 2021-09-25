#include <array>

#include <GLApp.h>

#include <bmp.h>
#include <Tesselation.h>

#include "DeferredShader.h"

static const std::string vertexShaderString {R"(#version 410
uniform mat4 MVP;
uniform mat4 MV;
uniform mat4 MVit;
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;
out vec3 normal;
out vec3 pos;
out vec2 texCoords;
void main() {
    gl_Position = MVP * vec4(vPos, 1.0);
    pos = (MV * vec4(vPos, 1.0)).xyz;
    texCoords = vTexCoords;
    normal = (MVit * vec4(vNormal, 0.0)).xyz;
})"};

static const std::string fragmentShaderString {R"(#version 410
uniform sampler2D torusTexture;
uniform vec3 color;
in vec3 pos;
in vec3 normal;
in vec2 texCoords;
layout(location = 0) out vec3 outColor;
layout(location = 1) out vec4 outPos;
layout(location = 2) out vec3 outNormal;
void main() {
    vec3 nnormal = normalize(normal);
    vec3 texValue = texture(torusTexture, texCoords).rgb;
    outColor  = color*texValue;
    outPos    = vec4(pos,1);
    outNormal = nnormal;
})"};

static const std::string dsFragmentShaderString {R"(#version 410
uniform sampler2D offscreenTexture0;
uniform sampler2D offscreenTexture1;
uniform sampler2D offscreenTexture2;
uniform vec3 lightPosViewSpace;
in vec2 texCoords;
layout(location = 0) out vec4 FragColor;
void main() {
    vec4 pos    = textureLod(offscreenTexture1, texCoords,0);
    vec3 color  = textureLod(offscreenTexture0, texCoords,0).rgb;
    vec3 normal = textureLod(offscreenTexture2, texCoords,0).rgb;
    vec3 nlightDir = normalize(lightPosViewSpace-pos.xyz);
    FragColor = vec4(color.rgb*dot(nlightDir,normal), pos.a);
})"};

struct TorusParams {
  Mat4 model;
  Vec3 color;
};

class DeferredShadingApp : public GLApp {
public:
  DeferredShadingApp() :
    GLApp(640,480,1,"Deferred Shading Demo",true,false),
    torusShader{GLProgram::createFromString(vertexShaderString, fragmentShaderString)},
    torusPosBuffer{GL_ARRAY_BUFFER},
    torusNormalBuffer{GL_ARRAY_BUFFER},
    torusTexBuffer{GL_ARRAY_BUFFER},
    torusIndexBuffer{GL_ELEMENT_ARRAY_BUFFER},
    torusTexture{GL_LINEAR, GL_LINEAR},
    deferredShader(dsFragmentShaderString, {
      {3,GLDataType::BYTE,false},
      {4,GLDataType::HALF,false},
      {3,GLDataType::HALF,false}
    })
  {
  }
  
  virtual void init() override {
    GL(glDisable(GL_BLEND));
    GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GL(glClearDepth(1.0f));
    GL(glCullFace(GL_BACK));
    GL(glEnable(GL_CULL_FACE));
    GL(glEnable(GL_DEPTH_TEST));
    GL(glDepthFunc(GL_LESS));    
    
    const Dimensions dim = glEnv.getFramebufferSize();
    GL(glViewport(0, 0, GLsizei(dim.width), GLsizei(dim.height)));
    
    const Tesselation torus = Tesselation::genTorus({0,0,0}, 0.8f, 0.3f);
        
    torusArray.bind();
    torusPosBuffer.setData(torus.getVertices(), 3);
    torusNormalBuffer.setData(torus.getNormals(), 3);
    torusTexBuffer.setData(torus.getTexCoords(),2);
    torusIndexBuffer.setData(torus.getIndices());
    
    torusArray.connectVertexAttrib(torusPosBuffer, torusShader, "vPos",3);
    torusArray.connectVertexAttrib(torusNormalBuffer, torusShader, "vNormal",3);
    torusArray.connectVertexAttrib(torusTexBuffer, torusShader, "vTexCoords",3);
    torusArray.connectIndexBuffer(torusIndexBuffer);
    
    vertexCount = GLsizei(torus.getIndices().size());
    
    Image torusImage{BMP::load("Torus.bmp")};
    torusTexture.setData(torusImage.data, torusImage.width, torusImage.height, torusImage.componentCount);
  }
      
  virtual void resize(int width, int height) override {
    GL(glViewport(0, 0, GLsizei(width), GLsizei(height)));
    deferredShader.resize(uint32_t(width), uint32_t(height));
  }
      
  virtual void keyboard(int key, int scancode, int action, int mods) override {
    if (action == GLFW_PRESS) {
      switch (key) {
        case GLFW_KEY_ESCAPE :
          closeWindow();
          break;
      }
    }
  }
  
  virtual void animate(double animationTime) override {
    this->animationTime = float(animationTime);
    
    const Dimensions dim = glEnv.getFramebufferSize();

    const float zNear  = 0.01f;
    const float zFar   = 1000.0f;
    const float fovY   = 45.0f;
    const float aspect = dim.aspect();

    projection = Mat4::perspective(fovY, aspect, zNear, zFar);    
    view       = Mat4::lookAt({0,0,-8}, {0,0,0}, {0,1,0});
        
    torusParams[0].model = Mat4::rotationY(this->animationTime*80) *
                           Mat4::rotationX(this->animationTime*70);
    torusParams[0].color = Vec3{
      fabs(sinf(this->animationTime*0.3f)),
      fabs(sinf(this->animationTime*0.8f)),
      fabs(sinf(this->animationTime*0.1f))
    };
    
    torusParams[1].model = torusParams[0].model *
                           Mat4::rotationZ(this->animationTime*100) *
                           Mat4::translation({2,0,0}) * Mat4::scaling(0.2f);
    torusParams[1].color = Vec3{
      fabs(sinf(this->animationTime*0.4f)),
      fabs(sinf(this->animationTime*0.1f)),
      fabs(sinf(this->animationTime*0.9f))
    };

    torusParams[2].model = torusParams[0].model *
                           Mat4::rotationZ(this->animationTime*100) *
                           Mat4::translation({-2,0,0}) * Mat4::scaling(0.2f);
    torusParams[2].color = Vec3{
      fabs(sinf(this->animationTime*0.1f)),
      fabs(sinf(this->animationTime*0.7f)),
      fabs(sinf(this->animationTime*0.4f))
    };

    torusParams[3].model = torusParams[0].model *
                           Mat4::rotationZ(this->animationTime*100) *
                           Mat4::translation({0,2,0}) * Mat4::scaling(0.2f);
    torusParams[3].color = Vec3{
      fabs(sinf(this->animationTime*0.8f)),
      fabs(sinf(this->animationTime*0.3f)),
      fabs(sinf(this->animationTime*0.1f))
    };

    torusParams[4].model = torusParams[0].model *
                           Mat4::rotationZ(this->animationTime*100) *
                           Mat4::translation({0,-2,0}) * Mat4::scaling(0.2f);
    torusParams[4].color = Vec3{
      fabs(sinf(this->animationTime*0.7f)),
      fabs(sinf(this->animationTime*0.8f)),
      fabs(sinf(this->animationTime*0.9f))
    };
    
  }
  
  virtual void draw() override {
    deferredShader.startFirstPass();
    GL(glDisable(GL_BLEND));
    GL(glClearColor(0,0,0,0));
    GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    torusShader.enable();
    torusArray.bind();
    torusShader.setTexture("torusTexture",torusTexture,0);
    for (const auto& param : torusParams) {
      const Mat4 modelView = view*param.model;
      const Mat4 modelViewProjection = projection*modelView;
      const Mat4 modelViewInverseTranspose = Mat4::transpose(Mat4::inverse(modelView));
              
      torusShader.setUniform("MVP",  modelViewProjection);
      torusShader.setUniform("MV",   modelView);
      torusShader.setUniform("MVit", modelViewInverseTranspose);
      torusShader.setUniform("color", param.color);
      GL(glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, (void*)0));
    }
    deferredShader.endFirstPass();

    const Dimensions dim = glEnv.getFramebufferSize();
    deferredShader.startSecondPass(dim.width, dim.height);
    GL(glClearColor(0.2f,0.2f,0.8f,0));
    GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GL(glEnable(GL_BLEND));
    const Vec3 lightPosViewSpace = view * Vec3{0,3,-4};
    deferredShader.getProgram().setUniform("lightPosViewSpace", lightPosViewSpace);
    deferredShader.endSecondPass();
  }
  
private:
  Vec2 mousePos;
  float animationTime;
  Mat4 view;
  Mat4 projection;

  std::array<TorusParams,5> torusParams;

  GLProgram   torusShader;
  GLArray     torusArray;
  GLBuffer    torusPosBuffer;
  GLBuffer    torusNormalBuffer;
  GLBuffer    torusTexBuffer;
  GLBuffer    torusIndexBuffer;
  GLsizei     vertexCount;
  GLTexture2D torusTexture;

  DeferredShader deferredShader;

};

#ifdef _WIN32
#include <Windows.h>
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
#else
int main(int argc, char** argv) {
#endif
  try {
    DeferredShadingApp myApp;
    myApp.run();
  }
  catch (const GLException& e) {
    std::stringstream ss;
    ss << "Insufficient OpenGL Support " << e.what();
#ifndef _WIN32
    std::cerr << ss.str().c_str() << std::endl;
#else
    MessageBoxA(
      NULL,
      ss.str().c_str(),
      "OpenGL Error",
      MB_ICONERROR | MB_OK
    );
#endif
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}