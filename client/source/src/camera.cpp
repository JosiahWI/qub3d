/*
*	 Copyright (C) 2018 Qub�d Engine Group.
*	 All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification,
*  are permitted provided that the following conditions are met:
*
*  1. Redistributions of source code must retain the above copyright notice, this
*  list of conditions and the following disclaimer.
*
*  2. Redistributions in binary form must reproduce the above copyright notice,
*  this list of conditions and the following disclaimer in the documentation and/or
*  other materials provided with the distribution.
*
*  3. Neither the name of the copyright holder nor the names of its contributors
*  may be used to endorse or promote products derived from this software without
*  specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
*  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
*  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
*  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
*  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
*  ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

using namespace qub3d;

float MOUSE_SENSITIVITY = 0.000075f;
float MOVE_SPEED = 0.01f;

Camera::Camera(SDL_Window *window): m_window(window)
{
	SDL_ShowCursor(SDL_FALSE);

	m_position = glm::vec3(0.f, 0.f, 0.f);
	m_direction = glm::vec3(0.f, 0.f, 0.f);
	m_rotation = glm::vec3(0.f, 0.f, 0.f);
	m_up = glm::vec3(0.f, 0.f, 0.f);
}

void Camera::update(float dt) 
{
	int mx, my, w, h;
	
	SDL_GetMouseState(&mx, &my);
	SDL_GetWindowSize(m_window, &w, &h);
	SDL_WarpMouseInWindow(m_window, w / 2, h / 2);

	m_rotation.x += MOUSE_SENSITIVITY * dt * (float)(w / 2.f - mx);
	m_rotation.y += MOUSE_SENSITIVITY * dt * (float)(h / 2.f - my);

	const float HALF_PI = M_PI / 2.f;

	m_rotation.y = glm::clamp(m_rotation.y, -HALF_PI, HALF_PI);

	m_direction.x = std::cos(m_rotation.y) * std::sin(m_rotation.x);
	m_direction.y = std::sin(m_rotation.y);
	m_direction.z = std::cos(m_rotation.y) * std::cos(m_rotation.x);

	glm::vec3 right(
		std::sin(m_rotation.x - M_PI / 2.f),
		0.f,
		std::cos(m_rotation.x - M_PI / 2.f)
	);

	m_up = glm::cross(right, m_direction);

	const Uint8* keys = SDL_GetKeyboardState(nullptr);
	
	if (keys[SDL_SCANCODE_W])
		m_position += m_direction * dt * MOVE_SPEED;
	
	if (keys[SDL_SCANCODE_S])
		m_position -= m_direction * dt * MOVE_SPEED;

	if (keys[SDL_SCANCODE_D])
		m_position += right * dt * MOVE_SPEED;

	if (keys[SDL_SCANCODE_A])
		m_position -= right * dt * MOVE_SPEED;
}

glm::mat4 Camera::calculateViewMatrix() const
{
	glm::vec3 centre = m_position + m_direction;

	return glm::lookAt(m_position, centre, m_up);
}
