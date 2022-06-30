-- This file will be compiled if path wasn't specified
-- You can change this file as you want

function world2d.Init()
    world2d.Window.SetTitle("world2d Application")

    ImGui = world2d.ImGui
    ImGui.Initialize()

    debug_dt = 0
    bg_color = ImGui.FloatArray4.new(0.3, 0.5, 0.4, 1)

    local wx, wy = world2d.Window.GetSize()
    window_width = ImGui.Int.new(wx)
    window_height = ImGui.Int.new(wy)
    dw, dh = world2d.Window.GetDisplaySize()

    show_demo_window = ImGui.Bool.new(false)
    show_about_window = ImGui.Bool.new(false)
    show_metrics_window = ImGui.Bool.new(false)
    show_style_selector = ImGui.Bool.new(false)
    show_font_selector = ImGui.Bool.new(false)
    show_user_guide = ImGui.Bool.new(false)
end

function world2d.Update(dt)
    debug_dt = dt
end

function world2d.Render()
    world2d.Graphics.SetDrawColor(bg_color[1] * 255, bg_color[2] * 255, bg_color[3] * 255, bg_color[4] * 255)
    world2d.Graphics.Clear()

    ImGui.Begin("Welcome to world2d!")

    ImGui.Text("world2d Version: "..world2d.Version)
    ImGui.Text("ImGui Version: "..ImGui.Version)
    ImGui.Text("Lua Version: ".._VERSION)
    ImGui.Text("Delta time: "..debug_dt)

    ImGui.Separator()

    ImGui.ColorEdit4("Background Color", bg_color)

    ImGui.Separator()

    ImGui.Text(string.format("Display size: (%i, %i)", dw, dh))

    ImGui.SliderInt("Window Width", window_width, 0, dw)
    ImGui.SliderInt("Window Height", window_height, 0, dh)

    if ImGui.Button("Set Window Size") then
        world2d.Window.SetSize(window_width.value, window_height.value)
    end

    ImGui.Separator()

    ImGui.Checkbox("Show Demo Window", show_demo_window)

    if show_demo_window.value == true then
        ImGui.ShowDemoWindow(show_demo_window)
    end

    ImGui.Checkbox("Show About Window", show_about_window)

    if show_about_window.value == true then
        ImGui.ShowAboutWindow(show_about_window)
    end

    ImGui.Checkbox("Show Metrics Window", show_metrics_window)

    if show_metrics_window.value == true then
        ImGui.ShowMetricsWindow(show_metrics_window)
    end

    ImGui.Checkbox("Show Style Selector", show_style_selector)

    if show_style_selector.value == true then
        ImGui.ShowStyleSelector("Style Selector")
    end

    ImGui.Checkbox("Show Font Selector", show_font_selector)

    if show_font_selector.value == true then
        ImGui.ShowFontSelector("Font Selector")
    end

    ImGui.Checkbox("Show User Guide", show_user_guide)

    if show_user_guide.value == true then
        ImGui.ShowUserGuide(show_user_guide)
    end

    ImGui.End()
end