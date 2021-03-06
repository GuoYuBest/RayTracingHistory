/**
 * A Brief History of Ray tracing
 *
 * GitHub: https://github.com/neil3d/RayTracingHistory
 *
 * Created by yanliang.fyl, 2020
 */

#pragma once
#include <tuple>

#include "TestSceneBase.h"
#include "framework/DirectRenderer.h"

namespace RayTracingHistory {

class Material;

class WhittedRayTracer : public DirectRenderer {
 public:
  virtual void _renderThread(MyScene::Ptr scene, MyCamera::Ptr camera) override;

 private:
  Ray _generateReflectionRay(const glm::vec3& dir, const glm::vec3& point,
                             const glm::vec3& normal);

  std::tuple<bool, float, Ray> _generateRefractationRay(
      const glm::vec3& dir, const glm::vec3& point, const glm::vec3& normal,
      float Kn);

  glm::vec3 _traceRay(Ray ray, TestSceneBase* pScene, int depth, float weight);

  glm::vec3 _shade(const glm::vec3& wo, const glm::vec3& pt,
                   const glm::vec3& normal, Material* mtl,
                   TestSceneBase* pScene);

  glm::vec3 _backgroundColor(const Ray& ray);
};

}  // namespace RayTracingHistory
