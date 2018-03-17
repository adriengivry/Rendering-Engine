#include <iostream>

#include "Engine.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "GraphParser.h"

using namespace Gyvr::Core::System;
using namespace Gyvr::Object;

int main(int argc, char** argv)
{	
	Engine engine(argv);
	
	auto& scene = engine.GetSceneManager()->CreateSceneFromUnity();
	auto& childs = scene.GetRoot().GetChilds();

	while (engine.IsRunning())
	{
		engine.PollEvents();

		if (engine.GetInputManager()->IsKeyEventOccured(InputManager::Key::KEY_ESCAPE, InputManager::KeyState::KEY_DOWN))
			engine.Quit();

		if (engine.GetInputManager()->IsKeyEventOccured(InputManager::Key::KEY_KP_ADD, InputManager::KeyState::KEY_DOWN))
		{
			for (auto& child : childs)
			{
				child->GetComponent<Transform>()->Translate(Gyvr::Math::Vec3(1, 2, 3));
				child->GetComponent<Transform>()->Rotate(Gyvr::Math::Vec3(0, 0, 45));
				child->GetComponent<Transform>()->Scale(Gyvr::Math::Vec3(1.2f, 1.2f, 1.2f));

				for (auto& child : childs)
				{
					std::string tab = "    ";
					std::cout << child->GetName() << std::endl;
					auto transform = child->GetComponent<Transform>();
					Gyvr::Math::Vec3 position = transform->GetPosition();
					std::cout << tab << "Position: (" << position.x << "," << position.y << "," << position.z << ")" << std::endl;

					Gyvr::Math::Vec3 rotation = transform->GetRotation();
					std::cout << tab << "Rotation: (" << rotation.x << "," << rotation.y << "," << rotation.z << ")" << std::endl;

					Gyvr::Math::Vec3 scale = transform->GetScale();
					std::cout << tab << "Scale: (" << scale.x << "," << scale.y << "," << scale.z << ")" << std::endl;
				}
			}
		}
		engine.Draw();
	}

	return EXIT_SUCCESS;
}
