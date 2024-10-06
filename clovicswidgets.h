#pragma once
#include "imgui_internal.h"
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include "imgui_freetype.h"
#include <vector>
#include <cmath>
#include <ctime> 
#include <string>
/*
made by clovics
clovics00x on discord (can change any time.)

*/

namespace fonts {
    ImFont* poppins2 = nullptr;
    ImFont* roboto1 = nullptr;
}



// tried replicating the widget that blackswipe/other spoofers use for their loading screen.
/*
  static float lastTime = ImGui::GetTime();
   float currentTime = ImGui::GetTime();
  float deltaTime = currentTime - lastTime;
   lastTime = currentTime;

    WrappingLineSpinnerWithShadow(deltaTime, windowSize);
    call the function like this

*/
void WrappingLineSpinnerWithShadow(float deltaTime, ImVec2 windowSize) {
    const float radius = 6.2f;
    const float shadowThickness = 2.9f;
    const float lineWidth = 3.0f;
    const float speed = 10.5f;
    static float angle = 0.0f;
    static bool reverse = false;

    ImVec2 center(402.9f, 251.0f); // where you want the center of the circle to be

    ImGui::GetWindowDrawList()->AddCircle(center, radius, IM_COL32(100, 100, 100, 80), 0, shadowThickness);

    if (!reverse) {
        ImGui::GetWindowDrawList()->PathArcTo(center, radius, -IM_PI / 2, angle - IM_PI / 2, 32);
        ImGui::GetWindowDrawList()->PathStroke(IM_COL32(155, 34, 32, 255), false, lineWidth);

        angle += speed * deltaTime;

        if (angle >= 2.0f * IM_PI) {
            reverse = true;
        }
    }
    else {
        ImGui::GetWindowDrawList()->PathArcTo(center, radius, IM_PI * 1.5f - angle, IM_PI * 1.5f, 32);
        ImGui::GetWindowDrawList()->PathStroke(IM_COL32(155, 34, 32, 255), false, lineWidth);

        angle -= speed * deltaTime;

        if (angle <= 0.0f) {
            reverse = false;
            angle = 0.0f; 
        }
    }
}




// some random Loading screen i saw on a spoofer UI
// just a circle looping and a % number in the middle
void RenderLoadingCircle(float radius, float shadowOffset) {

    float loadingProgress = 0.0f;
    float loadingSpeed = 0.5f;
    ImDrawList* drawList = ImGui::GetWindowDrawList();

    ImVec2 shadowPosition(400 + shadowOffset, 300 + shadowOffset);
    drawList->AddCircleFilled(shadowPosition, radius + 5.0f, IM_COL32(0, 0, 0, 100)); // Shadow

    ImVec2 center(400, 300);
    float startAngle = -IM_PI / 2;
    float endAngle = startAngle + 2.0f * IM_PI * loadingProgress;

    drawList->PathArcTo(center, radius, startAngle, endAngle, 100);
    drawList->PathStroke(IM_COL32(255, 255, 255, 255), false, 3.0f);

    loadingProgress += ImGui::GetIO().DeltaTime * loadingSpeed;
    if (loadingProgress > 1.0f) loadingProgress = 0.0f;

    int percent = static_cast<int>(loadingProgress * 100);
    std::string text = std::to_string(percent) + "%"; // remove percentage sign if u dont want it

    ImGui::PushFont(fonts::roboto1); // use your own font for this

    ImVec2 textSize = ImGui::CalcTextSize(text.c_str());

    ImVec2 textPosition(center.x - textSize.x / 2, center.y - textSize.y / 2);

    drawList->AddText(textPosition, IM_COL32(255, 255, 255, 255), text.c_str());

    ImGui::PopFont();
}
// reported.lol spoofers loading animation remake. 
// all credit to saucemachine.
void RenderLineLoadingAnimation(float deltaTime) {
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    static float lineProgress = 0.0f;

    const ImVec2 rectSize(200.0f, 10.0f);
    const float shadowOffset = 5.0f;      
    const float lineHeight = 10.0f;      
    const float lineWidth = 25.0f;      
    const float lineSpeed = 100.0f;      

    ImVec2 rectPosition(ImGui::GetWindowSize().x / 2 - rectSize.x / 2,
        ImGui::GetWindowSize().y / 2 - rectSize.y / 2);

    drawList->AddRectFilled(ImVec2(rectPosition.x + shadowOffset, rectPosition.y + shadowOffset),
        ImVec2(rectPosition.x + rectSize.x + shadowOffset, rectPosition.y + rectSize.y + shadowOffset),
        IM_COL32(0, 0, 0, 80), 10.0f);             

    drawList->AddRectFilled(rectPosition,
        ImVec2(rectPosition.x + rectSize.x, rectPosition.y + rectSize.y),
        IM_COL32(169, 169, 169, 100), 10.0f);                      


    lineProgress += deltaTime * lineSpeed;
    if (lineProgress > rectSize.x) {
        lineProgress = -lineWidth;
    }

    float lineXStart = rectPosition.x + lineProgress; 
    float lineXEnd = lineXStart + lineWidth;         

    float visibleLineXStart = max(lineXStart, rectPosition.x); 
    float visibleLineXEnd = min(lineXEnd, rectPosition.x + rectSize.x);

    if (lineXStart > rectPosition.x + rectSize.x) {
        lineProgress = -lineWidth; 
    }

    if (visibleLineXEnd > visibleLineXStart) {
        drawList->AddRectFilled(ImVec2(visibleLineXStart, rectPosition.y),
            ImVec2(visibleLineXEnd, rectPosition.y + lineHeight),
            IM_COL32(255, 255, 255, 255), 10.0f);                      
    }
}

// dm me more loader loading animations to recreate
