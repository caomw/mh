#include "3d/scene.h"

#include "3d/camera.h"

namespace lp
{

Scene::Scene(void) : m_dirty(true)
{
    
}

Scene::Scene(const std::vector<std::shared_ptr<Mesh> > & meshes)
    : m_meshes(meshes), m_dirty(true)
{

}

void Scene::addMesh(std::shared_ptr<Mesh> mesh)
{
    m_meshes.push_back(mesh);
    m_dirty = true;
}

void Scene::addMeshes(const std::vector<std::shared_ptr<Mesh> > & meshes)
{
    m_meshes.reserve(m_meshes.size() + meshes.size());
    m_meshes.insert(m_meshes.end(), meshes.begin(), meshes.end());
    m_dirty = true;
}

Eigen::Vector3f Scene::getCenter(void)
{
    if (m_dirty)
    {
        m_center = Eigen::Vector3f(0.0f, 0.0f, 0.0f);
        for (size_t i = 0; i < m_meshes.size(); ++i)
        {
            m_center += m_meshes[i]->getCenter();
        }
        m_center /= m_meshes.size();
        m_dirty = false;
    }

    return m_center;
}

void Scene::draw(std::shared_ptr<Shader> shader, std::shared_ptr<Camera> camera)
{
    shader->use();
    shader->setUniform("worldToCamera", camera->getWorldToCamera());
    shader->setUniform("cameraToClip",  camera->getCameraToClip());

    for (size_t i = 0; i < m_meshes.size(); ++i)
    {
        shader->setUniform("modelToWorld", m_meshes[i]->getModelToWorld());
        m_meshes[i]->draw();
    }

    glUseProgram(0);
}

} // namespace lp