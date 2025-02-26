#include "ParticlePool.h"

namespace engine
{

int ParticlePool::AllocateParticleIndex()
{
	int particleIndex = -1;
	if (!m_freeParticleIndexes.empty())
	{
		int index = m_freeParticleIndexes.back();
		m_freeParticleIndexes.pop_back();
		particleIndex = index;
	}
	else
	{
		++m_currentParticleCount;
		if (m_currentParticleCount >= m_maxParticleCount)
		{
			m_currentParticleCount = 0;
		}

		if (m_particles[m_currentParticleCount].isActive())
		{
			particleIndex = -1;
		}
		else
		{
			particleIndex = m_currentParticleCount;
		}
	}

	if (particleIndex != -1)
	{
		m_particles[particleIndex].Reset();
		m_particles[particleIndex].Active();
	}

	return particleIndex;
}

void ParticlePool::Update(float deltaTime)
{
	m_currentActiveCount = 0;
	for (int i = 0; i < m_maxParticleCount; ++i)
	{
		if (!m_particles[i].isActive())
		{
			continue;
		}

		m_particles[i].Update(deltaTime);
		if (!m_particles[i].isActive())
		{
			m_freeParticleIndexes.push_back(i);
		}
		else
		{
			++m_currentActiveCount;
		}
	}
}

void ParticlePool::AllParticlesReset()
{
	m_particles.resize(m_maxParticleCount);
	m_freeParticleIndexes.clear();
	m_freeParticleIndexes.reserve(m_maxParticleCount);
}

}
