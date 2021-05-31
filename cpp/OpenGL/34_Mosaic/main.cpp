#include <GLApp.h>
#include <FontRenderer.h>
#include <Rand.h>

#include "MosaicMaker.h"

class MyGLApp : public GLApp {
public:
  MosaicMaker mm{"/Users/lnc/lnc/cpp/OpenGL/34_Mosaic/smallImages",
                 "/Users/lnc/lnc/cpp/OpenGL/34_Mosaic/jens.bmp",
                 100, {5,5}, {4,7}, {1.5,1.0,1.0}, 0.5};
  FontRenderer fr{"helvetica_neue.bmp", "helvetica_neue.pos"};
  std::shared_ptr<FontEngine> fe{nullptr};
  std::string text;
  std::shared_ptr<GLTexture2D> result{nullptr};
  
  virtual void init() {
    glEnv.setTitle("Mosaic Maker");
    fe = fr.generateFontEngine();
    mm.generate();
    BMP::save("result.bmp", mm.getResultImage());
    
    result = std::make_shared<GLTexture2D>(mm.getResultImage(2048),
                                           GL_LINEAR, GL_LINEAR,
                                           GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    GL(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GL(glBlendEquation(GL_FUNC_ADD));
    GL(glEnable(GL_BLEND));
    GL(glClearColor(0,0,0,0));
  }
  
  virtual void draw() {
    GL(glClear(GL_COLOR_BUFFER_BIT));
    float imageAspect = float(mm.getResultImage().width) /
                        float(mm.getResultImage().height);    
    float scale = imageAspect/glEnv.getFramebufferSize().aspect();
    if (scale < 1)
      setDrawTransform(Mat4::scaling(scale, 1, 1));
    else
      setDrawTransform(Mat4::scaling(1, 1/scale, 1));
    drawImage(*result);
  }
};

#ifdef _WIN32
#include <Windows.h>
INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
#else
int main(int argc, char** argv) {
#endif
  try {
    MyGLApp myApp;
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