#include <iostream>

#include "CornellBoxDemo.h"
#include "DemoScene.h"
#include "MonteCarloPathTracer.h"
#include "SimpleMonteCarloApproach.h"
#include "framework/MyApp.h"
#include "framework/PinholeCamera.h"

using namespace RayTracingHistory;

// const char* const APP_NAME = "Path Tracing -  Kajiya 1986";
const char* const APP_NAME = "A Simple Monte Carlo Approach";

const uint32_t WINDOW_WIDTH = 1280;
const uint32_t WINDOW_HEIGHT = 720;

int main(int argc, char* argv[]) {
  MyApp app;
  try {
    app.init();
    app.createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME);
#if 1
    auto renderer = app.createRenderer<MonteCarloPathTracer>();
    auto scene = std::make_shared<CornellBoxDemo>();
    glm::vec3 eyePos(0, 2.5f, -8.5f);
    glm::vec3 lookAt(0, 2.5f, 0);
#else
    auto renderer = app.createRenderer<SimpleMonteCarloApproach>();
    auto scene = std::make_shared<DemoScene>();
    glm::vec3 eyePos(0, 10, -8);
    glm::vec3 lookAt(0, 1, 0);
#endif

    scene->init();

    auto camera = std::make_shared<PinholeCamera>();
    camera->setZNear(1.0f)
        .setAspect((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT)
        .setView(eyePos, lookAt, glm::vec3(0, 1, 0))
        .setFOV(45);
    camera->init();

    renderer->renderScene(scene, camera, glm::vec4(1, 1, 1, 1));

    app.mainLoop();

  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
  }

  app.shutdown();
  return 0;
}