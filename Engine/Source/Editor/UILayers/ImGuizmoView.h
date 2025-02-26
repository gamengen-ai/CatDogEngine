#include "ImGui/ImGuiBaseLayer.h"

namespace editor
{

class SceneView;

class ImGuizmoView : public engine::ImGuiBaseLayer
{
public:
	using ImGuiBaseLayer::ImGuiBaseLayer;
	virtual ~ImGuizmoView();

	virtual void Init() override;
	virtual void Update() override;

	void SetSceneView(const SceneView* pSceneView) { m_pSceneView = pSceneView; }

private:
	const SceneView* m_pSceneView = nullptr;
};

}