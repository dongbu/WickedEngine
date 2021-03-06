#include "stdafx.h"
#include "PostprocessWindow.h"


PostprocessWindow::PostprocessWindow(wiGUI* gui, Renderable3DComponent* comp) : GUI(gui), component(comp)
{
	assert(component && "PostprocessWnd invalid component!");
	assert(GUI && "Invalid GUI!");

	float screenW = (float)wiRenderer::GetDevice()->GetScreenWidth();
	float screenH = (float)wiRenderer::GetDevice()->GetScreenHeight();

	ppWindow = new wiWindow(GUI, "PostProcess Window");
	ppWindow->SetSize(XMFLOAT2(360, 520));
	GUI->AddWidget(ppWindow);

	float x = 110;
	float y = 0;

	lensFlareCheckBox = new wiCheckBox("LensFlare: ");
	lensFlareCheckBox->SetTooltip("Toggle visibility of light source flares. Additional setup needed per light for a lensflare to be visible.");
	lensFlareCheckBox->SetScriptTip("Renderable3DComponent::SetLensFlareEnabled(bool value)");
	lensFlareCheckBox->SetPos(XMFLOAT2(x, y += 35));
	lensFlareCheckBox->SetCheck(component->getLensFlareEnabled());
	lensFlareCheckBox->OnClick([&](wiEventArgs args) {
		component->setLensFlareEnabled(args.bValue);
	});
	ppWindow->AddWidget(lensFlareCheckBox);

	lightShaftsCheckBox = new wiCheckBox("LightShafts: ");
	lightShaftsCheckBox->SetTooltip("Enable light shaft for directional light sources.");
	lightShaftsCheckBox->SetScriptTip("Renderable3DComponent::SetLightShaftsEnabled(bool value)");
	lightShaftsCheckBox->SetPos(XMFLOAT2(x, y += 35));
	lightShaftsCheckBox->SetCheck(component->getLightShaftsEnabled());
	lightShaftsCheckBox->OnClick([&](wiEventArgs args) {
		component->setLightShaftsEnabled(args.bValue);
	});
	ppWindow->AddWidget(lightShaftsCheckBox);

	ssaoCheckBox = new wiCheckBox("SSAO: ");
	ssaoCheckBox->SetTooltip("Enable Screen Space Ambient Occlusion. (Deferred only for now)");
	ssaoCheckBox->SetScriptTip("Renderable3DComponent::SetSSAOEnabled(bool value)");
	ssaoCheckBox->SetPos(XMFLOAT2(x, y += 35));
	ssaoCheckBox->SetCheck(component->getSSAOEnabled());
	ssaoCheckBox->OnClick([&](wiEventArgs args) {
		component->setSSAOEnabled(args.bValue);
	});
	ppWindow->AddWidget(ssaoCheckBox);

	ssrCheckBox = new wiCheckBox("SSR: ");
	ssrCheckBox->SetTooltip("Enable Screen Space Reflections. (Deferred only for now)");
	ssrCheckBox->SetScriptTip("Renderable3DComponent::SetSSREnabled(bool value)");
	ssrCheckBox->SetPos(XMFLOAT2(x, y += 35));
	ssrCheckBox->SetCheck(component->getSSREnabled());
	ssrCheckBox->OnClick([&](wiEventArgs args) {
		component->setSSREnabled(args.bValue);
	});
	ppWindow->AddWidget(ssrCheckBox);

	sssCheckBox = new wiCheckBox("SSS: ");
	sssCheckBox->SetTooltip("Enable Subsurface Scattering. (Deferred only for now)");
	sssCheckBox->SetScriptTip("Renderable3DComponent::SetSSSEnabled(bool value)");
	sssCheckBox->SetPos(XMFLOAT2(x, y += 35));
	sssCheckBox->SetCheck(component->getSSSEnabled());
	sssCheckBox->OnClick([&](wiEventArgs args) {
		component->setSSSEnabled(args.bValue);
	});
	ppWindow->AddWidget(sssCheckBox);

	eyeAdaptionCheckBox = new wiCheckBox("EyeAdaption: ");
	eyeAdaptionCheckBox->SetTooltip("Enable eye adaption for the overall screen luminance");
	eyeAdaptionCheckBox->SetPos(XMFLOAT2(x, y += 35));
	eyeAdaptionCheckBox->SetCheck(component->getEyeAdaptionEnabled());
	eyeAdaptionCheckBox->OnClick([&](wiEventArgs args) {
		component->setEyeAdaptionEnabled(args.bValue);
	});
	ppWindow->AddWidget(eyeAdaptionCheckBox);

	motionBlurCheckBox = new wiCheckBox("MotionBlur: ");
	motionBlurCheckBox->SetTooltip("Enable motion blur for camera movement and animated meshes.");
	motionBlurCheckBox->SetScriptTip("Renderable3DComponent::SetMotionBlurEnabled(bool value)");
	motionBlurCheckBox->SetPos(XMFLOAT2(x, y += 35));
	motionBlurCheckBox->SetCheck(component->getMotionBlurEnabled());
	motionBlurCheckBox->OnClick([&](wiEventArgs args) {
		component->setMotionBlurEnabled(args.bValue);
	});
	ppWindow->AddWidget(motionBlurCheckBox);

	depthOfFieldCheckBox = new wiCheckBox("DepthOfField: ");
	depthOfFieldCheckBox->SetTooltip("Enable Depth of field effect. Additional focus and strength setup required.");
	depthOfFieldCheckBox->SetScriptTip("Renderable3DComponent::SetDepthOfFieldEnabled(bool value)");
	depthOfFieldCheckBox->SetPos(XMFLOAT2(x, y += 35));
	depthOfFieldCheckBox->SetCheck(component->getDepthOfFieldEnabled());
	depthOfFieldCheckBox->OnClick([&](wiEventArgs args) {
		component->setDepthOfFieldEnabled(args.bValue);
	});
	ppWindow->AddWidget(depthOfFieldCheckBox);

	depthOfFieldFocusSlider = new wiSlider(0.01f, 600, 100, 10000, "Focus: ");
	depthOfFieldFocusSlider->SetTooltip("Set the focus distance from the camera. The picture will be sharper near the focus, and blurrier further from it.");
	depthOfFieldFocusSlider->SetScriptTip("Renderable3DComponent::SetDepthOfFieldFocus(float value)");
	depthOfFieldFocusSlider->SetSize(XMFLOAT2(100, 20));
	depthOfFieldFocusSlider->SetPos(XMFLOAT2(x + 100, y));
	depthOfFieldFocusSlider->SetValue(component->getDepthOfFieldFocus());
	depthOfFieldFocusSlider->OnSlide([&](wiEventArgs args) {
		component->setDepthOfFieldFocus(args.fValue);
	});
	ppWindow->AddWidget(depthOfFieldFocusSlider);

	depthOfFieldStrengthSlider = new wiSlider(0.01f, 4, 100, 1000, "Strength: ");
	depthOfFieldStrengthSlider->SetTooltip("Set depth of field blur strength.");
	depthOfFieldStrengthSlider->SetScriptTip("Renderable3DComponent::SetDepthOfFieldStrength(float value)");
	depthOfFieldStrengthSlider->SetSize(XMFLOAT2(100, 20));
	depthOfFieldStrengthSlider->SetPos(XMFLOAT2(x + 100, y += 35));
	depthOfFieldStrengthSlider->SetValue(component->getDepthOfFieldStrength());
	depthOfFieldStrengthSlider->OnSlide([&](wiEventArgs args) {
		component->setDepthOfFieldStrength(args.fValue);
	});
	ppWindow->AddWidget(depthOfFieldStrengthSlider);

	bloomCheckBox = new wiCheckBox("Bloom: ");
	bloomCheckBox->SetTooltip("Enable bloom. The effect adds color bleeding to the brightest parts of the scene.");
	bloomCheckBox->SetScriptTip("Renderable3DComponent::SetBloomEnabled(bool value)");
	bloomCheckBox->SetPos(XMFLOAT2(x, y += 35));
	bloomCheckBox->SetCheck(component->getBloomEnabled());
	bloomCheckBox->OnClick([&](wiEventArgs args) {
		component->setBloomEnabled(args.bValue);
	});
	ppWindow->AddWidget(bloomCheckBox);

	fxaaCheckBox = new wiCheckBox("FXAA: ");
	fxaaCheckBox->SetTooltip("Fast Approximate Anti Aliasing. A fast antialiasing method, but can be a bit too blurry.");
	fxaaCheckBox->SetScriptTip("Renderable3DComponent::SetFXAAEnabled(bool value)");
	fxaaCheckBox->SetPos(XMFLOAT2(x, y += 35));
	fxaaCheckBox->SetCheck(component->getFXAAEnabled());
	fxaaCheckBox->OnClick([&](wiEventArgs args) {
		component->setFXAAEnabled(args.bValue);
	});
	ppWindow->AddWidget(fxaaCheckBox);

	colorGradingCheckBox = new wiCheckBox("Color Grading: ");
	colorGradingCheckBox->SetTooltip("Enable color grading of the final render. An additional lookup texture must be set for it to take effect.");
	colorGradingCheckBox->SetScriptTip("Renderable3DComponent::SetColorGradingEnabled(bool value)");
	colorGradingCheckBox->SetPos(XMFLOAT2(x, y += 35));
	colorGradingCheckBox->SetCheck(component->getColorGradingEnabled());
	colorGradingCheckBox->OnClick([&](wiEventArgs args) {
		component->setColorGradingEnabled(args.bValue);
	});
	ppWindow->AddWidget(colorGradingCheckBox);

	stereogramCheckBox = new wiCheckBox("Stereogram: ");
	stereogramCheckBox->SetTooltip("Compute a stereogram from the depth buffer. It produces a 3D sihouette image when viewed cross eyed.");
	stereogramCheckBox->SetScriptTip("Renderable3DComponent::SetStereogramEnabled(bool value)");
	stereogramCheckBox->SetPos(XMFLOAT2(x, y += 35));
	stereogramCheckBox->SetCheck(component->getStereogramEnabled());
	stereogramCheckBox->OnClick([&](wiEventArgs args) {
		component->setStereogramEnabled(args.bValue);
	});
	ppWindow->AddWidget(stereogramCheckBox);

	sharpenFilterCheckBox = new wiCheckBox("Sharpen Filter: ");
	sharpenFilterCheckBox->SetTooltip("Toggle sharpening post process of the final image.");
	sharpenFilterCheckBox->SetScriptTip("Renderable3DComponent::SetSharpenFilterEnabled(bool value)");
	sharpenFilterCheckBox->SetPos(XMFLOAT2(x, y += 35));
	sharpenFilterCheckBox->SetCheck(component->getSharpenFilterEnabled());
	sharpenFilterCheckBox->OnClick([&](wiEventArgs args) {
		component->setSharpenFilterEnabled(args.bValue);
	});
	ppWindow->AddWidget(sharpenFilterCheckBox);

	sharpenFilterAmountSlider = new wiSlider(0, 4, 1, 1000, "Amount: ");
	sharpenFilterAmountSlider->SetTooltip("Set sharpness filter strength.");
	sharpenFilterAmountSlider->SetScriptTip("Renderable3DComponent::SetSharpenFilterAmount(float value)");
	sharpenFilterAmountSlider->SetSize(XMFLOAT2(100, 20));
	sharpenFilterAmountSlider->SetPos(XMFLOAT2(x + 100, y));
	sharpenFilterAmountSlider->SetValue(component->getSharpenFilterAmount());
	sharpenFilterAmountSlider->OnSlide([&](wiEventArgs args) {
		component->setSharpenFilterAmount(args.fValue);
	});
	ppWindow->AddWidget(sharpenFilterAmountSlider);


	ppWindow->Translate(XMFLOAT3(screenW - 380, 50, 0));
	ppWindow->SetVisible(false);

}


PostprocessWindow::~PostprocessWindow()
{
	ppWindow->RemoveWidgets(true);
	GUI->RemoveWidget(ppWindow);
	SAFE_DELETE(ppWindow);
}
