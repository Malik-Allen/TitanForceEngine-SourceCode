#include "Camera.h"

#include "../../../Engine/Core/Engine.h"
#include "../../Devices/Window.h"


CameraComponent::CameraComponent( ) :
	Component( ID )
{
	m_position = glm::vec3(0.0f, 0.0f, 25.0f);
	m_fieldOfView = 45.0f;
	m_forward = glm::vec3( 0.0f, 0.0f, -1.0f );
	m_up = glm::vec3( 0.0f, 1.0f, 0.0f );
	m_worldUp = m_up;
	m_nearPlane = 0.5f;
	m_farPlane = 100.0f;
	m_yaw = -90.0f;
	m_pitch = 0.0f;
	m_right = glm::vec3();

	m_window = Engine::Get()->GetWindow();

	float aspect = static_cast<float>( m_window->GetWidth() ) / static_cast<float>( m_window->GetHeight() );

	m_perspective = glm::perspective(
		m_fieldOfView,
		aspect,
		m_nearPlane,
		m_farPlane
	);

	m_orthographic = glm::ortho(
		0.0f,
		static_cast<float>( m_window->GetWidth() ),
		0.0f,
		static_cast<float>( m_window->GetHeight() ),
		-1.0f,
		-1.0f
	);


}

CameraComponent::~CameraComponent() {}


void CameraSystem::Update( float deltaTime )
{
	for ( auto& c : m_components )
	{
		CameraComponent* camera = std::get<CameraComponent*>( c );
		TransformComponent* transform = std::get<TransformComponent*>( c );
		if ( camera )
		{

			// UpdateCameraPosition( camera, transform->GetPosition() );
			// UpdateCameraRotation( camera, transform->GetRotation() );
			UpdateCameraVector( camera );

		}


	}
}

std::vector<CameraComponent*> CameraSystem::GetCameras()
{
	std::vector<CameraComponent*> cameras;
	for ( auto& c : m_components )
	{
		cameras.push_back( std::get<CameraComponent*>( c ) );
	}
	return cameras;
}


void CameraSystem::UpdateCameraVector( CameraComponent* camera )
{

	camera->m_forward.x = cos( glm::radians( camera->m_yaw ) ) * cos( glm::radians( camera->m_pitch ) );
	camera->m_forward.y = sin( glm::radians( camera->m_pitch ) );
	camera->m_forward.z = sin( glm::radians( camera->m_yaw ) ) * cos( glm::radians( camera->m_pitch ) );

	camera->m_forward = glm::normalize( camera->m_forward );

	camera->m_right = glm::normalize( glm::cross( camera->m_forward, camera->m_worldUp ) );

	camera->m_up = glm::normalize( glm::cross( camera->m_right, camera->m_forward ) );

}

// TODO: Implement some sort of Proxy to receive whether or not to update camera component's position and rotation
void CameraSystem::UpdateCameraPosition( CameraComponent * camera, glm::vec3 position )
{
	camera->m_position = position;

}

// TODO: Implement some sort of Proxy to receive whether or not to update camera component's position and rotation
void CameraSystem::UpdateCameraRotation( CameraComponent * camera, glm::vec3 rotation )
{
	camera->m_yaw = rotation.x;
	camera->m_pitch = rotation.y;
}
