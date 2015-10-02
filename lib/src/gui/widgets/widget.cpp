#include "gui/widgets/widget.h"

#include "ext/imgui/imgui.h"
#include "ext/imgui/imgui_impl_glfw.h"

namespace lp
{

void Widget::draw(void)
{
    if (!predraw())
    {
        return;
    }

    drawContent();

    postdraw();
}

bool Widget::predraw(void)
{
    ImGui::SetNextWindowSize(ImVec2(m_width, m_height), ImGuiSetCond_FirstUseEver);
    if (!ImGui::Begin(m_title.c_str(), &m_enabled))
    {
        ImGui::End();
        return false;
    }

    return true;
}

void Widget::postdraw(void)
{
    ImGui::End();
}

} // namespace lp
